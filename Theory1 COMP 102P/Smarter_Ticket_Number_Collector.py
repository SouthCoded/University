import itertools

input = [3, 6]

digits = input[0]
goal = input[1]
total = 0 
print "Started"

def partitions(n, I=1):
    yield [n,]
    for i in range(I, n//2+1):
        for p in partitions(n-i, i):
            yield [i,] + p

r1 = list(partitions(goal))
print "Partions Done"

r5 = []
for x in r1:
	for y in x:
		over = False
		if y > 9 or len(x) > digits:
			over = True
	if over == False:
		r5.append(x)	

print "Filtering Done"

r2 = []
for x in range(len(r5)):
	if len(r5[x]) <= digits:	
		while len(r5[x]) < digits:
			r5[x].append(0)
		r2.append(r5[x])

print "Same Size Done"

r3 = set([])
for x in r2:
	r4 = set(itertools.permutations(x))
	r3 = (r3 | r4)

print "Permutations Done"

print len(r3)
