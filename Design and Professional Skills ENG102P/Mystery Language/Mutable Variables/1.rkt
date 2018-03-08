#lang MutableVars

a = "A"

fun test(b):
  b := "C"
  a := a ++ b
  a
end

test(a)

a