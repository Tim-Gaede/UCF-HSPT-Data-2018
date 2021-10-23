class Node:
   def __init__(self):
      self.child = [None for i in range(26)]
      self.count = 0


def addStr(root, str):
   LEN = len(str)
   strIdx = 0
   for c in str:
      idx =ord(c)-97
      if root.child[idx] == None:
         root.child[idx] = Node()
      root.child[idx].count = root.child[idx].count + 1
      root = root.child[idx]
      if strIdx == LEN-1:
         root.value = str
      strIdx += 1

def getStr(root, idx):
   global order

   if hasattr(root, 'value'):
      idx -= 1
      if idx == 0:
         return root.value

   count = 0
   for i in range(26):
      if root.child[order[i]] == None:
         continue
      if count + root.child[order[i]].count < idx:
         count += root.child[order[i]].count
      elif count + root.child[order[i]].count == idx:
         tmp = getStr(root.child[order[i]], idx-count)
         if tmp != None:
            return tmp
         else:
            break
      elif count + root.child[order[i]].count > idx:
         tmp = getStr(root.child[order[i]], idx-count)
         if tmp != None:
            return tmp
         else:
            break
   return root.value


# Loop over cases
T = int(input())
for t in range(1,T+1):
   order = [ i for i in range(26)]
   root = Node()
   N, M = map(int, input().split())
   for i in range(N):
      addStr(root, input())

   # Find answer
   print("Gift Exchange #"+str(t)+":")
   for i in range(M):
      query = input().split()
      if int(query[0]) == 1:
         idx1 = order.index(ord(query[1][0])-97)
         idx2 = order.index(ord(query[2][0])-97)
         temp = order[idx1]
         order[idx1] = order[idx2]
         order[idx2] = temp
      else:
         print(getStr(root, int(query[1])))
   print()

