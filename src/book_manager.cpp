#include "book_manager.h"
#include <fstream>
#include <iomanip>
#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>
void BookManager::buybook (char* IS,long long buy_num) {
  Book booktmp;
  memcpy(booktmp.ISBN,IS,21);
  std::vector<Book> book_=bo.find(booktmp);
  if (book_.empty() == true or book_.back().remain_num < buy_num) {
    std::cout  << "Invalid\n";
    return;
  }
  Book boo=book_.back();
  std::cout << std::fixed << std::setprecision(2) << boo.price * buy_num << "\n";
  bo.deleteinformation(boo);
  boo.remain_num-=buy_num;
  bo.insert(boo);

}
void BookManager::select (char* ISBN,AccountManager& account_manager) {
  Book tmp;
  Book booktmp;
  memcpy(booktmp.ISBN,ISBN,21);
  std::vector<Book> book_=bo.find(booktmp);
  if (book_.empty() == true) {
    memcpy(tmp.ISBN,ISBN,21);
    bo.insert(tmp);
    account_manager.accounts.back().book = tmp;
    return;
  }
  Book boo=book_.back();
  account_manager.accounts.back().book = boo;
}
void BookManager::modify (Book new_inf,AccountManager& account_manager,int flag) {
  Book tmp;
  if ((flag == 1 and memcmp(new_inf.ISBN , account_manager.accounts.back().book.ISBN,21) == 0) or account_manager.accounts.back().book.if_same(tmp)) {
    std::cout << "Invalid\n";
    return;
  }
  tmp=account_manager.accounts.back().book;
  if (flag == 1) {
    bo.deleteinformation(tmp);
    bo.insert(new_inf);
    Bookbookauther bookauthertmp;
    memcpy(bookauthertmp.bookauther,tmp.bookauther,61);
    memcpy(bookauthertmp.ISBN,tmp.ISBN,21);
    bookauther.deleteinformation(bookauthertmp);
    memcpy(bookauthertmp.ISBN,new_inf.ISBN,21);
    bookauther.insert(bookauthertmp);
    Bookbookname bookname_;
    memcpy(bookname_.bookname,tmp.bookname,61);
    memcpy(bookname_.ISBN,tmp.ISBN,21);
    bookname.deleteinformation(bookname_);
    memcpy(bookname_.ISBN,new_inf.ISBN,21);
    bookname.insert(bookname_);
    std::vector <keywordchar> key;
    key=tokekeyword(tmp.keyword);
    for (size_t i=0;i < key.size();i++) {
      keywordbook keyw;
      memcpy(keyw.keyword,key[i].ans,61);
      memcpy(keyw.ISBN,tmp.ISBN,21);
      keywordbook_.deleteinformation(keyw);
      memcpy(keyw.ISBN,new_inf.ISBN,21);
      keywordbook_.insert(keyw);
    }
  }
  if (flag == 2) {
    bo.deleteinformation(tmp);
    bo.insert(new_inf);
    Bookbookname bookname_;
    memcpy(bookname_.bookname,tmp.bookname,61);
    memcpy(bookname_.ISBN,tmp.ISBN,21);
    bookname.deleteinformation(bookname_);
    memcpy(bookname_.bookname,new_inf.bookname,61);
    bookname.insert(bookname_);
  }
  if (flag == 3) {
    bo.deleteinformation(tmp);
    bo.insert(new_inf);
    Bookbookauther aut;
    memcpy(aut.bookauther,tmp.bookauther,61);
    memcpy(aut.ISBN,tmp.ISBN,21);
    bookauther.deleteinformation(aut);
    memcpy (aut.bookauther,new_inf.bookauther,61);
    bookauther.insert(aut);
  }
  if (flag == 4) {
    bo.deleteinformation(tmp);
    bo.insert(new_inf);
    std::vector<keywordchar> key=tokekeyword(tmp.keyword);
    for (size_t i=0;i < key.size();i++) {
      keywordbook keyw;
      memcpy(keyw.keyword,key[i].ans,61);
      memcpy(keyw.ISBN,tmp.ISBN,21);
      keywordbook_.deleteinformation(keyw);
    }
    key.clear();
    key=tokekeyword(new_inf.keyword);
    for (size_t i=0;i < key.size();i++) {
      keywordbook keyw;
      memcpy(keyw.keyword,key[i].ans,61);
      memcpy(keyw.ISBN,new_inf.ISBN,21);
      keywordbook_.insert(keyw);
    }
  }
  if (flag == 5) {
    bo.deleteinformation(tmp);
    bo.insert(new_inf);
  }
  account_manager.accounts.back().book=new_inf;
}
void BookManager::import (long long Quantity, double TotalCost,AccountManager& account_manager) {
  Book tmp;
  if (memcmp(tmp.ISBN , account_manager.accounts.back().book.ISBN,21) == 0) {std::cout << "Invalid\n";return;}
  tmp=account_manager.accounts.back().book;
  bo.deleteinformation(tmp);
  tmp.remain_num+=Quantity;
  bo.insert(tmp);
  account_manager.accounts.back().book=tmp;
}
void BookManager::show (std::string type,char* inf) {
  std::vector<Book> boo;
  if (type == "ISBN") {
    Book tmp;
    memcpy(tmp.ISBN,inf,21);
    boo=bo.find(tmp);
    if (boo.empty()) {std::cout << "\n";return;}
    for (size_t i=0;i < boo.size();i++) {
      std::cout << boo[i].ISBN << '\t' << boo[i].bookname << '\t' << boo[i].bookauther << '\t' << boo[i].keyword << '\t' << std::fixed << std::setprecision(2) << boo[i].price << '\t' << boo[i].remain_num << '\n';
    }
  }
  else if (type == "name") {
    Bookbookname bookname_;
    memcpy(bookname_.bookname,inf,61);
    std::vector<Bookbookname> boona;
    boona=bookname.findindex(bookname_);
    if (boona.empty()) {std::cout << "\n";return;}
    std::vector<Book> allbooks;
    for (size_t i=0;i < boona.size();i++) {
      Book tmp;
      memcpy(tmp.ISBN,boona[i].ISBN,21);
      boo=bo.find(tmp);
      for (size_t j=0;j < boo.size();j++) {
        allbooks.push_back(boo[j]);
      }
    }
    std::sort(allbooks.begin(), allbooks.end());
    for (size_t i=0;i < allbooks.size();i++) {
      std::cout << allbooks[i].ISBN << '\t' << allbooks[i].bookname << '\t' << allbooks[i].bookauther << '\t' << allbooks[i].keyword << '\t' << std::fixed << std::setprecision(2) << allbooks[i].price << '\t' << allbooks[i].remain_num << '\n';
    }
  }
  else if (type == "auther") {
    Bookbookauther bookauther_;
    memcpy(bookauther_.bookauther,inf,61);
    std::vector<Bookbookauther> booau;
    booau=bookauther.findindex(bookauther_);
    if (booau.empty()) {std::cout << "\n";return;}
    std::vector<Book> allbooks;
    for (size_t i=0;i < booau.size();i++) {
      Book tmp;
      memcpy(tmp.ISBN,booau[i].ISBN,21);
      boo=bo.find(tmp);
      for (size_t j=0;j < boo.size();j++) {
        allbooks.push_back(boo[j]);
      }
    }
    std::sort(allbooks.begin(), allbooks.end());
    for (size_t i=0;i < allbooks.size();i++) {
      std::cout << allbooks[i].ISBN << '\t' << allbooks[i].bookname << '\t' << allbooks[i].bookauther << '\t' << allbooks[i].keyword << '\t' << std::fixed << std::setprecision(2) << allbooks[i].price << '\t' << allbooks[i].remain_num << '\n';
    }
  }
  else if (type == "keyword") {
    keywordbook keywo;
    memcpy(keywo.keyword,inf,61);
    std::vector<keywordbook > bookey;
    bookey=keywordbook_.findindex(keywo);
    if (bookey.empty()) {std::cout << "\n";return;}
    std::vector<Book> allbooks;
    for (size_t i=0;i < bookey.size();i++) {
      Book tmp;
      memcpy(tmp.ISBN,bookey[i].ISBN,21);
      boo=bo.find(tmp);
      for (size_t j=0;j < boo.size();j++) {
        allbooks.push_back(boo[j]);
      }
    }
    std::sort(allbooks.begin(), allbooks.end());
    for (size_t i=0;i < allbooks.size();i++) {
      std::cout << allbooks[i].ISBN << '\t' << allbooks[i].bookname << '\t' << allbooks[i].bookauther << '\t' << allbooks[i].keyword << '\t' << std::fixed << std::setprecision(2) << allbooks[i].price << '\t' << allbooks[i].remain_num << '\n';
    }
  }
  else if (type == "all") {
    std::vector<Book> allbooks;
    long long p = 0;
    while (p != -1) {
      block<Book> b;
      bo.rd(p, b);
      for (int i = 0; i < b.cnt; i++) {
        allbooks.push_back(b.d[i]);
      }
      p = b.nxt;
    }
    std::sort(allbooks.begin(), allbooks.end());
    if (allbooks.empty()) {std::cout << "\n";return;}
    for (size_t i=0;i < allbooks.size();i++) {
      std::cout << allbooks[i].ISBN << '\t' << allbooks[i].bookname << '\t' << allbooks[i].bookauther << '\t' << allbooks[i].keyword << '\t' << std::fixed << std::setprecision(2) << allbooks[i].price << '\t' << allbooks[i].remain_num << '\n';
    }
  }
}