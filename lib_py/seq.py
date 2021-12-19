import bisect


def longest_increase_subseq(arr):
    inc = []
    for x in arr:
        i = bisect.bisect(inc, x)
        if i == len(inc):
            inc.append(x)
        else:
            inc[i] = x
    return len(inc)
