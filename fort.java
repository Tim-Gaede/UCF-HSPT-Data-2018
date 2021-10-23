import java.util.*;
import java.math.*;
import java.io.*;

public class fort {
   public static void main(String[] args) {
      Scanner scan = new Scanner(System.in);
      
      // number of test cases to evaluate
      int t = scan.nextInt();
      
      // get to the next line where the input starts
      scan.nextLine();
      
      // evaluate test cases
      for(int tt = 0 ; tt < t ; tt++) {
         // read in potential password
         String s = scan.nextLine();
         
         // check if s is equals to "hey guys"
         if(s.equals("hey guys"))
            System.out.println(s);
         else
            System.out.println("buzz");
      }
   }
}
