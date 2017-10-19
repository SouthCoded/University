
coordinates =[3957, 3636, 115, 2480, 2781, 6194, 6430, 2506, 4847, 9451, 1425, 4618, 9552, 4532, 8339, 4209, 3143, 1469, 4916, 9803, 9634, 7114, 9502, 7363, 897, 1640, 2748, 9396, 7469, 4014, 9843, 4525, 4000, 7305, 4052, 6308, 6173, 4943, 7519, 3370]

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

	print("\n") 
	print("This is the final :" + str(finaldistanceList))
 	print("This is intermediate : " + str(intermediateList))
 	print("This is the current thing: " + str(distances[x]))
 	print("Final distance : " + str(finaldistance))

	if x==0:
		finaldistance += distances[x][0]
		finaldistanceList.append([distances[x][1],distances[x][2]])
		finaldistanceList.append([distances[x][3],distances[x][4]])
		changed = 1
	
	breaker = 0
 	for p in range(len(intermediateList)):
 		if breaker == 1: 
 			break
 		for i in range(len(intermediateList[p])):
	 		checker = 0
	 		merge = []
	 		temp = distances[x]
	 		holder = distances[x]

			#THIS IS FOR LINKING INTERMEDIATE AND FINALS
	 		if distances[x][1] == intermediateList[p][i][1] and distances[x][2] == intermediateList[p][i][2] and intermediateList[p][i] != distances[x]:
	 			for f in range(len(finaldistanceList)):
	 				 if distances[x][3] == finaldistanceList[f][0] and distances[x][4] == finaldistanceList[f][1]:
	 					for L in intermediateList[p]:
	 						dup1 = 0
		 					dup2 = 0
	 						for N in finaldistanceList:
	 							if L[1] == N[0] and L[2] == N[1]:
	 								dup1 = 1
	 							if L[3] == N[0] and L[4] == N[1]:
	 								dup2 = 1	
	 						if dup1 == 0 and dup2 == 0:
	 							finaldistanceList.append([L[1],L[2]])
	 							finaldistanceList.append([L[3],L[4]])
	 							finaldistance += L[0]
	 						elif dup1 == 1 and dup2 == 0:
	 							finaldistanceList.append([L[3],L[4]])
	 							finaldistance += L[0]
	 						elif dup1 == 0 and dup2 == 1:
	 							finaldistanceList.append([L[1],L[2]])
	 							finaldistance += L[0]
	 						elif dup1 == 1 and dup2 == 1:
	 							print("YOOO")
	 							finaldistance += L[0]
			 				changed = 1
			 			finaldistance += distances[x][0]
				 		temp = intermediateList[p]
	 		elif distances[x][1] == intermediateList[p][i][3] and distances[x][2] == intermediateList[p][i][4] and intermediateList[p][i] != distances[x]:
	 		 	for f in range(len(finaldistanceList)):
	 				 if distances[x][3] == finaldistanceList[f][0] and distances[x][4] == finaldistanceList[f][1]:
	 					for L in intermediateList[p]:
	 						dup1 = 0
		 					dup2 = 0
	 						for N in finaldistanceList:
	 							if L[1] == N[0] and L[2] == N[1]:
	 								dup1 = 1
	 							if L[3] == N[0] and L[4] == N[1]:
	 								dup2 = 1	
	 						if dup1 == 0 and dup2 == 0:
	 							finaldistanceList.append([L[1],L[2]])
	 							finaldistanceList.append([L[3],L[4]])
	 							finaldistance += L[0]
	 						elif dup1 == 1 and dup2 == 0:
	 							finaldistanceList.append([L[3],L[4]])
	 							finaldistance += L[0]
	 						elif dup1 == 0 and dup2 == 1:
	 							finaldistanceList.append([L[1],L[2]])
	 							finaldistance += L[0]
	 						elif dup1 == 1 and dup2 == 1:
	 							finaldistance += L[0]
			 				changed = 1
			 			finaldistance += distances[x][0]
				 		temp = intermediateList[p]
	 		elif distances[x][3] == intermediateList[p][i][1] and distances[x][4] == intermediateList[p][i][2] and intermediateList[p][i] != distances[x]:
	 		 	for f in range(len(finaldistanceList)):
	 				if distances[x][1] == finaldistanceList[f][0] and distances[x][2] == finaldistanceList[f][1]:
	 					for L in intermediateList[p]:
	 						dup1 = 0
		 					dup2 = 0
	 						for N in finaldistanceList:
	 							if L[1] == N[0] and L[2] == N[1]:
	 								dup1 = 1
	 							if L[3] == N[0] and L[4] == N[1]:
	 								dup2 = 1	
	 						if dup1 == 0 and dup2 == 0:
	 							finaldistanceList.append([L[1],L[2]])
	 							finaldistanceList.append([L[3],L[4]])
	 							finaldistance += L[0]
	 						elif dup1 == 1 and dup2 == 0:
	 							finaldistanceList.append([L[3],L[4]])
	 							finaldistance += L[0]
	 						elif dup1 == 0 and dup2 == 1:
	 							finaldistanceList.append([L[1],L[2]])
	 							finaldistance += L[0]
	 						elif dup1 == 1 and dup2 == 1:
	 							finaldistance += L[0]
			 				changed = 1
			 			finaldistance += distances[x][0]
				 		temp = intermediateList[p]
		 	elif distances[x][3] == intermediateList[p][i][3] and distances[x][4] == intermediateList[p][i][4] and intermediateList[p][i] != distances[x]:
	 		 	for f in range(len(finaldistanceList)):
	 				if distances[x][1] == finaldistanceList[f][0] and distances[x][2] == finaldistanceList[f][1]:
	 					for L in intermediateList[p]:
	 						dup1 = 0
		 					dup2 = 0
	 						for N in finaldistanceList:
	 							if L[1] == N[0] and L[2] == N[1]:
	 								dup1 = 1
	 							if L[3] == N[0] and L[4] == N[1]:
	 								dup2 = 1	
	 						if dup1 == 0 and dup2 == 0:
	 							finaldistanceList.append([L[1],L[2]])
	 							finaldistanceList.append([L[3],L[4]])
	 							finaldistance += L[0]
	 						elif dup1 == 1 and dup2 == 0:
	 							finaldistanceList.append([L[3],L[4]])
	 							finaldistance += L[0]
	 						elif dup1 == 0 and dup2 == 1:
	 							finaldistanceList.append([L[1],L[2]])
	 							finaldistance += L[0]
	 						elif dup1 == 1 and dup2 == 1:
	 							finaldistance += L[0]
			 				changed = 1
			 			finaldistance += distances[x][0]
				 		temp = intermediateList[p]
			
	 		if temp != distances[x]:
	 			intermediateList.remove(temp)
	 			breaker = 1
	 			print("REMOVED")
	 			break
	 		
	 		#CHECKS IF IT CAN ATTACH TO INTERMEDIATE
	 		if distances[x][1] == intermediateList[p][i][1] and distances[x][2] == intermediateList[p][i][2] and intermediateList[p][i] != distances[x]:
	 			for f in range(len(intermediateList)):
	 				for h in range(len(intermediateList[f])):
		 				if distances[x][3] == intermediateList[f][h][3] and distances[x][4] == intermediateList[f][h][4] and f != p:
		 				 	checker = 1
		 				 	merge = intermediateList[f]
		 				elif distances[x][3] == intermediateList[f][h][1] and distances[x][4] == intermediateList[f][h][2] and f != p:
		 				 	checker = 1
		 				 	merge = intermediateList[f]
		 				elif distances[x][3] == intermediateList[f][h][3] and distances[x][4] == intermediateList[f][h][4] and f == p:
		 				 	checker = 2
		 				elif distances[x][3] == intermediateList[f][h][1] and distances[x][4] == intermediateList[f][h][2] and f == p:
		 				 	checker = 2
	 			if checker == 1: #if it attaches two intermediates
	 				for z in merge:
	 					intermediateList[p].append(z)
	 				intermediateList[p].append(distances[x])
	 				changed = 2
	 			elif checker == 2: #checks if it attaches two intermediates in the same thing
	 				changed = 1
	 			else: #only attaches to one intermediate
	 				intermediateList[p].append(distances[x])
	 				changed = 1
			elif distances[x][1] == intermediateList[p][i][3] and distances[x][2] == intermediateList[p][i][4] and intermediateList[p][i] != distances[x]:
	 		 	for f in range(len(intermediateList)):
	 				for h in range(len(intermediateList[f])):
		 				if distances[x][3] == intermediateList[f][h][1] and distances[x][4] == intermediateList[f][h][2] and f != p:
		 				 	checker = 1
		 				 	merge = intermediateList[f]
		 				elif distances[x][3] == intermediateList[f][h][3] and distances[x][4] == intermediateList[f][h][4] and f != p:
		 				 	checker = 1
		 				 	merge = intermediateList[f]
		 				elif distances[x][3] == intermediateList[f][h][1] and distances[x][4] == intermediateList[f][h][2] and f == p:
		 				 	checker = 2
		 				elif distances[x][3] == intermediateList[f][h][3] and distances[x][4] == intermediateList[f][h][4] and f == p:
		 				 	checker = 2
	 			if checker == 1: #if it attaches two intermediates
	 				for z in merge:
	 					intermediateList[p].append(z)
	 				intermediateList[p].append(distances[x])
	 				changed = 2
	 			elif checker == 2: #checks if it attaches two intermediates in the same thing
	 				changed = 1
	 			else: #only attaches to one intermediate
	 				intermediateList[p].append(distances[x])
	 				changed = 1

	 		elif distances[x][3] == intermediateList[p][i][1] and distances[x][4] == intermediateList[p][i][2] and intermediateList[p][i] != distances[x]:
	 		 	print("3")
	 		 	for f in range(len(intermediateList)):
	 		 		for h in range(len(intermediateList[f])):
		 				if distances[x][1] == intermediateList[f][h][3] and distances[x][2] == intermediateList[f][h][2] and f != p:
		 				 	checker = 1
		 				 	merge = intermediateList[f]
		 				elif distances[x][1] == intermediateList[f][h][1] and distances[x][2] == intermediateList[f][h][2] and f != p:
		 				 	checker = 1
		 				 	merge = intermediateList[f]
		 				elif distances[x][1] == intermediateList[f][h][3] and distances[x][2] == intermediateList[f][h][4] and f == p:
		 				 	checker = 2
		 				elif distances[x][1] == intermediateList[f][h][1] and distances[x][2] == intermediateList[f][h][2] and f == p:
		 				 	checker = 2
	 			if checker == 1: #if it attaches two intermediates
	 				for z in merge:
	 					intermediateList[p].append(z)
	 				intermediateList[p].append(distances[x])
	 				changed = 2
	 			elif checker == 2: #checks if it attaches two intermediates in the same thing
	 				print("CORRECT")
	 				changed = 1
	 			else: #only attaches to one intermediate
	 				intermediateList[p].append(distances[x])
	 				changed = 1
	 			print(intermediateList)

	 		elif distances[x][3] == intermediateList[p][i][3] and distances[x][4] == intermediateList[p][i][4] and intermediateList[p][i] != distances[x]:	 		 	
	 		 	for f in range(len(intermediateList)):
	 		 		for h in range(len(intermediateList[f])):
		 				if distances[x][1] == intermediateList[f][h][1] and distances[x][2] == intermediateList[f][h][2] and f != p:
		 				 	checker = 1
			 				merge = intermediateList[f]
		 				elif distances[x][1] == intermediateList[f][h][3] and distances[x][2] == intermediateList[f][h][4] and f != p:
		 				 	checker = 1
			 				merge = intermediateList[f]
			 			elif distances[x][1] == intermediateList[f][h][1] and distances[x][2] == intermediateList[f][h][2] and f == p:
		 				 	checker = 2
		 				elif distances[x][1] == intermediateList[f][h][3] and distances[x][2] == intermediateList[f][h][4] and f == p:
		 				 	checker = 2
	 			if checker == 1: #if it attaches two intermediates
	 				for z in merge:
	 					intermediateList[p].append(z)
	 				intermediateList[p].append(distances[x])
	 				changed = 2
	 			elif checker == 2: #checks if it attaches two intermediates in the same thing
	 				changed = 1
	 			else: #only attaches to one intermediate
	 				intermediateList[p].append(distances[x])
	 				changed = 1
	 		
	 		if temp != distances[x]:
	 			intermediateList.remove(temp)
	 			print("REMOVED")
	 			break
	 		
	 		if changed == 2:
	 			intermediateList.remove(merge)
	 			breaker = 1
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



total = 0
for x in range((len(coordinates)/2)):
	total += x


print("------------------------------------------------------")		
print("All points : " + str(finaldistanceList))
print("# of Beginning Points: " + str(len(places)))
print("# of End Points: " + str(len(finaldistanceList)))
print("All of the distances calculated: " + str(distances))
#print("Number of distances calculated: " + str(len(distances)))
print("Number of distances needed to calculate: " + str(total))
print("Final distance : " + str(finaldistance))
print("------------------------------------------------------")		






