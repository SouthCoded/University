import Data.Char

square :: Int -> Int 
square x = x*x

pyth :: Int -> Int -> Int
pyth x y = square x + square y

isTriple :: Int -> Int -> Int -> Bool
isTriple x y z = if pyth x y > z 
				  then True
				  else False

isTripleAny :: Int -> Int -> Int -> Bool
isTripleAny x y z = if x > y && x > z
					then isTriple y z x
					else if y > x && y > z
					then isTriple x z y
					else isTriple x y z 


halfEvens :: [ Int ] -> [ Int ]
halfEvens xs = [if mod x 2 == 0 then div x 2 else x | x <- xs]

inRange :: Int -> Int -> [Int] -> [Int] 
inRange x y xs = [n | n <- xs, x <= n,  n <= y]

countPositives :: [Int] -> Int
countPositives xs = sum [1 | x <- xs , x > 0 ]

capitalised :: String -> String
capitalised l = [if x == head l then toUpper x else toLower x | x <- l]

title :: [String] -> [String]
title xs = [if x == head xs then capitalised x else if length x > 4 then capitalised x else [toLower c|c<-x]| x <- xs]

