-- Duncan Rowe, LabSheet3

mult :: [Int] -> Int
mult (x:xs) = foldr (*) x xs

posLit :: [Int] -> [Int]
posLit xs = filter (>0) xs

trueList :: [Bool] -> Bool
trueList (x:xs) = foldr (&&) x xs

evenList :: [Int] -> Bool
evenList xs = if foldr (+) 0 (map (`mod` 2) xs) > 0 then False else True

maxList :: Ord a => [a] -> a
maxList (x:[]) = x
maxList (x:xs) = maxList( filter (>=x) (xs ++ [x]))

maxList' :: Ord a => [a] -> a
maxList' (x:xs) = foldr max x xs

inRange :: Int -> Int -> [Int] -> [Int]
inRange x y ls = filter(<=y) (filter (>=x) ls)

countPositives :: [Int] -> Int
countPositives xs = foldr (+) 0 (map (+1) ((map (*0) (filter (>0) xs)  )))

myLength :: [a] -> Int
myLength xs = foldr (+) 0 (map (\x -> 1) xs)

myMap :: (a -> b) -> [a] -> [b]
myMap f xs = foldr ((:) . f) [] xs

myLength' :: [a] -> Int
myLength' xs = foldr ((+) . (\x -> 1)) 0 xs


