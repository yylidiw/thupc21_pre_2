import sys

maxl = 998244353

def check(num):
    datas = open("../data/{}.in".format(num),"r")

    n, k = datas.readline().split(" ")
    n, k = int(n), int(k)

    if k >= n:
        return False
    if n > 12 or n < 2:
        return False

    g = set()
    count = 0

    while True:
        data = datas.readline()
        if not data:
            break
        x, y, p, q = data.split(" ")
        x, y, p, q = int(x), int(y), int(p), int(q)

        if x == y:
            return False

        if x < 1 or x > n:
            return False
        if y < 1 or y > n:
            return False
        if not (0 <= p <= q < maxl and q > 0):
            return False
        if (x,y) not in g:
            g.add((x,y))
            count += 1
        else:
            return False

    return count == (n * (n-1)) 


if __name__ == "__main__":
    for i in range(1,21):
        if not check(i):
            print("Error {}".format(i))
        else:
            print("Pass check {}".format(i))