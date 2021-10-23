# Calc function serves to give the score for making a move 
# at position "idx" with the current board state represented
# by the bitmask "mask". Variables "three" and "four" represent
# whether or not there was a three/four in a row before this move
def calc(mask, idx, three, four):
  global afterThree
  global afterFour
  global val
  global P
  global Q

  sol = val[idx]

  used = [[False for j in range(4)] for i in range(4)]
  for i in range(16):
    if (mask & (1<<i)) != 0:
      used[i//4][i%4] = True
  
  if three == False:
    afterThree = False
    for i in range(4):
      for j in range(4):
        if afterThree:
          break
        if i-2>=0 and j+2<4 and used[i][j] and used[i-1][j+1] and used[i-2][j+2]:
          afterThree = True
        if j+2<4 and used[i][j] and used[i][j+1] and used[i][j+2]:
          afterThree = True
        if j+2<4 and i+2<4 and used[i][j] and used[i+1][j+1] and used[i+2][j+2]:
          afterThree = True
        if i+2<4 and used[i][j] and used[i+1][j] and used[i+2][j]:
          afterThree = True
      if afterThree:
        break
    if afterThree:
      sol = sol+P     
  
  if four == False:
    afterFour = False
    for i in range(4):
      for j in range(4):
        if afterFour:
          break
        if i-3>=0 and j+3<4 and used[i][j] and used[i-1][j+1] and used[i-2][j+2] and used[i-3][j+3]:
          afterFour = True
        if j+3<4 and used[i][j] and used[i][j+1] and used[i][j+2] and used[i][j+3]:
          afterFour = True
        if j+3<4 and i+3<4 and used[i][j] and used[i+1][j+1] and used[i+2][j+2] and used[i+3][j+3]:
          afterFour = True
        if i+3<4 and used[i][j] and used[i+1][j] and used[i+2][j] and used[i+3][j]:
          afterFour = True
      if afterFour:
        break
    if afterFour:
      sol = sol+Q
 
  return sol


# Dynamic programming solution where we represent our state as a bitmask of the
# pieces currently placed. We brute force all possible moves for a given state
# and maximize the score when it is Alex's turn and minimize the score when it is
# Barbs. The result implies that Alex wins when the score is positive, Barb when it
# is negative, and tie when zero.
def solve(mask, turn, three, four):
  global memo
  global afterThree
  global afterFour

  if(memo[mask] != -oo):
    return memo[mask]
  if(mask == ((1<<16) - 1)):
    return 0

  sol = oo if (turn == 1) else -oo
  if turn == 0:
    for i in range(16):
      if ((mask & (1 << i)) == 0):
        sol = max(sol , calc((mask|(1<<i)), i, three, four) + solve(mask|(1<<i), 1^turn, afterThree, afterFour))

  if turn == 1:
    for i in range(16):
      if ((mask & (1 << i)) == 0):
        sol = min(sol , -calc((mask|(1<<i)), i, three, four) + solve(mask|(1<<i), 1^turn, afterThree, afterFour))
  
  memo[mask] = sol
  return sol  


# Some variables to keep track of stuff
oo = 1000000000
afterThree = False
afterFour = False
val = []
P = 0
Q = 0

# Loop over cases
T = int(input())
for t in range(1,T+1):
  memo = [-oo]*(1<<16)
  P, Q = list(map(int, input().split(" ")))
  val = []
  for i in range(4):
    val.extend(list(map(int, input().split(" "))))
  
  sol = solve(0, 0, False, False)
  
  if sol == 0:
    print("Game #"+str(t)+": It's a draw.")
  if sol > 0:
    print("Game #"+str(t)+": Alex wins.")
  if sol < 0:
    print("Game #"+str(t)+": Barb wins.")
 
