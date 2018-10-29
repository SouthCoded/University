#Exercise3
import time
import pytest

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
			print("Not enough Space")

	# returns value with key "key" from the cache
	# raises an exception if key is not in the cache
	def lookup(self, key):
		try: 
			self.timeDict[key] = time.time()
			return self.cacheDict[key]
		except KeyError:
			print("Key not valid or has timed out")
	
	# removes dead elements
	def validate(self):

		LRU = list(self.cacheDict.keys())[0]

		for x in self.cacheDict.keys():

			if (time.time() - self.timeDict[x]) > self.ttl:
				del self.cacheDict[x]
				del self.timeDict[x]
				self.actualSize -= 1

		for x in self.cacheDict.keys():
			if self.timeDict[x] < self.timeDict[LRU]:
					LRU = x

		if self.actualSize == self.size:
			del self.cacheDict[LRU]
			del self.timeDict[LRU]
			self.actualSize -= 1

		
	def __iter__(self):

		self.n = 0
		sort = sorted(self.timeDict.values())
		keylist = []
		for x in sort:
			for y in self.timeDict.keys():
				if self.timeDict[y] == x:
					keylist.append((y,self.cacheDict[y]))

		keylist.reverse()
		return iter(keylist)

def test_example():
	cache = LRUCacheWithTTL(2, 100)
	cache.put("foo", 20)
	cache.put("bar", 10)
	element = cache.lookup("foo")

	x = 0
	for e in cache:
		if x == 0:
			assert e == ('foo', 20)
		if x == 1:
			assert e == ('bar', 10)

		x += 1

def test_validate():
	cache = LRUCacheWithTTL(2, 100)
	cache.put("foo", 20)
	cache.put("bar", 10)
	cache.put("third", 30)
	cache.validate()

	x = 0
	for e in cache:
		if x == 0:
			assert e == ('bar', 10)
		x += 1

def test_time():
	cache = LRUCacheWithTTL(3, 1)
	cache.put("foo", 20)
	cache.put("bar", 10)
	time.sleep(1)
	cache.validate()
	assert cache.lookup("foo") == None
	
def test_LRU():
	cache = LRUCacheWithTTL(3, 3)
	cache.put("foo", 20)
	cache.put("bar", 10)
	cache.lookup("foo")
	cache.put("here",30)
	cache.validate()
	x = 0
	for e in cache:
		if x == 0:
			assert e == ('here', 30)
		if x == 1:
			assert e == ('foo', 20)
		x += 1
	


