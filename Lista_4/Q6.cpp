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
    cin >> s;
    t = s;
    int m = size(t);
    reverse(t.begin(), t.end());
    s += '#' + t;

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
        if(z[i] == size(s) - i && i > m){
            string_view sv(s);
            cout << sv.substr(m + 1, i - m) << sv.substr(1, m - 1) << "\n";
            // for(int i = 0; i < z.size(); i++){
            //     cout << z[i];
            // }
            // cout << "\n";
            return 0;
        }
    }

	return 0;
}
