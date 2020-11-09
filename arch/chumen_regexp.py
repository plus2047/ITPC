import sys
from functools import lru_cache

# full match
@lru_cache(None)
def match(s, partten, i, j):
    if i == len(s) and j == len(partten):
        return True
    elif i == len(s) or j == len(partten):
        return False
    
    if j + 1 < len(partten) and partten[j + 1] == '*':
        if partten[j] == '.' or partten[j] == s[i]:
            return match(s, partten, i + 1, j) or\
                match(s, partten, i + 1, j + 2) or\
                match(s, partten, i, j + 2)
        else:
            return match(s, partten, i, j + 2)
    elif j + 1 < len(partten) and partten[j + 1] == '?':
        if partten[j] == '.' or partten[j] == s[i]:
            return match(s, partten, i + 1, j + 2) or match(s, partten, i, j + 2)
        else:
            return match(s, partten, i, j + 2)
    else:
        if partten[j] == '.' or partten[j] == s[i]:
            return match(s, partten, i + 1, j + 1)
        else:
            return False


def main():
    print(match("", "", 0, 0))
    print(match("a", "a",0, 0))
    print(match("a", ".", 0, 0))
    print(match("a", ".*", 0, 0))
    print(match("a", "a?", 0, 0))
    print(match("abcabc", "abc.*abc", 0, 0))
    print(match("abcabc", "abc?abc", 0, 0))
    print(match("abxxxacc", "abc.*abc", 0, 0))
    print(match("abcdabc", "abc?abc", 0, 0))


if __name__ == "__main__":
    main()
