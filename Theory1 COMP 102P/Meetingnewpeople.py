
inputs = [5925,1456018]

order = []

length = inputs[1]

ori = inputs[0]
first = [ori,1]
order.append(first)
ori = (ori * 31334) % 31337
second = [ori,2]
order.append(second)


for x in range(length-2):
	ori = (ori * 31334) % 31337
	temp = [ori,x+3]
	order.append(temp)

order.sort()

p = 0
for x in order:
	p = p + 1
	if x[1] == length:
		print p
