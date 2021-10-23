import operator, math

class DisjointSet:
    def __init__(self, N):
        self.N = N
        self.numSets = N
        self.rank = [0] * N
        self.setSize = [0] * N
        self.p = [i for i in range(N)]

    def findSet(self, i):
        if self.p[i] == i:
            return i
        else:
            self.p[i] = self.findSet(self.p[i])
            return self.p[i]

    def isSameSet(self, i, j):
        return self.findSet(i) == self.findSet(j)

    def unionSet(self, i, j):
        if not self.isSameSet(i, j):
            self.numSets -= 1
            x, y = self.findSet(i), self.findSet(j)
            if self.rank[x] > self.rank[y]:
                self.p[y] = x
                self.setSize[x] += self.setSize[y]
            else:
                self.p[x] = y
                self.setSize[y] += self.setSize[x]
                if self.rank[x] == self.rank[y]:
                    self.rank[y] += 1
            

# Loop over cases
T = int(input())
for t in range(T):
    # Read in number of radios
    N = int(input())
    if N == 0:
        break

    # Read in position of radios
    islands = []
    for i in range(N):
        x, y = map(int, input().split())
        islands.append((x, y))

    # Find the best "r" using "Disjoint Set"
    ds = DisjointSet(N)
    mx = 0
    edges = []
    for i in range(N):
        for j in range(i):
            edges.append((i, j, int(math.ceil(math.hypot(islands[i][0] - islands[j][0], islands[i][1] - islands[j][1])))))
    edges.sort(key=operator.itemgetter(2))
    for i in edges:
        if not ds.isSameSet(i[0], i[1]):
            mx = max(mx, i[2])
            ds.unionSet(i[0], i[1])
    print("Island #{}: {}".format(t + 1, mx))
    
