#include "account_manager.h"
#include "book_manager.h"
#include "log_manager.h"
#include <cstring>
#include <iostream>
#include <regex>
#include <set>
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
    std::string cmd=command;
    while (!cmd.empty() && cmd[0]==' ') cmd.erase(0,1);
    while (!cmd.empty() && cmd[cmd.size()-1]==' ') cmd.erase(cmd.size()-1,1);
    if (cmd.empty()) return;
    // 处理 quit 和 exit 指令
    if (cmd == "quit" || cmd == "exit") {
      exit(0);
    }
    std::regex suregex(R"(su ([A-Za-z0-9_]{1,30})( ([A-Za-z0-9_]{1,30}))?)");
    std::regex registerregex(R"(register ([A-Za-z0-9_]{1,30}) ([A-Za-z0-9_]{1,30}) ([\x21-\x7E]{1,30}))");
    std::regex passwdregex2(R"(passwd ([A-Za-z0-9_]{1,30}) ([A-Za-z0-9_]{1,30}))");
    std::regex passwdregex3(R"(passwd ([A-Za-z0-9_]{1,30}) ([A-Za-z0-9_]{1,30}) ([A-Za-z0-9_]{1,30}))");
    std::regex useraddregex(
        R"(useradd ([A-Za-z0-9_]{1,30}) ([A-Za-z0-9_]{1,30}) ([137]) ([\x21-\x7E]{1,30}))");
    std::regex deleteregex(R"(delete ([A-Za-z0-9_]{1,30}))");
    std::regex showallregex(R"(show)");
    std::regex showisbnregex(R"(show -ISBN=([\x21-\x7E]{1,20}))");
    std::regex shownameregex("show -name=\"([^\"]{1,60})\"");
    std::regex showauthorregex("show -author=\"([^\"]{1,60})\"");
    std::regex showkeywordregex("show -keyword=\"([^\"|]{1,60})\"");
    std::regex buyregex(R"(buy ([\x21-\x7E]{1,20}) (\d{1,10}))");
    std::regex selectregex(R"(select ([\x21-\x7E]{1,20}))");
    std::regex modifyregex(R"(modify (.+))");
    std::regex importregex(R"(import (\d{1,10}) (\d{1,13}(\.\d{1,2})?))");
    std::regex showfinanceregex(R"(show finance)");
    std::regex showfinancecntregex(R"(show finance (\d{1,10}))");
    std::regex logregex(R"(log)");
    std::regex reportfinanceregex(R"(report finance)");
    std::regex reportemployeeregex(R"(report employee)");
    std::smatch match;
    int curpri=0;
    if (!accountManager.accounts.empty()) curpri=accountManager.accounts.back().user.privilege;
    if (std::regex_match(cmd, match, suregex)) {
      char userID[31];
      memset(userID,0,31);
      std::string matched_str = match[1].str();
      matched_str.copy(userID, matched_str.size(), 0);
      char password[31];
      memset(password,0,31);
      if (match[3].matched == false) {
        accountManager.login(userID);
        return;
      }
      matched_str = match[3].str();
      matched_str.copy(password, matched_str.size(), 0);
      accountManager.login(userID, password);
    } else if (cmd == "logout") {
      accountManager.logout();
    } else if (std::regex_match(cmd, match, registerregex)) {
      char userID[31];
      memset(userID,0,31);
      std::string matched_str = match[1].str();
      matched_str.copy(userID, matched_str.size(), 0);
      char password[31];
      memset(password,0,31);
      matched_str = match[2].str();
      matched_str.copy(password, matched_str.size(), 0);
      char username[31];
      memset(username,0,31);
      matched_str = match[3].str();
      matched_str.copy(username, matched_str.size(), 0);
      accountManager.reg(userID, password, username);
    } else if (std::regex_match(cmd, match, passwdregex2)) {
      if (curpri < 1) {std::cout << "Invalid\n";return;}
      if (curpri != 7) {std::cout << "Invalid\n";return;}
      char userID[31];
      memset(userID,0,31);
      std::string matched_str = match[1].str();
      matched_str.copy(userID, matched_str.size(), 0);
      char newpassword[31];
      memset(newpassword,0,31);
      matched_str = match[2].str();
      matched_str.copy(newpassword, matched_str.size(), 0);
      accountManager.changeinf(userID, newpassword);
    } else if (std::regex_match(cmd, match, passwdregex3)) {
      if (curpri < 1) {std::cout << "Invalid\n";return;}
      char userID[31];
      memset(userID,0,31);
      std::string matched_str = match[1].str();
      matched_str.copy(userID, matched_str.size(), 0);
      char oldpassword[31];
      memset(oldpassword,0,31);
      matched_str = match[2].str();
      matched_str.copy(oldpassword, matched_str.size(), 0);
      char newpassword[31];
      memset(newpassword,0,31);
      matched_str = match[3].str();
      matched_str.copy(newpassword, matched_str.size(), 0);
      accountManager.changeinf(userID, oldpassword, newpassword);
    } else if (std::regex_match(cmd, match, useraddregex)) {
      char userID[31];
      memset(userID,0,31);
      std::string matched_str = match[1].str();
      matched_str.copy(userID, matched_str.size(), 0);
      char password[31];
      memset(password,0,31);
      matched_str = match[2].str();
      matched_str.copy(password, matched_str.size(), 0);
      matched_str = match[3].str();
      int privilege = matched_str[0] - '0';
      matched_str = match[4].str();
      char username[31];
      memset(username,0,31);
      matched_str.copy(username, matched_str.size(), 0);
      accountManager.useradd(userID, password, privilege, username);
    } else if (std::regex_match(cmd, match, deleteregex)) {
      char userID[31];
      memset(userID,0,31);
      std::string matched_str = match[1].str();
      matched_str.copy(userID, matched_str.size(), 0);
      accountManager.deleteuser(userID);
    } else if (std::regex_match(cmd, match, showfinancecntregex)) {
      if (curpri != 7) {std::cout << "Invalid\n";return;}
      long long num=std::stoll(match[1].str());
      if (num > 2147483647LL) {std::cout << "Invalid\n";return;}
      logmanager.show(num);
    } else if (std::regex_match(cmd, match, showfinanceregex)) {
      if (curpri != 7) {std::cout << "Invalid\n";return;}
      logmanager.show();
    } else if (std::regex_match(cmd, match, showisbnregex)) {
      if (curpri < 1) {std::cout << "Invalid\n";return;}
      char ISBN[21];
      memset(ISBN,0,21);
      std::string matched_str = match[1].str();
      matched_str.copy(ISBN, matched_str.size(), 0);
      bookManager.show("ISBN",ISBN);
    } else if (std::regex_match(cmd, match, shownameregex)) {
      if (curpri < 1) {std::cout << "Invalid\n";return;}
      char bookname[61];
      memset(bookname,0,61);
      std::string matched_str = match[1].str();
      matched_str.copy(bookname, matched_str.size(), 0);
      bookManager.show("name",bookname);
    } else if (std::regex_match(cmd, match, showauthorregex)) {
      if (curpri < 1) {std::cout << "Invalid\n";return;}
      char authorname[61];
      memset(authorname,0,61);
      std::string matched_str = match[1].str();
      matched_str.copy(authorname, matched_str.size(), 0);
      bookManager.show("auther",authorname);
    } else if (std::regex_match(cmd, match, showkeywordregex)) {
      if (curpri < 1) {std::cout << "Invalid\n";return;}
      char keyword[61];
      memset(keyword,0,61);
      std::string matched_str = match[1].str();
      matched_str.copy(keyword, matched_str.size(), 0);
      bookManager.show("keyword",keyword);
    } else if (std::regex_match(cmd, match, showallregex)) {
      if (curpri < 1) {std::cout << "Invalid\n";return;}
      bookManager.show("all",nullptr);
    } else if (std::regex_match(cmd, match, buyregex)) {
      if (curpri < 1) {std::cout << "Invalid\n";return;}
      char ISBN[21];
      memset(ISBN,0,21);
      std::string matched_str = match[1].str();
      matched_str.copy(ISBN, matched_str.size(), 0);
      long long Quantity = std::stoll(match[2].str());
      if (Quantity <= 0 || Quantity > 2147483647LL) {std::cout << "Invalid\n";return;}
      Book book;
      memcpy(book.ISBN,ISBN,21);
      std::vector<Book> found=bookManager.bo.find(book);
      if (found.empty()) {std::cout << "Invalid\n";return;}
      if (found.back().remain_num < Quantity) {std::cout << "Invalid\n";return;}
      Transaction txn;
      txn.type=true;
      txn.TotalCost=Quantity * found.back().price;
      bookManager.buybook(ISBN, Quantity);
      logmanager.insertTransaction(txn);
    } else if (std::regex_match(cmd, match, selectregex)) {
      if (curpri < 3) {std::cout << "Invalid\n";return;}
      char ISBN[21];
      memset(ISBN,0,21);
      std::string matched_str = match[1].str();
      matched_str.copy(ISBN, matched_str.size(), 0);
      bookManager.select(ISBN, accountManager);
    } else if (std::regex_match(cmd, match, modifyregex)) {
      if (curpri < 3) {std::cout << "Invalid\n";return;}
      Book tmp;
      if (accountManager.accounts.empty() || memcmp(accountManager.accounts.back().book.ISBN,tmp.ISBN,21)==0) {
        std::cout << "Invalid\n";return;
      }
      std::string params = match[1].str();
      std::regex isbnparam(R"(-ISBN=([\x21-\x7E]{1,20}))");
      std::regex nameparam("-name=\"([^\"]{1,60})\"");
      std::regex authorparam("-author=\"([^\"]{1,60})\"");
      std::regex keywordparam("-keyword=\"([^\"]{1,60})\"");
      std::regex priceparam(R"(-price=(\d{1,13}(\.\d{1,2})?))");
      bool hasISBN=false,hasName=false,hasAuthor=false,hasKeyword=false,hasPrice=false;
      char ISBN[21], bookname[61], authorname[61], keyword[61];
      memset(ISBN,0,21);memset(bookname,0,61);memset(authorname,0,61);memset(keyword,0,61);
      double price = -1;
      Book book = accountManager.accounts.back().book;
      std::istringstream iss(params);
      std::string part;
      while (iss >> part) {
        std::smatch pm;
        if (std::regex_match(part, pm, isbnparam)) {
          if (hasISBN) {std::cout << "Invalid\n";return;}
          hasISBN=true;
          std::string matched_str = pm[1].str();
          matched_str.copy(ISBN, matched_str.size(), 0);
        } else if (std::regex_match(part, pm, nameparam)) {
          if (hasName) {std::cout << "Invalid\n";return;}
          hasName=true;
          std::string matched_str = pm[1].str();
          matched_str.copy(bookname, matched_str.size(), 0);
        } else if (std::regex_match(part, pm, authorparam)) {
          if (hasAuthor) {std::cout << "Invalid\n";return;}
          hasAuthor=true;
          std::string matched_str = pm[1].str();
          matched_str.copy(authorname, matched_str.size(), 0);
        } else if (std::regex_match(part, pm, keywordparam)) {
          if (hasKeyword) {std::cout << "Invalid\n";return;}
          hasKeyword=true;
          std::string matched_str = pm[1].str();
          matched_str.copy(keyword, matched_str.size(), 0);
        } else if (std::regex_match(part, pm, priceparam)) {
          if (hasPrice) {std::cout << "Invalid\n";return;}
          hasPrice=true;
          price = std::stod(pm[1].str());
        } else {
          std::cout << "Invalid\n";return;
        }
      }
      if (!hasISBN && !hasName && !hasAuthor && !hasKeyword && !hasPrice) {
        std::cout << "Invalid\n";return;
      }
      if (hasKeyword) {
        std::vector<keywordchar> keys = tokekeyword(keyword);
        std::set<std::string> keySet;
        for (size_t i = 0; i < keys.size(); i++) {
          if (keySet.count(keys[i].ans)) {
            std::cout << "Invalid\n";return;
          }
          keySet.insert(keys[i].ans);
        }
      }
      if (hasISBN) {
        if (memcmp(book.ISBN,ISBN,21)==0) {std::cout << "Invalid\n";return;}
        Book checkBook;
        memcpy(checkBook.ISBN, ISBN, 21);
        std::vector<Book> existingBooks = bookManager.bo.find(checkBook);
        if (!existingBooks.empty()) {std::cout << "Invalid\n";return;}
        memcpy(book.ISBN, ISBN, 21);
        bookManager.modify(book,accountManager,1);
      }
      if (hasName) {
        memcpy(book.bookname, bookname, 61);
        bookManager.modify(book,accountManager,2);
      }
      if (hasAuthor) {
        memcpy(book.bookauther, authorname, 61);
        bookManager.modify(book,accountManager,3);
      }
      if (hasKeyword) {
        memcpy(book.keyword, keyword, 61);
        bookManager.modify(book,accountManager,4);
      }
      if (hasPrice) {
        book.price = price;
        bookManager.modify(book,accountManager,5);
      }
    } else if (std::regex_match(cmd, match, importregex)) {
      if (curpri < 3) {std::cout << "Invalid\n";return;}
      Book tmp;
      if (accountManager.accounts.empty() || memcmp(accountManager.accounts.back().book.ISBN,tmp.ISBN,21)==0) {
        std::cout << "Invalid\n";return;
      }
      long long Quantity = std::stoll(match[1].str());
      double TotalCost = std::stod(match[2].str());
      if (Quantity <= 0 || Quantity > 2147483647LL || TotalCost <= 0) {std::cout << "Invalid\n";return;}
      bookManager.import(Quantity, TotalCost, accountManager);
      Transaction txn;
      txn.TotalCost=TotalCost;
      txn.type=false;
      logmanager.insertTransaction(txn);
    }
    else if (std::regex_match(cmd, match, logregex)) {
      if (curpri != 7) {std::cout << "Invalid\n";return;}
      logmanager.generateLog();
    }
    else if (std::regex_match(cmd, match, reportfinanceregex)) {
      if (curpri != 7) {std::cout << "Invalid\n";return;}
      logmanager.generateFinanceReport();
    }
    else if (std::regex_match(cmd, match, reportemployeeregex)) {
      if (curpri != 7) {std::cout << "Invalid\n";return;}
      logmanager.generateEmployeeReport();
    }
    else std::cout << "Invalid\n";
  }
};