# Operations - these are used to check if a character is a valid starting point
ops = ['+', '-', '*', '/']
# Directional changes - these are used to quickly select a line in a given direction
radialDirections = [[-1, -1], [-1, 0], [-1, 1], [0, 1], [1, 1], [1, 0], [1, -1], [0, -1]]
# Operation Placeholder - This is used to increase readability, and to check if an operation has already been used
placeholder = '@'

# Read in the number of cases to consider
cases = int(input())

# Deal with each case
for i in range(1, cases+1):
    # Extract rows and columns from the input
    data = input().split()
    rows = int(data[0])
    cols = int(data[1])

    # Scan in puzzle
    puzzle = []
    for j in range(0, rows):
        puzzle.append(input())

    # Extract the number of queries
    queries = int(input())

    # Print out the header for each puzzle
    print("Number Search #" + str(i) + ":")

    # Scan in each query and search for it in the puzzle
    for x in range(0, queries):
        num = int(input())

        found = False

        # Try every possible direction, starting at every possible location in the grid
        for r in range(0, rows):
            for c in range(0, cols):
                if puzzle[r][c] in ops:
                    continue

                # Python is unable to break out of nested loops, so this is checked several times at the end of loops
                if int(puzzle[r][c]) == num:
                    found = True
                    break

                # Check each of the eight directions radiating out from the starting point
                for direction in radialDirections:

                    # Data Save Variables
                    op = '@'  # Saves the op to be used, or @ if no op is currently in use
                    curr = int(puzzle[r][c])  # Saves the current positive integer
                    firstHalf = 0  # Saves the first half of an expression
                    currR = r   # Holds a running total for the current row
                    currC = c   # Holds a running total for the current column

                    # Follow the selected direction until a break case is found
                    # This will be at most 15 iterations, as it will hit the edges of the grid
                    while True:

                        # Increment the current position in the chosen direction
                        currR += direction[0]
                        currC += direction[1]

                        # Stop searching if the algorithm fell off the edge of the puzzle
                        if currR < 0 or currR >= rows or currC < 0 or currC >= cols:
                            break

                        # Deal with finding an operation
                        if puzzle[currR][currC] in ops:
                            # We can only have one operation in a number, so stop searching if we find a second one
                            if op != '@':
                                break

                            # If this is the first op we found, save the curr so we can do calculations
                            else:
                                firstHalf = curr
                                op = puzzle[currR][currC]
                                # Setting curr to zero isn't a problem, because the total isn't checked unless a digit
                                # has been hit
                                curr = 0

                        # Otherwise, we must have found a digit
                        else:
                            # Move the last digit up
                            curr *= 10
                            curr += int(puzzle[currR][currC])

                            # Whether this is the first or second half, this may be the number we are looking for
                            # Checking it even if it is the second half allows the code to run faster, and removes an
                            # extra comparison
                            if curr == num:
                                found = True
                                break

                            # If we are using an operation, we need to do actual calculations
                            if op != '@':
                                value = .5  # Dummy value to insure op calculation works properly
                                if op == '+':
                                    value = firstHalf + curr
                                elif op == '-':
                                    value = firstHalf - curr
                                elif op == '*':
                                    value = firstHalf * curr
                                elif op == '/':
                                    value = firstHalf / curr

                                if value == num:
                                    found = True
                                    break

                    # Nested break out of direction loop
                    if found:
                        break

                # Nested break out of column loop
                if found:
                    break

            # Nested break out of row loop
            if found:
                break

        # Translate the result to the proper output
        if found:
            print("Yes")
        else:
            print("No")

    print()
