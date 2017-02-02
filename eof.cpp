// ios::eof example
#include <iostream>     // std::cout
#include <fstream>      // std::ifstream

int main (int argc, char const *argv[]) {

  std::ifstream is(argv[1]);   // open file

  char c;
  while (is.get(c))                  // loop getting single characters
    std::cout << c;

  if (is.eof())                      // check for EOF
    std::cout << "[EoF reached]\n";
  else
    std::cout << "[error reading]\n";

  is.close();                        // close file

  return 0;
}
