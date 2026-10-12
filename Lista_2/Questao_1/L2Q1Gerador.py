import random
import sys

def solve_reference(n, A):
    # Solução de referência para gerar o gabarito
    for k in range(1, n + 1):
        if A[n - k] >= k and (n - k == 0 or A[n - k - 1] < k):
            return k
    return -1

def generate_case():
    case_type = random.choice([
        "example", 
        "all_zeros", 
        "all_same", 
        "random_small", 
        "random_large", 
        "exact_k"
    ])
    
    if case_type == "example":
        exs = [
            (3, [0, 0, 0]),
            (4, [4, 4, 4, 5]),
            (8, [0, 1, 3, 6, 7, 9, 9, 10])
        ]
        n, A = random.choice(exs)
        
    elif case_type == "all_zeros":
        n = random.randint(1, 5000)
        A = [0] * n
        
    elif case_type == "all_same":
        n = random.randint(1, 5000)
        val = random.randint(1, 10000)
        A = [val] * n
        
    elif case_type == "exact_k":
        # Garante a construção de um array que possui um k válido
        n = random.randint(1, 50000)
        target_k = random.randint(1, n)
        small_part = [random.randint(0, max(0, target_k - 1)) for _ in range(n - target_k)]
        large_part = [random.randint(target_k, target_k + 100000) for _ in range(target_k)]
        A = sorted(small_part + large_part)
        
    elif case_type == "random_small":
        n = random.randint(1, 100)
        A = sorted([random.randint(0, 200) for _ in range(n)])
        
    else: # random_large
        n = random.randint(1000, 100000)
        A = sorted([random.randint(0, 200000) for _ in range(n)])

    ans = solve_reference(n, A)
    return n, A, ans

if __name__ == "__main__":
    n, A, ans = generate_case()
    
    with open("in.txt", "w") as f_in:
        f_in.write(f"{n}\n")
        f_in.write(" ".join(map(str, A)) + "\n")
        
    with open("gabarito.txt", "w") as f_out:
        f_out.write(f"{ans}\n")