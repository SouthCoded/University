from fractions import gcd

list = [3,7,14]

final = 0
total = 0

for x in range(len(list)-1):
  final = gcd(list[x],list[x+1])
  for final in range(len(list)-1):
  		gcd(final,list[x])

for x in range(len(list)):
	total = total + (list[x]/final)

print(str(final) + " " + str(total))
