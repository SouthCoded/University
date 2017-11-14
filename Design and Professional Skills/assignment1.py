import random 
import math
import re

hits = 0
total = 0
estimation = 0.0

def generate_random_points():
	x = random.uniform(0,1)
	y = random.uniform(0,1)
	return x,y

def checker(x,y):
	global hits
	
	radius = .5

	x = x - radius
	y = y - radius

	#Finds the vector
	z = math.sqrt((x**2 + y**2))

	#If the vector is less than the radius it is inside the circle
	if z < radius:
		 hits += 1
	
def estimate_pi(p):
	
	global total,estimation,hits

	try:
		if not (type(p) == int):
			raise ValueError()
	
	except ValueError:
		print ("Must be an integer")
	
	else:
		if p >= 7:
			print ("I Wouldn't pick a number that high unless you want to wait a while")

		else:
			#Calculates pi using the math module to the precision
			actualPi = math.floor((math.pi) * 10**p) / 10**p 
			total = 0
			hits = 0
				
			for l in range(1000000):	
				x,y = generate_random_points()
				checker(x,y)
				total += 1
				
				#Uses the monte carlo method to estimate the value of pi
				estimation = (float(hits)/total) * 4

				#Truncates to correct precision
				estimation = math.floor((estimation) * 10**p) / 10**p 

				#If they are equal, it stops the loop and prints the value
				if actualPi == estimation:
					break			

			print(estimation)

#estimate_pi("Insert Precision Here")

def letterToNumber(x):
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

def numberToLetter(x):
    return {
        0 :'a',
        1 :'b',
        2 :'c',
        3 :'d',
        4 :'e',
        5 :'f',
        6 :'g',
        7 :'h',
        8 :'i',
        9 :'j',
        10 :'k',
        11 :'l',
        12 :'m',
        13 :'n',
        14 :'o',
        15 :'p',
        16 :'q',
        17 :'r',
        18 :'s',
        19 :'t',
        20 :'u',
        21 :'v',
        22 :'w',
        23 :'x',
        24 :'y',
        25 :'z'
    }[x]

def lettersInFrequencyOrder(x):
    
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

	try:
		if not isinstance(text, str):
			raise ValueError()
	
	except ValueError:
		print("Must be a string")
	
	else:

		text = text.lower()
		text = list(text)
		total = len(text)

		textFrequency = [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0]
		letterList = ["","","","","","","","","","","","","","","","","","","","","","","","","",""]
		compareList = ["a","b","c","d","e","f","g","h","i","j","k","l","m","n","o","p","q","r","s","t","u","v","w","x","y","z"]

		threeLetterWords = {}

		#Counts the occurences of letters
		for x in text:
			position = letterToNumber(x)
			textFrequency[position] += 1
		
		#Calculates frequencie of each letter
		for x in range(len(textFrequency)):
			textFrequency[x] = textFrequency[x]/total

		#Sorts frequenies from highest to lowest
		sortedTextFrequency = sorted(textFrequency, reverse=True)


		for x in range(len(sortedTextFrequency)): #Goes through the sorted frequencies
			for y in range(len(textFrequency)): #Goes through the normal frequencies 
				if sortedTextFrequency[x] == textFrequency[y]: 
					letter = lettersInFrequencyOrder(y) #If they match, it finds the corresponding letter associated with that frequency 
					letterList[y] = letter #Adds letter to the appropriate spot it represents (ie a=1, b=2, c=3 ... etc)

		#For loop that identifies the three letter word "THE" by finding the most common 3 letter phrase
		for x in range(len(text)-2):
			
			fl = text[x]
			sl = text[x+1]
			tl = text[x+2]

			threeWord = str(fl+sl+tl)

			#If a new three letter word, adds it to the dictionary
			if threeWord not in threeLetterWords:
				threeLetterWords[threeWord] = 0
			
			#If it is the same three letter word, adds 1 to the value of that three letter word in the dictionary
			if threeWord in threeLetterWords:
				threeLetterWords[threeWord] += 1	
		
		highest = 0

		#Finds the highest value word in the dictionary
		for x in threeLetterWords.values():
			key = ""
			if x > highest:
				highest = x

		temp = -1


		for x in threeLetterWords:
			if threeLetterWords.get(x) == highest:

				#These for loops just swap the current values of T,H,E with the 3 letters that were most common 
				for y in range(len(letterList)):
					if letterList[y] == x[0]:
						temp = y #found where the first character is pointing to

				letterList[temp] =  letterList[letterToNumber("t")] #Finds what the first character is currently pointing to and sets it the value pointing to T
				letterList[letterToNumber("t")] = x[0] #Setting first character of the most common 3 digit word to T


				for y in range(len(letterList)):
					if letterList[y] == x[1]:
						temp = y

				letterList[temp] = letterList[letterToNumber("h")] #Finds what the second character is currently pointing to and sets it the value pointing to H
				letterList[letterToNumber("h")] = x[1] #Setting second character of the most common 3 digit word to H


				for y in range(len(letterList)):
					if letterList[y] == x[2]:
						temp = y

				letterList[temp] = letterList[letterToNumber("e")] #Finds what the third character is currently pointing to and sets it the value pointing to E
				letterList[letterToNumber("e")] = x[2] #Setting third character of the most common 3 digit word to E

		#Goes through each letter one at a time and decryptes each letter
		for x in range(len(text)):
			position = -1
			for y in range(len(letterList)):
				if text[x] == letterList[y]:
					position = y
			text[x] = numberToLetter(position)

		#Combines the list into one string again
		text = "".join(str(x) for x in text)

		print(text)


