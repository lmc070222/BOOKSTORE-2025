#include "utils.h"

std::vector<keywordchar> tokekeyword(const char *a) {
  std::vector<keywordchar> key;
  char *str = new char[strlen(a) + 1];
  strcpy(str, a);
  char *token = std::strtok(str, "|");
  while (token != nullptr) {
    keywordchar k;
    strncpy(k.ans, token, sizeof(k.ans) - 1);
    k.ans[sizeof(k.ans) - 1] = '\0';
    key.push_back(k);
    token = std::strtok(nullptr, "|");
  }
  delete[] str;
  return key;
}