
coordinates = [88, 94, 33, 25, 92, 85, 65, 9, 26, 39, 81, 13, 33, 65]

it = iter(coordinates)
places = []

#Creates coordinates
for x in it:
	places.append([x,next(it)])

distances = []

for x in range(len(places)-1):
	for y in range(len(places)):
		if(x != y and y>x):
			x1 = places[x][0]
			x2 = places[y][0]
			y1 = places[x][1]
			y2 = places[y][1]

			dist = abs(x1-x2) + abs(y1-y2)
			distances.append([dist,x1,y1,x2,y2])
	
distances.sort()

finaldistance = 0
finaldistanceList = []
intermediateList = [] #holds all of the components

for x in range(len(distances)-1):
	checker = 0
	changed = 0

	print("This is the final :" + str(finaldistanceList))
 	print("This is intermediate : " + str(intermediateList))
 	print("This is the current thing: " + str(distances[x]))
 	print("Final distance : " + str(finaldistance))

 	print("\n") 	

	if x==0:
		finaldistance += distances[x][0]
		finaldistanceList.append([distances[x][1],distances[x][2]])
		finaldistanceList.append([distances[x][3],distances[x][4]])
		changed = 1


 	for p in range(len(intermediateList)):
 		for i in range(len(intermediateList[p])):
	 		checker = 0
	 		temp = distances[x]
	 		holder = distances[x]
			print("These are the inputs " + str(distances[x]) + str(intermediateList[p]))
	 		print("------------------------")
	 	
	 		#THIS IS FOR LINKING INTERMEDIATE AND FINALS
	 		if distances[x][1] == intermediateList[p][i][1] and distances[x][2] == intermediateList[p][i][2] and intermediateList[p][i] != distances[x]:
	 			if intermediateList[p][i][0] == 0:
	 				for m in range(len(intermediateList)):
	 					if intermediateList[m][1] == intermediateList[p][i][3] and intermediateList[m][2] == intermediateList[p][i][4] and intermediateList[p][i] != intermediateList[m]:
	 						checker = 1
	 						holder = intermediateList[m]
	 					if intermediateList[m][3] == intermediateList[p][i][3] and intermediateList[m][4] == intermediateList[p][i][4] and intermediateList[p][i] != intermediateList[m]:
	 						checker = 1
	 						holder = intermediateList[m]
	 			for f in range(len(finaldistanceList)):
	 				 if distances[x][3] == finaldistanceList[f][0] and distances[x][4] == finaldistanceList[f][1]:
	 				 	if checker == 1:
	 				 		finaldistanceList.append([holder[1],holder[2]])
		 				 	finaldistanceList.append([holder[3],holder[4]])
		 				 	finaldistanceList.append([intermediateList[p][i][1],intermediateList[p][i][2]])
		 				 	finaldistance += distances[x][0]
		 				 	finaldistance += holder[0]
		 				 	temp = holder
		 				 	changed = 1
	 				 	else:
		 				 	finaldistanceList.append([intermediateList[p][i][1],intermediateList[p][i][2]])
		 				 	finaldistanceList.append([intermediateList[p][i][3],intermediateList[p][i][4]])
		 				 	finaldistance += distances[x][0]
		 				 	finaldistance += intermediateList[p][i][0]
		 				 	temp = intermediateList[p][i]
		 				 	changed = 1
	 		elif distances[x][1] == intermediateList[p][i][3] and distances[x][2] == intermediateList[p][i][4] and intermediateList[p][i] != distances[x]:
	 		 	if intermediateList[p][i][0] == 0:
	 				for m in range(len(intermediateList)):
	 					if intermediateList[m][1] == intermediateList[p][i][3] and intermediateList[m][2] == intermediateList[p][i][4] and intermediateList[p][i] != intermediateList[m][i]:
	 						checker = 1
	 						holder = intermediateList[m]
	 					if intermediateList[m][3] == intermediateList[p][i][3] and intermediateList[m][4] == intermediateList[p][i][4] and intermediateList[p][i] != intermediateList[m][i]:
	 						checker = 1
	 						holder = intermediateList[m]
	 		 	for f in range(len(finaldistanceList)):
	 				 if distances[x][3] == finaldistanceList[f][0] and distances[x][2] == finaldistanceList[f][1]:
	 				 	if checker == 1:
	 				 		finaldistanceList.append([holder[1],holder[2]])
		 				 	finaldistanceList.append([holder[3],holder[4]])
		 				 	finaldistanceList.append([intermediateList[p][i][3],intermediateList[p][i][4]])
		 				 	finaldistance += distances[x][0]
		 				 	finaldistance += holder[0]
		 				 	temp = holder
		 				 	changed = 1
	 				 	else:
		 				 	finaldistanceList.append([intermediateList[p][i][1],intermediateList[p][i][2]])
		 				 	finaldistanceList.append([intermediateList[p][i][3],intermediateList[p][i][4]])
		 				 	finaldistance += distances[x][0]
		 				 	finaldistance += intermediateList[p][i][0]
		 				 	temp = intermediateList[p][i]
		 				 	changed = 1
	 		elif distances[x][3] == intermediateList[p][i][1] and distances[x][4] == intermediateList[p][i][2] and intermediateList[p][i] != distances[x]:
	 		 	if intermediateList[p][i][0] == 0:
	 				for m in range(len(intermediateList)):
	 					if intermediateList[m][1] == intermediateList[p][i][3] and intermediateList[m][2] == intermediateList[p][i][4] and intermediateList[p][i] != intermediateList[m][i]:
	 						checker = 1
	 						holder = intermediateList[m]
	 					if intermediateList[m][3] == intermediateList[p][i][3] and intermediateList[m][4] == intermediateList[p][i][4] and intermediateList[p][i] != intermediateList[m][i]:
	 						checker = 1
	 						holder = intermediateList[m]
	 		 	for f in range(len(finaldistanceList)):
	 				if distances[x][1] == finaldistanceList[f][0] and distances[x][2] == finaldistanceList[f][1]:
	 					if checker == 1:
	 				 		finaldistanceList.append([holder[1],holder[2]])
		 				 	finaldistanceList.append([holder[3],holder[4]])
		 				 	finaldistanceList.append([intermediateList[p][i][1],intermediateList[p][i][2]])
		 				 	finaldistance += distances[x][0]
		 				 	finaldistance += holder[0]
		 				 	temp = holder
		 				 	changed = 1
	 				 	else:
		 					finaldistanceList.append([intermediateList[p][i][1],intermediateList[p][i][2]])
		 				 	finaldistanceList.append([intermediateList[p][i][3],intermediateList[p][i][4]])
		 				 	finaldistance += distances[x][0]
		 				 	finaldistance += intermediateList[p][i][0]
		 				 	temp = intermediateList[p][i]
			 				changed = 1
		 	elif distances[x][3] == intermediateList[p][i][3] and distances[x][4] == intermediateList[p][i][4] and intermediateList[p][i] != distances[x]:
	 		 	if intermediateList[p][i][0] == 0:
	 				for m in range(len(intermediateList)):
	 					if intermediateList[m][i][1] == intermediateList[p][i][1] and intermediateList[m][i][2] == intermediateList[p][i][2] and intermediateList[p][i] != intermediateList[m][i]:
	 						checker = 1
	 						holder = intermediateList[m]
	 					if intermediateList[m][i][3] == intermediateList[p][i][1] and intermediateList[m][i][4] == intermediateList[p][i][2] and intermediateList[p][i] != intermediateList[m][i]:
	 						checker = 1
	 						holder = intermediateList[m]
	 		 	for f in range(len(finaldistanceList)):
	 				if distances[x][1] == finaldistanceList[f][0] and distances[x][2] == finaldistanceList[f][1]:
	 					if checker == 1:
	 				 		finaldistanceList.append([holder[1],holder[2]])
		 				 	finaldistanceList.append([holder[3],holder[4]])
		 				 	finaldistanceList.append([intermediateList[p][i][3],intermediateList[p][i][4]])
		 				 	finaldistance += distances[x][0]
		 				 	finaldistance += holder[0]
		 				 	temp = holder
		 				 	changed = 1
	 				 	else:
		 					finaldistanceList.append([intermediateList[p][i][1],intermediateList[p][i][2]])
		 				 	finaldistanceList.append([intermediateList[p][i][3],intermediateList[p][i][4]])
		 				 	finaldistance += distances[x][0]
		 				 	finaldistance += intermediateList[p][i][0]
		 				 	temp = intermediateList[p][i]
			 				changed = 1
			
			if holder != distances[x] and temp != distances[x]:
				intermediateList.remove(intermediateList[p][i])
				intermediateList.remove(holder)
	 			print("REMOVED")
	 			break

	 		if temp != distances[x]:
	 			intermediateList.remove(intermediateList[p][i])
	 			print("REMOVED")
	 			break
			
			
	 		#CHECKS IF IT CAN ATTACH TO INTERMEDIATE
	 		if distances[x][1] == intermediateList[p][i][1] and distances[x][2] == intermediateList[p][i][2] and intermediateList[p][i] != distances[x]:
	 			for f in range(len(intermediateList)):
	 				for h in range(len(intermediateList[f])):
		 				if distances[x][3] == intermediateList[f][i][3] and distances[x][4] == intermediateList[f][i][4]:
		 				 	checker = 1
		 				if distances[x][3] == intermediateList[f][i][1] and distances[x][4] == intermediateList[f][i][2]:
		 				 	checker = 1
	 			if checker == 0:
	 				intermediateList[p][i][0] += distances[x][0]
	 				distances[x][0] = 0
	 				intermediateList[p].append(distances[x])
	 				changed = 1
			
			elif distances[x][1] == intermediateList[p][i][3] and distances[x][2] == intermediateList[p][i][4] and intermediateList[p][i] != distances[x]:
	 		 	for f in range(len(intermediateList)):
	 				if distances[x][3] == intermediateList[f][i][1] and distances[x][4] == intermediateList[f][i][2]:
	 				 	checker = 1
	 				if distances[x][3] == intermediateList[f][i][3] and distances[x][4] == intermediateList[f][i][4]:
	 				 	checker = 1
	 			if checker == 0:
	 				intermediateList[p][i][0] += distances[x][0]
	 				distances[x][0] = 0
	 				intermediateList[p].append(distances[x])
	 				changed = 1
	 	
	 		elif distances[x][3] == intermediateList[p][i][1] and distances[x][4] == intermediateList[p][i][2] and intermediateList[p][i] != distances[x]:
	 		 	#for f in range(len(intermediateList)):
	 				# if distances[x][1] == intermediateList[f][3] and distances[x][2] == intermediateList[f][2]:
	 				#  	checker = 1
	 				# if distances[x][1] == intermediateList[f][1] and distances[x][2] == intermediateList[f][2]:
	 				#  	checker = 1
	 			if checker == 0:
	 				intermediateList[p][i][0] += distances[x][0]
	 				distances[x][0] = 0
	 				intermediateList[p].append(distances[x])
	 				changed = 1

	 		elif distances[x][3] == intermediateList[p][i][3] and distances[x][4] == intermediateList[p][i][4] and intermediateList[p][i] != distances[x]:
	 		 	for f in range(len(intermediateList)):
	 				if distances[x][1] == intermediateList[f][1] and distances[x][2] == intermediateList[f][2]:
	 				 	checker = 1
	 				if distances[x][1] == intermediateList[f][3] and distances[x][2] == intermediateList[f][4]:
	 				 	checker = 1
	 			if checker == 0:
	 				intermediateList[p][i][0] += distances[x][0]
	 				distances[x][0] = 0
	 				intermediateList[p].append(distances[x])
	 				changed = 1
 
	 		if (temp != distances[x]):
	 			intermediateList.remove(temp)
	 			print("REMOVED")
	 			break
	 	

 	for p in range(len(finaldistanceList)):
 	
 		#CHECKS IF IT CAN ATTACH TO FINAL 	

 		if distances[x][1] == finaldistanceList[p][0] and distances[x][2] == finaldistanceList[p][1] and changed == 0:
 			for f in range(len(finaldistanceList)):
 				if distances[x][3] == finaldistanceList[f][0] and distances[x][4] == finaldistanceList[f][1]:
 				 	checker = 1
 			if checker == 0:
 				finaldistanceList.append([distances[x][3],distances[x][4]])
 				finaldistance += distances[x][0]
 				changed = 1
 		
 		elif distances[x][3] == finaldistanceList[p][0] and distances[x][4] == finaldistanceList[p][1] and changed == 0:
 		 	for f in range(len(finaldistanceList)):
 				if distances[x][1] == finaldistanceList[f][0] and distances[x][2] == finaldistanceList[f][1]:
 				 	checker = 1
 			if checker == 0:
 				finaldistanceList.append([distances[x][1],distances[x][2]])
 				finaldistance += distances[x][0]
 				changed = 1
 	

 	for h in range(len(finaldistanceList)):
 		if distances[x][1] == finaldistanceList[h][0] and distances[x][2] == finaldistanceList[h][1]:
 			checker = 1
 		if distances[x][3] == finaldistanceList[h][0] and distances[x][4] == finaldistanceList[h][1]:
 			checker = 1
 	
 	if checker == 0 and changed == 0:
 		print('I GOT ADDED ' + str(distances[x]))
 		intermediateList.append([distances[x]])
 			

	




# total = 0
# for x in range((len(coordinates)/2)):
# 	total += x



# print("All points : " + str(finaldistanceList))
# print("# of Beginning Points: " + str(len(places)))
# print("# of End Points: " + str(len(finaldistanceList)))
# print("All of the distances calculated: " + str(distances))
# print("Number of distances calculated: " + str(len(distances)))
# print("Number of distances needed to calculate: " + str(total))
# print("Final distance : " + str(finaldistance))

	





