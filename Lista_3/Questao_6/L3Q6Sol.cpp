#include <cstdio>
#include <cstring>
#include <cmath>
#include <queue>
#include <algorithm>

using namespace std;

// Direções: 0: Cima, 1: Baixo, 2: Esquerda, 3: Direita
const int dr[] = {-1, 1, 0, 0};
const int dc[] = {0, 0, -1, 1};

struct State {
    int rm, cm; // Posição atual da caixa
    int dir;    // Posição do robô em relação à caixa (0: Cima, 1: Baixo, 2: Esq, 3: Dir)
    int g;      // Quantidade de empurrões dados
    int h;      // Heurística (Distância de Manhattan até 'D')

    // Min-Heap baseada em f = g + h
    bool operator<(const State& other) const {
        if (g + h != other.g + other.h) {
            return g + h > other.g + other.h;
        }
        return h > other.h;
    }
};

int N, M;
char grid[205][205];
int dist_arr[205][205][4];
bool visited_robot[205][205];
bool vis_side[205][205];

// Verifica limites e se não é parede '#'
bool isValid(int r, int c) {
    return r >= 0 && r < N && c >= 0 && c < M && grid[r][c] != '#';
}

// Calculo da heurística de Manhattan
int calc_h(int rm, int cm, int rd, int cd) {
    return abs(rm - rd) + abs(cm - cd);
}

int main() {
    if (scanf("%d %d", &N, &M) != 2) return 0;

    int cr = -1, cc = -1;
    int mr = -1, mc = -1;
    int dr_target = -1, dc_target = -1;

    for (int i = 0; i < N; i++) {
        scanf("%s", grid[i]);
        for (int j = 0; j < M; j++) {
            if (grid[i][j] == 'C') { cr = i; cc = j; }
            else if (grid[i][j] == 'M') { mr = i; mc = j; }
            else if (grid[i][j] == 'D') { dr_target = i; dc_target = j; }
        }
    }

    // Se a caixa já está no destino
    if (mr == dr_target && mc == dc_target) {
        printf("0\n");
        return 0;
    }

    // Inicializa a matriz de distâncias com valor alto (Infinito)
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            for (int d = 0; d < 4; d++) {
                dist_arr[i][j][d] = 1e9;
            }
        }
    }

    priority_queue<State> pq;

    // BFS Inicial: Descobre quais lados de 'M' o robô alcança a partir de 'C'
    memset(visited_robot, 0, sizeof(visited_robot));
    queue<pair<int, int>> q_robot;

    q_robot.push({cr, cc});
    visited_robot[cr][cc] = true;

    while (!q_robot.empty()) {
        pair<int, int> curr = q_robot.front();
        q_robot.pop();

        int r = curr.first;
        int c = curr.second;

        for (int d = 0; d < 4; d++) {
            int nr = r + dr[d];
            int nc = c + dc[d];

            if (isValid(nr, nc) && !(nr == mr && nc == mc) && !visited_robot[nr][nc]) {
                visited_robot[nr][nc] = true;
                q_robot.push({nr, nc});
            }
        }
    }

    // Adiciona os lados alcançáveis da caixa na fila do A*
    for (int d = 0; d < 4; d++) {
        int rr = mr + dr[d];
        int rc = mc + dc[d];
        if (isValid(rr, rc) && visited_robot[rr][rc]) {
            int h = calc_h(mr, mc, dr_target, dc_target);
            dist_arr[mr][mc][d] = 0;
            pq.push({mr, mc, d, 0, h});
        }
    }

    int ans = -1;

    // Loop principal do A*
    while (!pq.empty()) {
        State cur = pq.top();
        pq.pop();

        if (cur.g > dist_arr[cur.rm][cur.cm][cur.dir]) continue;

        // Condição de parada: a caixa chegou a 'D'
        if (cur.rm == dr_target && cur.cm == dc_target) {
            ans = cur.g;
            break;
        }

        // --- TRANSIÇÃO 1: Mudar o Robô de lado ao redor da caixa (Custo g + 0) ---
        int robot_r = cur.rm + dr[cur.dir];
        int robot_c = cur.cm + dc[cur.dir];

        memset(vis_side, 0, sizeof(vis_side));
        queue<pair<int, int>> q_side;

        q_side.push({robot_r, robot_c});
        vis_side[robot_r][robot_c] = true;

        while (!q_side.empty()) {
            pair<int, int> curr = q_side.front();
            q_side.pop();

            int r = curr.first;
            int c = curr.second;

            for (int d = 0; d < 4; d++) {
                int nr = r + dr[d];
                int nc = c + dc[d];

                if (isValid(nr, nc) && !(nr == cur.rm && nc == cur.cm) && !vis_side[nr][nc]) {
                    vis_side[nr][nc] = true;
                    q_side.push({nr, nc});
                }
            }
        }

        for (int d2 = 0; d2 < 4; d2++) {
            if (d2 == cur.dir) continue;
            int nr_r = cur.rm + dr[d2];
            int nr_c = cur.cm + dc[d2];

            if (isValid(nr_r, nr_c) && vis_side[nr_r][nr_c]) {
                if (cur.g < dist_arr[cur.rm][cur.cm][d2]) {
                    dist_arr[cur.rm][cur.cm][d2] = cur.g;
                    pq.push({cur.rm, cur.cm, d2, cur.g, cur.h});
                }
            }
        }

        // --- TRANSIÇÃO 2: Empurrar a caixa (Custo g + 1) ---
        int push_dir = cur.dir ^ 1; // Inverte o lado (0<->1, 2<->3)
        int n_rm = cur.rm + dr[push_dir];
        int n_cm = cur.cm + dc[push_dir];

        if (isValid(n_rm, n_cm)) {
            int new_g = cur.g + 1;
            if (new_g < dist_arr[n_rm][n_cm][cur.dir]) {
                dist_arr[n_rm][n_cm][cur.dir] = new_g;
                int new_h = calc_h(n_rm, n_cm, dr_target, dc_target);
                pq.push({n_rm, n_cm, cur.dir, new_g, new_h});
            }
        }
    }

    printf("%d\n", ans);
    return 0;
}