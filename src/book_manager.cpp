#include "/home/lmc123456/Bookstore-2025/include/book_manager.h"
#include <fstream>
#include <iomanip>
#include <iostream>
#include <cstring>
#include <vector>
void BookManager::buybook (char* IS,long long buy_num) {
  Book booktmp;
  Book tmp;
  memcpy(booktmp.ISBN,IS,20);
  std::vector<Book> book_=bo.find(booktmp);
  if (book_.empty() == true or book_.back().remain_num < buy_num) {
    std::cout  << "Invalid\n";
    return;
  }
  Book boo=book_.back();
  std::cout << std::fixed << std::setprecision(2) << boo.price * buy_num;
  bo.deleteinformation(boo);
  boo.remain_num-=buy_num;
  bo.insert(boo);

}
void BookManager::select (char* ISBN,AccountManager& account_manager) {
  Book tmp;
  Book booktmp;
  memcpy(booktmp.ISBN,ISBN,20);
  std::vector<Book> book_=bo.find(booktmp);
  if (book_.empty() == true) {
    memcpy(tmp.ISBN,ISBN,20);
    bo.insert(tmp);
  }
  Book boo=book_.back();
  account_manager.accounts.back().book = boo;
}
void BookManager::modify (Book new_inf,AccountManager& account_manager,int flag) {
  Book tmp;
  if ((flag == 1 and memcmp(new_inf.ISBN , account_manager.accounts.back().book.ISBN,20) == 0) or account_manager.accounts.back().book.if_same(tmp)) {
    std::cout << "Invalid\n";
    return;
  }
  tmp=account_manager.accounts.back().book;
  if (flag == 1) {
    bo.deleteinformation(tmp);
    bo.insert(new_inf);
    Bookbookauther bookauthertmp;
    memcpy(bookauthertmp.bookauther,tmp.bookauther,60);
    memcpy(bookauthertmp.ISBN,tmp.ISBN,20);
    bookauther.deleteinformation(bookauthertmp);
    memcpy(bookauthertmp.ISBN,new_inf.ISBN,20);
    bookauther.insert(bookauthertmp);
    Bookbookname bookname_;
    memcpy(bookname_.bookname,tmp.bookname,60);
    memcpy(bookname_.ISBN,tmp.ISBN,20);
    bookname.deleteinformation(bookname_);
    memcpy(bookname_.ISBN,new_inf.ISBN,20);
    bookname.insert(bookname_);
    std::vector <keywordchar> key;
    key=tokekeyword(tmp.keyword);
    for (int i=0;i <= key.size()-1;i++) {
      keywordbook keyw;
      memcpy(keyw.keyword,key[i].ans,60);
      memcpy(keyw.ISBN,tmp.ISBN,20);
      keywordbook_.deleteinformation(keyw);
      memcpy(keyw.ISBN,new_inf.ISBN,20);
      keywordbook_.insert(keyw);
    }
  }
  if (flag == 2) {
    bo.deleteinformation(tmp);
    bo.insert(new_inf);
    Bookbookname bookname_;
    memcpy(bookname_.bookname,tmp.bookname,60);
    memcpy(bookname_.ISBN,tmp.ISBN,20);
    bookname.deleteinformation(bookname_);
    memcpy(bookname_.bookname,new_inf.bookname,60);
    bookname.insert(bookname_);
  }
  if (flag == 3) {
    bo.deleteinformation(tmp);
    bo.insert(new_inf);
    Bookbookauther aut;
    memcpy(aut.bookauther,tmp.bookauther,60);
    memcpy(aut.ISBN,tmp.ISBN,20);
    bookauther.deleteinformation(aut);
    memcpy (aut.bookauther,new_inf.bookauther,60);
    bookauther.insert(aut);
  }
  if (flag == 4) {
    bo.deleteinformation(tmp);
    bo.insert(new_inf);
    std::vector<keywordchar> key=tokekeyword(tmp.keyword);
    for (int i=0;i <= key.size()-1;i++) {
      keywordbook keyw;
      memcpy(keyw.keyword,key[i].ans,60);
      memcpy(keyw.ISBN,tmp.ISBN,20);
      keywordbook_.deleteinformation(keyw);
    }
    key.clear();
    key=tokekeyword(new_inf.keyword);
    for (int i=0;i <= key.size()-1;i++) {
      keywordbook keyw;
      memcpy(keyw.keyword,key[i].ans,60);
      memcpy(keyw.ISBN,tmp.ISBN,20);
      keywordbook_.deleteinformation(keyw);
    }
  }
  if (flag == 5) {
    bo.deleteinformation(tmp);
    bo.insert(new_inf);
  }
}
void BookManager::import (long long Quantity, long long TotalCost,AccountManager& account_manager) {
  Book tmp;
  if (memcmp(tmp.ISBN , account_manager.accounts.back().book.ISBN,20) == 0) return;
  bo.deleteinformation(tmp);
  tmp=account_manager.accounts.back().book;
  tmp.remain_num+=Quantity;
  bo.insert(tmp);
}
void BookManager::show (std::string type,char* inf) {
  std::vector<Book> boo;
  if (type == "ISBN") {
    Book tmp;
    memcpy(tmp.ISBN,inf,20);
    boo=bo.find(tmp);
    for (int i=0;i <= boo.size()-1;i++) {
      std::cout << boo[i].ISBN << '\t' << boo[i].bookname << '\t' << boo[i].bookauther << '\t' << boo[i].keyword << '\t' << boo[i].price << 't' << boo[i].remain_num << '\n';
    }
  }
  else if (type == "name") {
    Bookbookname bookname_;
    memcpy(bookname_.bookname,inf,60);
    std::vector<Bookbookname> boona;
    boona=bookname.findindex(bookname_);
    for (int i=0;i <= boona.size()-1;i++) {
      Book tmp;
      memcpy(tmp.ISBN,boona[i].ISBN,20);
      boo=bo.find(tmp);
      for (int i=0;i <= boo.size()-1;i++) {
        std::cout << boo[i].ISBN << '\t' << boo[i].bookname << '\t' << boo[i].bookauther << '\t' << boo[i].keyword << '\t' << boo[i].price << 't' << boo[i].remain_num << '\n';
      }
    }
  }
  else if (type == "auther") {
    Bookbookauther bookauther_;
    memcpy(bookauther_.bookauther,inf,60);
    std::vector<Bookbookauther> booau;
    booau=bookauther.findindex(bookauther_);
    for (int i=0;i <= booau.size()-1;i++) {
      Book tmp;
      memcpy(tmp.ISBN,booau[i].ISBN,20);
      boo=bo.find(tmp);
      for (int i=0;i <= boo.size()-1;i++) {
        std::cout << boo[i].ISBN << '\t' << boo[i].bookname << '\t' << boo[i].bookauther << '\t' << boo[i].keyword << '\t' << boo[i].price << 't' << boo[i].remain_num << '\n';
      }
    }
  }
  else if (type == "keyword") {
    keywordbook keywo;
    memcpy(keywo.keyword,inf,60);
    std::vector<keywordbook > bookey;
    bookey=keywordbook_.findindex(keywo);
    for (int i=0;i <= bookey.size()-1;i++) {
      Book tmp;
      memcpy(tmp.ISBN,bookey[i].ISBN,20);
      boo=bo.find(tmp);
      for (int i=0;i <= boo.size()-1;i++) {
        std::cout << boo[i].ISBN << '\t' << boo[i].bookname << '\t' << boo[i].bookauther << '\t' << boo[i].keyword << '\t' << boo[i].price << 't' << boo[i].remain_num << '\n';
      }
    }
  }
}