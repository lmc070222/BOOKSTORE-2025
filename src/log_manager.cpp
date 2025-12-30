#include "log_manager.h"
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
    std::cout << "Invalid\n";
    return;
  }
  if (count_ == 0) {
    std::cout << "\n";
    return;
  }
  for (long long i = count; i > count - count_; i--) {
    Transaction tmp;
    tmp.index = i;
    std::vector<Transaction> found = lo.find(tmp);
    if (found.empty())
      continue;
    Transaction txn = found.back();
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
  if (count == 0) {
    std::cout << "+ 0.00 - 0.00\n";
    return;
  }
  for (long long i = 1; i <= count; i++) {
    Transaction tmp;
    tmp.index = i;
    std::vector<Transaction> found = lo.find(tmp);
    if (found.empty())
      continue;
    Transaction txn = found.back();
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
  double totalIncome = 0.0;
  double totalExpenditure = 0.0;
  for (long long i = 1; i <= count; i++) {
    Transaction tmp;
    tmp.index = i;
    std::vector<Transaction> found = lo.find(tmp);
    if (found.empty())
      continue;
    Transaction txn = found.back();
    if (txn.type) {
      totalIncome += txn.TotalCost;
    } else {
      totalExpenditure += txn.TotalCost;
    }
  }
  std::cout << "Finance Report\n";
  std::cout << "==============================\n";
  std::cout << "Total Income: " << std::fixed << std::setprecision(2)
         << totalIncome << "\n";
  std::cout << "Total Expenditure: " << std::fixed << std::setprecision(2)
         << totalExpenditure << "\n";
  std::cout << "Net Profit: " << std::fixed << std::setprecision(2)
         << (totalIncome - totalExpenditure) << "\n";
  std::cout << "==============================\n";
  std::cout << "End of Report\n";
}
void LogManager::generateEmployeeReport() {
  std::cout << "Employee Work Report\n";
  std::cout << "==============================\n";
  std::cout << "Total Transactions Handled: " << count << "\n";
  std::cout << "==============================\n";
  std::cout << "End of Report\n";
}
void LogManager::generateLog() {
  std::cout << "System Logs\n";
  std::cout << "==============================\n";
  for (long long j = 1; j <= count; j++) {
    Transaction tmp;
    tmp.index = j;
    std::vector<Transaction> found = lo.find(tmp);
    if (found.empty())
      continue;
    Transaction txn = found.back();
    std::cout << "Transaction ID: " << txn.index << "\n";
    std::cout << "Total Cost: " << std::fixed << std::setprecision(2) << txn.TotalCost
        << "\n";
    std::cout << "Transaction Type: " << (txn.type ? "Sale" : "Purchase") << "\n";
    std::cout << "==============================\n";
  }
  std::cout << "End of Logs\n";
}
void LogManager::insertTransaction(Transaction &txn) {
  i++;
  txn.index = i;
  lo.insert(txn);
  count++;
}