#break_cipher("Insert Text Here")


simplifiedFormat = []

#A checker to make sure the input is correct
def formatter(p):
	
	global simplifiedFormat


	#Goes through the numbers
	for x in range(len(p)-4):
		temp = [p[x],p[x+1],p[x+2],p[x+3],p[x+4]]
		#If numbers match (num op num) or 1,2,3,2,4 then it is done, it will block out that section with 9's as it is correct
		if temp == [1,2,3,2,4]:
			for m in range(4):
				p[x+m] = 9
			#Replaces with 2 as (num op num) evaluates to a number, which is represented by 2
			p[x+4] = 2
	
	tempList = []
	#Goes through the list and takes out the blocked out sections
	for m in p:
		if m != 9 :
			tempList.append(m)

	#If there is no answer yet, it runs the program again		
	if len(tempList) > 4:
		for x in range(len(tempList)-4):
			temp = [tempList[x],tempList[x+1],tempList[x+2],tempList[x+3],tempList[x+4]]
			if temp == [1,2,3,2,4]:
				formatter(tempList)
			else:
				return ValueError
	#If there is no answer, there is an error as the expression can always be condensed to one number			
	elif tempList != [2]:
		return ValueError



#A method that just performs calculations
def operations(num1,op,num2):
	if op == "+":
		return str(int(num1)+int(num2))
	if op == "-":
		return str(int(num1)-int(num2))
	if op == "*":
		return str(int(num1)*int(num2))
	if op == "/":
		return str(int(num1)/int(num2))

#Actually calculates the expression
def calculate(e):

	tempList = []
	#Goes through the expression and finds the parantheses
	for x in range(len(e)):
		if e[x] == "(" and e[x+4] == ")":
			ans = operations(e[x+1],e[x+2],e[x+3])
			tempList.append(ans)
			#Block out the finished expression
			for m in range(5):
					e[x+m] = " "
		else:
			if e[x] != " ":
				tempList.append(e[x]) #Add the rest of the expression that is not blocked out

	#Each expression has one answer, therefore calculate until you have one answer
	if len(tempList) > 1:
		calculate(tempList)
	else: 
		print (tempList[0])

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

		#Checks for division by zero
		for x in range(len(expression)-1):
			if expression[x] == "/":
				if expression[x+1] == "0":
					raise ZeroDivisionError

		tempList = []
		
		#Simply combines the numbers together
		for x in range(len(expression)):
			#If it is not a number it doesn't matter
			if expression[x] not in numbers:
				tempList.append(expression[x])
			#If it is a number, check it is not a single digit, if it isn't combine them 	
			elif expression[x] in numbers and expression[x-1] not in numbers:
				if expression[x+1] in numbers:
					length = 0
					for y in range(len(expression)-x):
						while expression[x+y] in numbers:
							length += 1
							y += 1
						break
					#Combines the numbers to form one number
					num = int(''.join(map(str,expression[x:length+x])))
					tempList.append(str(num))					
				else:
					tempList.append(expression[x])

		expression = tempList
		
		#Goes through the expression to simplfy it into numbers for error checking
		for p in range(len(expression)):
			
			if expression[p] == "(":
				simplifiedFormat.append(1)

			elif expression[p] == ")":
				simplifiedFormat.append(4)

			elif expression[p] in operands:
				simplifiedFormat.append(3)
			
			else:
				simplifiedFormat.append(2)

		ans = formatter(simplifiedFormat)

		#Checks for exceptions
		if ans != None:
			raise ans

		
	except ValueError:
		print ("Invalid Characters")
	
	except ZeroDivisionError:
		print("Don't divide by zero")

	else:
		calculate(expression)


#calculator("Insert Expression")




