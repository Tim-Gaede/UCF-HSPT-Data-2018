
#include <stdio.h>
#include <stdlib.h>

// The dy/dx arrays store the eight directions that can be taken
// while searching for numbers. Storing them this way lets us iterate
// over them.
int dy[8]={1,0,-1,-1,-1,0,1,1};
int dx[8]={1,1,1,0,-1,-1,-1,0};


int r,c;

int preOp(int i,int j,char puzzle[r][c],long long numSoFar,int dir,long long find);
int postOp(int i,int j,char puzzle[r][c],long long numOne,long long numTwo,int op,int dir,long long find);

int main(int argc, char *argv[]) {
   int p,loop;

   // Loop over the number of puzzles
   scanf("%d",&p);
   for(loop=1;loop<=p;loop++){
      // Get the number of rows and columns
      scanf("%d",&r);
      scanf("%d",&c);

      // Read in the puzzle
      char puzzle[r][c];
      int i,j;
      for(i=0;i<r;i++){
         scanf("%s",puzzle[i]);
      }

      // Read in the number of queries
      int q,qloop;
      scanf("%d",&q);

      // Loop over the number of queries
      printf("Number Search #%d:\n",loop);
      for(qloop=0;qloop<q;qloop++){
         // Read in the number to search for (we need "long long" because we
         // need more than 32 bits)
         long long m;
         scanf("%lli",&m);
         
         // These loops try starting at every possible index in the
         // puzzle and going to every possible direction
         int ans=0,dir;
         for(i=0;i<r;i++){
            for(j=0;j<c;j++){
               // We can't start with things that aren't numbers
               if(puzzle[i][j]<'0'||puzzle[i][j]>'9')
                  continue;
                  
               // This tries all eight directions using the dy/dx arrays
               // (we "or" in each answer together)
               for(dir=0;dir<8;dir++){
                  ans|=preOp(i,j,puzzle,0,dir,m);
               }
            }
         }

         // Output answer whether we found an answer
         if(ans)
            printf("Yes\n");
         else
            printf("No\n");
      }
      printf("\n");
   }
   return 0;
}

// This is a helper function to make sure we never go out of bounds
int inBounds(int i,int j){
   if(i<0||i>=r||j<0||j>=c)
      return 0;
   return 1;
}

// preOp iterates over the number search in the designated direction
// as long as it hasn't taken an operator yet
int preOp(int i,int j,char puzzle[r][c],long long numOne,int dir,long long find){
   // numOne stores the number we're currently building. If it's
   // zero, that means we haven't taken anything yet, which isn't
   // allowed
   if(numOne==find&&find>0)
      return 1;
   
   // Make sure it is in bounds
   if(!inBounds(i,j))
      return 0;
   char next=puzzle[i][j];
   
   // If the character we're on is a number, add it to our current
   // number and keep searching
   // (next-'0' is the integer value of a digit stored as a character)
   if(next>='0'&&next<='9'){
      // We always add dy[dir] and dx[dir] because that represents the
      // direction we're searching in
      return preOp(i+dy[dir],j+dx[dir],puzzle,numOne*10+next-'0',dir,find);
   }
   
   // If our current character isn't a number, we have to use our other
   // function
   if(next=='+')
      return postOp(i+dy[dir],j+dx[dir],puzzle,numOne,0,0,dir,find);
   else if(next=='-')
      return postOp(i+dy[dir],j+dx[dir],puzzle,numOne,0,1,dir,find);
   else if(next=='*')
      return postOp(i+dy[dir],j+dx[dir],puzzle,numOne,0,2,dir,find);
   else
      return postOp(i+dy[dir],j+dx[dir],puzzle,numOne,0,3,dir,find);
}

//postOp iterates over the number search after we've seen an operator
int postOp(int i,int j,char puzzle[r][c],long long numOne,long long numTwo,
   int op,int dir,long long find){
   // If we're out of bounds or we're trying to add another operator,
   // this isn't possible
   if(!inBounds(i,j)||puzzle[i][j]<'0'||puzzle[i][j]>'9')
      return 0;
      
   // numTwo is the number we're building after the operator
   numTwo=numTwo*10+puzzle[i][j]-'0';
   long long ans=0;
   if(op==0)
      ans=numOne+numTwo;
   else if(op==1)
      ans=numOne-numTwo;
   else if(op==2)
      ans=numOne*numTwo;
   else{
      //If numOne%numTwo!=0, then numOne/numTwo isn't an integer,
      //so it's not allowed to be the solution and we have to
      //move on
      if(numTwo==0||numOne%numTwo!=0){
         if(!inBounds(i,j)||puzzle[i][j]<'0'||puzzle[i][j]>'9')
            return 0;
         return postOp(i+dy[dir],j+dx[dir],puzzle,numOne,numTwo,op,dir,find);
      }
      ans=numOne/numTwo;
   }

   // If we found the answer, return so; otherwise, keep searching
   if(ans==find)
      return 1;
   return postOp(i+dy[dir],j+dx[dir],puzzle,numOne,numTwo,op,dir,find);
}
