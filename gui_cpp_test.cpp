// C++ GUI test program to read an image and convert it to gray with OpenCV 4
// You can compile the program with:
// opencv only     g++ gui_cpp_test.cpp -o gui_cpp_test `pkg-config --cflags --libs opencv`      
// with tesseract  g++ gui_cpp_test.cpp -o gui_cpp_test -llept -ltesseract `pkg-config --cflags --libs opencv`
#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>
#include <tesseract/baseapi.h>
#include <leptonica/allheaders.h>

float convertToFLoat (std::string word)
{
    word.erase(remove(word.begin(), word.end(), ' '), word.end());
    float water = stof(word)/1000;
    return water;
}

void printPictInfo(cv::Mat image)
{
    std::cout << "Image type: " << image.type() << std::endl;
    std::cout<<"number of channels"<<image.channels() <<std::endl;    
}


void removeAlphaChannel(cv::Mat image)
{

// Split channels of the png files
std::vector<cv::Mat> pngChannels(4);
cv::split(image, pngChannels);
/*
cv::imshow("Input image", image);
cv::imshow("Input image R", pngChannels[0]);
cv::imshow("Input image G", pngChannels[1]);
cv::imshow("Input image B", pngChannels[2]);
cv::imshow("Input image A", pngChannels[3]);

// Set to 255(white) the RGB channels where the Alpha channel(mask) is 0(transparency)
pngChannels[0].setTo(cv::Scalar(255), pngChannels[3]==0);
pngChannels[1].setTo(cv::Scalar(255), pngChannels[3]==0);
pngChannels[2].setTo(cv::Scalar(255), pngChannels[3]==0);

// Merge again the channels
cv::Mat test_image_output;
cv::merge(pngChannels, test_image_output);

// Show the merged channels.
cv::imshow("Output image", test_image_output);

// For saving with changes, conversion is needed.
cv::cvtColor(test_image_output, test_image_output, cv::COLOR_RGBA2RGB);
cv::imwrite("NoAlpha.png", test_image_output);    
 */   
}

float recognizeDigits(cv::Mat im)
{
    using namespace std;
   std::string outText;
    // Create Tesseract object
    tesseract::TessBaseAPI *ocr = new tesseract::TessBaseAPI();
     
    // Initialize tesseract to use English (eng) and the LSTM OCR engine. 
    ocr->Init(NULL, "digits", tesseract::OEM_LSTM_ONLY);
 
    // Set Page segmentation mode to PSM_AUTO (3)
    ocr->SetPageSegMode(tesseract::PSM_AUTO);
        //ocr->SetPageSegMode(tesseract::PSM_SINGLE_BLOCK);
 
    Pix *image = pixRead("recognize.png"); 
    if (!image) {
       fprintf(stderr, "Leptonica can't process input file!\n");
       return 2;
     }
     
     
     ocr->SetImage(image);
    
    //            image    columns  rows     bytes per pixel,bytes per line    
    //ocr->SetImage(im.data, im.cols, im.rows, 1, im.step);
    
    cout<<"step" << im.step<<endl;
     // Run Tesseract OCR on image
    outText = string(ocr->GetUTF8Text());
    ocr->End();
    cout << "recognized text: "<< outText << endl; // Destroy used object and release memory ocr->End();
    return convertToFLoat(outText);
}
// Get rid of too white places
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

//string convertToString(char* a, int size) 
//{ 
//    string s(a); 
  
    // we cannot use this technique again 
    // to store something in s 
    // because we use constructors 
    // which are only called 
    // when the string is declared. 
  
    // Remove commented portion 
    // to see for yourself 
  
    /* 
    char demo[] = "gfg"; 
    s(demo); // compilation error  
    */
  
//    return s; 
//} 

std::string convertToString(char* a) 
{ 
    unsigned char i; 
    std::string s = ""; 
    // do not want to create endless loop  
    for (i = 0; i < 255; i++) { 
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
    int size = 18; 
    cout <<"sizeof: " << size << endl;
    
    string fileName = convertToString(argv[1]);
    cout << "filename: " << fileName<< endl; 
    //img_file = img_file + fileName;
    //cout << "connected" << img_file<< endl;
    
    
    //std::string s = convertToString(argv[0], argc);
    //img_file += s; 
    //const std::string img_file{"../Desktop/2020_1_14_20_58_36.jpg"};
    const unsigned char maxValue = 255;  // 0 - black, 255 - white

    // Check if we can open the file
    cv::Mat input = cv::imread(fileName, 1);
    printPictInfo(input);
    if(!input.data) {
        std::cout << "Can't open file " << img_file << '\n';
        return -1;
    }

    // Convert to gray
    cv::Mat output;
    cvtColor(input, output, cv::COLOR_BGR2GRAY);
    printPictInfo(output);
    //cv::imwrite("GrayImage.jpg", output);
    // crop image 
                                    // x    y    width    height       
    cv::Mat cropped (output, cv::Rect(555, 110, 1670-555, 290-100) ); // using a rectangle
    //
    //cv::imshow("cropped", cropped);   //       alfa, beta

    //saturatePict (cropped, 130);
    printPictInfo(cropped);
    medianBlur ( cropped, cropped, 5 );
    //cv::imshow("median blur", cropped);
    
    cv::Mat dst;

    // (InputArray src, OutputArray dst, double maxValue, int adaptiveMethod, int thresholdType, int blockSize, double C)
    cv::adaptiveThreshold(cropped,dst, maxValue,cv::ADAPTIVE_THRESH_GAUSSIAN_C, cv::THRESH_BINARY, 101, 7.0);
    
    //cv::imshow("bw_image.png", dst);
    //cv::imwrite("bw_image.png", dst);
    // whitening of borders
	cout << "rows" << dst.rows << "columns" << dst.cols << endl;
    // const int ranges [9] [2] = {{0,20}, {91,158}, {241,307}, {385, 455}, {530,597}, {679,742}, {822,866}, {966,1041}, {1105, 1115}};  
    //                                 0         0          1           1          9          9          5   
	const int ranges [9] [2] = {{0,20}, {89,159}, {237,307}, {383, 455}, {526,600}, {671,742}, {823,866}, {964,1039}, {1103, 1115}};
    
    for( int y = 0; y < dst.rows; y++ ) 
	{
        for( int x = 0; x < dst.cols; x++ ) 
		{
			for ( int i = 0; i < sizeof(ranges)/8; i++)
			{
			    if ((x > ranges[i][0]) && (x < ranges[i][1]))
                {
                    dst.at<char>(y,x) = 255;
                }
			}
		}
	}
    
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
    //cv::waitKey(0);
    cv::destroyAllWindows();

    return 0;
}

