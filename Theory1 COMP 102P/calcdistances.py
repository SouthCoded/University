coordinates = [24, 93, 11, 69, 40, 54, 27, 10, 17, 26, 53, 81, 96, 29]


#[25, 67, 13, 2, 74, 100, 19, 24, 52, 41, 80, 47, 35, 29, 6, 59, 99, 90, 17, 59], 270
# [7892, 8269, 4510, 2866, 7380, 1398, 6835, 7206, 5315, 3373, 6333, 4586, 1634, 2964, 3671, 355, 6290, 5598, 8022, 2987, 7226, 1345, 8372, 4326, 3027, 4621, 3354, 103, 9318, 4119, 7030, 9825, 7905, 8555, 8893, 9978, 6842, 8909, 2707, 8915]
# 34960
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


totadistance = 269


for x in distances:
	print x
# [26, 27, 10, 17, 26] included
# [37, 24, 93, 11, 69] included
# [40, 40, 54, 53, 81] included
# [41, 24, 93, 53, 81] included
# [49, 11, 69, 17, 26] included
# [81, 40, 54, 96, 29] included

