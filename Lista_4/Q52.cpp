#include <vector>
#include <iostream>
#include <cstdio>
#include <string>
#include <algorithm>

using namespace std;

int main() {
    // Otimizando cin e cout ----------------------------------------------
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    //---------------------------------------------------------------------

    // Leitura de dados ---------------------------------------------------
    string s, t;
    cin >> s >> t;
    // if (s.size() > t.size()) {
    //     cout << -1 << "\n";
    //     return 0;
    // }
    
    int m = s.size();
    s += '#' + t;
    int n = s.size();
    //--------------------------------------------------------------------

    // Cálculo da Z funct para a string 'a' ------------------------------
    vector<int> z(n, 0);
    int l = 0, r = 0;

    // janela [l, r)
    for(int i = 1; i < m; i++){
        if (i < r)
            z[i] = min(r - i, z[i - l]); // espelho

        while (i + z[i] < n && s[z[i]] == s[i + z[i]])
            ++z[i];

        if (i + z[i] > r) {
            l = i; // nova janela
            r = i + z[i];
        }
    }
    //--------------------------------------------------------------------

    // Procura se 'b' contém um sufixo de 'a' (ou 'a') no início ---------
    int i = 0;
    int j = 0;
    int sum = 0;
    while(i < m){
        if(s[i] == s[m + 1 + j] && i < m){
            j++;
        }
        i++;
    }
    if(j == 0){
        cout << -1 << "\n"; // Se não contém, printa -1
        return 0;
    }
    z[m+1] = j;
    sum++;
    //--------------------------------------------------------------------

    // Verifica se o restante de 'b' é composto por 'a' e termina com um sufixo de 'a'
    i = m+1 + j;
    while(i < n){
        while (i + z[i] < n && z[i] < m && s[z[i]] == s[i + z[i]]){
           z[i]++;
        }
        if(z[i] == m){
            sum++;
        }
        else{
            if(i + z[i] < n){
                cout << -1 << "\n";
                return 0;
            }
            else{
                sum++;
            }
        }
        i += z[i];
    }

    cout << sum << "\n";
    //-----------------------------------------------------------------------

    return 0;
}
