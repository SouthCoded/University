
factorial :: Int -> Int
factorial 1 = 1
factorial n = if n > 0 then n*factorial(n-1) else 0


sumFac :: Int -> Int
sumFac 1 = 1
sumFac n = (factorial n) + sumFac(n-1)

gList :: [Int]
gList = [x*x |x <- [1..10],(x*x*x)>200,(x*x*x)<1000]

isPrime :: Int -> Bool
isPrime n = if [x | x <- [2..(n-1)], n `mod` x == 0] == [] then True else False
