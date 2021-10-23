import java.util.*;

public class alisaurus {
   public static void main(String[] args) {
      // Read in number of scenarios
      Scanner scan = new Scanner(System.in);
      int t = scan.nextInt();

      // Loop over scenarios
      for(int q = 1; q <= t; q++){
         // Read in number of alisauruses and see if it splits evenly
         int x = scan.nextInt();
         if(360 % x == 0){
            System.out.println("Attack!");
         }
         else{
            System.out.println("No go.");
         }
      }
   }
}
