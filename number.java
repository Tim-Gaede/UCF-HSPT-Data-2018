import java.util.*;
import java.io.*;

public class number {

   static HashSet<Long> nums;
   static char[][] grid;

   public static void main(String[] args) throws FileNotFoundException {
      Scanner scan = new Scanner(System.in);
      PrintWriter out = new PrintWriter(System.out);
      int t = scan.nextInt();
      for(int q = 1; q <= t; q++){
         nums = new HashSet<Long>();
         int r = scan.nextInt();
         int c = scan.nextInt();
         grid = new char[r][c];
         for(int i = 0; i < r; i++){
            String s = scan.next();
            for(int j = 0; j < c; j++){
               grid[i][j] = s.charAt(j);
            }
         }
         //For each row and column, we do a search in all directions
         //We store our numbers in a HashSet to easily look them up.
         for(int i = 0; i < r; i++){
            for(int j = 0; j < c; j++){
               if(isNum(grid[i][j])){
                  search(i, j);
               }
            }
         }
         //Now we can easily answer our queries
         out.println("Number Search #"+q+":");
         int query = scan.nextInt();
         for(int i = 0; i < query; i++){
            long m = scan.nextLong();
            if(nums.contains(m)){
               out.println("Yes");
            }
            else{
               out.println("No");
            }
         }
         out.println();
      }
      out.flush();
   }

   //Given a position and direction, finds all available numbers
   static void go(int row, int col, int dr, int dc){
      //Pre serves as our number before we find the operation,
      //Post is the number that comes after. This way we can easily
      //compute what numbers we find by Number = Pre (operation) Post
      char op = '?';
      String pre = "";
      String post = "";
      while(inBounds(row, col)){
         //This means we have found an operation.
         if(!isNum(grid[row][col])){
            //Numbers can only be found using one or zero operations
            //If we find two operations, we stop the search.
            if(op != '?') return;
            op = grid[row][col];
         }
         else{
            if(op == '?'){
               //Zero operations - just concatenate the numbers
               pre += grid[row][col];
               nums.add(Long.parseLong(pre));
            }
            else{
               //Compute using one operation
               post += grid[row][col];
               if(op == '+')
                  nums.add(Long.parseLong(pre)+Long.parseLong(post));
               if(op == '-')
                  nums.add(Long.parseLong(pre)-Long.parseLong(post));
               if(op == '*')
                  nums.add(Long.parseLong(pre)*Long.parseLong(post));
               if(op == '/'){
                  long a = Long.parseLong(pre);
                  long b = Long.parseLong(post);
                  if(a % b == 0) nums.add(a/b);
               }
            }
         }
         row += dr;
         col += dc;
      }
   }
   
   //This function prepares a search in all possible directions
   static void search(int row, int col){
      int[] dx = {1, 1, 0, -1, -1, -1, 0, 1};
      int[] dy = {0, 1, 1, 1, 0, -1, -1, -1};
      for(int i = 0; i < 8; i++){
         go(row, col, dx[i], dy[i]);
      }
   }
   
   //Returns true if a character is a digit
   static boolean isNum(char c){
      return c <= '9' && c >= '0';
   }
   
   //Makes sure that we are in array bounds
   static boolean inBounds(int row, int col){
      return row < grid.length && col < grid[0].length && row >= 0 && col >= 0;
   }
}
