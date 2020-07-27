import random


def digit_count(n, d):
    ns = str(n)
    size = len(ns)
    loop_cnt = 10 ** (size - 1)
    total = 0
    for i, c in enumerate(ns):
        cnt = 0
        if i != 0:
            loop_n = int(ns[:i])
            cnt += loop_cnt * (loop_n if d != 0 else loop_n - 1)

        if int(c) == d:
            cnt += 1 if i == size - 1 else int(ns[i + 1:]) + 1
        elif int(c) > d and (i != 0 or d != 0):
            cnt += loop_cnt

        total += cnt
        loop_cnt //= 10

    return total


def nth_element(vec, n):
    size = len(vec)
    if size <= 1 or n >= size:
        return vec

    left, right = 0, size
    while True:

        mid = vec[left]
        while True:
            while right - 1 > left and vec[right - 1] >= mid:
                right -= 1
            right -= 1
            if left == right:
                break
            vec[left] = vec[right]
            while left + 1 < right and vec[left + 1] <= mid:
                left += 1
            left += 1
            if left == right:
                break
            vec[right] = vec[left]

        vec[left] = mid

        if left == n:
            break
        elif left < n:
            left, right = left + 1, size
        elif left > n:
            left, right = 0, left

    return vec


def word_count(s, n, test=False):
    from collections import Counter
    cnt = Counter(s.split())
    cnt_to_word = [(v, k) for k, v in cnt.items()]
    if test:
        return sorted(cnt_to_word)[-n:]
    else:
        nth_element(cnt_to_word, len(cnt_to_word) - n)
        return cnt_to_word[-n:]


def main():
    def test_digit_count():

        def check_count(n, d):
            total = 0
            for i in range(1, n + 1):
                for c in str(i):
                    total += int(c) == d
            return total

        for i in range(1, 1000):
            for j in range(10):
                if check_count(i, j) != digit_count(i, j):
                    print(i, j, check_count(i, j), digit_count(i, j))
                    return False
        return True

    def test_nth_element():
        for i in range(100):
            vec = []
            for j in range(100):
                vec.append(random.random())
            n = random.randint(0, 99)
            vec = nth_element(vec, n)
            if vec[n] != sorted(vec)[n]:
                print(vec)
                return False
        return True

    def test_word_count():
        for t in range(10):
            nums = []
            for i in range(100):
                nums.append(random.randint(0, 20))
            s = " ".join(str(n) for n in nums)
            s1 = set(word_count(s, 10, True))
            s2 = set(word_count(s, 10, False))
            if s1 != s2:
                print(s1, s2)
                print(s)
                return False
        return True

    if test_digit_count():
        print("digit count test pass")
    if test_nth_element():
        print("nth element test pass")
    if test_word_count():
        print("word count test pass")


if __name__ == "__main__":
    main()
