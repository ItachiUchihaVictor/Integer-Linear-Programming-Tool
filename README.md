# Integer-Linear-Programming-Tool-Very-Easy-to-Use-
This program provides an Integer Linear Programming (ILP) Tool that makes programmers or researchers easily solve an integer linear programming problem without too much effort made. It works directly on ILP problem on Bipartite Graph but it could works on more general ILP problems with some minor changes.

# How It Works & How To Use It

The main souce code is ILP.cpp. 

The program was designed to solve an Integer Problem Problem stated in Section 7.1. of Reference. But it could be used to solve any Integer Linear Programming problem with some minor changes. You may drop the 2nd (resp. 3rd) constraint as you need by commenting Line 110-111 (resp. modifying the non-negative constraint in Line 103). 

![solarized palette](https://user-images.githubusercontent.com/22741950/28516468-f04112e2-7093-11e7-8b94-bdb9b0d120a2.png)

The program first generates a .mod file to present the problem to be solve with data filled in (as shwon in Line 49-216). Then, it converts the .mod file into .mps file with GLPK tool as shown in Line 224 and solves the problem with CBC as shown in Line 226. In the aforementioned procedure, it generates a message.txt and solu.txt file showing the message and solution given by CBC. Finally, it removes the .mod file, the .mps file, the message.txt and the solu.txt and give a stat.txt showing the running time and space consumption of this program. 

To use the program, you first need to figure out how to fill your data into the integer programming problem and modify Line 49-216 accordingly. In our implementation, the vector 'amount' is the 'x' vector in the problem as shown in the figure and the vector 'profit' is the vector 'f' in the problem shown in the figure. The concatenation of the two vectors 'capacity' and 'demand' is the vector 'b' in problem as shown in the figure. A in the problem shown in the above figure is an incident matrix of a bipartite graph (https://en.wikipedia.org/wiki/Bipartite_graph). Since each column of A has exactly two 1s, we used two vector 'p' and 'o' to store the row number of the two 1s in each column.

# Integer Linear Programming Solver Used in This Program

GLPK (GNU Linear Programming Kit) 

Webpage: https://www.gnu.org/software/glpk/

CBC (Coin-or branch and cut)

Webpage: https://projects.coin-or.org/Cbc

# Data Description

config.txt is the configure file. It contains "product data file" "customer data file" "f file" "number of product" "number of customer" "number of attribute of each product" "number of attribute of each customer" "k (percentage)" "parameter 1" "parameter 2". The last two value could be ignored.

There are three different data files, "o", "p" and "f". "f" file defines what a matchable pair is (see Line 175 and Line 179). "p" is the product file (format: <Product id> <capacity> <attr 1><atrr 2> ... <attr n>  <cost>). "o" is customer file (format:<Customer id><demand><attr 1><atrr 2>    ...    <attr n>    <price>).

# Reference

Profit Maximization with Sufficient Customer Satisfactions. Cheng Long, Raymond Chi-Wing Wong, Victor Junqiu Wei. ACM Transactions on Knowledge Discovery from Database. 
