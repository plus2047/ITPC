import heapq

def has_word(string, blacklist, whitelist):
    whilte_matches = []
    for word in whitelist:
        if not word:
            continue
        start = 0
        while start < len(string):
            start = string.find(word, start)
            if start == -1:
                break
            whilte_matches.append((start, start + len(word)))
            start += len(word)

    black_matches = []
    for word in blacklist:
        if not word:
            continue
        start = 0
        while start < len(string):
            start = string.find(word, start)
            if start == -1:
                break
            black_matches.append((start, start + len(word)))
            start += len(word)

    black_matches.sort()
    whilte_matches.sort()

    max_white_end_heap = []
    current_whilte = 0

    for black_start, black_end in black_matches:
        # add all white matches that start before the black match
        while current_whilte < len(whilte_matches) and whilte_matches[current_whilte][0] <= black_start:
            white_start, white_end = whilte_matches[current_whilte]
            heapq.heappush(max_white_end_heap, (-white_end, white_start))
            current_whilte += 1        

        if not (max_white_end_heap and -max_white_end_heap[0][0] >= black_end):
            return True

    return False


# %%
def main():
    # print(has_word("helloworld!!!", ["world"], ["oworld!"]))
    # print(has_word("helloworld!!!", ["world"], ["world"]))
    # print(has_word("helloworld!!!", ["world"], ["oworld!"]))
    # print(has_word("helloworld!!!", ["world"], []))
    # print(has_word("helloworld!!!", ["world"], ["owo"]))

    assert has_word("helloworld!!!", [], []) is False
    assert has_word("helloworld!!!", [""], []) is False

    assert has_word("helloworld!!!", ["he"], []) is True
    assert has_word("helloworld!!!", ["!!"], []) is True

    assert has_word("helloworld!!!", ["he"], ["hel"]) is False
    assert has_word("helloworld!!!", ["!!"], ["!!!"]) is False

    assert has_word("helloworld!!!", ["ll", "owo"], []) is True
    assert has_word("helloworld!!!", ["ll", "owo"], ["ell"]) is True
    assert has_word("helloworld!!!", ["ll", "owo"], ["llo", "owor"]) is False

    assert has_word("helloworldandworld!!!", ["world"], []) is True
    assert has_word("helloworldandworld!!!", ["world"], ["oworld"]) is True
    assert has_word("helloworldandworld!!!", ["world"], ["oworld", "dworld"]) is False
    assert has_word("helloworldandworld!!!", ["world"], ["world"]) is False

    print("Done")


if __name__ == "__main__":
    main()

# %%
