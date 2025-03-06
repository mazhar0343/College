#SUMMER 2024
#CS355
#MUHAMMAD AZHAR
#ASSIGNMENT 6 - ROUTING TABLES

import os
from subprocess import check_output

import OutputUtil as ou


def exec_cmd(cmd):
    results = check_output(cmd, shell=True)
    #results = subprocess.call(cmd, shell=True)
    return results


# [2] Define a function get_routing_table by using the function from the previous step to run "route print" and then parsing the output into a table (2-D list).
def get_routing_table(routing_data):
    s = routing_data.decode()
    s = s[s.find("Destination"): s.find("Internet6") - 1].strip()
    #print(s)
    lines = s.split('\n')
    print(lines)
    data = [[get(x, 0, 17), get(x, 18, 37), get(x, 38, 44), get(x, 45, 62), get(x, 63, 70)] for x in lines]
    for row in data:
        print(row)
    return data


def get(s, i, j):
    return s[i:j + 1].strip()


def get_ip_address():
    ip = input("Enter IP Address:")
    return ip


def binary_address(ip_address):
    ip_address = strip_mask(ip_address)
    octets = ip_address.split('.')
    binary = ""
    for octet in octets:
        binary += bin(int(octet))[2:].zfill(8)
    return binary


def validate_ip_address(ip_address):
    octets = ip_address.split('.')
    if len(octets) != 4:
        return False
    for octet in octets:
        if not octet.isdigit():
            return False
        if int(octet) < 0 or int(octet) > 255:
            return False
    return True


def strip_mask(ip_address):
    return ip_address.split("/")[0] if "/" in ip_address else ip_address


def get_ip_address_class(ip_address):
    ip_class = "?"
    if ip_address[0:1] == "0":
        ip_class = "A"
    elif ip_address[0:2] == "10":
        ip_class = "B"
    elif ip_address[0:3] == "110":
        ip_class = "C"
    elif ip_address[0:4] == "1110":
        ip_class = "D"
    elif ip_address[0:5] == "1111":
        ip_class = "E"
    return ip_class


def matching_prefix_bits(bin1, bin2):
    bits = 0
    n1 = len(bin1)
    n2 = len(bin2)
    n = min(n1, n2)
    for i in range(n):
        if (bin1[i] != bin2[i]):
            break
        else:
            bits += 1
    return bits


def get_next_hop(ip_address, table):
    ip_addr_bin = binary_address(ip_address)
    all_ones = '1' * 32
    best_row = -1
    best_bits = -1
    for row in table[2:]:
        mask_db = row[0]
        mask_bin = binary_address(mask_db)
        mask_bits = matching_prefix_bits(mask_bin, all_ones)
        net_dest_db = row[0]
        net_dest_bin = binary_address(net_dest_db)
        bits = matching_prefix_bits(net_dest_bin[0:mask_bits], ip_addr_bin)
        if bits > best_bits:
            best_bits = bits
            best_row = row
    return best_row[2], best_bits

def process_addresses(ip_addresses, table):
    for ip_addr in ip_addresses:
        if validate_ip_address(ip_addr):
            binary = binary_address(ip_addr)
            next_hop, best_bits = get_next_hop(ip_addr, table)
            print("ip address: ", ip_addr, "bin", binary, "next hop", next_hop, "best_bits", best_bits)
        else:
            print("Invalid IP Address:", ip_addr)

def main():
    results = exec_cmd("netstat -nr")
    print(results)
    table = get_routing_table(results)

    headers = table[0]
    data = table[1:]
    alignment = ["l", "l", "l", "l", "r"]
    types = ["S", "S", "S", "S", "N"]
    title = "Muhammad's Forwarding Table"
    ou.write_html_file("Assignment06.html",title, headers, types, alignment, data, True)

    #ip_addr = get_ip_address()
    ip_addresses = ["abc.def.ghi.jkl","111-111-111-111",
                    "613.613.613.613", "123.123.123",
                    "225.225.225.225", "241.242.243.244",
                    "127.0.0.1", "52.3.73.91", "216.239.63.255"]
    process_addresses(ip_addresses, table)


if __name__ == '__main__':
    main()
