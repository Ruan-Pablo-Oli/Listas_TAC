#!/bin/bash

# Compila o código C++
g++ -std=c++17 -o Q1 Q1.cpp
if [ $? -ne 0 ]; then
  echo -e "\e[31mErro de compilação!\e[0m"
  exit 1
fi

total=0
passaram=0

# Lê in.txt e out.txt simultaneamente usando descritores de arquivo
exec 3<in.txt
exec 4<out.txt

echo "Iniciando bateria de testes..."

while read -r linha_in <&3 && read -r linha_out_esperada <&4; do
  ((total++))

  # Roda o programa passando a linha atual
  saida_programa=$(echo "$linha_in" | ./Q1 | tr -d '\r\n')
  linha_out_esperada=$(echo "$linha_out_esperada" | tr -d '\r\n')

  if [ "$saida_programa" == "$linha_out_esperada" ]; then
    echo -e "\e[32m[OK]\e[0m Teste $total passou."
    ((passaram++))
  else
    echo -e "\e[31m[FALHA]\e[0m Teste $total"
    echo "  Entrada  : $linha_in"
    echo "  Esperado : '$linha_out_esperada'"
    echo "  Recebido : '$saida_programa'"
  fi
done

# Fecha os descritores
exec 3<&-
exec 4<&-

echo "======================================="
if [ "$passaram" -eq "$total" ]; then
  echo -e "\e[32mResultado: TODOS os $total testes passaram!\e[0m"
else
  echo -e "\e[33mResultado: $passaram / $total testes passaram.\e[0m"
fi
