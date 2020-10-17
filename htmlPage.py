#!/usr/bin/python3
import os

class logHtml:
    def __init__(self, filePath, textToHtml):
        if os.path.isfile(filePath):
            self.htmlFile = open(filePath, 'a')
        else: 
            self.htmlFile = open(filePath, 'w')

    def writeHeader(self, text): 
        message = """<html>
        <head></head> <h1>""" + text
        message += """</h1>"""
        self.htmlFile.write(message)
    
    def writeBody(self, text):
        message = "<body><p>" + text + "</p></body>"
        self.htmlFile.write(message)
    
    def writeImage(self, pathToImage):
        message = "<img src=" + pathToImage + '>'
        self.htmlFile.write(message)

    def closeHtml(self):
        self.htmlFile.write("</html>")
        self.htmlFile.close()

#basePath = "/home/pi/Scripts/"
basePath = os.getcwd()
web = logHtml(os.path.join(basePath, "unrecognized.html"), "hello")
web.writeHeader("2020_20_20")
web.writeBody("Issues that can be here")
web.writeImage(os.path.join(basePath, "recognize.png"))
print (os.path.join(basePath, "recognize.png"))
web.closeHtml()
