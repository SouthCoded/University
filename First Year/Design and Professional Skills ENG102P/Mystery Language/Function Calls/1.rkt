#lang FunctionCalls


fun first(in):
 if in > 0:
   1 + first(in - 1)
 else:
   0
 end
end


first(5)