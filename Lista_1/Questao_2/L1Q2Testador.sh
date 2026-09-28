#!/bin/bash

echo "Compilando solucao.cpp com otimizacao -O2..."
g++ -O2 -std=c++17 L1Q2Sol.cpp -o solucao

if [ $? -ne 0 ]; then
    echo "Erro de compilação!"
    exit 1
fi

TOTAL_TESTES=50

echo "--------------------------------------------------------"
echo "Iniciando bateria de testes..."
echo "--------------------------------------------------------"

for i in $(seq 1 $TOTAL_TESTES)
do
    # 1. Gera o arquivo in.txt e gabarito.txt
    python3 L1Q2Gerador.py $i

    # 2. Executa o C++ salvando as metricas no arquivo temporario 'time.log'
    /usr/bin/time -o time.log -f "%e %M" ./solucao < in.txt > out.txt
    
    # 3. Le os dados de tempo e memoria do arquivo temporario
    USAGE=$(cat time.log)
    TEMPO=$(echo $USAGE | awk '{print $1}')
    MEMORIA_KB=$(echo $USAGE | awk '{print $2}')
    MEMORIA_MB=$(echo "scale=2; $MEMORIA_KB / 1024" | bc)

    # 4. Compara a saída com o gabarito
    diff -w out.txt gabarito.txt > /dev/null

    if [ $? -ne 0 ]; then
        echo "ERRO NO TESTE $i"
        echo "--------------------------------------------------------"
        echo "Entrada (in.txt):"
        head -c 100 in.txt
        echo -e "\n..."
        echo "Sua saída: $(cat out.txt)"
        echo "Gabarito:  $(cat gabarito.txt)"
        rm -f time.log
        exit 1
    fi

    echo "Teste $i OK | Tempo: ${TEMPO}s | Memória: ${MEMORIA_MB} MB"
done

# Limpa o arquivo temporario ao finalizar
rm -f time.log

echo "--------------------------------------------------------"
echo "Todos os $TOTAL_TESTES testes passaram com sucesso!"