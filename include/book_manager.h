#pragma once
#include "/home/lmc123456/Bookstore-2025/include/account_manager.h"
#include "/home/lmc123456/Bookstore-2025/include/book.h"
#include "/home/lmc123456/Bookstore-2025/include/utils.h"
#include <cstring>
#include <vector>
class BookManager {
public:
  memoryriver<Book, block<Book>> bo;
  memoryriver<Bookbookname,block<Bookbookname>> bookname;
  memoryriver<Bookbookauther, block<Bookbookauther>> bookauther;
  memoryriver<keywordbook, block<keywordbook>> keywordbook_;
  BookManager() {
    bo.f.open("booksISBN.dat", std::ios::in | std::ios::out | std::ios::binary);
    bookname.f.open("bookbookname.dat", std::ios::in | std::ios::out | std::ios::binary);
    bookauther.f.open("booksbookauther.dat", std::ios::in | std::ios::out | std::ios::binary);
    keywordbook_.f.open("bookskeyword.dat", std::ios::in | std::ios::out | std::ios::binary);
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
  void import(long long Quantity, long long TotalCost,
              AccountManager &account_manager);
};