#!/bin/bash

echo "Compilando solucao.cpp com otimizacao -O2..."
g++ -O2 -std=c++17 L1Q6Sol.cpp -o solucao

if [ $? -ne 0 ]; then
    echo "❌ Erro de compilação!"
    exit 1
fi

TOTAL_TESTES=50

echo "--------------------------------------------------------"
echo "Iniciando bateria de testes..."
echo "--------------------------------------------------------"

for i in $(seq 1 $TOTAL_TESTES)
do
    # 1. Executa o gerador Python
    python3 L1Q6Gerador.py

    # 2. Roda o C++ e mede tempo e memória
    /usr/bin/time -o time.log -f "%e %M" ./solucao < in.txt > out.txt
    
    USAGE=$(cat time.log)
    TEMPO=$(echo $USAGE | awk '{print $1}')
    MEMORIA_KB=$(echo $USAGE | awk '{print $2}')
    MEMORIA_MB=$(echo "scale=2; $MEMORIA_KB / 1024" | bc)

    # 3. Compara a saída
    diff -w out.txt gabarito.txt > /dev/null

    if [ $? -ne 0 ]; then
        echo "❌ ERRO NO TESTE $i"
        echo "--------------------------------------------------------"
        echo "Entrada (in.txt):"
        cat in.txt
        echo "Sua saída: $(cat out.txt)"
        echo "Gabarito:  $(cat gabarito.txt)"
        rm -f time.log
        exit 1
    fi

    echo "✅ Teste $i OK | Tempo: ${TEMPO}s | Memória: ${MEMORIA_MB} MB"
done

rm -f time.log

echo "--------------------------------------------------------"
echo "🎉 Todos os $TOTAL_TESTES testes passaram com sucesso!"