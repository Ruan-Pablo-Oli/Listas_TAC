import random
import sys

def resolver_gabarito(A, k):
    # Somas de 1 elemento
    somas = set(A)
    
    # Se k = 1, verifica se 0 está no vetor
    if k == 1:
        return "Sim" if 0 in somas else "Nao"
    
    # Somas de 2 elementos (S_2 = S_1 + S_1)
    somas_2 = {x + y for x in somas for y in somas}
    if k == 2:
        return "Sim" if 0 in somas_2 else "Nao"
        
    # Somas de 4 elementos (S_4 = S_2 + S_2)
    somas_4 = {x + y for x in somas_2 for y in somas_2}
    if k == 4:
        return "Sim" if 0 in somas_4 else "Nao"
        
    # Somas de 8 elementos (S_8 = S_4 + S_4)
    somas_8 = {x + y for x in somas_4 for y in somas_4}
    if k == 8:
        return "Sim" if 0 in somas_8 else "Nao"

def gerar_caso():
    k_opcoes = [1, 2, 4, 8]
    k = random.choice(k_opcoes)
    
    # Gera n entre 10 e 500 para testes rápidos locais
    n = random.randint(10, 500)
    
    # Seleciona 'n' inteiros distintos no intervalo [-1000, 1000]
    valores = random.sample(range(-1000, 1001), n)
    valores.sort() # Garante que a entrada esteja ordenada
    
    return n, k, valores

if __name__ == "__main__":
    n, k, A = gerar_caso()
    gabarito = resolver_gabarito(A, k)
    
    # Escreve a entrada em in.txt
    with open("in.txt", "w") as f:
        f.write(f"{n} {k}\n")
        f.write(" ".join(map(str, A)) + "\n")
        
    # Escreve a saída esperada em gabarito.txt
    with open("gabarito.txt", "w") as f:
        f.write(f"{gabarito}\n")