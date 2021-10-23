import java.util.Arrays;
import java.util.Scanner;

/*
 * If we sort the gifts by price, then the smallest difference in price will either
 * be between the first two gifts or the last two gifts (If we sort them, this difference
 * will always be positive if we calculate it correctly). We can take whichever difference
 * is smaller, and print that as our answer.
 */

public class gifts {
   public static void main(String[] args) {
      Scanner s=new Scanner(System.in);
      int v=s.nextInt();                                                       //read in the number of test cases
      for (int visit=0; visit<v; visit++) {
         int[] gifts= {s.nextInt(), s.nextInt(), s.nextInt()};                 //read in the three gift prices
         Arrays.sort(gifts);                                                   //sort by price in increasing order
         System.out.println(Math.min(gifts[1]-gifts[0], gifts[2]-gifts[1]));   //print out the smaller difference in price
      }
   }
}
