#Exercise 2

#        (w,v)                   (mx w)
#thief([(2,50), (3,100), (5,140)], 17) = 550

def thief(obj,max_weight):

	try:
		#Creates array of length max_weight and fills with 0
		weightArray = [[0 for j in range(len(obj)+1)] for i in range(max_weight+1)]

		#Goes through the list
		for w in range(max_weight):
			#Goes through the object
			for i in range(len(obj)):
				#If the object weight is less than the weight 			
				if obj[i][0] <= w+1:
	
					#Checks if the item will be added
					if (weightArray[w+1 - obj[i][0]][0] + obj[i][1]) > weightArray[w+1][0]:
						#Adds the other item values to the current item
						for p in range(len(obj)):
							weightArray[w+1][p+1] = weightArray[w+1 - obj[i][0]][p+1] 

						#Adds one in the category of the item that you will be adding
						weightArray[w+1][i+1] = weightArray[w+1 - obj[i][0]][i+1] + 1

					weightArray[w+1][0] = max(weightArray[w+1 - obj[i][0]][0] + obj[i][1],weightArray[w+1][0])

		return weightArray[max_weight][1:]
	
	except TypeError:
		return "Wrong Type"

print(thief([(2,50),(3,100),(5,140)], 17))

def test_thief_example():
	assert thief([(2,50), (3,100), (5,140)], 17) == [1,5,0]

def test_thief_zero():
	assert thief([(2,50), (3,100), (5,140)], 17) > 0

		





