#Exercise 1 

#        (w,v)                   (mx w)
#thief([(2,50), (3,100), (5,140)], 17) = 550

def thief(obj,max_weight):

	try:
		#Creates array of length max_weight and fills with 0
		weightArray = [max_weight+1]
		weightArray = [0 for i in range(max_weight+1)]

		#Goes through the list
		for w in range(max_weight):
			#Goes through the object
			for i in range(len(obj)):
				#If the object weight is less than the weight 			
				if obj[i][0] <= w+1:
					# Checks weight and sees if for that weight that is the maximum value
					# or if the object added increases its value
					weightArray[w+1] = max(weightArray[w+1 - obj[i][0]] + obj[i][1],weightArray[w+1])

		return weightArray[max_weight]
	except TypeError:
		return "Wrong Type"

print(thief([(3,100),(5,140),(2,50)], 17))

def test_thief_example():
	assert thief([(2,50), (3,100), (5,140)], 17) == 550

def test_thief_zero():
	assert thief([(2,50), (3,100), (5,140)], 17) > 0

		





