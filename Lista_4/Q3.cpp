<<<<<<< HEAD
#include <iostream>
#include <string>
#include <vector>
=======
>>>>>>> 8a2a3a4cbc53ac766034196c666506956de6557d
#include <algorithm>
#include <cstdio>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector<int> z_function(const string& s) {
    int n = s.size();
    vector<int> z(n, 0);
    int l = 0, r = 0;

    // janela [l, r)
    for (int i = 1; i < n; i++) {
        if (i < r)
            z[i] = min(r - i, z[i - l]); // espelho

        while (i + z[i] < n && s[z[i]] == s[i + z[i]])
            ++z[i];

        if (i + z[i] > r) {
            l = i; // nova janela
            r = i + z[i];
        }
    }

    return z;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

<<<<<<< HEAD
    string s;
    cin >> s;
    int n = s.size();

    vector<int> z = z_function(s);

    for (int p = 1; p <= n / 2; p++) {
        if (n % p == 0 && z[p] == n - p) {
            cout << "SIM\n";
            return 0;
        }
=======
  string s;
  cin >> s;
  int n = s.size();
  vector<int> z(n, 0);
  int inicio = 1;
  int i = 1;

  while (i < n) {
    while (i + z[i] < n && z[i] < inicio && s[z[i]] == s[i + z[i]]) {
      z[i]++;
>>>>>>> 8a2a3a4cbc53ac766034196c666506956de6557d
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

<<<<<<< HEAD
    cout << "NAO\n";
    return 0;
}
=======
  cout << "NAO\n";
  return 0;
}
>>>>>>> 8a2a3a4cbc53ac766034196c666506956de6557d
