#ifndef IMAGEIN_H_
#define IMAGEIN_H_

#include <string>
#include <list>
#include <ctime>

#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#include "Directory.h"

class ImageIn {
public:
    virtual ~ImageIn();

    virtual bool obtainImage() = 0;

    virtual cv::Mat & getImage();
    virtual time_t getTime();
    virtual void setOutputDir(const std::string & outDir);
    virtual void saveImage();

protected:
    cv::Mat _img;
    time_t _time;
    std::string _outDir;
};

class FolderImage: public ImageIn {
public:
    FolderImage(const Directory & directory);

    virtual bool obtainImage();

private:
    Directory _directory;
    std::list<std::string>::const_iterator _itFilename;
    std::list<std::string> _filenameList;
};


class CameraImage: public ImageIn {
public:
    CameraImage(int device);

    virtual bool obtainImage();

private:
    cv::VideoCapture _capture;
};


#endif /* IMAGEIN_H_ */