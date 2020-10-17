#!/usr/bin/python3
import os

class logHtml:
    def __init__(self, filePath):
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
        message = "<body><pre>" + text + "</pre></body>"
        self.htmlFile.write(message)
    
    def writeImage(self, pathToImage):
        message = "<img src=" + pathToImage + '>'
        self.htmlFile.write(message)
    
    def writeAll (self, header, text, image):
        self.writeHeader(header)
        self.writeBody(text)
        self.writeImage(image)        

    def closeHtml(self):
        self.htmlFile.write("</html>")
        self.htmlFile.close()

########Example how to use

#basePath = "/home/pi/Scripts/"
#basePath = os.getcwd()
#web = logHtml(os.path.join(basePath, "unrecognized.html"))
#web.writeHeader("2020_20_20")
#web.writeBody("Issues that can be here")
#web.writeImage(os.path.join(basePath, "recognize.png"))

