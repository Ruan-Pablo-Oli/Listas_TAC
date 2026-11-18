#include <algorithm>
#include <cstdio>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  string s;
  cin >> s;
  int n = s.size();
  vector<int> z(n, 0);
  int inicio = 1;
  int i = 1;

  while (i < n) {
    while (i + z[i] < n && z[i] < inicio && s[z[i]] == s[i + z[i]]) {
      z[i]++;
    }
    if (z[i] != inicio) {
      inicio = i + 1;
      i++;
    } else {
      i += z[i];
      if (i == n) {
        cout << "SIM\n";
        return 0;
      }
    }
  }

  cout << "NAO\n";
  return 0;
}
