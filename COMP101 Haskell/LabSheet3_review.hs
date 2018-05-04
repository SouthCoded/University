mult :: [Int] -> Int
mult ls = foldr (*) 1 ls

posList :: [Int] -> [Int]
posList ls = filter (>0) ls 

trueList :: [Bool] -> Bool
trueList ls = foldr (&&) True ls

evenList :: [Int] -> Bool
evenList ls = if foldr (+) 0 (map (`mod` 2) ls) == 0 then True else False

maxList :: Ord [a] -> a
maxList ls = 