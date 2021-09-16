//server as receiver
#include<stdio.h>
#include<string.h>
#include<sys/socket.h>
#include<unistd.h>
#include<stdlib.h>
#include<arpa/inet.h>   
#include<unistd.h> 
#include<errno.h>

int receive_image(int socket){ // Start function 
    int buffersize = 0, recv_size = 0,size = 0, read_size, write_size, packet_index =1,stat;
    char filename[1024]; char buffer[] = "Got it";
    char imagearray[10241],verify = '1';
    FILE *image;


    read(socket, filename, 256);

    //Find the size of the image
    do{
        stat = read(socket, &size, sizeof(int));
    }while(stat<0);


    printf("Packets received.\n");
    printf("Image size: %i\n",size);

    //Send our verification signal
    do{
        stat = write(socket, &buffer, sizeof(int));
    }while(stat<0);

    image = fopen(filename, "w");

    if( image == NULL) {
        printf("Error has occurred. Image file could not be opened\n");
        return -1; 
    }

    int need_exit = 0;
    struct timeval timeout = {10,0};

    fd_set fds;
    int buffer_fd, buffer_out;

    while(recv_size < size) {
    //while(packet_index < 2){

        FD_ZERO(&fds);
        FD_SET(socket,&fds);

        buffer_fd = select(FD_SETSIZE,&fds,NULL,NULL,&timeout);

        if (buffer_fd < 0)
           printf("error: bad file descriptor set.\n");

        if (buffer_fd == 0)
           printf("error: buffer read timeout expired.\n");

        if (buffer_fd > 0)
        {
            do{
                read_size = read(socket,imagearray, 10241);
            }while(read_size <0);

            //Write the currently read data into our image file
            write_size = fwrite(imagearray,1,read_size, image);

            if(read_size !=write_size) {
                printf("error in read write\n");    
            }


            recv_size += read_size;
            packet_index++;
        }

    }

    fclose(image);
    printf("Image successfully Received! as %s\n", filename);
    return 1;
}


int main(int argc , char *argv[]) {
  if(argc != 2){
    printf("usage: \n\t %s 8080[Port Number]\n",argv[0]);
    exit(0);
  }
  else{
    int PORT = atoi(argv[1]);
    int socket_desc , new_socket , c, read_size,buffer = 0;
    struct sockaddr_in server , client;
    char *readin;

    //Create socket
    socket_desc = socket(AF_INET , SOCK_STREAM , 0);
    if (socket_desc == -1){
      printf("Could not create socket");
    }

    //Prepare the sockaddr_in structure
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons( PORT );

    //Bind
    if( bind(socket_desc,(struct sockaddr *)&server , sizeof(server)) < 0){
     puts("bind failed");
     return 1;
    }

    puts("bind done");

    //Listen
    listen(socket_desc , 3);

    //Accept and incoming connection
    puts("Waiting for incoming connections...");
    c = sizeof(struct sockaddr_in);

    if((new_socket = accept(socket_desc, (struct sockaddr *)&client,(socklen_t*)&c))){
      puts("Connection accepted");
    }

    fflush(stdout);

    if (new_socket<0){
      perror("Accept Failed");
      return 1;
    }

    receive_image(new_socket);
    close(socket_desc);
    fflush(stdout);
    return 0;
  }
}
