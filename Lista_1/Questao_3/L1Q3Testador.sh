#!/bin/bash

echo "Compilando solucao.cpp com otimizacao -O2..."
g++ -O2 -std=c++17 L1Q3Sol.cpp -o solucao

if [ $? -ne 0 ]; then
    echo "Erro de compilação!"
    exit 1
fi

TOTAL_TESTES=50

echo "--------------------------------------------------------"
echo "Iniciando bateria de testes para Desembaralhando 3..."
echo "--------------------------------------------------------"

for i in $(seq 1 $TOTAL_TESTES)
do
    # 1. Gera in.txt e gabarito.txt
    python3 L1Q3Gerador.py $i

    # 2. Executa a solução em C++ gravando métricas em time.log
    /usr/bin/time -o time.log -f "%e %M" ./solucao < in.txt > out.txt
    
    # 3. Extrai métricas de tempo e memória
    USAGE=$(cat time.log)
    TEMPO=$(echo $USAGE | awk '{print $1}')
    MEMORIA_KB=$(echo $USAGE | awk '{print $2}')
    MEMORIA_MB=$(echo "scale=2; $MEMORIA_KB / 1024" | bc)

    # 4. Compara saída ignorando espaços extras em branco (-w)
    diff -w out.txt gabarito.txt > /dev/null

    if [ $? -ne 0 ]; then
        echo "❌ ERRO NO TESTE $i"
        echo "--------------------------------------------------------"
        echo "Entrada (in.txt):"
        head -c 100 in.txt
        echo -e "\n..."
        echo "Sua saída (out.txt):"
        head -n 10 out.txt
        echo "..."
        echo "Gabarito esperado (gabarito.txt):"
        head -n 10 gabarito.txt
        echo "..."
        rm -f time.log
        exit 1
    fi

    echo "✅ Teste $i OK | Tempo: ${TEMPO}s | Memória: ${MEMORIA_MB} MB"
done

rm -f time.log

echo "--------------------------------------------------------"
echo "🎉 Todos os $TOTAL_TESTES testes passaram com sucesso!"