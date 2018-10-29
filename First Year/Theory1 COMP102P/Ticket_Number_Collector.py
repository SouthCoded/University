
input = [6, 12]

digits = input[0]
goal = input[1]
total = 0

number = 10 ** (digits) -1

for x in range(number):
	numTotal = 0
	full = x

	while(full > 0):
		part = full % 10
		numTotal += part
		full = full/10

	if numTotal == goal:
		total = total + 1
	

print(total)

