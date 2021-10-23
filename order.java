import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashSet;
import java.util.Scanner;

/*
 * This is primarily an implementation problem. It is helpful to sort the array and remove duplicates first, and then combining
 * ranges is fairly straight-forward
 */

public class order {
   public static void main(String[] args) {
      Scanner s=new Scanner(System.in);
      int d=s.nextInt();
      for (int day=0; day<d; day++) {
         int p=s.nextInt();

         //hashsets automatically remove duplicates for you
         HashSet<Integer> set=new HashSet<>();
         for (int i=0; i<p; i++)
            set.add(s.nextInt());
         int[] a=new int[set.size()];
         int index=0;
         for (int i:set)
            a[index++]=i;
         Arrays.sort(a);
         int rangeStart=a[0];
         ArrayList<Range> ranges=new ArrayList<>();
         for (int i=1; i<a.length; i++) {
            if (a[i]!=a[i-1]+1) {
               //then we broke a continuous range
               ranges.add(new Range(rangeStart, a[i-1]));
               rangeStart=a[i];
            }
         }
         //don't forget to add the last range
         ranges.add(new Range(rangeStart, a[a.length-1]));
         
         //finally, print out the answer
         System.out.print("Day #"+(day+1)+": ");
         for (int i=0; i<ranges.size()-1; i++) {
            System.out.print(ranges.get(i)+", ");
         }
         System.out.print(ranges.get(ranges.size()-1));
         System.out.println('\n');
      }
   }
   
   private static class Range {
      int start, end;
      public Range(int start, int end) {
         this.start=start;
         this.end=end;
      }
      
      public String toString() {
         if (start==end)
            return ""+start;
         return start+"-"+end;
      }
   }
}
