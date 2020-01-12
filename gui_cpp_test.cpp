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

float recognizeDigits(cv::Mat im)
{
    using namespace std;
   std::string outText;
    // Create Tesseract object
    tesseract::TessBaseAPI *ocr = new tesseract::TessBaseAPI();
    ocr->SetVariable("tessedit_char_blacklist", "!%");
     
    // Initialize tesseract to use English (eng) and the LSTM OCR engine. 
    ocr->Init(NULL, "digits", tesseract::OEM_LSTM_ONLY);
 
    // Set Page segmentation mode to PSM_AUTO (3)
    ocr->SetPageSegMode(tesseract::PSM_AUTO);
 
    //            image    columns  rows     bytes per pixel,    
    ocr->SetImage(im.data, im.cols, im.rows, 3, im.step);
     // Run Tesseract OCR on image
    outText = string(ocr->GetUTF8Text());
    ocr->End();
    //cout << "recognized text: "<< outText << endl; // Destroy used object and release memory ocr->End();
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
            else
			{
				im.at<char>(y,x) = im.at<char>(y,x);
			}
        }
    }	
}


int main() {
    const std::string img_file{"../Desktop/2020_1_6_22_16_7.jpg"};
    const unsigned char maxValue = 255;  // 0 - black, 255 - white
    using namespace std;
    // Check if we can open the file
    cv::Mat input = cv::imread(img_file, 1);
    if(!input.data) {
        std::cout << "Can't open file " << img_file << '\n';
        return -1;
    }

    // Convert to gray
    cv::Mat output;
    cvtColor(input, output, cv::COLOR_BGR2GRAY);

    cv::imwrite("GrayImage.jpg", output);
    // crop image 
                                    // x    y    width    height       
    cv::Mat cropped (output, cv::Rect(555, 110, 1670-555, 290-100) ); // using a rectangle
    //
    cv::imshow("cropped", cropped);   //       alfa, beta

    saturatePict (cropped, 130);
    
    medianBlur ( cropped, cropped, 5 );
    cv::imshow("median blur", cropped);
    
    cv::Mat dst;

    // (InputArray src, OutputArray dst, double maxValue, int adaptiveMethod, int thresholdType, int blockSize, double C)
    cv::adaptiveThreshold(cropped,dst, maxValue,cv::ADAPTIVE_THRESH_GAUSSIAN_C, cv::THRESH_BINARY, 101, 7.0);
    
    cv::imshow("bw_image.png", dst);
    cv::imwrite("bw_image.png", dst);
    // whitening of borders
    
    cv::Mat ManuallyUpdated =  cv::imread("new.png", 1); 
    if(!ManuallyUpdated.data) 
	{
        std::cout << "Can't open file " << "new.png" << '\n';
        return -1;
    }
      
    cout << "Actual state: " << recognizeDigits (ManuallyUpdated) <<endl;

    // Wait until the presses any key
    cv::waitKey(0);
    cv::destroyAllWindows();

    return 0;
}

