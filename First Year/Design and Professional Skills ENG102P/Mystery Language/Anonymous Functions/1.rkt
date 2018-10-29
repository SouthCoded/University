#lang AnonymousFunctions

p = 0
x = 5


temp = lam(): p:= test() end

test = lam(): x + 4 end


temp()

