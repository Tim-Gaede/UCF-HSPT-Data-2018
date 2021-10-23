import java.util.Scanner;

public class hundred {

   public static void main(String[] args) {
      // Read in number of values
      Scanner in = new Scanner(System.in);
      int t = in.nextInt();

      // Loop over values
      for(int i = 0; i < t;i++) {
         // Read them and convert them!
         int n = in.nextInt();
         System.out.println(n*120);
      }
   }

}
