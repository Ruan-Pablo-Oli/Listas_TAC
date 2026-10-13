import random

def solve_reference(n, k, peso):
    low = max(peso)
    high = sum(peso)
    ans = high

    def can_ship(capacity):
        days = 1
        current_weight = 0
        for w in peso:
            if current_weight + w > capacity:
                days += 1
                current_weight = w
            else:
                current_weight += w
        return days <= k

    while low <= high:
        mid = (low + high) // 2
        if can_ship(mid):
            ans = mid
            high = mid - 1
        else:
            low = mid + 1

    return ans

def generate_case():
    case_type = random.choice([
        "example", 
        "k_equals_1", 
        "k_equals_n", 
        "uniform_weights", 
        "random_small", 
        "random_large"
    ])

    if case_type == "example":
        exs = [
            (5, 2, [13, 10, 7, 5, 15]),
            (5, 3, [4, 2, 10, 3, 8]),
            (8, 3, [3, 1, 4, 1, 1, 1, 1, 1])
        ]
        n, k, peso = random.choice(exs)

    elif case_type == "k_equals_1":
        n = random.randint(1, 1000)
        k = 1
        peso = [random.randint(1, 10**6) for _ in range(n)]

    elif case_type == "k_equals_n":
        n = random.randint(1, 1000)
        k = n
        peso = [random.randint(1, 10**6) for _ in range(n)]

    elif case_type == "uniform_weights":
        n = random.randint(10, 5000)
        k = random.randint(1, n)
        val = random.randint(1, 10**6)
        peso = [val] * n

    elif case_type == "random_small":
        n = random.randint(1, 100)
        k = random.randint(1, n)
        peso = [random.randint(1, 1000) for _ in range(n)]

    else: # random_large
        n = random.randint(10000, 100000)
        k = random.randint(1, n)
        peso = [random.randint(1, 10**8) for _ in range(n)]

    ans = solve_reference(n, k, peso)
    return n, k, peso, ans

if __name__ == "__main__":
    n, k, peso, ans = generate_case()

    with open("in.txt", "w") as f_in:
        f_in.write(f"{n} {k}\n")
        f_in.write(" ".join(map(str, peso)) + "\n")

    with open("gabarito.txt", "w") as f_out:
        f_out.write(f"{ans}\n")