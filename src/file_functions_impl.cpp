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

std::vector<char> ReadFileData(std::fstream& file, std::streamsize file_size){
  std::vector<char> file_data;

  file_data.resize(file_size);
  file.read(&file_data[0], file_size);
  file.close();
}

std::string ReadWordFromData(std::vector<char>& file_data){
  std::string word;
  for(int i{0}; i < file_data.size(); ++i){
    word.push_back(file_data[i]);

    if(iswspace(file_data[i])){
      file_data.erase(file_data.begin(), file_data.begin() + i + 1);
      return word;
    }
  }
}

ImageSize GetImageSize(std::vector<char>& file_data){
  bool magic_number_read{false};
  std::string number_string;

  ImageSize image_size;

  int magic_number{std::atoi(ReadWordFromData(file_data).c_str())};
  image_size.width = std::atoi(ReadWordFromData(file_data).c_str());
  image_size.height = std::atoi(ReadWordFromData(file_data).c_str());
  int max_greyscale_value{std::atoi(ReadWordFromData(file_data).c_str())};

  return image_size;
}
