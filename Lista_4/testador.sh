#!/bin/bash

# Verifica se os argumentos necessários foram fornecidos
if [ "$#" -ne 2 ]; then
    echo "Uso: $0 <codigo.cpp> <diretoria_dos_testes>"
    exit 1
fi

CODIGO=$1
DIRETORIA=$2
EXECUTAVEL="./programa_teste"

echo "A compilar $CODIGO..."
g++ -O2 -Wall "$CODIGO" -o "$EXECUTAVEL"

if [ $? -ne 0 ]; then
    echo "Erro de compilação. Abortando."
    exit 1
fi

echo "A iniciar testes..."
echo "------------------------"

# Percorre todos os ficheiros de entrada
for input_file in "$DIRETORIA"/*.in; do
    base_name=$(basename "$input_file" .in)
    expected_output="$DIRETORIA/$base_name.out"
    
    # Executa o programa redirecionando a entrada e capturando a saída
    $EXECUTAVEL < "$input_file" > "resultado_temp.out"
    
    # Compara o resultado com o ficheiro .out (ignorando espaços em branco no final das linhas com -w)
    if diff -w "resultado_temp.out" "$expected_output" > /dev/null; then
        echo -e "Teste $base_name: \e[32mPASSOU\e[0m"
    else
        echo -e "Teste $base_name: \e[31mFALHOU\e[0m"
        echo "--- Esperado ---"
        cat "$expected_output"
        echo "--- Obtido ---"
        cat "resultado_temp.out"
        echo "------------------------"
    fi
done

# Limpeza dos ficheiros temporários
rm "$EXECUTAVEL" "resultado_temp.out"
