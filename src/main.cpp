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
  while (getline(std::cin, command)) {
    // 去除前后空格
    std::string cmd = command;
    while (!cmd.empty() && cmd[0]==' ') cmd.erase(0,1);
    while (!cmd.empty() && cmd[cmd.size()-1]==' ') cmd.erase(cmd.size()-1,1);
    if (cmd == "quit" || cmd == "exit") {
      break;
    }
    commandpaser.parseCommand(command);
  }
  return 0;
}