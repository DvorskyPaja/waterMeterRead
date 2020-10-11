#!/usr/bin/python3
import pytesseract
import sys, re, os
from openpyxl import load_workbook
from PIL import Image

def init():
    global img =Image.open (os.path.join(os.getcwd() ,"recognize.png"))
    #print (os.path.join(os.getcwd() ,"recognize.png"))
def recognize():
    custom_config = r"-c tessedit_char_whitelist=0123456789 --psm 6 -l digits"
    #custom_config = r'--oem 3 --psm 6 outputbase digits'

    recognized = pytesseract.image_to_string(img, config = custom_config)
    print (recognized)
    text = pytesseract.image_to_data(img, config=custom_config)
    #print (text)
    replaced = recognized.replace(' ', '')
    #print (replaced)
    print(actualConsumption)
    return actualConsumption = float(replaced)/1000 

# Writing into txt for web
def writeIntoTxt (file, actualConsumption):
    file = open(file, 'a')  
    file.write('\n'+ date +"\t" + time + "\t" + str(actualConsumption))
    file.close()

init()
writeIntoTxt('/home/pi/Scripts/web/text.txt', recognize())

# writing into xlsx
wb = load_workbook('/home/pi/Desktop/technicka.xlsx')
ws = wb['Sheet']


row_count = ws.max_row
column_count = ws.max_column
writeTo = 'C' + str(row_count+1)

print ('Argument List:', str(sys.argv[1])
result = re.search(r'\/([0-9|_]+)\.\w+$', str(sys.argv[1]))
fullDateTime = str(result.group(1))
fullDateTime = re.split('_', fullDateTime)


date = str(fullDateTime[2] + '.' + fullDateTime[1] + '.' + fullDateTime[0])
time = str(fullDateTime[3] + ':' + fullDateTime[4])

# Write actual consumtion
ws[('C' + str(row_count+1))] = str(actualConsumption)
ws[('A' + str(row_count+1))] = date
ws[('B' + str(row_count+1))] = time

text = ws['A1'].value
print (text)
wb.save('/home/pi/Desktop/technicka.xlsx')