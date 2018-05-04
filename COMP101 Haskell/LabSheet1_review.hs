import Data.Char

square :: Int -> Int
square x = x * x

pyth :: Int -> Int -> Int
pyth x y = square x + square y

isTriple :: Int -> Int -> Int -> Bool
isTriple x y z = pyth x y == square z 

isTripleAny :: Int -> Int -> Int -> Bool
isTripleAny x y z = if  x > z && x > y then isTriple y z x else if y > z && y > x then isTriple z x y  else isTriple x y z

halfEvens :: [Int] -> [Int]
halfEvens xs = [ if x `mod` 2 == 0 then x `div` 2 else x |x <- xs]

inRange ::  Int -> Int -> [Int] -> [Int]
inRange x y ls = [ l | l <- ls , l > x && l < y]

countPositives ::  [Int] -> Int 
countPositives ls = sum [ 1 | l <- ls , l > 0 ]

capitalised :: String -> String
capitalised (l:ls) = toUpper l :[ toLower x | x <- ls]

lower :: String -> String
lower ls = [toLower x | x <- ls]

title :: [String] -> [String]
title (l:lss) = capitalised l : [ if length ls > 4 then capitalised ls else lower ls | ls <- lss]
