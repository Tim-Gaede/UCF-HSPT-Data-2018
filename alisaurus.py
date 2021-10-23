# Read in number of scenarios
t = int(input())

# Loop over scenarios
for i in range(t):
    # Read in number of Alisauruses
    x = int(input())

    # If they split the circle evenly, they can attack!
    if(360 % x == 0):
        print("Attack!");
    else:
        print("No go.");
