#pragma once
#include "account_manager.h"
#include "book.h"
#include "utils.h"
#include <cstring>
#include <vector>
class BookManager {
public:
  memoryriver<Book, block<Book>> bo;
  memoryriver<Bookbookname,block<Bookbookname>> bookname;
  memoryriver<Bookbookauther, block<Bookbookauther>> bookauther;
  memoryriver<keywordbook, block<keywordbook>> keywordbook_;
  BookManager() {
    bo.initialise("booksISBN.dat");
    bookname.initialise("bookbookname.dat");
    bookauther.initialise("booksbookauther.dat");
    keywordbook_.initialise("bookskeyword.dat");
  }
  ~BookManager() { 
    bo.f.close();
    bookname.f.close();
    bookauther.f.close();
    keywordbook_.f.close();
   }
  Book selectedBook;
  void show(std::string type,
            char *inf); 
  void buybook(char *IS, long long buy_num);
  void select(char *ISBN, AccountManager &account_manager);
  void modify(Book new_inf, AccountManager &account_manager,int flag);
  void import(long long Quantity, double TotalCost,
              AccountManager &account_manager);
};