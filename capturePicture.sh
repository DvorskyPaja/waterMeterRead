#!/bin/bash
echo "changing directory"
cd ../Pictures
raspistill -o $1
echo $1
cd ../Scripts
 
