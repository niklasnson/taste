#include "package.h"
#include <iostream>

Package::Package(int num) : num(num){}

void 
Package::identify() { 
  std::cout << "Package id: " << num <<  " identified." << std::endl;
}
bool 
Package::operator==(Package const & rhs) const {
 return num == rhs.num;  
}
