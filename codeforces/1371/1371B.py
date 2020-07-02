import sys
 
 
def read_num_list():
    return [int(i) for i in sys.stdin.readline().split()]
 
 
def solve(_turn):
    n, r = read_num_list()
    a = min(n - 1, r)
    res = a * (a + 1) // 2
    if r >= n:
        res += 1
    print(res)
 
 
def main():
    T = read_num_list()[0]
    for i in range(T):
        solve(i + 1)
 
 
if __name__ == "__main__":
    main()