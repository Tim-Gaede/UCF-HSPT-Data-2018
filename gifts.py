
# Read in number of visits
n = int(input())

# Loop over the visits
for i in range(n):
   # Read in the 3 gifts
   a, b, c = map(int, input().split())

   # Output the smallest difference
   print(min(abs(a-b), abs(a-c), abs(b-c)))
