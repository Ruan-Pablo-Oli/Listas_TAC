#include <bits/stdc++.h>

using namespace std;
long long d;
vector<long long> a, tmp;

static char buf[1 << 21];

long long merge_modificado(int l, int r) {
  if (r - l <= 1)
    return 0;
  int m = (l + r) / 2;
  long long cont = merge_modificado(l, m) + merge_modificado(m, r);
  int p = l;
  for (int j = m; j < r; j++) {
    while (p < m && a[p] <= a[j] + d)
      p++;
    cont += p - l;
  }

  merge(a.begin() + l, a.begin() + m, a.begin() + m, a.begin() + r,
        tmp.begin() + l);
  copy(tmp.begin() + l, tmp.begin() + r, a.begin() + l);
  return cont;
}

int main() {
  int n;
  fgets(buf, sizeof buf, stdin);
  sscanf(buf, "%d %lld", &n, &d);
  a.resize(n);
  tmp.resize(n);

  fgets(buf, sizeof buf, stdin);
  char *p = buf;
  for (int i = 0; i < n; i++)
    a[i] = strtoll(p, &p, 10);
  fgets(buf, sizeof buf, stdin);
  p = buf;
  for (int i = 0; i < n; i++)
    a[i] -= strtoll(p, &p, 10);

  printf("%lld\n", merge_modificado(0, n));
  return 0;
}
