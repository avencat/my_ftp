# my_ftp
Repository for the my_ftp project that I realized on my 2nd year at Epitech
During this project, we had to do a ftp server that handle several commands that are listed above.
I've also done a ftp client to communicate with the server.

# Installation
make

# Usage
## Server
./server [port] [path_to_the_anonymous_root_directory]

## Client
./client [ip_address_of_the_server] [port]

# Commands available
            USER <SP> <username> <CRLF>   : Specify user for authentication
            PASS <SP> <password> <CRLF>   : Specify password for authentication

            CWD  <SP> <pathname> <CRLF>   : Change working directory
            CDUP <CRLF>                   : Change working directory to parent directory

            QUIT <CRLF>                   : Disconnection

            DELE <SP> <pathname> <CRLF>   : Delete file on the server

            PWD  <CRLF>                   : Print working directory

            PASV <CRLF>                   : Enable "passive" mode for data transfer

            PORT <SP> <host-port> <CRLF>  : Enable "active" mode for data transfer


            HELP [<SP> <string>] <CRLF>   : List available commands

            NOOP <CRLF>                   : Do nothing

            (the following are commands using data transfer )

            RETR <SP> <pathname> <CRLF>   : Download file from server to client
            STOR <SP> <pathname> <CRLF>   : Upload file from client to server
            LIST [<SP> <pathname>] <CRLF> : List files in the current working directory 
