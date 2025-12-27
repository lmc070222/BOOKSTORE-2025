#pragma once
#include <cstring>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
const int BLOCK_SIZE = 300;
template <class information> struct block {
  int cnt;
  long long nxt;
  information d[BLOCK_SIZE];
};
template <class information, class Block> class memoryriver {
private:
  std::string filename;

public:
  std::fstream f;
  memoryriver(){};
  memoryriver(std::string s) { filename = s; };
  void initialise(std::string s) {
    filename = s;
    f.open(filename, std::ios::in | std::ios::out | std::ios::binary);
    if (!f) {
      f.clear();
      std::ofstream o(filename, std::ios::binary);
      Block b;
      b.cnt = 0;
      b.nxt = -1;
      o.write((char *)&b, sizeof(Block));
      o.close();
      f.open(filename, std::ios::in | std::ios::out | std::ios::binary);
    }
  }
  void init() {
    f.open(filename, std::ios::in | std::ios::out | std::ios::binary);
    if (!f) {
      f.clear();
      std::ofstream o(filename, std::ios::binary);
      Block b;
      b.cnt = 0;
      b.nxt = -1;
      o.write((char *)&b, sizeof(Block));
      o.close();
      f.open(filename, std::ios::in | std::ios::out | std::ios::binary);
    }
  }

  void rd(long long p, Block &b) {
    f.seekg(p);
    f.read((char *)&b, sizeof(Block));
  } // 读取位置在p的块并将内容存储在b中

  void wr(long long p, const Block &b) {
    f.seekp(p);
    f.write((char *)&b, sizeof(Block));
  } // 将块b的内容写在p的位置

  long long alloc() {
    f.seekp(0, std::ios::end);
    long long p = f.tellp();
    Block b;
    b.cnt = 0;
    b.nxt = -1;
    f.write((char *)&b, sizeof(Block));
    return p;
  } // 在文件的末尾加入一个空快并返回块的位置

  void split(long long p) {
    Block b;
    rd(p, b);
    if (b.cnt < BLOCK_SIZE)
      return;
    int m = b.cnt / 2;
    long long np = alloc();
    Block nb;
    nb.cnt = b.cnt - m;
    nb.nxt = b.nxt;
    for (int i = 0; i < nb.cnt; i++)
      nb.d[i] = b.d[m + i];
    b.cnt = m;
    b.nxt = np;
    wr(p, b);
    wr(np, nb);
  } // 实现分裂

  void insert(information infor) {
    long long p = 0;
    while (true) {
      Block b;
      rd(p, b);
      bool here = (b.nxt == -1);
      if (!here && b.cnt > 0) {
        if (infor < b.d[b.cnt - 1])
          here = true;
        else if (infor == b.d[b.cnt - 1])
          here = true;
      }
      if (here) {
        int lo = 0, hi = b.cnt;
        while (lo < hi) {
          int mid = (lo + hi) / 2;
          if (b.d[mid] < infor)
            lo = mid + 1;
          else
            hi = mid;
        }
        if (lo < b.cnt && b.d[lo] == infor)
          return;
        for (int i = b.cnt; i > lo; i--)
          b.d[i] = b.d[i - 1];
        b.d[lo] = infor;
        b.cnt++;
        wr(p, b);
        split(p);
        return;
      }
      p = b.nxt;
    }
  }

  void deleteinformation(information infor) {
    long long p = 0;
    while (p != -1) {
      Block b;
      rd(p, b);
      if (b.cnt > 0) {
        int c2;
        if (infor < b.d[b.cnt - 1]) {
          c2 = -1;
        } else if (infor == b.d[b.cnt - 1]) {
          c2 = 0;
        } else
          c2 = 1;
        if (c2 <= 0) {
          int lo = 0, hi = b.cnt;
          while (lo < hi) {
            int mid = (lo + hi) / 2;
            if (b.d[mid] < infor)
              lo = mid + 1;
            else
              hi = mid;
          }
          if (lo < b.cnt && b.d[lo] == infor) {
            for (int i = lo; i < b.cnt - 1; i++)
              b.d[i] = b.d[i + 1];
            b.cnt--;
            wr(p, b);
            return;
          }
        }
        if (c2 < 0)
          return;
      }
      p = b.nxt;
    }
  }

  std::vector<information> find(information infor) {
    std::vector<information> res;
    long long p = 0;
    while (p != -1) {
      Block b;
      rd(p, b);
      if (b.cnt > 0) {
        int c2;
        if (infor < b.d[b.cnt - 1]) {
          c2 = -1;
        } else if (infor == b.d[b.cnt - 1]) {
          c2 = 0;
        } else
          c2 = 1;
        if (c2 <= 0) {
          int lo = 0, hi = b.cnt;
          while (lo < hi) {
            int mid = (lo + hi) / 2;
            if (b.d[mid] < infor)
              lo = mid + 1;
            else
              hi = mid;
          }
          for (int i = lo; i < b.cnt and b.d[i] == infor; i++) {
            res.push_back(b.d[i]);
          }
        }
        if (c2 < 0)
          break;
      }
      p = b.nxt;
    }
    return res;
  }
   std::vector<information> findindex(information infor) {
    std::vector<information> res;
    long long p = 0;
    while (p != -1) {
      Block b;
      rd(p, b);
      if (b.cnt > 0) {
        int c2;
        if (infor.compare(infor , b.d[b.cnt - 1]) == -1) {
          c2 = -1;
        } else if (infor.compare(infor , b.d[b.cnt - 1]) == 0) {
          c2 = 0;
        } else
          c2 = 1;
        if (c2 <= 0) {
          int lo = 0, hi = b.cnt;
          while (lo < hi) {
            int mid = (lo + hi) / 2;
            if (infor.compare(b.d[mid] , infor) == -1)
              lo = mid + 1;
            else
              hi = mid;
          }
          for (int i = lo; i < b.cnt and (infor.compare(b.d[i] , infor) == 0); i++) {
            res.push_back(b.d[i]);
          }
        }
        if (c2 < 0)
          break;
      }
      p = b.nxt;
    }
    return res;
  }
  void close() { f.close(); };
};
struct keywordchar {
  char ans[60];
};
std::vector<keywordchar> tokekeyword(const char *a) ;