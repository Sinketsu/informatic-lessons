cmax, nmax = -2001, -2001

n = int(input())
for _ in range(n):
    c = int(input())
    if c&1:
        if c > nmax:
            nmax = c
    else:
        if c > cmax:
            cmax = c

_R = cmax + nmax
if _R > 0 and _R&1:
    pass
else:
    _R = -1
R = int(input())
print('Вычисленное контрольное значение: {}'.format(_R))
if R == _R:
    print('Контроль пройден')
else:
    print('Контроль не пройден')