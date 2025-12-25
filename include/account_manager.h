#pragma once
#include "/home/lmc123456/Bookstore-2025/include/book.h"
#include "utils.h"
#include <cstring>
#include <fstream>
#include <vector>
const int maxsize = 30;
class User {
public:
  char username[30];
  char id[30];
  char password[30];
  int privilege = 0;

  User() {
    memset(username, 0, 30);
    memset(id, 0, 30);
    memset(password, 0, 30);
    privilege = 0;
  }
  User(char *name, char *ID, char *pas, int pri) {
    for (int i = 0; i < maxsize; i++) {
      username[i] = name[i];
      id[i] = ID[i];
      password[i] = pas[i];
      privilege = pri;
    }
  }
  bool operator<(const User &u) const { return strcmp(id, u.id) < 0; }
  bool operator==(const User &u) const { return strcmp(id, u.id) == 0; }
  void changepass(char *new_pas);
};
struct ubook {
  User user;
  Book book;
};
class AccountManager {
private:
  memoryriver<User, block<User>> acc;

public:
  std::vector<ubook> accounts;
  AccountManager() {
    acc.f.open("accounts.dat", std::ios::in | std::ios::out | std::ios::binary);
    User user0 ;
    char root[30]="root";
    char sjtu[30]="sjtu";
    memcpy (user0.username,root,30);
    memcpy (user0.id,root,30);
    memcpy (user0.password,sjtu,30);
    user0.privilege=7;
    acc.insert(user0);
  }
  ~AccountManager() { acc.f.close(); }
  void login(char *userid, char *pas);
  void login(char *userid);
  void logout();
  void reg(char *userid, char *pas, char *name);
  void changeinf(char *userid, char *old_pas, char *new_pas);
  void changeinf(char *userid, char *new_pas);
  void useradd(char *userid, char *pas, int pri, char *username);
  void deleteuser(char *userid);
};