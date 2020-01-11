// C++ GUI test program to read an image and convert it to gray with OpenCV 4
// You can compile the program with:
// opencv only     g++ gui_cpp_test.cpp -o gui_cpp_test `pkg-config --cflags --libs opencv`      
// with tesseract  g++ gui_cpp_test.cpp -o gui_cpp_test -llept -ltesseract `pkg-config --cflags --libs opencv`
#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>
#include <tesseract/baseapi.h>
#include <leptonica/allheaders.h>

void recognizeDigits(cv::Mat im)
{
    using namespace std;
   std::string outText;
    // Create Tesseract object
    tesseract::TessBaseAPI *ocr = new tesseract::TessBaseAPI();
    //ocr->SetVariable("classify_bln_numeric_mode", "1");
    ocr->SetVariable("tessedit_char_blacklist", "!%");
     
    // Initialize tesseract to use English (eng) and the LSTM OCR engine. 
    ocr->Init(NULL, "digits", tesseract::OEM_LSTM_ONLY);
 
    // Set Page segmentation mode to PSM_AUTO (3)
    ocr->SetPageSegMode(tesseract::PSM_AUTO);
 
    //            image    columns  rows     bytes per pixel,    
    ocr->SetImage(im.data, im.cols, im.rows, 3, im.step);
 
    // Run Tesseract OCR on image
    outText = string(ocr->GetUTF8Text());
    
    cout << "recognized text: "<< outText << endl; // Destroy used object and release memory ocr->End();
    int water = stoi(outText);
    //for ()
    cout<< outText[5]<< endl;
    cout << "actual consumption: "<< water<< endl;
    ocr->End();
}


int main() {
    const std::string img_file{"../Desktop/2020_1_6_22_16_7.jpg"};
    const unsigned char maxValue = 255;  // 0 - black, 255 - white
    unsigned char thresh = 55;
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
    std::cout <<"rows:"<<output.rows << "columns" << output.cols << '\n';
    // crop image 
                                    // x    y    width    height       
    cv::Mat cropped (output, cv::Rect(555, 110, 1670-555, 290-100) ); // using a rectangle
    //
    cv::imshow("cropped", cropped);   //       alfa, beta
 
 const unsigned char saturation = 130;  
    cv::Mat newImage = cropped;
    for( int y = 0; y < cropped.rows; y++ ) {
        for( int x = 0; x < cropped.cols; x++ ) {
            //for( int c = 0; c < cropped.channels(); c++ ) {
                if (cropped.at<char>(y,x) > saturation)
                {
                    newImage.at<char>(y,x) = saturation;
                }     
                  newImage.at<char>(y,x) = cropped.at<char>(y,x);
            //}
        }
    }

    
    medianBlur ( cropped, cropped, 5 );
    cv::imshow("median blur", cropped);
    
    cv::Mat dst;
    
    //cv::threshold(cropped,dst, thresh, maxValue, cv::THRESH_BINARY);
    // (InputArray src, OutputArray dst, double maxValue, int adaptiveMethod, int thresholdType, int blockSize, double C)
    cv::adaptiveThreshold(cropped,dst, maxValue,cv::ADAPTIVE_THRESH_GAUSSIAN_C, cv::THRESH_BINARY, 101, 7.0);
    
    cv::imshow("bw_image.png", dst);
    cv::imwrite("bw_image.png", dst);
    
    cv::Mat ManuallyUpdated =  cv::imread("new.png", 1); 
        cv::imshow("new.png", newImage);
       if(!ManuallyUpdated.data) {
        std::cout << "Can't open file " << "new.png" << '\n';
        return -1;
    }
      
    recognizeDigits (ManuallyUpdated);
    //std::this_thread::sleep_for(1000);
    // Wait until the presses any key
    cv::waitKey(0);
    //do 
    //{
    //     std::cout << '\n' << "Press a key to continue...";
    //} while (std::cin.get() != '\n');

    cv::destroyAllWindows();

    return 0;
}

