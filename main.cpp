// C++ GUI test program to read an image and convert it to gray with OpenCV 4
// You can compile the program with:
// opencv only     g++ gui_cpp_test.cpp -o gui_cpp_test `pkg-config --cflags --libs opencv`      
// with tesseract  g++ gui_cpp_test.cpp -o gui_cpp_test -llept -ltesseract `pkg-config --cflags --libs opencv`

#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>
// for OCR
#include <tesseract/baseapi.h>
#include <leptonica/allheaders.h>
// To obtain image
#include "imageIn.h"


// Supporting info
void printPictInfo(cv::Mat image)
{
    std::cout << "Image type: " << image.type() << std::endl;
    std::cout<<"number of channels"<<image.channels() <<std::endl;    
}


// Get rid of too white places from flash (white led diode)
void saturatePict(cv::Mat &im, unsigned int satlimit)
{
    //cv::Mat newImage = cropped;
    for( int y = 0; y < im.rows; y++ ) 
	{
        for( int x = 0; x < im.cols; x++ ) 
		{
            if (im.at<char>(y,x) > satlimit)
            {
                im.at<char>(y,x) = satlimit;
            }  
        }
    }	
}

// based on passed coordinates in const array fill places between them by white spaces
void whiteningPicture (cv::Mat &img)
{
    //                                 0         0          1           1          9          9          5   
	const int ranges [9] [2] = {{0,20}, {89,159}, {237,307}, {383, 455}, {526,600}, {671,742}, {823,860}, {964,1039}, {1103, 1115}};
    for( int y = 0; y < img.rows; y++ ) 
	{
        for( int x = 0; x < img.cols; x++ ) 
		{
			for ( int i = 0; i < sizeof(ranges)/8; i++)
			{
			    if ((x > ranges[i][0]) && (x < ranges[i][1]))
                {
                    img.at<char>(y,x) = 255;
                }
			}
		}
	}

}

// function to convert array of chars to string
// because from bash we receive array of char
std::string convertToString(char* a) 
{ 
    unsigned char i; 
    std::string s = "";  
    for (i = 0; i < 100; i++) { 
        if (a[i] =='\0') return s;
        s = s + a[i]; 
    } 
    return s; 
} 

int main(int argc, char *argv[]) {
    using namespace std;    
    std::string img_file{"/home/pi/Desktop/"};
    cout <<"argv[1]"<< argv[1] <<endl;
    cout <<"argc"<< argc <<endl;
    
    string fileName = convertToString(argv[1]);
 
    const unsigned char maxValue = 255;  // 0 - black, 255 - white

    // Check if we can open the file
    cv::Mat inputImage = cv::imread(fileName, 1);
    
    
    
    printPictInfo(inputImage);
    if(!inputImage.data) {
        std::cout << "Can't open file " << img_file << '\n';
        return -1;
    }

    // Convert to gray
    cv::Mat grayImg;
    cvtColor(inputImage, grayImg, cv::COLOR_BGR2GRAY);
    printPictInfo(grayImg);
    printf("imshow");
    cv::imshow("Grayed", grayImg);


    // crop image 
                                    // x    y    width    height       
    cv::Mat cropped (grayImg, cv::Rect(555, 110, 1670-555, 290-100) ); // using a rectangle

    //saturatePict (cropped, 130);
    printPictInfo(cropped);
    medianBlur ( cropped, cropped, 5 );
    
    cv::Mat dst;

    // (InputArray src, OutputArray dst, double maxValue, int adaptiveMethod, int thresholdType, int blockSize, double C)
    cv::adaptiveThreshold(cropped,dst, maxValue,cv::ADAPTIVE_THRESH_GAUSSIAN_C, cv::THRESH_BINARY, 101, 7.0);
    
 
    // whitening of borders
	cout << "rows" << dst.rows << "columns" << dst.cols << endl;
    // const int ranges [9] [2] = {{0,20}, {91,158}, {241,307}, {385, 455}, {530,597}, {679,742}, {822,866}, {966,1041}, {1105, 1115}};  
    //                                 0         0          1           1          9          9          5   
	const int ranges [9] [2] = {{0,20}, {89,159}, {237,307}, {383, 455}, {526,600}, {671,742}, {823,860}, {964,1039}, {1103, 1115}};
    
    whiteningPicture (dst);
    
	//cv::imshow("after whitening", dst);
	
    //cv::Mat ManuallyUpdated =  cv::imread("new.png", 1); 
    //if(!ManuallyUpdated.data) 
	//{
    //    std::cout << "Can't open file " << "new.png" << '\n';
    //    return -1;
    //}
    //removeAlphaChannel(dst);
    cv::imwrite("/home/pi/Scripts/recognize.png", dst);
    //float water = recognizeDigits (dst);
    //cout << "Actual state: " << water <<endl;
    //cv::imshow("ManuallyUpdated",dst);
    // Wait until the presses any key
    cv::waitKey(0);
    cv::destroyAllWindows();

    return 0;
}

