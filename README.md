# Flask-painter
#### Video Demo: <URL HERE>
#### Description:

##### My Project contains 2 subprograms

I  : The first is the C command line tool. which I started writing when I finished my C lectures.
     This command-line tool takes a BMP file (with 24-bit colors) and represents it in ASCII characters.
     This program requires the BMP file to be with a BM Signature.
     The program is capable of printing/outputting the image in 2 ways depending on the user's preference.
     The first method of outputting is by printing the image in the terminal. This method is preferable if the user
     doesn't need the transformed image to be stored in its computer and just wants the picture to be printed for a one time use.
     The second method of outputting is going to store a output txt file with the ASCII format. This is method, unlike the first method,
     gives you access to using the ASCII formated BMP permentaly for multiude of use for the user's liking.
     
     The first method Usage
     ./painter -i ( input bmp file ) 
     The second method Usage
     ./painter -i ( input bmp file ) -o ( output txt file )

II : The second one is flask code with html css .
     This Web page is used as an UI ( User Interface )for my c command line tool.
     This page takes an input of a BMP file for the c program.
	 Later after processing the BMP file it gives the prompt to download the formated txt file.
     With this method of using the program it gives access to multiple users to use it without downloading the tool and having to write any commands in the terminal.
     This web page is a much more convenient way of using the tool as it is very straight forward and user friendly.
