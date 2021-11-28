
import sympy
import numpy as np
from sympy import sin,cos,exp,Matrix,pi


q1 = sympy.Symbol("q1")
q2 = sympy.Symbol("q2")
l1 = sympy.Symbol("l1")
l2 = sympy.Symbol("l2")

x = l1*cos(q1) + l2*cos(q1+q2)
z = l1*sin(q1) + l2*sin(q1+q2)
J = Matrix([  [x.diff(q1), x.diff(q2)],
              [z.diff(q1), z.diff(q2)]  ])
print("*********J*********")
print(J)

t = sympy.Symbol('t')
_q1 = sympy.Symbol("_q1")
_q2 = sympy.Symbol("_q2")
w1 = sympy.Symbol("w1")
w2 = sympy.Symbol("w2")
l1 = sympy.Symbol("l1")
l2 = sympy.Symbol("l2")

M = Matrix([  [cos(q1), cos(q1 + q2)],
              [sin(q1), sin(q1 + q2)]  ])
L = Matrix([[l1, l2]])
P = M*L.T
J = Matrix([  [P[0,:].diff(q1), P[0,:].diff(q2)],
              [P[1,:].diff(q1), P[1,:].diff(q2)]])# x=P[0,:], z=P[1,:]
print("*********J*********")
print(J)
print("*********J.inv*********")
print(J.inv())

print("********* orthogonal_matrix *********")
orth_J = J.T * J #Jの直交行列
print(orth_J)

print("********* J+ *********")
print(orth_J.inv() * J.T)






