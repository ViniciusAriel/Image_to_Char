#include <fstream>              // std::fstream, std::streamsize
#include <vector>               // std::vector
#include <string>               // std::string
#include <cwctype>              // iswspace
#include <limits>               // std::numeric_limits
#include "image_size.hpp"       // Struct: ImageSize

std::streamsize GetFileSize(std::fstream& file);

ImageSize GetImageSize(std::vector<char>& file_data);

std::vector<char> ReadFileData(std::fstream& file, std::streamsize file_size);
