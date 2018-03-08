#lang MutableStructures

b = {"x":1}

fun hey(c):
  c["x"] :=2
end

hey(b)

b



  