#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int main(void){
   int cases;
   int slices;
   int sidelength;
   double rectangleArea;
   double height;
   double totalArea;

   // Read in number of deliveries
   scanf("%d",&cases);

   // Deal with each pizza delivery individually
   for(int i = 1; i <= cases; i++){
      // Parse out the number of pizza slices and the side length from the input
      scanf("%d",&slices);
      scanf("%d",&sidelength);

      // To find the height of an equilateral triangle, use the 30/60/90 triangle
      // formed by the height, one side, and half of the other side

      // The ratio of side lengths in 30/60/90 right triangles, with a hypotenuse of 2s:
      // Short leg = s
      // Long leg = sqrt(3)*s

      // Since the height is the long leg in this 30/60/90 triangle, and the hypotenuse
      // is the side of the equilateral triangle, we can calculate the height
      height = sqrt(3.0)*sidelength/2.0;
      //printf("Sidelength: %.3f\n",height);

      // The rectangular area that a single slice takes up is just base*height
      rectangleArea = sidelength*height;

      // Triangular pizza slices can be laid flush against each other, alternating
      // pointing up and pointing down, for maximum pizza-to-area ratio.

      // Figure 1:
      // --------   --------
      // \  /\  /   \  /\  /\
      //  \/  \/     \/  \/  \
      //   ----       --------

      // So compute the total area (accounting for the odd cases of an 'extra' slice)
      totalArea = (slices/2)*rectangleArea + (rectangleArea/2);
      if(slices%2 != 0){
         totalArea += .5*rectangleArea;
      }

      // But if there is only one slice, it takes up exactly it's rectangular area!
      if(slices == 1){
         totalArea = rectangleArea;
      }

      // Print out the answer in the proper format
      printf("Order #%d: %.3f\n",i,totalArea);
   }

   return 0;
}
