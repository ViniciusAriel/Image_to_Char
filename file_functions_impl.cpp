#include "file_functions.hpp"

std::streamsize GetFileSize(std::fstream& file){
  //Extracts (and ignores) all characters until end or file or reach max stream
  file.ignore(std::numeric_limits<std::streamsize>::max());
  //Counts charactes extracted until now
  std::streamsize file_size{file.gcount()};
  //Clear error flags (like end of file, for example)
  file.clear();
  //Sets the position of the next character to be extracted back to the
  //beginning
  file.seekg(0, std::ios_base::beg);

  return file_size;
}

ImageSize GetImageSize(std::vector<char>& file_data){
  bool magic_number_read{false};
  std::string number_string;

  ImageSize image_size;

  for(int i{0}; i < file_data.size(); ++i){
    //creates string from buffer data
    number_string.push_back(file_data[i]);

    //Read magic number
    if(iswspace(file_data[i]) && !magic_number_read){
      magic_number_read = true;
      number_string = "";
    }
    //Reads width
    else if(iswspace(file_data[i]) && image_size.width == 0){
      image_size.width = std::atoi(number_string.c_str());
      number_string = "";
    }
    //Reads height
    else if(iswspace(file_data[i]) && image_size.height == 0){
      image_size.height = std::atoi(number_string.c_str());
      number_string = "";
    }
    //Ignores the highest value for each pixel
    else if(iswspace(file_data[i])){
      //Erases read data from buffer so we don't have to store where we left off
      file_data.erase(file_data.begin(), file_data.begin() + i + 1);
      break;
    }
  }

  return image_size;
}
