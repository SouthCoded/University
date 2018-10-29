mult :: [Int] -> Int
mult ls = foldr (*) 1 ls

posList :: [Int] -> [Int]
posList ls = filter (>0) ls 

trueList :: [Bool] -> Bool
trueList ls = foldr (&&) True ls

evenList :: [Int] -> Bool
evenList ls = if foldr (+) 0 (map (`mod` 2) ls) == 0 then True else False

maxList :: Ord a => [a] -> a
maxList (l:[]) = l
maxList (l:ls) = maxList (if filter (>= l) ls == [] then [l] else filter (>= l) ls)

inRange :: Int -> Int -> [Int] -> [Int] 
inRange x y ls = filter (<=y) (filter (>=x) ls) 

countPositives :: [Int] -> Int
countPositives ls = foldr (+) 0 (map (^0) (filter (>0) ls)) 

myLength :: [a] -> Int
myLength ls = foldr (+) 0 (map (\l -> 1) ls)

myMap :: (a -> b) -> [a] -> [b]
myMap f ls = foldr ((:).f) [] ls

myLength' :: [a] -> Int
myLength' xs = foldr ((+) . (\x -> 1)) 0 xs
