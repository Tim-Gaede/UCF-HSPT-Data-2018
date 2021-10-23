#This approach operates on the principle that there are only about 60 different numbers
#that any other given number could reach a sum-tone with. We can keep a solution bag of
#all possible solutions using a hashmap. To find the solution for a given note,
#we can check all the powers of two that this could sum with, and then store the best one.

#To learn more about solution bags, watch the very well made Algorithms Live episode on them:
#   https://www.youtube.com/watch?v=oaYsWnohXpA

#Efficiency: O((log2(10^18)+1)*n) = O(61*n), plus hash collisions

# Loop over songs
t=int(input())
for song in range(1, t+1):
   n=int(input());
   solutions={};
   ans=1;
   line=input().split(" ");
   for i in line:
      note=int(i);
      powOf2=2;
      bestScore=1;#We can always take just ourselves
      while (powOf2<=2000000000000000000):
         #see if there are any solutions in our bag that we can add on to
         if powOf2>note:
            matchingNote=powOf2-note;
            otherScore=solutions.get(matchingNote, 0)+1;
            bestScore=max(bestScore, otherScore);
         powOf2=powOf2*2;
      solutions[note]=bestScore;
      ans=max(ans, bestScore);
   print("Song #"+str(song)+": "+str(ans));
   
