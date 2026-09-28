#include <iostream>
#include <map>

#include <vector>
using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int n;

  cin >> n;
  vector<int> V(n);
  map<int, int> T;

  for (int i = 0; i < n; i++) {
    cin >> V[i];
  }

  for (int j = 1; j <= n - 2; j++) {
    int i = j - 1;
    T[V[i]] = i;
    for (int k = j + 1; k <= n - 1; k++) {
      printf("para j = %d e k = %d, procurando por %d\n", j, k, -(V[j] + V[k]));
      auto it = T.find(-(V[j] + V[k]));
      if (it != T.end()) {
        printf("encontrado: %d %d %d\n", it->second, j, k);
        cout << it->second << " " << j << " " << k << "\n";
      }
    }
  }

  return 0;
}
