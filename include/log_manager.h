#pragma once
#include "utils.h"
#include <cstring>
#include <vector>
struct Transaction {
  public:
  int index=0;
  long long TotalCost=0;
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
  int i=1;
  memoryriver <Transaction,block<Transaction>> lo;
  LogManager () {lo.f.open("transaction.dat",std::ios::in|std::ios::out|std::ios::binary);}
  ~LogManager () {lo.f.close();}
  long long count=0;
  void show (long long count_);
  void show ();
  void generateFinanceReport();
  void generateEmployeeReport();
  void generateLog();
  void addlog ();
  void insertTransaction (Transaction& txn); 
};