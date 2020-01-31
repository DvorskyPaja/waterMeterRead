#!/bin/bash
export LD_LIBRARY_PATH=/opt/opencv-4.1.0/lib
echo "generateImageName.py"
IMAGE=$(python /home/pi/Scripts/generateImageName.py)
echo "opencv"
echo $IMAGE
/home/pi/Scripts/gui_cpp_test $IMAGE
echo "recognize"
python /home/pi/Scripts/ocr_recognize.py $IMAGE
/home/pi/Scripts/send.sh
