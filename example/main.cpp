#include <fstream>
#include <iostream>
#include "../asar.hpp"

int main() {
  Asar resources("resources.asar");

  std::string data1 = resources.unpack("/im/not/exist");
  std::string data2 = resources.unpack("/assets/image.png");

  std::cout << data1 << std::endl;

  std::ofstream image("image.png");
  image.write(data2.c_str(), data2.size());
 
  return 1;
}
