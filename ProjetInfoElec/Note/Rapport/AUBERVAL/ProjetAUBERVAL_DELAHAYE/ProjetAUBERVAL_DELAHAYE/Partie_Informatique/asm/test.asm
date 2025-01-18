# 0 : a
# 1 : b
eq
pushi 0
push 0
eq
jf toto
pushi 1
pop 1
jp toto1
toto :
pushi 0
pop 1
toto1 : 
end
