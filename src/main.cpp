#include "/home/lmc123456/Bookstore-2025/include/account_manager.h"
#include "/home/lmc123456/Bookstore-2025/include/book.h"
#include "/home/lmc123456/Bookstore-2025/include/book_manager.h"
#include "/home/lmc123456/Bookstore-2025/include/log_manager.h"
#include "/home/lmc123456/Bookstore-2025/include/utils.h"
#include "/home/lmc123456/Bookstore-2025/src/Paser.cpp"
#include <cstring>
#include <iostream>
CommandParser commandpaser;
std::string command="";
int main() {
  std::cout << 1 << std::endl;
  getline(std::cin,command);
  while (command != "quit" and command != "exit") {
    commandpaser.parseCommand(command);
    getline(std::cin,command);
    std::cout << "sss" << std::endl;
  }
  return 0;
}
