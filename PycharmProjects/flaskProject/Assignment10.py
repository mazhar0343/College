#CSCI 355
#SUMMER 2024
#MUHAMMAD AZHAR
#ASSIGNMENT 10 - FLASK SERVER

from flask import Flask

app = Flask(__name__)


@app.route('/')
def hello_world():  # put application's code here
    return 'Hello World!'

@app.route('/hello/<name>')
def hello_name(name):  # put application's code here
    return 'Hello %s!' % name


if __name__ == '__main__':
    app.run()
