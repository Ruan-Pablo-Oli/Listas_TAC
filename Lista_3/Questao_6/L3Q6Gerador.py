#!/usr/bin/env python3
import sys
import random
from collections import deque

def solve(n, m, grid):
    cr = cc = mr = mc = dr_target = dc_target = -1
    for i in range(n):
        for j in range(m):
            if grid[i][j] == 'C': cr, cc = i, j
            elif grid[i][j] == 'M': mr, mc = i, j
            elif grid[i][j] == 'D': dr_target, dc_target = i, j

    if mr == dr_target and mc == dc_target:
        return 0

    dr = [-1, 1, 0, 0]
    dc = [0, 0, -1, 1]

    def is_valid(r, c):
        return 0 <= r < n and 0 <= c < m and grid[r][c] != '#'

    # BFS Inicial a partir do Robô 'C'
    vis_robot = [False] * (n * m)
    q = deque([(cr, cc)])
    vis_robot[cr * m + cc] = True

    while q:
        r, c = q.popleft()
        for d in range(4):
            nr, nc = r + dr[d], c + dc[d]
            if is_valid(nr, nc) and (nr, nc) != (mr, mc) and not vis_robot[nr * m + nc]:
                vis_robot[nr * m + nc] = True
                q.append((nr, nc))

    INF = 10**9
    dist = [[[INF] * 4 for _ in range(m)] for _ in range(n)]
    dq = deque()

    for d in range(4):
        rr, rc = mr + dr[d], mc + dc[d]
        if is_valid(rr, rc) and vis_robot[rr * m + rc]:
            dist[mr][mc][d] = 0
            dq.append((mr, mc, d))

    vis_side = [False] * (n * m)

    while dq:
        rm, cm, d = dq.popleft()
        cost = dist[rm][cm][d]

        if rm == dr_target and cm == dc_target:
            return cost

        # Transição 1: Mover robô ao redor da caixa (Custo 0)
        rr, rc = rm + dr[d], cm + dc[d] # Usa cm (coluna atual da caixa)
        
        for i in range(n * m): vis_side[i] = False
        
        q_side = deque([(rr, rc)])
        vis_side[rr * m + rc] = True

        while q_side:
            r, c = q_side.popleft()
            for d_dir in range(4):
                nr, nc = r + dr[d_dir], c + dc[d_dir]
                idx = nr * m + nc
                if is_valid(nr, nc) and (nr, nc) != (rm, cm) and not vis_side[idx]:
                    vis_side[idx] = True
                    q_side.append((nr, nc))

        for d2 in range(4):
            if d2 == d: continue
            nrr, nrc = rm + dr[d2], cm + dc[d2]
            if is_valid(nrr, nrc) and vis_side[nrr * m + nrc]:
                if dist[rm][cm][d2] > cost:
                    dist[rm][cm][d2] = cost
                    dq.appendleft((rm, cm, d2))

        # Transição 2: Empurrar a caixa (Custo 1)
        push_dir = d ^ 1
        n_rm, n_cm = rm + dr[push_dir], cm + dc[push_dir]
        if is_valid(n_rm, n_cm):
            if dist[n_rm][n_cm][d] > cost + 1:
                dist[n_rm][n_cm][d] = cost + 1
                dq.append((n_rm, n_cm, d))

    return -1

def generate_random_grid(n, m, wall_prob=0.2):
    grid = [['.' for _ in range(m)] for _ in range(n)]
    
    for i in range(n):
        for j in range(m):
            if random.random() < wall_prob:
                grid[i][j] = '#'

    positions = random.sample([(r, c) for r in range(n) for c in range(m)], 3)
    c_pos, m_pos, d_pos = positions

    grid[c_pos[0]][c_pos[1]] = 'C'
    grid[m_pos[0]][m_pos[1]] = 'M'
    grid[d_pos[0]][d_pos[1]] = 'D'

    return ["".join(row) for row in grid]

def get_test_case(test_num):
    if test_num == 1:
        return 4, 4, ["D###", "..M.", ".##.", "...C"]
    elif test_num == 2:
        return 4, 3, ["D##", ".C.", "##.", "..M"]
    elif test_num == 3:
        return 4, 4, ["D..#", ".#M.", "...C", "...."]
    elif test_num == 4:
        return 2, 2, ["CM", "D."]
    elif test_num == 5:
        return 3, 3, ["###", "#M#", "C.D"]
    else:
        n = random.randint(10, 30)
        m = random.randint(10, 30)
        return n, m, generate_random_grid(n, m, wall_prob=random.uniform(0.1, 0.25))

def main():
    test_num = int(sys.argv[1]) if len(sys.argv) > 1 else 1
    n, m, grid = get_test_case(test_num)

    with open("in.txt", "w") as f:
        f.write(f"{n} {m}\n")
        for row in grid:
            f.write(f"{row}\n")

    ans = solve(n, m, grid)
    with open("gabarito.txt", "w") as f:
        f.write(f"{ans}\n")

if __name__ == "__main__":
    main()