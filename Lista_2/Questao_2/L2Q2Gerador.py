import random

def solve_reference(n, A, m, B):
    sum_A = sum(A)
    sum_B = sum(B)
    diff = sum_B - sum_A
    
    # Se a diferença for ímpar, é impossível igualar as somas
    if diff % 2 != 0:
        return "-1"
        
    delta = diff // 2
    set_B = set(B)
    sorted_A = sorted(list(set(A)))
    
    # Busca pelo menor x que possui um y correspondente em B
    for x in sorted_A:
        y = x + delta
        if y in set_B:
            return f"{x} {y}"
            
    return "-1"

def generate_case():
    case_type = random.choice([
        "example", 
        "no_solution_odd", 
        "random_small", 
        "random_large", 
        "same_values"
    ])
    
    if case_type == "example":
        exs = [
            (3, [1, 2, 1], 3, [2, 2, 2]),
            (4, [4, 1, 2, 1], 4, [1, 5, 2, 2]),
            (6, [2, 1, 1, 1, 7, 4], 4, [3, 1, 2, 4])
        ]
        n, A, m, B = random.choice(exs)
        
    elif case_type == "no_solution_odd":
        n = random.randint(1, 1000)
        m = random.randint(1, 1000)
        A = [random.randint(1, 100) for _ in range(n)]
        B = [random.randint(1, 100) for _ in range(m)]
        # Força diferença ímpar entre as somas
        if (sum(B) - sum(A)) % 2 == 0:
            B[0] += 1
            
    elif case_type == "same_values":
        n = random.randint(100, 5000)
        m = random.randint(100, 5000)
        val_a = random.randint(1, 1000)
        val_b = random.randint(1, 1000)
        A = [val_a] * n
        B = [val_b] * m
        
    elif case_type == "random_small":
        n = random.randint(1, 100)
        m = random.randint(1, 100)
        A = [random.randint(1, 200) for _ in range(n)]
        B = [random.randint(1, 200) for _ in range(m)]
        
    else: # random_large
        n = random.randint(10000, 100000)
        m = random.randint(10000, 100000)
        A = [random.randint(1, 10**8) for _ in range(n)]
        B = [random.randint(1, 10**8) for _ in range(m)]

    ans = solve_reference(n, A, m, B)
    return n, A, m, B, ans

if __name__ == "__main__":
    n, A, m, B, ans = generate_case()
    
    with open("in.txt", "w") as f_in:
        f_in.write(f"{n}\n")
        f_in.write(" ".join(map(str, A)) + "\n")
        f_in.write(f"{m}\n")
        f_in.write(" ".join(map(str, B)) + "\n")
        
    with open("gabarito.txt", "w") as f_out:
        f_out.write(f"{ans}\n")