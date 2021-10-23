#include <stdio.h>
#include <stdlib.h>

static void one_case(void) {
   int a, b, c;

   // Read in the three gifts
   scanf("%d %d %d", &a, &b, &c);

   // Default min difference
   int diff = abs(b - a);

   // Now check all other pairings
   if (abs(c - a) < diff)
      diff = abs(c - a);
   if (abs(c - b) < diff)
      diff = abs(c - b);
  
   // Print result
   printf("%d\n", diff);
}

int main(void) {
   // Read the number of gifts
   int t;
   scanf("%d", &t);

   // Loop over the cases
   while(t--) one_case();

   return 0;
}

