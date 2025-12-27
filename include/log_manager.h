#pragma once
#include "utils.h"
#include <cstring>
#include <vector>
struct Transaction {
  public:
  int index=0;
  double TotalCost=0;
  bool type=0;
  bool operator==(Transaction other) {
    if (this->index == other.index) return true;
    return  false;
  }
  bool operator<(Transaction other) {
    if (this->index < other.index) return true;
    return  false;
  }
  bool operator<=(Transaction other) {
    if (this->index <= other.index) return true;
    return  false;
  }
  bool operator>(Transaction other) {
    if (this->index > other.index) return true;
    return  false;
  }
  bool operator>=(Transaction other) {
    if (this->index >= other.index) return true;
    return  false;
  }
};
class LogManager {
  public:
  int i=0;
  memoryriver <Transaction,block<Transaction>> lo;
  std::fstream countfile;
  LogManager () {
    lo.initialise("transaction.dat");
    countfile.open("transaction_count.dat",std::ios::in|std::ios::out|std::ios::binary);
    if (!countfile) {
      countfile.clear();
      std::ofstream o("transaction_count.dat",std::ios::binary);
      long long zero=0;
      o.write((char*)&zero,sizeof(long long));
      o.close();
      countfile.open("transaction_count.dat",std::ios::in|std::ios::out|std::ios::binary);
    }
    countfile.seekg(0);
    countfile.read((char*)&count,sizeof(long long));
    i=count;
  }
  ~LogManager () {
    countfile.seekp(0);
    countfile.write((char*)&count,sizeof(long long));
    countfile.close();
    lo.f.close();
  }
  long long count=0;
  void show (long long count_);
  void show ();
  void generateFinanceReport();
  void generateEmployeeReport();
  void generateLog();
  void addlog ();
  void insertTransaction (Transaction& txn); 
};