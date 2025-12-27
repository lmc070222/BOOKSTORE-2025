#pragma once
#include <cstring>
#include <vector>
class Book {
public:
  char ISBN[21];
  char bookname[61];
  char bookauther[61];
  char keyword[61];
  long long remain_num = 0;
  double price;
  Book &operator=(const Book &other) {
    memcpy(ISBN, other.ISBN, 21);
    memcpy(this->bookauther, other.bookauther, 61);
    memcpy(bookname, other.bookname, 61);
    memcpy(keyword, other.keyword, 61);
    remain_num = other.remain_num;
    price = other.price;
    return *this;
  }
  bool if_same(const Book &other) {
    if (memcmp(ISBN, other.ISBN, 21) == 0 and
        memcmp(this->bookauther, other.bookauther, 61) == 0 and
        memcmp(bookname, other.bookname, 61) == 0 and
        memcmp(keyword, other.keyword, 61) == 0 and
        remain_num == other.remain_num and price == other.price)
      return true;
    return false;
  }
  Book() {
    memset(ISBN, 0, sizeof(ISBN));
    memset(bookname, 0, sizeof(bookname));
    memset(bookauther, 0, sizeof(bookauther));
    memset(keyword, 0, sizeof(keyword));
    remain_num = 0;
    price = 0.0;
  }
  bool operator<(const Book &b) const { return strcmp(ISBN, b.ISBN) < 0; }
  bool operator==(const Book &b) const { return strcmp(ISBN, b.ISBN) == 0; }
};
class Bookbookname {
  public:
  char ISBN[21];
  char bookname[61];
  Bookbookname &operator=(const Bookbookname &other) {
    memcpy(ISBN, other.ISBN, 21);
    memcpy(bookname, other.bookname, 61);
    return *this;
  }
  Bookbookname() {
    memset(ISBN, 0, sizeof(ISBN));
    memset(bookname, 0, sizeof(bookname));
  }
  bool operator<(const Bookbookname &b) const { return (strcmp(bookname, b.bookname) < 0) or (strcmp(bookname, b.bookname) == 0 and strcmp(ISBN, b.ISBN) < 0); }
  bool operator==(const Bookbookname &b) const { return strcmp(bookname, b.bookname) == 0 and strcmp(ISBN,b.ISBN) == 0 ; }
  int compare (const Bookbookname &a,const Bookbookname &b) {
    if (strcmp(a.bookname, b.bookname) < 0) return -1;
    if (strcmp(a.bookname, b.bookname) == 0) return 0;
    if (strcmp(a.bookname, b.bookname) > 0 ) return 1;
    return 1;
  }
};
class Bookbookauther {
  public:
  char ISBN[21];
  char bookauther[61];
  Bookbookauther &operator=(const Bookbookauther &other) {
    memcpy(ISBN, other.ISBN, 21);
    memcpy(this->bookauther, other.bookauther, 61);
    return *this;
  }
  Bookbookauther() {
    memset(ISBN, 0, sizeof(ISBN));
    memset(bookauther, 0, sizeof(bookauther));
  }
  bool operator<(const Bookbookauther &b) const { return (strcmp(bookauther, b.bookauther) < 0) or (strcmp(bookauther, b.bookauther) == 0 and strcmp(ISBN,b.ISBN) < 0); }
  bool operator==(const Bookbookauther &b) const { return (strcmp(bookauther, b.bookauther) == 0 and strcmp(ISBN,b.ISBN) == 0); }
  int compare (const Bookbookauther &a,const Bookbookauther &b) {
    if (strcmp(a.bookauther, b.bookauther) < 0) return -1;
    if (strcmp(a.bookauther, b.bookauther) == 0) return 0;
    if (strcmp(a.bookauther, b.bookauther) > 0 ) return 1;
    return 1;
  }
};
class keywordbook {
  public:
  char ISBN[21];
  char keyword[61];
  keywordbook &operator=(const keywordbook &other) {
    memcpy(ISBN, other.ISBN, 21);
    memcpy(keyword, other.keyword, 61);
    return *this;
  }
  bool operator<(const keywordbook &b) const { return strcmp(keyword, b.keyword) < 0 or (strcmp(keyword,b.keyword) == 0 and strcmp(ISBN,b.ISBN) < 0); }
  bool operator==(const keywordbook &b) const { return strcmp(keyword, b.keyword) == 0 and strcmp(ISBN,b.ISBN) == 0; }
   int compare (const keywordbook &a,const keywordbook &b) {
    if (strcmp(a.keyword, b.keyword) < 0) return -1;
    if (strcmp(a.keyword, b.keyword) == 0) return 0;
    if (strcmp(a.keyword, b.keyword) > 0 ) return 1;
    return 1;
  }
};