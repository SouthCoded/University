import Data.Char

square :: Int -> Int
square x = x * x

pyth :: Int -> Int -> Int
pyth x y = square x + square y

isTriple :: Int -> Int -> Int -> Bool
isTriple x y z = if pyth x y > square z then True else False

isTriple' :: Int -> Int -> Int -> Bool
isTriple' x y z = if maximum([x,y,z]) == z then isTriple x y z else isTriple z y x