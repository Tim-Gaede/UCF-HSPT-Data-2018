import java.util.*;

public class tic {
   
   static int a;
   static int b;
   static int[][] grid;
   static boolean[] threeInRow;
   static boolean[] fourInRow;
   
   static int[] dp;
   static int oo = Integer.MAX_VALUE;

   public static void main(String[] args) {
      Scanner scan = new Scanner(System.in);

      //Precompute which masks have three in a row or four in a row
      threeInRow = new boolean[1 << 16];
      fourInRow = new boolean[1 << 16];
      for(int i = 0; i < 1 << 16; i++){
         int[][] arr = convert(i);
         if(three(arr)){
            threeInRow[i] = true;
            if(four(arr)){
               fourInRow[i] = true;
            }
         }
      }

      //Scan input
      int t = scan.nextInt();
      for(int q = 1; q <= t; q++){
         a = scan.nextInt();
         b = scan.nextInt();
         grid = new int[4][4];
         for(int i = 0; i < 4; i++){
            for(int j = 0; j < 4; j++){
               grid[i][j] = scan.nextInt();
            }
         }

         //Prepare our dp array to store answers for masks
         dp = new int[1 << 16];
         Arrays.fill(dp, oo);
         dp[(1 << 16)-1] = 0;
         int diff = go(0);

         //If the difference is negative, that means the player
         //to move first loses. If it is positive then he wins.
         if(diff < 0){
            System.out.println("Game #"+q+": Barb wins.");
         }
         else if(diff > 0){
            System.out.println("Game #"+q+": Alex wins.");
         }
         else{
            System.out.println("Game #"+q+": It's a draw.");
         }
      }
   }
   
   //Computes the maximum difference between the first player that makes
   //the move and the player that moves after
   static int go(int mask){
      if(dp[mask] != oo) return dp[mask];
      int max = -oo;
      for(int i = 0; i < 16; i++){
         int on = mask & (1 << i);
         if(on == 0){
            //We can transition to a mask that includes this bit
            //When we transition, we add the value at the cell
            //as well as check for the first three/four in a row bonus
            int next = mask | (1 << i);
            int add = grid[i/4][i%4];
            if(!threeInRow[mask]){
               if(threeInRow[next]){
                  add += a;
               }
            }
            if(!fourInRow[mask]){
               if(fourInRow[next]){
                  add += b;
               }
            }
            max = Math.max(max, add-go(next));
         }
      }
      return dp[mask] = max;
   }
   
   //Determines if the grid has four 1s in a row
   static boolean four(int[][] arr){
      //Row
      for(int i = 0; i < 4; i++){
         for(int j = 0; j < 4; j++){
            if(arr[i][j] == 0) break;
            if(j == 3) return true;
         }
      }
      //Column
      for(int i = 0; i < 4; i++){
         for(int j = 0; j < 4; j++){
            if(arr[j][i] == 0) break;
            if(j == 3) return true;
         }
      }
      //Diagonal 1
      for(int i = 0; i < 4; i++){
         if(arr[i][i] == 0) break;
         if(i == 3) return true;
      }
      //Diagonal 2
      for(int i = 0; i < 4; i++){
         if(arr[i][3-i] == 0) break;
         if(i == 3) return true;
      }
      return false;
   }
   
   //Determines if the grid has three 1s in a row
   static boolean three(int[][] arr){
      for(int i = 0; i < 4; i++){
         for(int j = 0; j < 4; j++){
            //Row
            int ok = 1;
            for(int k = 0; k < 3; k++){
               if(j+k >= 4){
                  ok = 0;
                  break;
               }
               ok &= arr[i][j+k];
            }
            if(ok == 1) return true;
            //Column
            ok = 1;
            for(int k = 0; k < 3; k++){
               if(i+k >= 4){
                  ok = 0;
                  break;
               }
               ok &= arr[i+k][j];
            }
            if(ok == 1) return true;
            //Diagonal 1
            ok = 1;
            for(int k = 0; k < 3; k++){
               if(i+k >= 4 || j+k >= 4){
                  ok = 0;
                  break;
               }
               ok &= arr[i+k][j+k];
            }
            if(ok == 1) return true;
            //Diagonal 2
            ok = 1;
            for(int k = 0; k < 3; k++){
               if(i-k < 0 || j+k >= 4){
                  ok = 0;
                  break;
               }
               ok &= arr[i-k][j+k];
            }
            if(ok == 1) return true;
         }
      }
      return false;
   }
   
   //Converts a mask to its 2d array representation
   static int[][] convert(int mask){
      int[][] res = new int[4][4];
      for(int i = 0; i < 16; i++){
         int on = mask & (1 << i);
         if(on != 0){
            res[i/4][i%4] = 1;
         }
      }
      return res;
   }
   
   //Function used for debugging
   static void print(int[][] arr){
      for(int i = 0; i < arr.length; i++){
         for(int j = 0; j < arr.length; j++){
            System.out.print(arr[i][j]+" ");
         }
         System.out.println();
      }
   }
}
