#!/usr/bin/env python3
import random
from collections import deque

def solve(n, m, edges):
    out_degree = [0] * n
    adj_rev = [[] for _ in range(n)]

    for u, v in edges:
        out_degree[u] += 1
        adj_rev[v].append(u)

    # Inicia com os vértices de grau de saída 0 (sorvedouros)
    q = deque([i for i in range(n) if out_degree[i] == 0])
    seguros = []

    while q:
        u = q.popleft()
        seguros.append(u)
        for v in adj_rev[u]:
            out_degree[v] -= 1
            if out_degree[v] == 0:
                q.append(v)

    seguros.sort()
    
    # Formata a linha do gabarito: k seguido dos vértices ordenados
    if seguros:
        return f"{len(seguros)} " + " ".join(map(str, seguros))
    return "0"

def generate():
    # Varia tamanhos aleatórios de testes (pequenos a grandes)
    mode = random.choice(["small", "medium", "large"])
    if mode == "small":
        n = random.randint(1, 20)
        m = random.randint(0, min(50, n * (n - 1)))
    elif mode == "medium":
        n = random.randint(100, 1000)
        m = random.randint(100, min(5000, n * (n - 1)))
    else:
        n = random.randint(10000, 50000)
        m = random.randint(10000, min(200000, n * (n - 1)))

    edges = set()
    attempts = 0
    max_attempts = m * 5
    while len(edges) < m and attempts < max_attempts:
        attempts += 1
        u = random.randint(0, n - 1)
        v = random.randint(0, n - 1)
        if u != v:
            edges.add((u, v))

    edge_list = list(edges)
    random.shuffle(edge_list)

    # Escreve a entrada em in.txt
    with open("in.txt", "w") as f:
        f.write(f"{n} {len(edge_list)}\n")
        for u, v in edge_list:
            f.write(f"{u} {v}\n")

    # Calcula e escreve o gabarito em gabarito.txt
    ans = solve(n, len(edge_list), edge_list)
    with open("gabarito.txt", "w") as f:
        f.write(f"{ans}\n")

if __name__ == "__main__":
    generate()