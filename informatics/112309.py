
s1 = set()
s2 = set()
flag = True

input()
a = input().split(' ')

for item in a:
    if item not in s1:
        s1.add(item)
        continue
    if item not in s2:
        print(item, end=' ')
        flag = False
        s2.add(item)

if flag:
    print(0)