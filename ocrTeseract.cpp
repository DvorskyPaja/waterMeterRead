// not working properly
// Data from Watermeter are read without decimal point
// and in form of string
// it needs conversion
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