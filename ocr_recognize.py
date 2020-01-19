#!/usr/bin/python3
import pytesseract
import sys, re
from openpyxl import load_workbook
from PIL import Image
img =Image.open ("/home/pi/Scripts/recognize.png")

custom_config = r"-c tessedit_char_whitelist=02345678 --psm 6 -l digits"
#custom_config = r'--oem 3 --psm 6 outputbase digits'

recognized = pytesseract.image_to_string(img, config = custom_config)
print (recognized)
text = pytesseract.image_to_data(img, config=custom_config)
print (text)
replaced = recognized.replace(' ', '')
print (replaced)
actualConsumption = float(replaced)/1000 
print(actualConsumption)

# writing into xlsx

from openpyxl import load_workbook
wb = load_workbook('/home/pi/Desktop/technicka.xlsx')
ws = wb['Sheet']


row_count = ws.max_row
column_count = ws.max_column
writeTo = 'C' + str(row_count+1)

print 'Argument List:', str(sys.argv[1])
result = re.search(r'\/([0-9|_]+)\.\w+$', str(sys.argv[1]))
fullDateTime = str(result.group(1))
fullDateTime = re.split('_', fullDateTime)


# Write actual consumtion
ws[('C' + str(row_count+1))] =  str(actualConsumption)
ws[('A' + str(row_count+1))] =  str(fullDateTime[2] + '.' + fullDateTime[1] + '.' + fullDateTime[0])
ws[('B' + str(row_count+1))] =  str(fullDateTime[3] + ':' + fullDateTime[4])


text = ws['A1'].value
print (text)
wb.save('/home/pi/Desktop/technicka.xlsx')


