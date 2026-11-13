#include <vector>
#include <iostream>
#include <cstdio>
#include <string>
#include <algorithm>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string s;
    cin >> s;
    int n = s.size();
    vector<long long int> z(n, 0);
    int l = 0, r = 0;
    long long int sum = n;
    z[0] = n;
    // janela [l, r)
    for (int i = 1; i < n; i++) {
        if (i < r)
            z[i] = min<long long int>(r - i, z[i - l]); // espelho

        while (i + z[i] < n && s[z[i]] == s[i + z[i]])
            ++z[i];

        if (i + z[i] > r) {
            l = i; // nova janela
            r = i + z[i];
        }
        sum += z[i];
    }
    cout << sum << "\n";

	return 0;
}
