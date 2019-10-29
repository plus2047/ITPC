#%% we can use this script to generate huge input data.
import random

with open("_main.in", "w") as f:
    def print_to_file(str):
        print(str, file=f)

    N, S = 50000, 1000
    print_to_file("%s %s" % (N, 1000))
    for i in range(N):
        skills = random.choices(range(S), k = 5)
        skills = [str(n + 1) for n in set(skills)]
        print_to_file("%s " % len(skills) + " ".join(skills))

#%% or we can use this script as a playground
