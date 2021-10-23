#Scan input
testcases = int(input())
for i in range(testcases):
  length = int(input())
  array = list(map(int, input().split(" ")))
  
  #Sort the array
  array.sort()
  
  #Initialize some useful variables
  result = "Day #"+str(i+1)+":"
  left = -1
  right = -1
  first = True
  
  #Now we condense the string
  for j in range(length):
    if (left == -1):
      left = array[j]
      right = array[j]
    else:
      if (array[j] == right+1):
        #This condenses the string
        right = array[j]
      else:
        if(array[j] != right):
          #We add to the result
          if(first == False):
            #In this case, we printed a set of numbers already, so we add a comma
            result += ","
          if(left == right):
            #In this case, there is only one number to print
            result += " "+str(left)
          else:
            #In this case, we print a range of numbers
            result += " "+str(left)+"-"+str(right)
          first = False
          left = array[j]
          right = array[j]
  
  if(left != -1):
    #We add the final set of numbers to our result
    #We follow the same procedure as we did in our for loop above
    if(first == False):
      result += ","
    if(left == right):
      result += " "+str(left)
    else:
      result += " "+str(left)+"-"+str(right)
  
  #We have our result
  print(result)
  print()
