#include "account_manager.h"
#include <cstring>
#include <iostream>
#include <vector>
void User::changepass (char* new_pass) {
  memcpy (password,new_pass,31 );
}
void AccountManager::login (char *userid,char* pas) {
	User usertmp;
	memcpy (usertmp.id,userid,31);
	std::vector<User> found=acc.find(usertmp);
	if (found.empty()) {std::cout << "Invalid\n";return;}
	User users=found.back();
	if (memcmp(users.password,pas,31) != 0) {std::cout << "Invalid\n";return;}
	ubook uboo;
	uboo.user=users;
	accounts.push_back (uboo);
}
void AccountManager::login(char *userid) {
	User usertmp;
	memcpy (usertmp.id,userid,31);
	std::vector<User> found=acc.find(usertmp);
	if (found.empty()) {std::cout << "Invalid\n";return;}
	User users=found.back();
	int curpri=0;
	if (!accounts.empty()) curpri=accounts.back().user.privilege;
	if (curpri <= users.privilege) {std::cout << "Invalid\n";return;}
	ubook uboo;
	uboo.user=users;
	accounts.push_back (uboo);
}
void AccountManager::logout () {
	if (accounts.empty()) {std::cout << "Invalid\n";return;}
	accounts.pop_back();
}
void AccountManager::reg (char *userid, char *pas, char *name) {
	User usertmp;
	memcpy (usertmp.id,userid,31);
	std::vector<User> found=acc.find(usertmp);
	if (!found.empty()) {std::cout << "Invalid\n";return;}
	User users;
	memcpy (users.username,name,31);
	memcpy (users.id,userid,31);
	memcpy (users.password,pas,31);
	users.privilege=1;
	acc.insert(users);
}
void AccountManager::changeinf (char *userid, char *old_pas, char *new_pas) {
	int curpri=0;
	if (!accounts.empty()) curpri=accounts.back().user.privilege;
	if (curpri < 1) {std::cout << "Invalid\n";return;}
	User usertmp;
	memcpy (usertmp.id,userid,31);
	std::vector<User> found=acc.find(usertmp);
	if (found.empty()) {std::cout << "Invalid\n";return;}
	User users=found.back();
	if (memcmp(old_pas,users.password,31) != 0) {std::cout << "Invalid\n";return;}
	acc.deleteinformation(users);
	memcpy(users.password,new_pas,31);
	acc.insert(users);
}
void AccountManager::changeinf(char *userid,  char *new_pas) {
	int curpri=0;
	if (!accounts.empty()) curpri=accounts.back().user.privilege;
	if (curpri != 7) {std::cout << "Invalid\n";return;}
	User usertmp;
	memcpy (usertmp.id,userid,31);
	std::vector<User> found=acc.find(usertmp);
	if (found.empty()) {std::cout << "Invalid\n";return;}
	User users=found.back();
	acc.deleteinformation(users);
	memcpy(users.password,new_pas,31);
	acc.insert(users);
}
void AccountManager::useradd(char *userid, char *pas, int pri, char *username) {
	int curpri=0;
	if (!accounts.empty()) curpri=accounts.back().user.privilege;
	if (curpri <= pri or curpri < 3) {std::cout << "Invalid\n";return;}
	User usertmp;
	memcpy (usertmp.id,userid,31);
	std::vector<User> found=acc.find(usertmp);
	if (!found.empty()) {std::cout << "Invalid\n";return;}
	User users;
	memcpy (users.id,userid,31);
	memcpy (users.password,pas,31);
	users.privilege=pri;
	memcpy (users.username,username,31);
	acc.insert(users);
}
void AccountManager::deleteuser(char* userid) {
	int curpri=0;
	if (!accounts.empty()) curpri=accounts.back().user.privilege;
	if (curpri != 7) {std::cout << "Invalid\n";return;}
	for (auto it=accounts.begin();it != accounts.end();it++) {
		if (memcmp((*it).user.id,userid,31) == 0) {std::cout << "Invalid\n";return;}
	}
	User usertmp;
	memcpy (usertmp.id,userid,31);
	std::vector<User> found=acc.find(usertmp);
	if (found.empty()) {std::cout << "Invalid\n";return;}
	acc.deleteinformation (found.back());
}