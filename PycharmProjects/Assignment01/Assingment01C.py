#CS355
#Summer 2024
#Muhammad Azhar
#Assignment 1 - Socket Program

import socket
import sys

#[1] Define a function get_host_info() to determine your computer’s IP address.
def get_host_info():
    hostname = socket.gethostname()
    ip_addr = socket.gethostbyname("localhost")
    print("Your Computer Name is:" + hostname)
    print("Your Computer IP Address is:" + ip_addr)
    return ip_addr

# [2] Define a function binary_address() to convert your IP Address from “dotted decimal notation” to a 32-bit binary string.
def binary_address(ip_address):
    octets = ip_address.split('.')
    binary = ""
    for octets in octets:
        binary += bin(int(octets))[2:].zfill(8)
    #print(ip_address, binary, len(binary))
    return binary

#[3] Write a function to determine if the address is Class A, B, C, D or E by examining the first few bits of the 32-bit string.
def get_ip_address_class(ip_address):
    ip_class = "?"
    if ip_address[0:1] == "0" : ip_class = "A"
    elif ip_address[0:2] == "10" : ip_class = "B"
    elif ip_address[0:3] == "110" : ip_class = "C"
    elif ip_address[0:4] == "1110" : ip_class = "D"
    elif ip_address[0:5] == "1111" : ip_class = "E"
    return ip_class

# [4] Define a function port_type(port) to determine the type of port number.
def port_type(port):
    if 0 <= port <= 1023:
        return "Well Know"
    elif 1024 <= port <= 49151:
        return "Registerd"
    elif 49152 <= port <= 65535:
        return "Dynamic/Private"

#[5] Write a function to connect to the Google server
def connect_to_server(host_name, port):
    try:
        s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        print("Socket successfully created")
    except socket.error as err:
        print("socket creation failed with error %s" % (err))
    try:
        if host_name == "localhost":
            host_ip = "127.0.0.1"
        else:
            host_ip = socket.gethostbyname(host_name)
        host_ip = socket.gethostbyname(host_name)
    except socket.gaierror:
        print("there was an error resolving the host")
        sys.exit()
    s.connect((host_ip, port))
    print("the socket has successfully connected to", host_name, "@", host_ip, "at port", port)
    print("Ip address", host_ip, "in binary is", binary_address(host_ip))
    print("IP address is", host_ip, "is class", get_ip_address_class(binary_address(host_ip)))
    print("Port:", port, "is" ,port_type(port))
    message = s.recv(2048).decode()
    print("Recive from server", message)
    s.close()

def main():
    ip_address = get_host_info()
    binary_address(ip_address)
    #connect_to_server("www.google.com", 80)
    connect_to_server("www.djxmmx.net", 17)
    connect_to_server("time-a-wwv.nist.gov", 13)
    connect_to_server("localhost", 12345)
if __name__ == "__main__":
    main()

