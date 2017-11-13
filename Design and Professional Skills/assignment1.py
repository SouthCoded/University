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
		print ("Must be an integer")
	
	else:

		if p > 7:
			print ("I Wouldn't pick a number that high unless you want to wait a while")
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

			print (best_estimate)


#estimate_pi(8)

def alphabetFrequency(x):
    return {
        'a': 0,
        'b': 1,
        'c': 2,
        'd': 3,
        'e': 4,
        'f': 5,
        'g': 6,
        'h': 7,
        'i': 8,
        'j': 9,
        'k': 10,
        'l': 11,
        'm': 12,
        'n': 13,
        'o': 14,
        'p': 15,
        'q': 16,
        'r': 17,
        's': 18,
        't': 19,
        'u': 20,
        'v': 21,
        'w': 22,
        'x': 23,
        'y': 24,
        'z': 25,
    }[x]

def letterReplacement(x):
    
    return {
        0: 'e',
        1: 't',
        2: 'a',
        3: 'o',
        4: 'i',
        5: 'n',
        6: 's',
        7: 'h',
        8: 'r',
        9: 'd',
        10: 'l',
        11: 'u', 
        12: 'c',
		13: 'm',
		14: 'w',
		15: 'f',
		16: 'y',
		17: 'g', 
		18: 'p',
		19: 'b',
		20: 'v',
		21: 'k',
		22: 'x',
		23: 'j',
		24: 'q',
		25: 'z'
    }[x]

def break_cipher(text):

	text = text.lower()
	text = list(text)
	total = len(text)

	textFrequency = [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0]
	letterList = ["","","","","","","","","","","","","","","","","","","","","","","","","",""]

	for x in text:
		position = alphabetFrequency(x)
		textFrequency[position] += 1

	for x in range(len(textFrequency)):
		textFrequency[x] = textFrequency[x]/total

	sortedTextFrequency = sorted(textFrequency, reverse=True)

	for x in range(len(textFrequency)):
		for y in range(len(sortedTextFrequency)):
			if textFrequency[x] == sortedTextFrequency[y]:
				letter = letterReplacement(y)
				letterList[x] = letter

	for x in range(len(text)):
		position = alphabetFrequency(text[x])
		text[x] = letterList[position]

	text = " ".join(str(x) for x in text)

	print(text)

break_cipher("LIVITCSWPIYVEWHEVSRIQMXLEYVEOIEWHRXEXIPFEMVEWHKVSTYLXZIXLIKIIXPIJVSZEYPERRGERIMWQLMGLMXQERIWGPSRIHMXQEREKIETXMJTPRGEVEKEITREWHEXXLEXXMZITWAWSQWXSWEXTVEPMRXRSJGSTVRIEYVIEXCVMUIMWERGMIWXMJMGCSMWXSJOMIQXLIVIQIVIXQSVSTWHKPEGARCSXRWIEVSWIIBXVIZMXFSJXLIKEGAEWHEPSWYSWIWIEVXLISXLIVXLIRGEPIRQIVIIBGIIHMWYPFLEVHEWHYPSRRFQMXLEPPXLIECCIEVEWGISJKTVWMRLIHYSPHXLIQIMYLXSJXLIMWRIGXQEROIVFVIZEVAEKPIEWHXEAMWYEPPXLMWYRMWXSGSWRMHIVEXMSWMGSTPHLEVHPFKPEZINTCMXIVJSVLMRSCMWMSWVIRCIGXMWYMX")






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
		print (l[0])

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
		print ("Invalid Characters")

	else:
		calculate(expression)


#calculator("((100+4)+(52*4))")




