# %%
def rgbSort(arr):
    n = len(arr)
    p1 = p2 = n - 1
    p0 = 0
    while p0 <= p1:
        if arr[p0] == 'g':
            arr[p0], arr[p1] = arr[p1], arr[p0]
            p1 -= 1
        elif arr[p0] == 'b':
            arr[p0], arr[p1] = arr[p1], arr[p0]
            arr[p1], arr[p2] = arr[p2], arr[p1]
            p2 -= 1
            p1 -= 1
        else:
            p0 += 1
    return arr

def main():
    print(rgbSort(['b', 'r', 'g', 'g', 'r', 'b']))
    print(rgbSort(['r', 'b', 'b', 'r', 'g', 'g', 'r', 'b']))
    print(rgbSort(['r']))
    print(rgbSort([]))

    print("HelloWorld!!!")


if __name__ == "__main__":
    main()

# %%
