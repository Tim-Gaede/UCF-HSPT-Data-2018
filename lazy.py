#using an edge class helps organize things
class Edge:
    def __init__(self,u,v,w,ident):
        self.u=u
        self.v=v
        self.w=w
        self.ident=ident

# Loop over the cases
testcases = int(input())
for testcase in range(1,testcases+1):
    n, m, r = map(int, input().split())

    #construct the grpah
    graph = []
    for road in range(1,r+1):
        a, b, w = map(int,input().split())
        graph.append(Edge(a,b,w,road))
    allcosts = []

    #we consider the highway in our answers, but don't make it part of the graph
    allcosts.append(m)

    #recursively find all edge unique paths
    def sumOfPaths(path, node, cost):
        if(node==n):
            allcosts.append(cost)
            return
        for p in graph:
            if(p.u==node and p not in path):
                newPath = list(path)
                newPath.append(p)
                takethis = sumOfPaths(newPath,p.v, cost + p.w)
    sumOfPaths([],1,0)

    # Find highest cost path
    highest = 0
    for cost in allcosts:
        highest = max(highest,cost)

    #normalize everything to the most expensive path
    sum = 0
    for cost in allcosts:
        sum += 1.0*highest/cost

    #now the odds of using our road is how much better ours is relative to the normalized sum
    answer = (highest/m)/sum
    print("City #{0:d}: {1:.3f}%".format(testcase,answer*100))
