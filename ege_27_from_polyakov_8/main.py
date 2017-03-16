m1 = -1
m2 = -1
m0_1 = -1
m0_2 = -1

n = int(input())
for _ in range(0, n):
    a = int(input())
    if a % 3 == 0:
        if a >= m0_1:
            m0_1, m0_2 = a, m0_1
        elif a > m0_2:
            m0_2 = a
    elif a % 3 == 1:
        m1 = max(m1, a)
    else:
        m2 = max(m2, a)
check_sum = int(input())
if (m1 == -1 or m2 == -1) and m0_2 == -1:
    our_chk_sum = 1
else:
    our_chk_sum = max(m1 + m2, m0_1 + m0_2)
print('Вычисленное контрольное значение: {}'.format(our_chk_sum))
if check_sum == our_chk_sum:
    print('Контроль пройден')
else:
    print('Контроль не пройден')