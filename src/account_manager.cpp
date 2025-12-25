#include "/home/lmc123456/Bookstore-2025/include/account_manager.h"
#include <cstring>
#include <vector>
void User::changepass (char* new_pass) {
  memcpy (password,new_pass,30 );
}
void AccountManager::login (char *userid,char* pas) {
	char* true_pass=new char[30];
	User usertmp;
	memcpy (usertmp.id,userid,30);
	User users=acc.find(usertmp).back();
	memcpy(true_pass,users.password,30);
	ubook uboo;
	uboo.user=users;
	if (memcmp(true_pass,pas,30) == 0) accounts.push_back (uboo);
}
void AccountManager::login(char *userid) {
	User usertmp;
	memcpy (usertmp.id,userid,30);
	User users=acc.find(usertmp).back();
	if (accounts.back().user.privilege >= users.privilege) return;
	ubook uboo;
	uboo.user=users;
	accounts.push_back (uboo);
}
void AccountManager::logout () {
	if (accounts.back().user.privilege < 1) return;
	accounts.pop_back();
}
void AccountManager::reg (char *userid, char *pas, char *name) {
	User users;
	memcpy (users.username,name,30);
	memcpy (users.id,userid,30);
	memcpy (users.password,pas,30);
	acc.insert(users);
}
void AccountManager::changeinf (char *userid, char *old_pas, char *new_pas) {
	User com;
	if (accounts.back().user.privilege < 1) return;
	User usertmp;
	memcpy (usertmp.id,userid,30);
	User users=acc.find(usertmp).back();
	if (memcmp(com.id,users.id,30) != 0) return;
	if (memcmp(old_pas,users.password,30) != 0) return;
	acc.deleteinformation(users);
	memcpy(users.password,new_pas,30);
	acc.insert(users);
}
void AccountManager::changeinf(char *userid,  char *new_pas) {
	if (accounts.back().user.privilege != 7) return;
	User com;
	User usertmp;
	memcpy (usertmp.id,userid,30);
	User users=acc.find(usertmp).back();
	if (memcmp(com.id,users.id,30) != 0) return;
	acc.deleteinformation(users);
	memcpy(users.password,new_pas,30);
	acc.insert(users);
}
void AccountManager::useradd(char *userid, char *pas, int pri, char *username) {
	User users;
	if (accounts.back().user.privilege <= pri or accounts.back().user.privilege < 3) return;
	User usertmp;
	memcpy (usertmp.id,userid,30);
	User userstmp=acc.find(usertmp).back();
	if (!(userstmp == users)) return;
	memcpy (users.id,userid,30);
	memcpy (users.password,pas,30);
	users.privilege=pri;
	memcpy (users.username,username,30);
	acc.insert(users);
}
void AccountManager::deleteuser(char* userid) {
	if (accounts.back().user.privilege != 7) return;
	for (auto it=accounts.begin();it != accounts.end();it++) {
		if (memcmp((*it).user.id,userid,30) == 0) return;
	}
	User usertmp;
	memcpy (usertmp.id,userid,30);
	acc.deleteinformation (usertmp);
}

