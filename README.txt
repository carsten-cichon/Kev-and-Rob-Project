# CSC 590 Project Robbie Cichon and Keven McDowell 
## Spring 2019
Using Windows API and Winsock to build a keylogger trojan that utilizes a webserver and database.

## Who did what?

### Robbie:
Robbie wrote the main function for the keylogger and the keyboard operating system hook callback originally, but it had to be changed up to
add in the socket functionality that sent data to the server.  To make up for the fact that he did not end up having much time to directly program
much of the project, he helped write the entire paper about the program and created the presentation, and he helped provide some of the ideas for extra features, 
like adding the ability to add the keylogger to the registry.

### Keven:
Keven did most of the coding for the project.  He made the keylogger handle shift and caps lock for letters properly, 
he made the keylogger handle storing and sending keystrokes when enter or space is pressed, he handled the keylogger 
getting the host name of the computer, he handled making sure that only numbers and letters were recorded by the 
keylogger, and he handled the functionality for building http requests from scratch and sending them through a socket 
to the web server along with all other extra features.  He also wrote the entire webserver and web pages, and he set 
up the database for the server.

## How to run it / How was it compiled?

This is mean't only for Windows machines since it uses the Windows API.

NOTE: I deleted the executables since I didn't want any accidental virus installations in case you decided to test this.  
The keylogger file on the webserver where the keylogger would be downloaded from has a placeholder file.  If you want to 
test the project re-compile the code using the instructions below and put the executable there.  If you do this though, make sure you delete the 
registry key if you run it as an administrator.  It is probably safest to run this inside a Windows 7 or Windows 10 VM. 

The trojan is made specifically to work only in Windows. It was compiled using the following:

-- g++ -static -static-libgcc -static-libstdc++ keylogger.cpp -o NotAVirus -lws2_32

This statically includes Dlls used by the program so people that don't have g++ installed on their computers can run the trojan.  It greatly increases the size of
the keylogger, but it's necessary to make it portable between Windows machines.

We demonstrated the code with the console visible to give more insight into the functionality, but you can compile it to 
hide the console at runtime using the following:

-- g++ -static -static-libgcc -static-libstdc++ keylogger.cpp -o NotAVirus -lws2_32 -mwindows

To run the webserver, you must have node.js installed on your machine. Then you can just navigate into the webserver directory and run "npm install".  All
required dependencies will be installed, and once the installation finishes, you can do "npm start" and the server will start.  When you run npm install, node.js
uses the node package manager to download all dependencies listed in the package.json file, which allows us to have portable applications
that allow us to transport everything but the modules folder since we can download it from anywhere.

To view the dummy page, go to http://localhost:8080/

To see the keylogger data go to http://localhost:8080/hiddenkeylogger

This project also requires you to have MongoDB installed on your machine for database operations. 
You can download MongoDB here:  https://www.mongodb.com/download-center/community

With the webserver running, and MongoDB installed and running, you should be able to run, or re-compile and run the keylogger 
and have it successfully send data to the server and store it in the database, which can then be viewed at http://localhost:8080/hiddenkeylogger.
