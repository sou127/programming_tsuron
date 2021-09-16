//client as sender
#include<stdio.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>   
#include<sys/ioctl.h>
#include<stdlib.h>
#include<unistd.h> 
#include<errno.h>

int send_image(int socket, char* local_file, char* remote_file){
  FILE *picture;
  int size, read_size, stat;
  char send_buffer[10240], read_buffer[256];

  picture = fopen(local_file, "r");
  printf("Getting Picture Size\n");   

  if(picture == NULL) {
    printf("Error Opening Image File"); 
  } 

  fseek(picture, 0, SEEK_END);
  size = ftell(picture);
  fseek(picture, 0, SEEK_SET);
  printf("Total Picture size: %i\n",size);

  //Send remote file name
  printf("Sending Remote File Name\n");
  write(socket, (void *)remote_file, 256);

  //Send Picture Size
  printf("Sending Picture Size\n");
  write(socket, (void *)&size, sizeof(int));

  //Send Picture as Byte Array
  printf("Sending Picture as Byte Array\n");

  do { //Read while we get errors that are due to signals.
    stat=read(socket, &read_buffer , 255);
  } while (stat < 0);

  printf("Received data in socket\n");
  printf("Socket data: %s\n", read_buffer);

  while(!feof(picture)) {
    //Read from the file into our send buffer
    read_size = fread(send_buffer, 1, sizeof(send_buffer)-1, picture);

    //Send data through our socket 
    do{
      stat = write(socket, send_buffer, read_size);  
    }while (stat < 0);

    //Zero out our send buffer

    bzero(send_buffer, sizeof(send_buffer));
  }
}

int main(int argc , char *argv[]) {
    if(argc != 5){
        printf("sample usage: \n\t %s 127.0.0.1 8080 1_local.jpg 1_remote.jpg\n",argv[0]);
        exit(0);
    }
    else{
        char* address = argv[1];
        int PORT = atoi(argv[2]);
        char* local_file = argv[3];
        char* remote_file = argv[4];

        int socket_desc;
        struct sockaddr_in server;
        char *parray;

        //Create socket
        socket_desc = socket(AF_INET , SOCK_STREAM , 0);

        if (socket_desc == -1) {
            printf("Could not create socket");
        }

        memset(&server,0,sizeof(server));
        server.sin_addr.s_addr = inet_addr( address );
        server.sin_family = AF_INET;
        server.sin_port = htons( PORT );

        //Connect to remote server
        if (connect(socket_desc , (struct sockaddr *)&server , sizeof(server)) < 0) {
            printf("%s",strerror(errno));
            close(socket_desc);
            puts("Connect Error");
            return 1;
        }
        puts("Connected\n");
        
        send_image(socket_desc, local_file, remote_file);
        close(socket_desc);

        return 0;
    }
  }
