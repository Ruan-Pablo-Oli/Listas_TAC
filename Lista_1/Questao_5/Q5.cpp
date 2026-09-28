#include <iostream>
#include <vector>

using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int n;
  cin >> n;
  vector<int> V(24004);
  vector<int> C(6001);
  vector<int> S(12001);
  int m = 0;
  for (int i = 0; i < n; i++) {
    int x;
    cin >> x;
    if (C[x + 3000] < 4) {
      C[x + 3000]++;
      V[m] = x;
      m++;
    }
  }

  for (int i = 0; i < m; i++) {
    for (int j = i + 1; j < m; j++) {
      if (S[-(V[i] + V[j]) + 6000]) {
        cout << "Sim\n";
        return 0;
      }
    }

    for (int k = 0; k < i; k++) {
      S[V[k] + V[i] + 6000] = true;
    }
  }

  cout << "Nao\n";

  return 0;
}
