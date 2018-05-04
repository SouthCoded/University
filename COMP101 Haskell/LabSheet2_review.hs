import Data.Char

inRange :: Int -> Int -> [Int] -> [Int]
inRange x y [] = []
inRange x y (l:ls) = if l > x && l < y then l: inRange x y ls else inRange x y ls 

countPositives :: [Int] -> Int
countPositives [] = 0
countPositives (l:ls) = if l > 0 then 1 + countPositives ls else countPositives ls 

capitalised :: String -> String
capitalised [] = []
capitalised ls 
	| length ls > 1 = capitalised(init ls) ++ [toLower(last ls)]
	| otherwise = [toUpper (head ls)]

lower :: String -> String
lower [] = []
lower (l:ls) = toLower l : lower ls

title :: [String] -> [String]
title [] = []
title ls 
	| length(last ls) > 4 = title (init ls) ++ [capitalised (last ls)] 
	| length ls == 1 = [capitalised (head ls)]
	| otherwise = title(init ls) ++ [lower(last ls)]   

-- isort ::  Ord a => [a] -> [a]
-- isort [] = []
-- isort (l:ls) = if l > last ls then isort (ls:l) else isort  init ls:l:last ls 

merge :: Ord a => [a] -> [a] -> [a]
merge [] [] = []
merge xs ys 
	| xs == [] = ys
	| ys == [] = xs
	| (head xs) > (head ys) = (head ys): merge xs (tail ys)
	| otherwise = (head xs): merge (tail xs) ys

-- msort :: Ord a => [a] -> [a]
-- msort ls 
-- 	| length ls > 1 = msort (head ls) >> msort (tail ls) 
-- 	| otherwise = ls 


rotor :: Int -> String -> String
rotor n ls = if n < 0 || n > length ls then "error" else drop n ls ++ take n ls

makeKey :: Int -> [(Char,Char)]
makeKey n = zip "ABCDEFGHIJKLMNOPQRSTUVWXYZ" (rotor n "ABCDEFGHIJKLMNOPQRSTUVWXYZ")

lookUp :: Char -> [(Char,Char)] -> Char
lookUp c ls = if null ls then c else if fst (head ls) == c then snd (head ls) else lookUp c (tail ls)

encipher :: Int -> Char -> Char
encipher n c = lookUp c (makeKey n) 

normalise ::  String -> String
normalise ls = [toUpper l | l <-(filter isLetter ls)]

encipherStr :: Int -> String -> String
encipherStr n ls = [encipher n l | l <- (normalise ls)] 












