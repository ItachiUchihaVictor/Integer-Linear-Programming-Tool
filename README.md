# Integer-Linear-Programming-Tool-Very-Easy-to-Use-
This program provides an Integer Linear Programming Tool that makes programmers or researchers easily solve an integer linear programming problem without too much effort made.

# How It Works & How To Use It

The main souce code is ILP.cpp. 

The program was designed to solve an Integer Problem Problem stated in Section 7.1. of Reference. But it could be used to solve any Integer Linear Programming problem with some minor changes. 

![solarized palette](https://user-images.githubusercontent.com/22741950/28516468-f04112e2-7093-11e7-8b94-bdb9b0d120a2.png)

The program first generates a .mod file to present the problem to be solve with data filled in (as shwon in Line 49-216). Then, it converts the .mod file into .mps file with GLPK tool as shown in Line 224 and solves the problem with CBC as shown in Line 226. In the aforementioned procedure, it generates a message.txt and solu.txt file showing the message and solution given by CBC. Finally, it removes the .mod file, the .mps file, the message.txt and the solu.txt and give a stat.txt showing the running time and space consumption of this program. 

To use the program, you first need to figure out how to fill your data into the integer programming problem. 

# Integer Linear Programming Solver Used in This Program

GLPK (GNU Linear Programming Kit) 
Webpage: https://www.gnu.org/software/glpk/

CBC (Coin-or branch and cut)

Webpage: https://projects.coin-or.org/Cbc

# Reference

Profit Maximization with Sufficient Customer Satisfactions. Cheng Long, Raymond Chi-Wing Wong, Victor Junqiu Wei. ACM Transactions on Knowledge Discovery from Database. 
