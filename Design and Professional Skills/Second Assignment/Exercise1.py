#Exercise 1 
#        (w,v)                   (mx w)
#thief([(2,50), (3,100), (5,140)], 17) = 550

import pytest

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
	except IndexError:
		return "Weight should be positive"

@pytest.mark.parametrize("test_inputs",[([], 100), ([], 10), ([], 20)])
def test_thief_no_input(test_inputs):
    obj, max_weight = test_inputs
    assert thief(obj,max_weight) == 0

@pytest.mark.parametrize("test_inputs",
[([(2,50)], -17), ([(2,50), (1, 100), (1, 100)], -10), ([(2,50), (1, 100)], -1)])
def test_thief_max_weight(test_inputs):
    obj, max_weight = test_inputs
    assert thief(obj, max_weight) == "Weight should be positive"

def test_thief_example():
	assert thief([(2,50), (3,100), (5,140)], 17) == 550

def test_thief_zero():
	assert thief([(2,50), (3,100), (5,140)], 17) > 0

@pytest.mark.parametrize("test_inputs",[([(2,50), (3,100), (5,140)], "A"),([(2,50), (3,100), (5,140)], "6")])
def test_thief_error(test_inputs):
	ax, bx = test_inputs
	print(thief(ax,bx))
	assert thief(ax,bx) == "Wrong Type"

		





