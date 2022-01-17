
#include <string>
#include <list>
#include <dirent.h>
#include <cstring>

#include "directory.h"

Directory::Directory(const char* path, const char* extension) :
        _path(path), _extension(extension) {
}
// to list files in directory
std::list<std::string> Directory::list() {
    std::list<std::string> files;
    DIR *dir;
    struct dirent *ent;

    if ((dir = opendir(_path.c_str())) != NULL) {
        while ((ent = readdir(dir)) != NULL) {
            if ((ent->d_type == DT_REG || ent->d_type == DT_LNK)    // DT_REG is regular (normal) file, 
                    && hasExtension(ent->d_name, _extension.c_str())) {
                files.push_back(std::string(ent->d_name));
            }
        }
        closedir(dir);
    }
    return files;
}

// to get path with name of file
std::string Directory::fullpath(const std::string filename) {
    std::string path(_path);
    path += "/";
    path += filename;
    return path;
}

bool Directory::hasExtension(const char* name, const char* ext) {
    if (name == NULL || ext == NULL) {
        return false;
    }
    size_t len = strlen(name);
    size_t extlen = strlen(ext);
                                        // here please note that name is pointer - so pointer's arithmetics
    return (len >= extlen) && (0 == strcmp(name + len - extlen, ext));
}