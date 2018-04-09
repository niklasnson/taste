#include <iostream> 
#include "server.h"
#include "client.h"
#include "package.h"

void usage(char* name) {
  std::cout << std::endl << name << " [options]" << std::endl << 
  "Options:" << std::endl;
}

int main(int argc, char *argv[]) {
  /*
  if (argc == 1) {
    usage(argv[0]);
    return 0; 
  }
  */
  
  Server server; 
  Client client(server); 
  client.send_unorded_packages(25);
  return 0; 
}