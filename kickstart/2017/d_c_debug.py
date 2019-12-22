# %%
# get sample
def read_num_list(f):
    return [int(x) for x in f.readline().split()]


sample_idx = 21
with open("_main.in") as f:
    T = read_num_list(f)[0]
    for i in range(T):
        N, P, H = read_num_list(f)
        if i == sample_idx:
            print(" ".join((str(x) for x in (N, P, H))))
        for line in range(N):
            line = f.readline()
            if i == sample_idx:
                print(line, end="")


# %%
# compare output
import numpy as np
def get_nums(f):
    s = open(f).read().split("\n")
    s = [float(x.split()[2]) for x in s if x != ""]
    return s


def diff(nums1, nums2):
    return [abs(nums1[i] - nums2[i]) for i in range(len(nums1))]

nums1, nums2 = get_nums("_main.out"), get_nums("_main_ref.out")

d = np.asarray(diff(nums1, nums2))
print(d)
print(np.max(d))
print(np.argmax(d))

# %%
