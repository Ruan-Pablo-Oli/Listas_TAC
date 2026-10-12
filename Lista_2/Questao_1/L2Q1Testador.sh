#!/bin/bash

CPP_FILE=${1:-L2Q1Sol.cpp}
EXEC="L2Q1"
NUM_TESTS=50

echo "=========================================="
echo " Compilando $CPP_FILE com g++ -O3..."
echo "=========================================="

g++ -O3 "$CPP_FILE" -o "$EXEC"
if [ $? -ne 0 ]; then
    echo -e "\033[0;31m[ERRO DE COMPILAÇÃO]\033[0m Falha ao compilar $CPP_FILE"
    exit 1
fi

echo -e "\033[0;32m[SUCESSO]\033[0m Compilado com sucesso!\n"
echo "Iniciando bateria de $NUM_TESTS testes..."
echo "------------------------------------------"

PASSED=0
FAILED=0

for i in $(seq 1 $NUM_TESTS); do
    # Gera in.txt e gabarito.txt
    python3 L2Q1Gerador.py

    # Executa o programa C++ medindo o tempo
    START=$(date +%s.%N)
    ./"$EXEC" < in.txt > out.txt
    END=$(date +%s.%N)

    RUNTIME=$(python3 -c "print(f'{$END - $START:.3f}')")

    # Compara a saída produzida com o gabarito
    diff -q -w out.txt gabarito.txt > /dev/null

    if [ $? -eq 0 ]; then
        echo -e "Teste #$i: \033[0;32m[PASSOU]\033[0m (Tempo: ${RUNTIME}s)"
        PASSED=$((PASSED + 1))
    else
        echo -e "Teste #$i: \033[0;31m[FALHOU]\033[0m (Tempo: ${RUNTIME}s)"
        FAILED=$((FAILED + 1))
        echo "--- Entrada (in.txt) ---"
        head -n 2 in.txt
        echo "--- Esperado (gabarito.txt) ---"
        cat gabarito.txt
        echo "--- Obtido (out.txt) ---"
        cat out.txt
        echo "------------------------------------------"
        break
    fi
done

echo "------------------------------------------"
if [ $FAILED -eq 0 ]; then
    echo -e "\033[0;32mTODOS OS $NUM_TESTS TESTES PASSARAM COM SUCESSO!\033[0m"
else
    echo -e "\033[0;31mRESULTADO: $PASSED aprovados, $FAILED falharam.\033[0m"
fi

# Limpeza de arquivos temporários
rm -f in.txt out.txt gabarito.txt "$EXEC"