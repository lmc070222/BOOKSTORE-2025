#include "/home/lmc123456/Bookstore-2025/include/account_manager.h"
#include "/home/lmc123456/Bookstore-2025/include/book_manager.h"
#include "/home/lmc123456/Bookstore-2025/include/log_manager.h"
#include <cstring>
#include <iostream>
#include <regex>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>
class CommandParser {
private:
  AccountManager accountManager;
  BookManager bookManager;
  LogManager logmanager;
  std::string order;

public:
  void parseCommand(const std::string &command) {
    std::regex suregex(R"(su (\w{1,30}) (\w{1,30})?)");
    std::regex registerregex(R"(register (\w{1,30}) (\w{1,30}) (\w{1,30}))");
    std::regex passwdregex(R"(passwd (\w{1,30}) (\w{1,30})? (\w{1,30}))");
    std::regex useraddregex(
        R"(useradd (\w{1,30}) (\w{1,30}) (\d{1}) (\w{1,30}))");
    std::regex deleteregex(R"(delete (\w{1,30}))");
    std::regex showregex(
        R"(show (-ISBN=([A-Za-z0-9]{1,20})| -name=\"([^\"]+)\"| -author=\"([^\"]+)\"| -keyword=\"([^\"]+)\")?)");
    std::regex buyregex(R"(buy (\w{1,20})\s+(\d+))");
    std::regex selectregex(R"(select (\w{1,20}))");
    std::regex modifyregex(
    R"(modify ((-ISBN=([A-Za-z0-9]{1,20}))|(-name=\"([^\"]+)\")|(-author=\"([^\"]+)\")|(-keyword=\"([^\"]+)\")|(-price=\d+(\.\d+)?))+)"); 
    std::regex importregex(R"(import \d+ \d+)");
    std::regex showfinanceregex(R"(show finance (\d+)?)");
    std::smatch match;
    if (std::regex_match(command, match, suregex)) {
      char userID[30];
      std::string matched_str = match[1].str();
      matched_str.copy(userID, matched_str.size(), 0);
      char password[30];
      if (match[2].matched == false) {
        accountManager.login(userID);
        return;
      }
      matched_str = match[2].str();
      matched_str.copy(password, matched_str.size(), 0);
      accountManager.login(userID, password);
    } else if (command == "logout") {
      accountManager.logout();
    } else if (std::regex_match(command, match, registerregex)) {
      char userID[30];
      std::string matched_str = match[1].str();
      matched_str.copy(userID, matched_str.size(), 0);
      char password[30];
      matched_str = match[2].str();
      matched_str.copy(password, matched_str.size(), 0);
      char username[30];
      matched_str = match[3].str();
      matched_str.copy(username, matched_str.size(), 0);
      accountManager.reg(userID, password, username);
    } else if (std::regex_match(command, match, passwdregex)) {
      char userID[30];
      std::string matched_str = match[1].str();
      matched_str.copy(userID, matched_str.size(), 0);
      char newpassword[30];
      matched_str = match[3].str();
      matched_str.copy(newpassword, matched_str.size(), 0);
      if (match[2].matched == false) {
        accountManager.changeinf(userID, newpassword);
        return;
      }
      char oldpassword[30];
      matched_str = match[2].str();
      matched_str.copy(oldpassword, matched_str.size(), 0);
      accountManager.changeinf(userID, oldpassword, newpassword);
    } else if (std::regex_match(command, match, useraddregex)) {
      char userID[30];
      std::string matched_str = match[1].str();
      matched_str.copy(userID, matched_str.size(), 0);
      char password[30];
      matched_str = match[2].str();
      matched_str.copy(password, matched_str.size(), 0);
      matched_str = match[3].str();
      int privilege = matched_str[0] - '0';
      matched_str = match[4].str();
      char username[30];
      matched_str.copy(username, matched_str.size(), 0);
      accountManager.useradd(userID, password, privilege, username);
    } else if (std::regex_match(command, match, deleteregex)) {
      char userID[30];
      std::string matched_str = match[1].str();
      matched_str.copy(userID, matched_str.size(), 0);
      accountManager.deleteuser(userID);
    } else if (std::regex_match(command, match, showregex)) {

    } else if (std::regex_match(command, match, buyregex)) {
      char ISBN[20];
      std::string matched_str = match[1].str();
      matched_str.copy(ISBN, matched_str.size(), 0);
      Transaction txn;
      txn.type=false;
      long long Quantity = std::stoll(match[2].str());
      Book book;
      memcpy(book.ISBN,ISBN,20);
      txn.TotalCost=Quantity * bookManager.bo.find(book).back().price;
      bookManager.buybook(ISBN, Quantity);
      logmanager.insertTransaction(txn);
    } else if (std::regex_match(command, match, selectregex)) {
      char ISBN[20];
      std::string matched_str = match[1].str();
      matched_str.copy(ISBN, matched_str.size(), 0);
      bookManager.select(ISBN, accountManager);
    } else if (std::regex_match(command, match, modifyregex)) {
      char ISBN[20], bookname[60], authorname[60], keyword[60];
      double price = -1;
      Book book = accountManager.accounts.back().book;
      if (match[3].matched) {
        std::string matched_str = match[3].str();
        matched_str.copy(ISBN, matched_str.size(), 0);
        memcpy(book.ISBN, ISBN, 20);
        bookManager.modify(book,accountManager,1);
      }
      if (match[5].matched) {
        std::string matched_str = match[5].str();
        matched_str.copy(bookname, matched_str.size(), 0);
        memcpy(book.bookname, bookname, 60);
        bookManager.modify(book,accountManager,2);
      }
      if (match[7].matched) {
        std::string matched_str = match[7].str();
        matched_str.copy(authorname, matched_str.size(), 0);
        memcpy(book.bookauther, authorname, 60);
        bookManager.modify(book,accountManager,3);
      }
      if (match[9].matched) {
        std::string matched_str = match[9].str();
        matched_str.copy(keyword, matched_str.size(), 0);
        memcpy(book.keyword, keyword, 60);
        bookManager.modify(book,accountManager,4);
      }
      if (match[11].matched) {
        book.price = std::stod(match[11].str());
        bookManager.modify(book,accountManager,5);
      }
    } else if (std::regex_match(command, match, importregex)) {
      long long Quantity = std::stol(match[1].str());
      long long TotalCost = std::stol(match[2].str());
      bookManager.import(Quantity, TotalCost, accountManager);
      Transaction txn;
      txn.TotalCost=TotalCost;
      txn.type=true;
      logmanager.insertTransaction(txn);
    }
    else if (std::regex_match(command, match, showfinanceregex)) {
      long long num;
      if (match[1].matched) {
        num=std::stod(match[1].str());
        logmanager.show(num);
        return;
      }
      else logmanager.show();
    }
    else std::cout << "Invalid\n";
  }
};
