#include <iostream>
#include <vector>

using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int n;
  bool find = 0;

  cin >> n;
  vector<int> V(n);

  for (int i = 0; i < n; i++) {
    cin >> V[i];
  }

  int i = 0;
  while (i <= n - 3) {
    int j = i + 1;
    int k = n - 1;
    while (j < k) {
      if (V[i] + V[j] + V[k] == 0) {
        cout << i << " " << j << " " << k << "\n";
        j++;
        k--;
        find = 1;
      } else if (V[i] + V[j] + V[k] > 0) {
        k--;
      } else {
        j++;
      }
    }
    i++;
  }

  if (!find) {
    cout << "0\n";
  }

  return 0;
}
