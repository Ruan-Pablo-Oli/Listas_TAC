#include <cstdio>
#include <cstdlib>
#include <vector>

using namespace std;

static char buf[60000000];

int main() {
  fgets(buf, sizeof buf, stdin);
  int n = atoi(buf);
  vector<int> array(n);

  fgets(buf, sizeof buf, stdin);
  char *p = buf;

  for (int i = 0; i < n; i++) {
    array[i] = strtol(p, &p, 10);
  }
  int inicio = 0;
  int fim = n - 1;
  int pos = -1; // Guarda o menor i encontrado

  while (inicio <= fim) {
    int m = inicio + (fim - inicio) / 2;
    if (array[m] >= n - m) {
      pos = m;
      fim = m - 1;
    } else {
      inicio = m + 1;
    }
  }

  int k = n - pos;
  if (pos != -1 && (pos == 0 || array[pos - 1] < k))
    printf("%d\n", k);
  else
    printf("-1\n");

  return 0;
}
