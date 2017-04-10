# our size of "window"
d = 8

n = int(input())
queue = []
x = -1
_max = -1

for _ in range(d):
    queue.append(int(input()))

n -= d

for _ in range(n):
    c = queue.pop(0)
    if c > _max:
        _max = c
    c = int(input())
    if c * _max > x:
        x = c * _max

print(x)