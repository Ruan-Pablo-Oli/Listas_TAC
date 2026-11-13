#include <vector>
#include <iostream>
#include <cstdio>
#include <string>
#include <algorithm>

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

    string s, t;
    cin >> s >> t;

    if (s.size() != t.size()) {
        cout << "NAO\n";
        return 0;
    }

    s += '#' + t;
    vector<int> z = z_function(s);

    // cout << "z: ";
    // for(int i = 0; i < z.size(); i++) {
    //     cout << z[i] << " ";
    // }
    // cout << "\n";

    for(int i = size(t) + 1; i < z.size(); i++) {
        if (z[i] == size(s) - i) {
            for(int j = 0; j < size(t) - z[i]; j++) {
                if(s[z[i] + j] != s[size(t) + 1 + j]) {
                    cout << "NAO\n";
                    return 0;
                }
            }
            cout << "SIM\n";
            return 0;
        }
    }
    cout << "NAO\n";

	return 0;
}
