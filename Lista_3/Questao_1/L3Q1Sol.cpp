#include<cstdio>
#include<vector>
#include<queue>

using namespace std;

static char buf[32];

int main(){
    int n, m;
    if(scanf("%d %d", &n, &m) != 2) return 0;

    vector<vector<int>> grafo(n);
    vector<int> graus(n,0);
    
    
    for(int i=0; i<m; i++){
        int u,v;
        scanf("%d %d", &u, &v);
        graus[v]++;
        grafo[u].push_back(v);
    }
    
    queue<int> fila;
    for(int v=0; v<n; v++){
        if(graus[v] == 0) fila.push(v);
    }

    vector<int> ordem;

    while(!fila.empty()){
        int u = fila.front();
        fila.pop();

        ordem.push_back(u);

        for(int v:grafo[u]){
            graus[v]--;
            if(graus[v] == 0){
                fila.push(v);
            }
        }
    }

    for(int i=0; i<n; i++){
        printf("%d%c", ordem[i], (i==n-1) ? '\n':' ');
    }


    return 0;
}