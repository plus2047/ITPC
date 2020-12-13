import sys

def get_level(cnt):
    cnt3w = cnt1w = cnt5k = 0
    last3w = -5
    for i, x in enumerate(cnt):
        if x > 30000 and i - last3w > 4:
            last3w = i
            cnt3w += 1
        if x > 10000:
            cnt1w += 1
        elif x > 5000:
            cnt5k += 1
    if cnt3w >= 4:
        return 2
    elif cnt1w >= 15:
        return 3
    elif cnt5k >= 15:
        return 4
    else:
        return 5


judge = {
    2: "excellent",
    3: "excellent",
    4: "good",
    5: "bad"
}


def main():
    lines = sys.stdin.readlines()
    scores = []  # (level, step, order, name)
    for i, p in enumerate(lines):
        words = p.strip().split(":")
        name = words[0]
        cnt = [int(x) for x in words[1].split()]
        scores.append((get_level(cnt), -sum(cnt), i, name))
    scores.sort()
    for level, total, order, name in scores:
        print(f"{name}:{judge[level]} {-total}")


if __name__ == "__main__":
    main()

# %%
