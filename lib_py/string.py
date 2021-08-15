def getKmpNext(pattern):
    """ get KMP next arrray

    next[i] is the biggest k s.t. pattern[:k] == pattern[:i + 1][-k:]
    """
    nextArr = [0] * len(pattern)
    i, j = 1, 0
    while i < len(pattern):
        while j and pattern[j] != pattern[i]:
            j = nextArr[j - 1]
        if pattern[i] == pattern[j]:
            j += 1
        nextArr[i] = j
        i += 1
    return nextArr


def kmpFind(pattern, target, nextArr):
    i, j = 0, 0
    while i < len(target):
        while j and pattern[j] != target[i]:
            j = next[j - 1]
        if pattern[j] == target[i]:
            j += 1
        if j == len(pattern):
            return i - j + 1
    return -1


def manacher(s):
    t = "^#" + "#".join(s) + "#$"
    arm = [0] * len(t)
    right = center = 0
    for i in range(1, len(t) - 1):
        if i < right:
            arm[i] = min(arm[center * 2 - i], right - i)
        while t[i - arm[i] - 1] == t[i + arm[i] + 1]:
            arm[i] += 1
        if i + arm[i] > right:
            right, center = i + arm[i], i
    return arm[2:-2:2]
