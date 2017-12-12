#Exercise3
import time

class LRUCacheWithTTL:
	
	# creates cache
	def __init__(self, size, ttl):
		self.size = size
		self.ttl = ttl
		self.cacheDict = {}
		self.timeDict = {}
		self.actualSize = 0

	# puts "value" into the cache with key "key"
	def put(self, key, value):
		if self.actualSize < self.size:
			self.actualSize += 1
			self.cacheDict[key] = value
			self.timeDict[key] = time.time()
		else:
			self.validate()
			self.actualSize += 1
			self.cacheDict[key] = value
			self.timeDict[key] = time.time()

	# returns value with key "key" from the cache
	# raises an exception if key is not in the cache
	def lookup(self, key):
		self.validate()
		try: 
			self.timeDict[key] = time.time()
			return self.cacheDict[key]
		except KeyError:
			print("Key not valid")
	
	# removes dead elements
	def validate(self):
		try:
			LRU = list(self.cacheDict.keys())[0]
			
			for x in self.cacheDict.keys():

				if self.timeDict[x] < self.timeDict[LRU]:
					LRU = x

				if time.time() - self.timeDict[x] > self.ttl:
					del self.cacheDict[x]
					del self.timeDict[x]

			del self.cacheDict[LRU]
			del self.timeDict[LRU]

		except NameError:
			print("Entered Wrong Name")

	def print(self):
		sorted = sort(self.timeDict.keys())
		for x in sorted:
			



cache = LRUCacheWithTTL(2, 100)
cache.put("One",1)
cache.put("Two",2)
cache.put("Three",3)
cache.lookup("One")
