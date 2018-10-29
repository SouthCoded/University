#Exercise 2

#        (w,v)                   (mx w)
#thief([(2,50), (3,100), (5,140)], 17) = 550

import pytest

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
	except IndexError:
		return "Weight should be positive"
	

print(thief([(2,10),(3,20),(5,30),(8,52),(9,60),(13,83)],50))

def test_thief_example():
	assert thief([(2,50), (3,100), (5,140)], 17) == [1,5,0]

def test_thief_zero():
	assert len(thief([(2,50), (3,100), (5,140)], 17)) >= 0

def test_thief_negative():
	for x in thief([(2,50), (3,100), (5,140)], 17):
		assert x >= 0

@pytest.mark.parametrize("test_inputs",[([], 100), ([], 10), ([], 20)])
def test_thief_no_input(test_inputs):
    obj, max_weight = test_inputs
    assert thief(obj,max_weight) == []

@pytest.mark.parametrize("test_inputs",
[([(2,50)], -17), ([(2,50), (1, 100), (1, 100)], -10), ([(2,50), (1, 100)], -1)])
def test_thief_max_weight(test_inputs):
    obj, max_weight = test_inputs
    assert thief(obj, max_weight) == "Weight should be positive"

@pytest.mark.parametrize("test_inputs",[([(2,50), (3,100), (5,140)], "A"),([(2,50), (3,100), (5,140)], "6")])
def test_thief_error(test_inputs):
	ax, bx = test_inputs
	print(thief(ax,bx))
	assert thief(ax,bx) == "Wrong Type"
		





