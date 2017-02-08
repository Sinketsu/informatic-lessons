# python 3

n = int(input())

m92, c92 = 3010, 0
m95, c95 = 3010, 0
m98, c98 = 3010, 0

for i in range(0, n):
	# Так как это ЕГЭ, то мы не будем тратить процессорное время на проверки входных значений,
	# а также не будем проверять результаты функций и обрабатывать исключения.
	# Мне ужасно обидно за это, и я обещаю никогда так не писать в реальной жизни...
	company, street, mark, price = input().strip().split()
	if mark == '92':
		if price < m92:
			m92, c92 = price, 1
		elif price == m92:
			c92 += 1
	elif mark == '95':
		if price < m95:
			m95, c95 = price, 1
		elif price == m95:
			c95 += 1
	else:
		if price < m98:
			m98, c98 = price, 1
		elif price == m98:
			c98 += 1

print('{} {} {}'.format(c92, c95, c98))