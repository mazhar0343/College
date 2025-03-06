#CSCI 355
#SUMMER 2024
#MUHAMMAD AZHAR
#ASSIGNMENT 9 - CRYPTOGRAPHY

import math
import numpy as np
import rsa


def read_file(filename):
    with open(filename, 'r', encoding="UTF-8") as file:
        return file.read().strip()


expected_freqs = [8.2, 1.5, 2.8, 4.3, 12.581, 2.2, 2.0, 6.1, 7.0, 0.15, 0.77, 4.0, 2.4,
 6.7, 7.5, 1.9, 0.095, 6.0, 6.3, 9.1, 2.8, 0.98, 2.4, 0.15, 2.0, 0.074]

def distance(x, y):
    return math.sqrt(sum([(x[i] - y[i]) ** 2 for i in range(len(x))]))

def count_letters(text):
    acutal_freqs = [0] * 26
    for c in text:
        index = ord(c) - ord('A')
        acutal_freqs[index] += 1
    size = len(text)
    return [100 * freq / size for freq in acutal_freqs]

def shift_char(c, shift):
    shifted_char = chr(ord("A") + ((ord(c) - ord("A") + shift) % 26))
    return shifted_char

def shift_text(text, shift):
    return "".join([shift_char(c, shift) for c in text])

def find_best_shift(text):
    best_shift = 0
    best_distance = 999999
    for shift in range(26):
        shifted_text = shift_text(text, shift)
        acutal_freqs = count_letters(shifted_text)
        d = distance(acutal_freqs, expected_freqs)
        if d < best_distance:
            best_distance = d
            best_shift = shift
    return best_shift

def write_file(file_name, text):
    with open(file_name, 'w', encoding="UTF-8") as file:
        file.write(text)

def do_9a():
    encrypted_text = read_file("encrypted.txt")
    actual_freqs = count_letters(encrypted_text)
    print(actual_freqs)
    print(expected_freqs)
    best_shift = find_best_shift(encrypted_text)
    print("The best shift is", best_shift)
    decrypted_text = shift_text(encrypted_text, best_shift)
    print("The decrypted text is ")
    print(decrypted_text)
    write_file("decrypted.txt", decrypted_text)

def simplify_text(text):
    return "".join([c.upper() for c in text if c.isalnum() or c in [' ', '.']])

def random_permutation(size):
    return np.random.permutation(size)


def do_9b():
    permutation = random_permutation(38)
    print(permutation)
    message = ".".join([str(i) for i in permutation])
    print(message)
    (public_key, private_key) = rsa.newkeys(1024)
    ciphertext = rsa.encrypt(message.encode("utf8"), public_key)
    print(ciphertext)
    message2 = rsa.decrypt(ciphertext, private_key)
    print(message2.decode("utf8"))

def main():
    do_9a()
    do_9b()


if __name__ == '__main__':
    main()