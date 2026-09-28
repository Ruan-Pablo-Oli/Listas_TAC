#include <iostream>
#include <string>
#include <queue>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int alfabeto_r[26] = {0};
    int alfabeto_s[26] = {0};
    queue<char> s;
    int contador = 0;
    int indice_sim = 0;
    char c;
    bool flag = 1;
    bool finalflag = 1;
    

    while(cin.get(c) && !isspace(c)){
        int pos = c - 'a';
        alfabeto_r[pos] += 1;
        contador++;
    }


    while(cin.get(c)){
        if(isspace(c)) continue;
        else{
            
            int pos = c - 'a';
            s.push(c);
            alfabeto_s[pos] += 1;


            if(s.size() > contador){
                indice_sim++;
                pos = s.front() - 'a';
                alfabeto_s[pos] -= 1;
                s.pop();
            }

            if(s.size() == contador){
                for(int i=0; i<26; i++){
                    if(alfabeto_r[i] != alfabeto_s[i]) {flag=0; break;}
                    else{
                        flag=1;    
                    }
                }
                if(flag){
                    //cout << "Sim\n";    
                    //return 0;
                    cout << indice_sim << "\n";
                    finalflag = 0;
                }
            }


        }
    }

    if(finalflag) cout << "Nao\n";  
    return 0;
}