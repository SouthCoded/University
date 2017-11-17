import copy


grid = [["X","X","X","X"],["X","X","X","X"],["X","X","X","X"],["X","X","X","X"]]
totalGrid = [["O","O","O","O"],["O","O","O","O"],["O","O","O","O"],["O","O","O","O"]]

input = [1, 2, 5, 6, 7, 8, 10, 11, 12, 14, 15]

memList = []
whacked = []
answer = []
allAnswer = []

count = 0

biggest = -9

def setupGrid(input,grid):
	if input == 1:
		grid[3][0] = "O"
	elif input == 2:
		grid[3][1] = "O"
	elif input == 3:
		grid[3][2] = "O"
	elif input == 4:
		grid[3][3] = "O"
	elif input == 5:
		grid[2][0] = "O"
	elif input == 6:
		grid[2][1] = "O"
	elif input == 7:
		grid[2][2] = "O"
	elif input == 8:
		grid[2][3] = "O"
	elif input == 9:
		grid[1][0] = "O"
	elif input == 10:
		grid[1][1] = "O"
	elif input == 11:
		grid[1][2] = "O"
	elif input == 12:
		grid[1][3] = "O"
	elif input == 13:
		grid[0][0] = "O"
	elif input == 14:
		grid[0][1] = "O"
	elif input == 15:
		grid[0][2] = "O"
	elif input == 16:
		grid[0][3] = "O"

def backtoNumbers(l):
	x = l[0]
	y = l[1]

	if x == 3 and y == 0:
		return 1
	elif x == 3 and y == 1:
		return 2
	elif x == 3 and y == 2:
		return 3
	elif x == 3 and y == 3:
		return 4
	elif x == 2 and y == 0:
		return 5
	elif x == 2 and y == 1:
		return 6
	elif x == 2 and y == 2:
		return 7
	elif x == 2 and y == 3:
		return 8 
	elif x == 1 and y == 0:
		return 9
	elif x == 1 and y == 1:
		return 10
	elif x == 1 and y == 2:
		return 11
	elif x == 1 and y == 3:
		return 12 
	elif x == 0 and y == 0:
		return 13
	elif x == 0 and y == 1:
		return 14
	elif x == 0 and y == 2:
		return 15
	elif x == 0 and y == 3:
		return 16

def printGrid(grid):
	for x in range(4):
		print(grid[x])
	print("\n")

def whack(x,y,grid):

	global biggest 
	grid[x][y] = "X"

	if x+1 <= 3 and grid[x+1][y] == "O":
		grid[x+1][y] = "X"
	elif x+1 <= 3 and grid[x+1][y] == "X":
		grid[x+1][y] = "O"
	
	if x-1 >= 0 and grid[x-1][y] == "O":
		grid[x-1][y] = "X"
	elif x-1 >= 0 and grid[x-1][y] == "X":
		grid[x-1][y] = "O"
	
	if y+1 <= 3 and grid[x][y+1] == "O":
		grid[x][y+1] = "X"
	elif y+1 <= 3 and grid[x][y+1] == "X":
		grid[x][y+1] = "O"
	
	if y-1 >= 0 and grid[x][y-1] == "O":
		grid[x][y-1] = "X"
	elif y-1 >= 0 and grid[x][y-1] == "X":
		grid[x][y-1] = "O"
	
	#print("WHACKED: " + str(x) + "," +  str(y) + "\n")
	whacked.append([x,y])
	biggest = -9

def possibleWhack(x,y,grid):
	
	total = 0

	if grid[x][y] == "O":

		#Crosshairs
		if x+1 <= 3 and grid[x+1][y] == "O":
			total += 1
		if x-1 >= 0 and grid[x-1][y] == "O":
			total += 1
		if y+1 <= 3 and grid[x][y+1] == "O":
			total += 1
		if y-1 >= 0 and grid[x][y-1] == "O":
			total += 1

		if x+1 > 3:
			total += 1
		if x-1 < 0:
			total += 1
		if y+1 > 3:
			total += 1
		if y-1 < 0:
			total += 1

		return total
	else:
		return -9

def calculateNext(grid):
	
	global biggest

	for x in range(4):
		for y in range(4):
			totalGrid[x][y] = possibleWhack(x,y,grid)
			if totalGrid[x][y] > biggest:
				biggest = totalGrid[x][y]

def memory(grid,totalGrid,whacked): 
	
	global memList	
	global biggest

	first = True

	for x in range(4):
		for y in range(4):
			
			if totalGrid[x][y] == biggest and first == True:
				first = False
			elif totalGrid[x][y] <= biggest and totalGrid[x][y] >= 0:
				g = copy.deepcopy(grid)
				tG = copy.deepcopy(totalGrid)
				w = copy.deepcopy(whacked)
				memList.append([x,y,g,tG,w])

def done(grid):
	for x in range(4):
		for y in range(4):
			if grid[x][y] == "O":
				return True
	return False


for x in input:
	setupGrid(x,grid)

calculateNext(grid)
memory(grid,totalGrid,whacked)


while done(grid):

	count += 1
	
	if count > 10:

		count = 0
		x = memList[0][0]
		y = memList[0][1]
		grid = memList[0][2]
		totalGrid = memList[0][3]
		whacked = memList[0][4]

		
		whack(x,y,grid)
		calculateNext(grid)
		memory(grid,totalGrid,whacked)
		# if x == 3 and y == 1:
		# 	printGrid(grid)
		# 	printGrid(totalGrid)
		# 	print(memList[len(memList)-3:])

		memList.pop(0)

	if count < 10:
		repeat = False
		for x in range(4):
			for y in range(4):
				if totalGrid[x][y] == biggest and repeat == False:
					whack(x,y,grid)
					calculateNext(grid)
					memory(grid,totalGrid,whacked)

					repeat = True

allAnswer += [whacked]
firstOnes = True
memList.append([[0],[0],[0],[0],[0]])

top = 0

while len(memList) > 0:

	x = memList[0][0]
	y = memList[0][1]
	grid = memList[0][2]
	totalGrid = memList[0][3]
	whacked = memList[0][4]

	if memList[0][3] == [0]:
		firstOnes = False
		memList.pop(0)
		x = memList[0][0]
		y = memList[0][1]
		grid = memList[0][2]
		totalGrid = memList[0][3]
		whacked = memList[0][4]

	else:
		whack(x,y,grid)
		calculateNext(grid)

		# if grid == [["O","X","X","X"],["X","O","X","O"],["O","X","O","X"],["O","X","X","X"]] and x == 2 and y == 1:
		# 	print("FIRST")
		# 	printGrid(totalGrid)

		memList.pop(0)

		while done(grid):
			
			count += 1

			if count < 10:
				repeat = False
				for x in range(4):
					for y in range(4):
						if totalGrid[x][y] == biggest and repeat == False:
							whack(x,y,grid)
							calculateNext(grid)

							if firstOnes == True:
								memory(grid,totalGrid,whacked)
							
							repeat = True
			else:
				count = 0
				break
	
	if not done(grid):
		allAnswer += [whacked]

smallest = 10

for x in allAnswer:
	if len(x) < smallest:
		smallest = len(x)
		whacked = x

for y in whacked:
		answer.append(backtoNumbers(y))
print(answer)

# for x in allAnswer:
# 	answer = []
# 	for y in x:
# 		answer.append(backtoNumbers(y))
# 	print(answer)


