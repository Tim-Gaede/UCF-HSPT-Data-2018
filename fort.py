# Read in the number of cases to consider
cases = int(input())

# Deal with each case
for i in range(0, cases):
    password = input()

    # Check if the input is "hey guys", and print buzz if it is not
    if password == "hey guys":
        print(password)
    else:
        print("buzz")
