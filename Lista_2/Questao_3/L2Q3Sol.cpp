#include <cstdio>
#include <cstdlib>
#include <vector>

using namespace std;

static char buf[1 << 21];

int main() {

  int n;
  int k;
  long long max = 0;
  long long min = 0;
  fgets(buf, sizeof buf, stdin);
  sscanf(buf, "%d %d", &n, &k);
  fgets(buf, sizeof buf, stdin);
  char *p = buf;
  vector<int> A(n);
  for (int i = 0; i < n; i++) {
    A[i] = strtol(p, &p, 10);
    max += A[i];
    if (A[i] > min)
      min = A[i];
  }

  long long m;
  while (min < max) {
    m = min + (max - min) / 2;
    int c_k = 1;
    long long count = A[0];
    for (int i = 0; i < n - 1; i++) {
      if (count + A[i + 1] <= m) {
        count += A[i + 1];
      } else {
        count = A[i + 1];
        c_k++;
      }
    }
    if (c_k > k) {
      min = m + 1;
    } else {
      max = m;
    }

    if (min == max) {
      break;
    }
  }

  if (min == max) {
    printf("%lld\n", min);
  }

  return 0;
}
