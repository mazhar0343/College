#CS355
#Summer 2024


#[1] Define a function get_host_info() to determine your computer’s IP address.
#See https://www.geeksforgeeks.org/python-program-find-ip-address/

import socket

def get_host_info():
    hostname = socket.gethostname()
    ip_addr = socket.gethostbyname(hostname)
    print("Your Computer Name is:" + hostname)
    print("Your Computer IP Address is:" + ip_addr)


def main():
    get_host_info()

if __name__ == '__main__':
    main()