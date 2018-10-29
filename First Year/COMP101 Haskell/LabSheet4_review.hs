import Test.QuickCheck

halfEvens :: [Int] -> [Int]
halfEvens xs = [ if x `mod` 2 == 0 then x `div` 2 else x |x <- xs]

inRange ::  Int -> Int -> [Int] -> [Int]
inRange x y ls = [ l | l <- ls , l > x && l < y]

countPositives ::  [Int] -> Int 
countPositives ls = sum [ 1 | l <- ls , l > 0 ]

prop_HalfEvens x = halfEvens[2,4,6] == [1,2,3]

