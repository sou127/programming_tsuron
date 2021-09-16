Program Description: A simple Client-Server Socket Program to send Image file from Client (Sender) to Server (Receiver). (GitHub Link: https://github.com/sou127/programming_tsuron/week13)

Program Usage: Compile sender.c and receiver.c on locations desired (remote or local computer). 

Example:
(Step 1):	gcc receiver.c -o receiver
		gcc sender.c -o sender		// directory independent of receiver

(Step 2):	./receiver 8080		//run server first (important)

(Step 3):	./sender 127.0.0.1 8080 local_file.jpg remote_file.jpg	//run client


Sender Program (sender.c):

Lines 1-9: Required Header Files

Lines 11-59: Function for Sending Image
Breakdown of the function:
	Lines 12-14: Declaring required variables
	Lines 16-21: Getting the local image and handling error
	Lines 23-26: Finding size of image through fseek and ftell
	Lines 28-44: writing remote file name, picture size and picture as an array to the socket
	Lines 46-58: sending the data through the socket and zeroing out the send buffer

Lines 61-110: Main Function
Breakdown of the main function:
	Lines 62-65: Handling user input and showing usage example
	Lines 67-74: Declaring required variables if input is valid
	Lines 76-81: Creating socket and handling errors
	Lines 83-86: Preparing the sockaddr structure
	Lines 89-95: Connecting to remote server
	Line 97: Calling the send image function
	Line 98: Closing the socket after use



Receiver Program (receive.c):

Lines 1-9: Required Header Files

Lines 11-91: Function for Receiving Image
Breakdown of the function:
	Lines 12-15: Declaring variables
	Lines 18-28: Reading the remote filename and size of image and printing it.
	Lines 30-32: Keep writing until there is nothing to left (verifying)
	Lines 34-39: Creating file and error handling
	Lines 41-45: Declaring required variables
	Lines 47-77: Writing image and error handling in while loop
	Lines 81-83: Closing image after writing

Lines 87-141: Main Function
Breakdown of main function:
	Lines 88-92: Handling user input and showing usage example
	Lines 93-96: Declaring required variables if correct input is provided
	Lines 99-102: Socket Creation
	Lines 105-107: Preparing the sockaddr structure
	Lines 110-115: Binding
	Line 118: Listen
	Lines 121-133: Accept and handle errors
	Lines 135-138: Calling the receive function and closing socket
