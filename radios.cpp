#include <iostream>
using namespace std;

/*
Solution path: We will binary search the minimum signal length, and run a DFS to
check if a signal length is sufficiently large to for all islands to communicate.
*/

int n;
int xs[201], ys[201];

//returns the distance from tower i to tower j, squared
long long distSquared(int i, int j) {
   long long dx=xs[i]-xs[j];
   long long dy=ys[i]-ys[j];
   return dx*dx+dy*dy;
}

//Checks whether a given radius is large enough for all towers to communicate
bool works(long long r) {
   bool reachable[201];
   int stack[202];
   stack[0]=1;//stack[0] stores the size of the stack, indecies 1 to 200 store the data.
   stack[1]=0;
   for (int i=0; i<n; i++)
      reachable[i]=false;
   
   //Do a DFS with my array-based stack. Runs in O(v+E) because each node can be added at most once
   //r is of type long long because it is being squared, and it is possible it could overflow if
   //r gets near 10^5, which is what I set high to in the binary search.
   reachable[0]=true;
   while (stack[0]!=0) {
      int current=stack[stack[0]--];
      for (int i=0; i<n; i++) {
         if (distSquared(current, i)<=r*r&&!reachable[i]) {
            reachable[i]=true;
            stack[++stack[0]]=i;
         }
      }
   }
   
   for (int i=0; i<n; i++)
      if (!reachable[i])
         return false;
      
   //If there were no islands that were unreachable, then this radius is sufficiently large
   return true;
         
}

int main() {
   //read in number of islands
   int t;
   cin>>t;

   //loop over each island
   for (int tt=1; tt<=t; tt++) {
      //get number of towers and read them in
      cin>>n;
      for (int i=0; i<n; i++) {
         cin>>xs[i];
         cin>>ys[i];
      }

      //coordinates are bounded by 10^4, so high is definitely large enough
      //This will binary search for the smallest r that works.
      int low=0, high=100000;
      while (low<high) {
         int mid=(low+high)/2;
         if (works(mid)) {
            high=mid;
         }
         else {
            low=mid+1;
         }
      }
      //the loop will end when low==high at the minimum valid radius
      cout<<"Island #"<<tt<<": "<<low<<endl;
   }
   return 0;
}
