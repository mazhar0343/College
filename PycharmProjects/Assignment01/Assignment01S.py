#CS355
#Summer 2024
#Muhammad Azhar
#Assignment 1 - Socket Program

import socket

def run_server(port):
    s = socket.socket()
    print("Socket successfully created")
    s.bind(('', port))
    print("socket binded to %s" % (port))
    s.listen(5)
    print("socket is listening")
    while True:
        c, addr = s.accept()
        print('Got connection from', addr)
        c.send('Thank you for connecting'.encode())
        c.close()
def main():
    run_server(12345)

if __name__ == '__main__':
    main()