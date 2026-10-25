#!/usr/bin/env python3
import sys
import random

def generate_dag(n, m):
    # Garante que M esteja dentro dos limites válidos para um DAG com ordem única
    min_m = n - 1
    max_m = n * (n - 1) // 2
    m = max(min_m, min(m, max_m))

    # Cria uma permutação aleatória dos vértices (a única ordem topológica válida)
    perm = list(range(n))
    random.shuffle(perm)

    edges = set()

    # 1. Arestas obrigatórias do caminho hamiltoniano para garantir ordem ÚNICA
    for i in range(n - 1):
        edges.add((perm[i], perm[i + 1]))

    # 2. Adiciona arestas extras para alcançar a quantidade M desejada (sem criar ciclos)
    attempts = 0
    max_attempts = m * 10
    while len(edges) < m and attempts < max_attempts:
        attempts += 1
        a = random.randint(0, n - 2)
        b = random.randint(a + 1, n - 1)
        u, v = perm[a], perm[b]
        edges.add((u, v))

    edge_list = list(edges)
    random.shuffle(edge_list)  # Mistura a ordem de exibição das arestas

    print(f"{n} {len(edge_list)}")
    for u, v in edge_list:
        print(f"{u} {v}")

if __name__ == "__main__":
    # Aceita N e M como argumentos de linha de comando ou usa valores padrão
    n = int(sys.argv[1]) if len(sys.argv) > 1 else 1000
    m = int(sys.argv[2]) if len(sys.argv) > 2 else 3000
    generate_dag(n, m)