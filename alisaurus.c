#include <stdio.h>

int main(){

  int t;
  int x;

  // Read in number of scenarios
  scanf("%d", &t);

  // Loop over each scenario
  for(int i = 0; i < t; i++){
    // Read in the number of alisauruses
    scanf("%d", &x);

    // If they can evenly divide the circle, they will attack
    if(360 % x == 0){
        printf("Attack!\n");
    }
    else{
        printf("No go.\n");
    }

  }

}
