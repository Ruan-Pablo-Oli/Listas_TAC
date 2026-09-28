import sys
import random
import string
from collections import Counter

# ==============================================================================
# 1. CASOS DE TESTE MANUAIS (Exemplos do enunciado e testes de borda)
# ==============================================================================
CASOS_MANUAIS = [
    ("bbaa", "aba"),           # Exemplo 1 -> Nao
    ("ab", "baaab"),          # Exemplo 2 -> 0 \n 3
    ("aa", "xxaaabbaya"),     # Exemplo 3 -> 2 \n 3
    ("a", "aaaaa"),           # Anagramas sobrepostos contínuos -> 0, 1, 2, 3, 4
    ("abcd", "abc"),          # |s| < |r| -> Nao
    ("abc", "abc"),           # |s| == |r| exato -> 0
]

# ==============================================================================
# 2. GERADOR ALEATÓRIO DE CASOS (Até 10^6 caracteres)
# ==============================================================================
def gerar_caso_aleatorio():
    tam_r = random.randint(1, 500)
    tam_s = random.randint(tam_r, 100000) # Pode aumentar para 1000000 para estresse máximo
    
    letras = string.ascii_lowercase
    r = ''.join(random.choice(letras) for _ in range(tam_r))
    s_list = [random.choice(letras) for _ in range(tam_s)]
    
    # Injeta de 1 a 5 anagramas aleatórios de r em posições randômicas de s
    num_injecoes = random.randint(0, 5)
    for _ in range(num_injecoes):
        anagrama_r = ''.join(random.sample(r, len(r)))
        pos = random.randint(0, tam_s - tam_r)
        s_list[pos : pos + tam_r] = list(anagrama_r)

    s = ''.join(s_list)
    return r, s

# ==============================================================================
# 3. GABARITO / SOLUÇÃO DE REFERÊNCIA (Coleta todos os índices em O(N))
# ==============================================================================
def resolver_gabarito(r, s):
    tam_r = len(r)
    tam_s = len(s)
    
    if tam_s < tam_r:
        return "Nao"

    freq_r = Counter(r)
    freq_s = Counter(s[:tam_r])
    
    indices = []

    # Checa primeira janela (índice 0)
    if freq_r == freq_s:
        indices.append(0)

    # Desliza a janela pelas posições restantes
    for i in range(tam_r, tam_s):
        # Entra o caractere da direita
        freq_s[s[i]] += 1
        
        # Sai o caractere da esquerda
        saindo = s[i - tam_r]
        freq_s[saindo] -= 1
        if freq_s[saindo] == 0:
            del freq_s[saindo]

        # Se for anagrama, o índice de início é (i - tam_r + 1)
        if freq_r == freq_s:
            indices.append(i - tam_r + 1)

    if not indices:
        return "Nao"
    
    # Formata cada índice em uma nova linha
    return "\n".join(str(idx) for idx in indices)

# ==============================================================================
# 4. FLUXO PRINCIPAL
# ==============================================================================
if __name__ == "__main__":
    num_teste = int(sys.argv[1]) if len(sys.argv) > 1 else 1

    if num_teste <= len(CASOS_MANUAIS):
        r, s = CASOS_MANUAIS[num_teste - 1]
    else:
        r, s = gerar_caso_aleatorio()

    gabarito = resolver_gabarito(r, s)

    with open("in.txt", "w") as f:
        f.write(f"{r} {s}\n")

    with open("gabarito.txt", "w") as f:
        f.write(f"{gabarito}\n")