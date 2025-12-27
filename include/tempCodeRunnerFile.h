 void insert(information infor) {
    long long p = 0;
    while (true) {
      Block b;
      rd(p, b);
      bool here = (b.nxt == -1);
      if (!here && b.cnt > 0) {
        if (infor < b.d[b.cnt - 1])
          here = true;
        else if (infor < b.d[b.cnt - 1] or infor == b.d[b.cnt - 1])
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