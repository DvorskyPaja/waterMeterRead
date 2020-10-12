#!/bin/bash
export LD_LIBRARY_PATH=/opt/opencv-4.1.0/lib
echo "generateImageName.py"
IMAGE=$(python /home/pi/Scripts/generateImageName.py)
echo "opencv"
echo $IMAGE
echo "gui_cpp_test"
/home/pi/Scripts/gui_cpp_test $IMAGE
echo "recognize using ocr_recognize.py"
python /home/pi/Scripts/ocr_recognize.py $IMAGE
echo "Sending to WEB"
/home/pi/Scripts/send.sh
