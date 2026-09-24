#include <iostream>
#include <string>

using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  string r, s;

  cin >> r >> s;

  if (r.size() > s.size() || s.size() > r.size()) {
    printf("Nao\n");
    return 0;
  }

  int T[26] = {0};

  for (size_t i = 0; i < r.size(); i++) {
    T[r[i] - 'a']++;
  }

  for (size_t i = 0; i < s.size(); i++) {
    int indice = s[i] - 'a';
    if (T[indice] >= 1) {
      T[indice]--;
    } else {
      printf("Nao\n");
      return 0;
    }
  }

  printf("Sim\n");
  return 0;
}
