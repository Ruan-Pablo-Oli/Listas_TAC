#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;
    std::vector<int> array(n);

    for(int i=0; i<n; i++){
        cin >> array[i];
    }

    int inicio = 0;
    int fim = n-1;
    int pos = -1; //Guarda o menor i encontrado

    int m;


    while(inicio <= fim){
        m = inicio + (fim - inicio)/2;
        if(array[m] >= n-m){
            pos = m;
            fim = m-1;
        }
        else {
            inicio = m+1;
        }
    }

    int k;
    if(pos != -1){
        k = n - pos;
        if(pos == 0 || array[pos-1] < k){
            cout << k << "\n";
        }else{
            cout << -1 << "\n";
        }
    }
    else {
        cout << -1 << "\n";
    }

    return 0;
}