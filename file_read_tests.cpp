#include <fstream>
#include <iostream>
#include <cstddef>

int main(){

  std::fstream file;
  file.open("capivara.png", std::ios::in | std::ios::binary);

  if(!file){
    //Change to a error handling later
    std::cout << "File not found!\n";
  }
  else{
      //Try later:
      //char b[1024];
      char b;
      while (true){
        //Checks End of File
        if(file.eof()){
          break;
        }
        file >> b;
        std::cout << b;
      }
  }

  file.close();

  return 0;

}
