#ifndef DIRECTORY_H_
#define DIRECTORY_H_

#include <string>
#include <list>

class Directory {
public:
    Directory(const char* path, const char* extension);
    // To list files in directory
    std::list<std::string> list();
    // to get full path including file name
    std::string fullpath(const std::string filename);
private:
    bool hasExtension(const char* name, const char* ext);
    std::string _path;
    std::string _extension;
};

#endif /* DIRECTORY_H_ */