import math

a, b = input().split(' ')
a = int(a)
b = int(b)

flag = True

lim1 = math.ceil(math.sqrt(a))
lim2 = math.ceil(math.sqrt(b))

sum = 0
for i in range(2, lim1):
    if a % i == 0:
        t = a // i
        sum += i
        if t != i:
            sum += t
sum += 1  # increment for divider 1
if sum != b:
    flag = False

sum ^= sum
for i in range(2, lim2):
    if b % i == 0:
        t = b // i
        sum += i
        if t != i:
            sum += t
sum += 1  # increment for divider 1
if sum != a:
    flag = False

print('YES' if flag else 'NO')