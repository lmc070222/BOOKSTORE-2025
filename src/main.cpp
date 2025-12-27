#include "account_manager.h"
#include "book.h"
#include "book_manager.h"
#include "log_manager.h"
#include "utils.h"
#include "Paser.cpp"
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