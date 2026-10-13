#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <vector>

using namespace std;

static char buf[1 << 24];

int main() {
  fgets(buf, sizeof buf, stdin);
  int n = atoi(buf);
  vector<int> A(n);
  long long sum_A = 0;
  fgets(buf, sizeof buf, stdin);
  char *p = buf;
  for (int i = 0; i < n; i++) {
    A[i] = strtol(p, &p, 10);
    sum_A += A[i];
  }

  sort(A.begin(), A.end());

  fgets(buf, sizeof buf, stdin);
  int m = atoi(buf);
  vector<int> B(m);
  long long sum_B = 0;
  fgets(buf, sizeof buf, stdin);
  p = buf;
  for (int i = 0; i < m; i++) {
    B[i] = strtol(p, &p, 10);
    sum_B += B[i];
  }
  sort(B.begin(), B.end());

  if ((sum_B - sum_A) % 2 != 0) {
    printf("-1\n");
    return 0;
  }

  long long d = (sum_B - sum_A) / 2;

  bool find = false;
  int i = 0;
  int j = 0;
  while (i < n && j < m) {
    long long diff = B[j] - A[i];

    if (diff == d) {
      printf("%d %d\n", A[i], B[j]);
      find = true;
      break;
    } else if (diff < d) {
      j++;
    } else {
      i++;
    }
  }

  if (!find) {
    printf("-1\n");
  }

  return 0;
}
