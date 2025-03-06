#CSCI355
#Summer 2024
#Muhammad Azhar
#Assignment 3 - HTML and CSS

import OutputUtil as ou
def read_file(filename):
    with open(filename) as file:
        lines = file.readlines()
        headers = lines[0].strip().split(",")
        data = [line.strip().split(",") for line in lines[1:]]
    return headers, data
def main():
    headers, data = read_file("USStates.csv")
    for row in data:
        href = "https://en.wikipedia.org/wiki/" + row[0].replace(' ', '_')
        a_attributes = 'href="' + href + '" target="_blank"'
        td_cont = ou.create_element(ou.TAG_A, row[0], a_attributes)
        row[0] = td_cont
    filename = "USStates.html"
    title = "US States"
    types = ["S", "S", "S", "N"]
    alignments = ["l", "l", "l", "r"]
    ou.write_html_file(filename, title, headers, types, alignments, data, True)

if __name__ == "__main__":
    main()