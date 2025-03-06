#CSCI 355
#Summer 2024
#Muhammad Azhar
#Assignment 8 - Error Detection and Correction

from random import random, randint

def random_bits(n, p=.05):
    return "".join(["1" if random() < p else "0" for _ in range(n)])

def ed_parity_1d(bits, even=True):
    n1 = bits.count("1")
    return 1 if (n1 % 2 == 1) == even else 0

def ed_parity_2d(bits, nr, nc, even=True):
    if nr * nc != len(bits):
        return "?????"
    arr = [bits[j * nc:(j+1) * nc] for j in range(nr)]
    arr2 = ["".join([arr[i][j] for i in range(nr)]) for j in range(nc)]
    print(arr2)
    print(arr)
    row_parity = [ed_parity_1d(a, even) for a in arr]
    col_parity = [ed_parity_1d(a, even) for a in arr2]
    return row_parity, col_parity

def ed_checksum(bits):
    mid = len(bits) // 2
    bits1 = bits[:mid]
    bits2 = bits[mid:]
    bits3 = ""
    s = 0
    c = 0
    for i in range(mid-1, -1, -1):
        bit1 = int(bits1[i])
        bit2 = int(bits2[i])
        s = (bit1 + bit2 + c) % 2
        c = 1 if bit1 + bit2 + c >= 2 else 0
        bits3 = str(s) + bits3
    ones_complement = "".join(["1" if bits3[i] == "0" else "0" for i in range(mid)])
    return ones_complement

def compare_parity(parity1, parity2):
    for i in range(len(parity1)):
        if parity1[i] != parity2[i]:
            return i
    return -1


def xor(a, b):
    # initialize result
    result = []

    # Traverse all bits, if bits are
    # same, then XOR is 0, else 1
    for i in range(1, len(b)):
        if a[i] == b[i]:
            result.append('0')
        else:
            result.append('1')

    return ''.join(result)


# Performs Modulo-2 division
def mod2div(dividend, divisor):
    # Number of bits to be XORed at a time.
    pick = len(divisor)

    # Slicing the dividend to appropriate
    # length for particular step
    tmp = dividend[0: pick]

    while pick < len(dividend):

        if tmp[0] == '1':

            # replace the dividend by the result
            # of XOR and pull 1 bit down
            tmp = xor(divisor, tmp) + dividend[pick]

        else:  # If leftmost bit is '0'
            # If the leftmost bit of the dividend (or the
            # part used in each step) is 0, the step cannot
            # use the regular divisor; we need to use an
            # all-0s divisor.
            tmp = xor('0' * pick, tmp) + dividend[pick]

            # increment pick to move further
        pick += 1

    # For the last n bits, we have to carry it out
    # normally as increased value of pick will cause
    # Index Out of Bounds.
    if tmp[0] == '1':
        tmp = xor(divisor, tmp)
    else:
        tmp = xor('0' * pick, tmp)

    checkword = tmp
    return checkword


# Function used at the sender side to encode
# data by appending remainder of modular division
# at the end of data.


def ed_crc(data, key):
    l_key = len(key)

    # Appends n-1 zeroes at end of data
    appended_data = data + '0' * (l_key - 1)
    remainder = mod2div(appended_data, key)

    # Append remainder in the original data
    codeword = data + remainder
    print("Remainder : ", remainder)
    print("Encoded Data (Data + Remainder) : ",codeword)

    return remainder

def main():
    bits = random_bits(100, .9)
    print(bits)
    print(ed_parity_1d("100", True))
    print(ed_parity_1d("100", False))
    print(ed_parity_1d("101", False))

    row_partiy1, col_parity1 = ed_parity_2d(bits, 4, 25, True)

    i = randint(0, len(bits)-1)
    bits1 = bits[0:i]+("1" if bits[i] == "0" else "0")+bits[i+1:]
    row_partiy2, col_parity2 = ed_parity_2d(bits1, 4, 25, True)
    row = compare_parity(row_partiy1, row_partiy2)
    col = compare_parity(col_parity1, col_parity2)
    print("\nBit Error Introduce at position", i)
    print("Row Error Parity at row:", row, "\nCol Error Parity at col:", col)
    error_pos = 25 * row * col
    print("Error Dectected at Pos:", error_pos)
    message = "1110011001100110" + "1101010101010101"
    print("\nmessage", message)
    print("ed_checksum", ed_checksum(message))

    data = "100100"
    key = "1101"
    crc = ed_crc(data, key)
    print("crc : data", data, "key", key, "crc", crc)

if __name__ == '__main__':
    main()