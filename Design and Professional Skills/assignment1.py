import random 
import math
import re

hits = 0
total = 0
estimation = 0.0
best_estimate = 0.0

def generate_random_points():
	x = random.uniform(0,1)
	y = random.uniform(0,1)
	return x,y

def checker(x,y):
	global hits
	r = .5

	x = x -.5
	y = y-.5

	z = math.sqrt((x**2 + y**2))

	if z < r:
		 hits += 1
	
def estimate_pi(p):
	
	global total,estimation,hits,best_estimate

	try:
		if not (type(p) == int):
			raise ValueError()
	
	except ValueError:
		print "Must be an integer"
	
	else:

		if p > 7:
			print "I Wouldn't pick a number that high unless you want to wait a while"
		else:
			for m in range(p*5):
				
				total = 0
				hits = 0
				
				for l in range(p*100000):	
					x,y = generate_random_points()
					checker(x,y)
					total += 1
				
				estimation = (float(hits)/total) * 4

				best_estimate = (float(best_estimate) + estimation)/2

			best_estimate = "%0.*f" % (p, best_estimate)

			print best_estimate


#estimate_pi(8)

parantheses = []

def formatter(p):
	
	global parantheses
	subset = False

	for x in range(len(p)-4):
		temp = [p[x],p[x+1],p[x+2],p[x+3],p[x+4]]
		if temp == [1,2,3,2,4]:
			for m in range(4):
				p[x+m] = 9
			p[x+4] = 2
	l = []
	for m in p:
		if m != 9 :
			l.append(m)
	if len(l) > 4:
		for x in range(len(l)-4):
			temp = [l[x],l[x+1],l[x+2],l[x+3],l[x+4]]
			if temp == [1,2,3,2,4]:
				formatter(l)
			else:
				return ValueError
	elif l != [2]:
		return ValueError


def operations(num1,op,num2):
	if op == "+":
		return str(int(num1)+int(num2))
	if op == "-":
		return str(int(num1)-int(num2))
	if op == "*":
		return str(int(num1)*int(num2))
	if op == "/":
		return str(int(num1)/int(num2))

def calculate(e):
	l = []
	for x in range(len(e)):
		if e[x] == "(" and e[x+4] == ")":
			ans = operations(e[x+1],e[x+2],e[x+3])
			l.append(ans)
			for m in range(5):
					e[x+m] = " "
		else:
			if e[x] != " ":
				l.append(e[x])
	if len(l) > 1:
		calculate(l)
	else: 
		print l[0]

def calculator(exp):

	expression = list(str(exp).replace(" ", "")) 	#Takes out the spaces to make it easier to deal with 
	

	terms = {"1","2","3","4","5","6","7","8","9","0","*","-","+","/","(",")"}
	operands = {"*","-","+","/"}
	numbers = {"1","2","3","4","5","6","7","8","9","0"}

	try:
		
		#Checks for invalid characters
		for x in range(len(expression)):
	   		if expression[x] not in terms:
	   			raise ValueError

	   	#Checks for negative numbers
	   	for x in range(len(expression)-1):
	   		if expression[x] == "-":
	   			if expression[x+1] in numbers:
	   				raise ValueError

	   	l = []
		for x in range(len(expression)):
			if expression[x] not in numbers:
				l.append(expression[x])
			elif expression[x] in numbers and expression[x-1] not in numbers:
				if expression[x+1] in numbers:
					length = 0
					for y in range(len(expression)-x):
						while expression[x+y] in numbers:
							length += 1
							y += 1
						break
					num = int(''.join(map(str,expression[x:length+x])))
					l.append(str(num))					
				else:
					l.append(expression[x])

		expression = l
			
	   	for p in range(len(expression)):
			
			if expression[p] == "(":
				parantheses.append(1)

			elif expression[p] == ")":
				parantheses.append(4)

			elif expression[p] in operands:
				parantheses.append(3)
			
			else:
				parantheses.append(2)

		ans = formatter(parantheses)
		if ans != None:
			raise ans
		
	except ValueError:
		print "Invalid Characters"

	else:
		calculate(expression)


calculator("((100+4)+(52*4))")




