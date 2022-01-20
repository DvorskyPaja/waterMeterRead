#include <ctime>
#include <string>
#include <list>
#include <iostream>

//#include <log4cpp/Category.hh>
//#include <log4cpp/Priority.hh>


//#include "Directory.h"
#include "imageIn.h"

ImageIn::~ImageIn() 
{

}

cv::Mat& ImageIn::getImage() {
    return _img;
}

time_t ImageIn::getTime() {
    return _time;
}

void ImageIn::setOutputDir(const std::string & outDir) {
    _outDir = outDir;
}


void ImageIn::saveImage() {
    struct tm date;
    localtime_r(&_time, &date);
    char filename[PATH_MAX];
    strftime(filename, PATH_MAX, "/%Y%m%d-%H%M%S.png", &date);
    std::string path = _outDir + filename;
    if (cv::imwrite(path, _img)) {
        //log4cpp::Category::getRoot() << log4cpp::Priority::INFO << "Image saved to " + path;
        std::cout << "image saved";
    }
}

// *************Class FolderImage*************

FolderImage::FolderImage(const Directory& directory) :
        _directory(directory) {
    _filenameList = _directory.list();
    _filenameList.sort();
    _itFilename = _filenameList.begin();
}

bool FolderImage::obtainImage() {
    if (_itFilename == _filenameList.end()) {
        return false;
    }
    std::string path = _directory.fullpath(*_itFilename);

    _img = cv::imread(path.c_str());

    // read time from file name
    struct tm date;
    memset(&date, 0, sizeof(date));
    date.tm_year = atoi(_itFilename->substr(0, 4).c_str()) - 1900;
    date.tm_mon = atoi(_itFilename->substr(4, 2).c_str()) - 1;
    date.tm_mday = atoi(_itFilename->substr(6, 2).c_str());
    date.tm_hour = atoi(_itFilename->substr(9, 2).c_str());
    date.tm_min = atoi(_itFilename->substr(11, 2).c_str());
    date.tm_sec = atoi(_itFilename->substr(13, 2).c_str());
    _time = mktime(&date);

    //log4cpp::Category::getRoot() << log4cpp::Priority::INFO << "Processing " << *_itFilename << " of " << ctime(&_time);

    // save copy of image if requested
    if (!_outDir.empty()) {
        saveImage();
    }

    _itFilename++;
    return true;
}

#if CAMERA_PRESENT==1
CameraImage::CameraImage(int device, int flashLedPosition) {
    _capture.open(device);
    _LED = flashLedPosition; 
}

bool CameraImage::obtainImage() {
    time(&_time);
    // flash on
    wiringPiSetup();			// Setup the library
    pinMode(_LED, OUTPUT);		// Configure GPIO0 as an output
    delay(500);
    digitalWrite(_LED, true);
    
    // read image from camera
    bool success = _capture.read(_img);
    std::cout << "image captured" << std::endl;
    //log4cpp::Category::getRoot() << log4cpp::Priority::INFO << "Image captured: " << success;
    digitalWrite(_LED, false); // flash off


    // save copy of image if requested
    if (success && !_outDir.empty()) {
        saveImage();
    }

    return success;
}
#endif




