
# My-FTP

The goal of the project is to create a FTP server.

I use the protocol given by Epitech, which is a RFC959 compliant protocol.

The network communication will be achieved through the use of TCP sockets.

For this project, It's forbidden to multi-thread our process.

Authentication can be done through the 'Anonymous' account on the server without requiring a password.



## Authors

- [@Toavina](https://github.com/Andriamanampisoa/)


## Installation

You can clone this repository using ```git clone```.

```bash
  git clone git@github.com:Andriamanampisoa/My-FTP.git
  cd My-FTP
```
    
To run the project, use the following commands :

```bash
  make
  ./myftp --help
```

You can use netcat to connect to the server, for example.
## Tech Stack

**Server:** C (standard C library)


## Usage/Examples

Server initialization :
```bash
./myftp 4045 test-repo/
```

Client connection :
```bash
netcat 0.0.0.0 4045

USER Anonymous
PASS
```


## Documentation

Availables features :

```bash
USER : For user authentication \
PASS : For authentication (password) \

CWD : Change working directory \
CDUP : Change working directory to parent directory \

QUIT : Disconnection

DELE : Delete file on the server

PWD : Print working directory

PASV : Enable "passive" mode for data transfer

NOOP : Do nothing (test command)

RETR : Download file from server to client (pasv mode only)
STOR : Upload file from client to server (pasv mode only)
LIST : List files in the current working directory (pasv mode only)
```