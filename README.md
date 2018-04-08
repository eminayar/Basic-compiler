# Basic-compiler
Implementation of a basic compiler that generates A86 code for a squence of expressions and assignments that involve +,* and power operations

Expressions are infix expressions:

*operation* | *meaning*
------------ | ----------
a + b | addition
a * b | multiplication
pow(a,n) | power, a<sup>n</sup>

## Assumptions
* All numbers are non negative
* Undefined variables has value 0
* All constants are written in hexadecimal format. The leading digit of a hexadecimal constant is always a numeric digit.
* All variables and expressions are 32 bit.
* Pow expression can accept expressions

*#* | *line* | *type*
----------- | -------------- | -------------
1 | x1 = 1abcd | assingment of a constant to a variable
2 | y = 16 | assignment of a constant to a variable
3 | x = x1*y*pow(2,0) | assingment of an expression to a variable
4 | y = (x+1)*3 | assignment of an expression to a variable
5 | x | print command
6 | y | print command

The output of the 6 lines is:

1abcd0

503673
