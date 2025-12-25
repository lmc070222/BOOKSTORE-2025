#include "/home/lmc123456/Bookstore-2025/include/log_manager.h"
#include <cstring>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>

void LogManager::show(long long count_) {
  double totalIncome = 0.0;
  double totalExpenditure = 0.0;
  if (count_ > count || count_ < 0) {
    return;
  }
  for (long long i = count; i > count - count_; i--) {
    Transaction tmp;
    tmp.index = i;
    Transaction txn = lo.find(tmp).back(); // 查找交易
    if (txn.type) {
      totalIncome += txn.TotalCost;
    } else {
      totalExpenditure += txn.TotalCost;
    }
  }
  std::cout << "+ " << std::fixed << std::setprecision(2) << totalIncome
            << " - " << std::fixed << std::setprecision(2) << totalExpenditure
            << "\n";
}
void LogManager::show() {
  double totalIncome = 0.0;
  double totalExpenditure = 0.0;
  for (long long i = 1; i <= count; i++) {
    Transaction tmp;
    tmp.index = i;
    Transaction txn = lo.find(tmp).back();
    if (txn.type) {
      totalIncome += txn.TotalCost;
    } else {
      totalExpenditure += txn.TotalCost;
    }
  }
  std::cout << "+ " << std::fixed << std::setprecision(2) << totalIncome
            << " - " << std::fixed << std::setprecision(2) << totalExpenditure
            << "\n";
}
void LogManager::generateFinanceReport() {
  std::ostringstream report;
  double totalIncome = 0.0;
  double totalExpenditure = 0.0;
  for (long long i = 1; i <= count; i++) {
    Transaction tmp;
    tmp.index = i;
    Transaction txn = lo.find(tmp).back();
    if (txn.type) {
      totalIncome += txn.TotalCost;
    } else {
      totalExpenditure += txn.TotalCost;
    }
  }
  report << "Finance Report\n";
  report << "==============================\n";
  report << "Total Income: " << std::fixed << std::setprecision(2)
         << totalIncome << "\n";
  report << "Total Expenditure: " << std::fixed << std::setprecision(2)
         << totalExpenditure << "\n";
  report << "Net Profit: " << std::fixed << std::setprecision(2)
         << (totalIncome - totalExpenditure) << "\n";
  report << "==============================\n";
  report << "End of Report\n";
  std::cout << report.str();
}
void LogManager::generateEmployeeReport() {
  std::ostringstream report;
  long long totalTransactions = 0;
  for (long long i = 0; i < count; i++) {
    Transaction txn = lo.find(Transaction()).back();
    totalTransactions++;
  }
  report << "Employee Work Report\n";
  report << "==============================\n";
  report << "Total Transactions Handled: " << totalTransactions << "\n";
  report << "==============================\n";
  report << "End of Report\n";
  std::cout << report.str();
}
/*void LogManager::generateLog() {
  std::ostringstream log;
  log << "System Logs\n";
  log << "==============================\n";
  for (long long i = 0; i < count; i++) {
    Transaction txn = lo.find(Transaction());
    log << "Transaction ID: " << txn.TransactionID << "\n";
    log << "ISBN: " << txn.ISBN << "\n";
    log << "Quantity: " << txn.Quantity << "\n";
    log << "Total Cost: " << txn.TotalCost << "\n";
    log << "Transaction Type: " << (txn.type ? "Sale" : "Purchase") << "\n";
    log << "==============================\n";
  }
  log << "End of Logs\n";
  std::cout << log.str();
}*/
void LogManager::insertTransaction(Transaction &txn) {
  i++;
  txn.index = i;
  lo.insert(txn);
  count++;
}
