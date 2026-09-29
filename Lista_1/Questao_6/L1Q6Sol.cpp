#include <iostream>
#include <vector>

using namespace std;



int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;
    vector<int> V(n);
    int k;
    cin >> k;

    for(int i=0;i<n;i++){
        cin >> V[i];
        if(V[i] == 0){
            cout << "Sim\n"; return 0;
        }
    }

    if(k == 1){
        cout << "Nao\n"; return 0;
    }
    
    if(k >= 2){
        int i=0, j=n-1;
        while(i<j){
            if(V[i]+V[j]==0){
                cout << "Sim\n"; return 0;
            }
            else if(V[i] + V[j] > 0){
                j--;
            }
            else{
                i++;
            }
        }
    }

    if(k >= 4){
        bool S2[4005] = {false};
        int offset_S2 = 2000;
        int result;
        for(int i=0; i<n; i++){
            for(int j=0;j<n; j++){
                result = V[i]+V[j];
                S2[result + offset_S2] = true;
            }
        }
        for(int x=-2000; x<=2000; x++){
            if(S2[x + offset_S2] && S2[-x + offset_S2]){
                cout << "Sim\n"; return 0;
            }
        }
        if(k = 8){
            bool S4[8005] = {false};
            int offset_S4 = 4000;
            int result_S4;
            for(int a = -2000; a<=2000; a++){
                if(!S2[a+offset_S2]) continue;
    
                for(int b=-2000; b<=2000; b++){
                    if(S2[b+offset_S2]){
                        result_S4 = a + b;
                        S4[result_S4+offset_S4] = true; 
                    }
                }
            }
            for(int x=-4000; x<=4000; x++){
                if(S4[x + offset_S4] && S4[-x + offset_S4]){
                    cout << "Sim\n"; return 0;
                }
            }
        }
    }


    cout << "Nao\n";
    return 0;
}