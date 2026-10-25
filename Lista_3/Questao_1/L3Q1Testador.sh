#!/bin/bash

# Compilação da solução
echo "=== Compilando L3Q1Sol.cpp ==="
g++ -O3 L3Q1Sol.cpp -o L3Q1Sol
if [ $? -ne 0 ]; then
    echo "Erro de compilação!"
    exit 1
fi

# Função validadora de saída em Python embutido
validate() {
python3 - << 'EOF'
import sys

try:
    with open("input.txt") as f:
        tokens = f.read().split()
    if not tokens:
        sys.exit(1)
        
    n = int(tokens[0])
    m = int(tokens[1])
    edges = []
    idx = 2
    for _ in range(m):
        edges.append((int(tokens[idx]), int(tokens[idx+1])))
        idx += 2

    with open("output.txt") as f:
        out_tokens = f.read().split()

    if len(out_tokens) != n:
        print(f" [FAIL] Tamanho incorreto: esperado {n}, obtido {len(out_tokens)}")
        sys.exit(1)

    out = [int(x) for x in out_tokens]
    pos = {val: i for i, val in enumerate(out)}

    if len(pos) != n or any(x < 0 or x >= n for x in out):
        print(" [FAIL] A saída não é uma permutação válida de 0 a N-1")
        sys.exit(1)

    for u, v in edges:
        if pos[u] >= pos[v]:
            print(f" [FAIL] Violição de pré-requisito: {u} aparece depois de {v}")
            sys.exit(1)

    print(" [OK]")
except Exception as e:
    print(f" [FAIL] Erro na validação: {e}")
    sys.exit(1)
EOF
}

# Casos de teste a serem executados: (N M)
TEST_CASES=(
    "5 7"
    "10 20"
    "1000 5000"
    "50000 200000"
    "100000 500000"
)

echo "=== Executando Casos de Teste ==="
i=1
for case in "${TEST_CASES[@]}"; do
    set -- $case
    N=$1
    M=$2
    
    echo -n "Teste $i (N=$N, M=$M): "
    
    # Gera o arquivo de entrada
    python3 L3Q1Gerador.py $N $M > input.txt
    
    # Executa a solução e mede o tempo
    START=$(date +%s%N)
    ./L3Q1Sol < input.txt > output.txt
    END=$(date +%s%N)
    
    DIFF=$(( (END - START) / 1000000 ))
    
    # Valida o resultado
    validate
    echo "  Tempo de execução: ${DIFF} ms"
    
    i=$((i+1))
done

# Limpeza de arquivos temporários
rm -f input.txt output.txt L3Q1Sol
echo "=== Testes Concluídos com Sucesso ==="