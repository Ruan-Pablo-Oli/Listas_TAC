#include<cstdio>
#include<vector>
#include<queue>
#include<algorithm>

using namespace std;
static char buf[32];

int main(){
    int n, m;
    if(scanf("%d %d", &n,&m) != 2) return 0;

    vector<vector<int>> grafo(n);
    vector<int> grau(n,0);

    for(int i=0; i<m; i++){
        int u, v;
        scanf("%d %d", &u, &v);
        grau[u]++;
        grafo[v].push_back(u);
    }

    queue<int> fila;
    for(int v=0; v<n; v++){
        if(grau[v]==0) fila.push(v);
    }

    vector<int> safe;
    while(!fila.empty()){
        int u = fila.front();
        fila.pop();
        safe.push_back(u);

        for(int v:grafo[u]){
            grau[v]--;
            if(grau[v]==0){
                fila.push(v);
            }
        }
    }

    sort(safe.begin(), safe.end());

    int tam = safe.size();
    printf("%d", tam);
    for(int i=0; i<tam; i++){
        printf(" %d", safe[i]);
    }
    printf("\n");

    return 0;
}