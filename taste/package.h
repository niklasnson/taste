#ifndef PACKAGE_H
#define PACKAGE_H

class Package {
 public:
  Package(int num);
  void identify(); 
  bool operator==(Package const & rhs) const; 
  
 private:
  int num;
};

#endif
