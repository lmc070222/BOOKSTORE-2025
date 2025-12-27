#pragma once
#include "book.h"
#include "utils.h"
#include <cstring>
#include <fstream>
#include <vector>
const int maxsize = 31;
class User {
public:
  char username[31];
  char id[31];
  char password[31];
  int privilege = 0;

  User() {
    memset(username, 0, 31);
    memset(id, 0, 31);
    memset(password, 0, 31);
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
    acc.initialise("accounts.dat");
    User user0 ;
    char root[31]="root";
    char sjtu[31]="sjtu";
    memcpy (user0.username,root,31);
    memcpy (user0.id,root,31);
    memcpy (user0.password,sjtu,31);
    user0.privilege=7;
    std::vector<User> found=acc.find(user0);
    if (found.empty()) acc.insert(user0);
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