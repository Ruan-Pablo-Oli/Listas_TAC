import sys
import random
import string
from collections import Counter

# ==============================================================================
# 1. CASOS DE TESTE MANUAIS (Adicione aqui suas entradas customizadas)
# ==============================================================================
# Formato: (r, s)
CASOS_MANUAIS = [
    ("bba", "abb"),
    ("bbaa", "aba"),
    ("a", "b"),
    ("abcabc", "xxabcabyy"),
    ("aba", "aab"),              # Teste de borda: anagrama no início
    ("aba", "baa"),              # Teste de borda: anagrama no fim
    ("abcd", "abc"),             # Teste de borda: |s| < |r|
    ("a", "a"),                  # Teste mínimo
]

# ==============================================================================
# 2. GERADOR ALEATÓRIO DE CASOS (Configurável por problema)
# ==============================================================================
def gerar_caso_aleatorio():
    # Tamanhos ajustados para o novo limite de 10^6
    tam_r = random.randint(1, 1000000)
    tam_s = random.randint(tam_r, 1000000) # Use 1000000 para estresse máximo
    
    letras = string.ascii_lowercase
    r = ''.join(random.choice(letras) for _ in range(tam_r))
    s = ''.join(random.choice(letras) for _ in range(tam_s))
    
    # 50% de chance de forçar a existência do anagrama em s
    if random.random() > 0.5:
        anagrama_r = ''.join(random.sample(r, len(r)))
        pos_insercao = random.randint(0, len(s) - len(r))
        s = s[:pos_insercao] + anagrama_r + s[pos_insercao + len(r):]

    return r, s

# ==============================================================================
# 3. GABARITO / SOLUÇÃO DE REFERÊNCIA OTIMIZADA O(N)
# ==============================================================================
def resolver_gabarito(r, s):
    tam_r = len(r)
    tam_s = len(s)
    
    if tam_s < tam_r:
        return "Nao"

    freq_r = Counter(r)
    freq_s = Counter(s[:tam_r])

    if freq_r == freq_s:
        return "Sim"

    for i in range(tam_r, tam_s):
        freq_s[s[i]] += 1
        saindo = s[i - tam_r]
        freq_s[saindo] -= 1
        if freq_s[saindo] == 0:
            del freq_s[saindo]

        if freq_r == freq_s:
            return "Sim"

    return "Nao"

# ==============================================================================
# 4. FLUXO PRINCIPAL
# ==============================================================================
if __name__ == "__main__":
    # Recebe o número da iteração atual via argumento de linha de comando
    num_teste = int(sys.argv[1]) if len(sys.argv) > 1 else 1

    # Decide se usa caso manual ou gera um aleatório
    if num_teste <= len(CASOS_MANUAIS):
        r, s = CASOS_MANUAIS[num_teste - 1]
    else:
        r, s = gerar_caso_aleatorio()

    gabarito = resolver_gabarito(r, s)

    # Escreve nos arquivos de entrada e gabarito
    with open("in.txt", "w") as f:
        f.write(f"{r} {s}\n")

    with open("gabarito.txt", "w") as f:
        f.write(f"{gabarito}\n")