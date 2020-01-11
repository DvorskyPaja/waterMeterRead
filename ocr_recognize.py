#!/usr/bin/python3
import pytesseract
from PIL import Image
img =Image.open ("new.png")

custom_config = r'-c tessedit_char_whitelist=02345678 --psm 6'
#custom_config = r'--oem 3 --psm 6 outputbase digits'

text = pytesseract.image_to_string(img, config = custom_config)
print (text)
text = pytesseract.image_to_data(img, config=custom_config)
print (text)
