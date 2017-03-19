d = 6									# минимальное расстояние

n = int(input())
queue = []
_min = 1000000
mc = 1001

for _ in range(n):
    c = int(input())
    queue.append(c)
    if len(queue) < 7:
        continue
    a = queue.pop(0)
    if a & 1 and a < mc:				# a & 1 - проверка на нечетность
        mc = a
    if (mc * c) & 1 and mc * c < _min:
        _min = mc * c
print(_min)