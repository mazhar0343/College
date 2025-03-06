#SUMMER 2024
#CSCI 355
#MUHAMMAD AZHAR
#ASSIGNMENT 4 - DATA SCRAPING

import requests
import html5lib
from bs4 import BeautifulSoup
import OutputUtil as OU

def show_webpage_html(url):
    response = requests.get(url)
    print(response.content)

def parse_html(url):
    response = requests.get(url)
    soup = BeautifulSoup(response.content, 'html5lib')
    print(soup.prettify())

def next_text(itr):
    return next(itr).text

def next_int(itr):
    return int(next_text(itr).replace(",",""))

def get_covid_data(dict_country_population):
    url = 'https://www.worldometers.info/coronavirus/countries-where-coronavirus-has-spread/'
    page = requests.get(url)
    soup = BeautifulSoup(page.text, 'html.parser')
    data = []
    soup.find_all('td') #will scrape every table-data element in the url's table
    itr = iter(soup.find_all('td'))
    # This loop will keep repeating as long as there is data available in the iterator
    while True:
        try:
            country = next_text(itr)
            if country.startswith("Japan"):
                country = "Japan"
            cases = next_int(itr)
            deaths = next_int(itr)
            continent = next_text(itr)
            if country in dict_country_population:
                population = dict_country_population[country]
                cases_per_capita = round(cases/population,2)
                death_rate = round(deaths/cases,2)
                data.append((country, continent, population, cases, deaths, cases_per_capita, death_rate)),
            else:
                print("Country not found", country)

        # StopIteration error is raised when there are no more elements left for iteration
        except StopIteration:
            break
    return data
    # Sort the data by the number of confirmed cases
    # data.sort(key=lambda row: row[1], reverse=True)

def get_country_population():
    dict_country_population = {}
    url = "https://www.worldometers.info/world-population/population-by-country"
    page = requests.get(url)
    soup = BeautifulSoup(page.text, 'html.parser')
    data = []
    soup.find_all('td') #will scrape every table-data element in the url's table
    itr = iter(soup.find_all('td'))
    while True:
        try:
            junk = next_text(itr)
            country = next_text(itr)
            population = next_int(itr)
            junk = next_text(itr)
            junk = next_text(itr)
            junk = next_text(itr)
            junk = next_text(itr)
            junk = next_text(itr)
            junk = next_text(itr)
            junk = next_text(itr)
            junk = next_text(itr)
            junk = next_text(itr)
            dict_country_population[country] = population
        # StopIteration error is raised when there are no more elements left for iteration
        except StopIteration:
            break

    return dict_country_population
def main():
    dict_country_population = get_country_population()
    data = get_covid_data(dict_country_population)
    headers = ["Country", "Continent", "Population", "Cases", "Deaths", "Cases per Capita", "Death Rate"]
    types = ["S", "S", "N", "N", "N", "N", "N"]
    alignments = ["l", "l", "r", "r", "r", "r", "r"]
    title = "Scraped Covid-19 Data"
    OU.write_html_file("Assignment4.html", title, headers, types, alignments, data, True)
    OU.write_xml_file("Assignment4.xml", title, headers, data, True)
    OU.write_tt_file("Assignment4.txt", title, headers, data, alignments)
    OU.write_csv_file("Assignment04.csv", headers, data)
    # x_label = "Population"
    # y_label = "Cases"
    # x_data = [row[2] for row in data]
    # y_data = [row[3] for row in data]
    # x_ticks = [i for i in range(len(x_data))]
    # y_ticks = [i for i in range(len(y_data))]
    # OU.write_bar_graph("Assignment4.png", title, x_label, x_label, x_ticks, y_label, y_data, y_ticks)

if __name__ == '__main__':
    main()