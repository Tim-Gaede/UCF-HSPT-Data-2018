
import math

#Loop over the cases
testcases = int(input())
for testcase in range(1, testcases+1):
    #Read case
    n, m = map(int, input().split())

    #For an isosceles triangle, the following is the formula for the height (just pythagorean theorem)
    bottom = m/2
    height = math.sqrt(m*m - bottom*bottom)

    #We alternate layering triangular slices next to each other
    #/\/\/\/\/\
    #this means we only get the width from half of these slices
    width = 1+(n-1)/2
    answer = height*width*m
    print("Order #{0}: {1:.3f}".format(testcase,round(answer,3)))
