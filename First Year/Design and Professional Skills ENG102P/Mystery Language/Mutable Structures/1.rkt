#lang MutableStructures

b = {"x":1}
a = {"x":b}

fun hey(c):
  d = c["x"]
  d["x"]:= 3
end

hey(a)

a



  