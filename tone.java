
import java.util.Arrays;
import java.util.HashMap;
import java.util.Scanner;

public class tone
{
   static long[] pow2 = new long[63];
   static int[][] pair;
   static int[] dp;
   public static void main(String[] args)
   {
      //Pre-compute the powers of 2
      pow2[0] = 1;
      for (int i = 1; i < pow2.length; i++)
         pow2[i] = pow2[i-1]*2;
      
      // Loop over the songs
      Scanner scan = new Scanner(System.in);
      int t = scan.nextInt();
      for (int testCase = 1; testCase <= t; testCase++)
      {
         // Read in the frequencies
         int n = scan.nextInt();
         long[] frequencies = new long[n];
         for (int i = 0; i < n; i++)
            frequencies[i] = scan.nextLong();
         
         //For each number in the array, we need to know its closest neighbor before it which helps it to produce a power of 2 sum tone.
         //We will store the index of this neighbor in 'pair' for every power of 2.
         pair = new int[n][pow2.length];
         HashMap<Long, Integer> map = new HashMap<>(); //Stores the index of the last occurrence of each number
         for (int i = 0; i < n; i++)
         {
            for (int j = 0; j < pow2.length; j++)
            {
               if (frequencies[i] < pow2[j])
               {
                  Integer idx = map.get(pow2[j] - frequencies[i]); //The values at indexes i and idx sum to this power of 2
                  if (idx == null)
                     pair[i][j] = -1; //There is no partner to make this sum tone                     
                  else
                     pair[i][j] = idx;
               }
               else
                  pair[i][j] = -1; //There is no partner to make this sum tone
            }
            map.put(frequencies[i], i);
         }

         //Initialize memo table
         dp = new int[n];
         Arrays.fill(dp, -1);
         
         //We will find the max length by trying each ending value of the possible subsequences
         int max = 0;
         for (int i = 0; i < n; i++)
            max = Math.max(max, getMaxLength(i));
         
         System.out.printf("Song #%d: %d\n", testCase, max);
      }
   }


   /*
    * This method returns the maximum length of the subsequence specified in the problem, which ends at index idx (0-based).
    * For example, if the array is [2, 5, 6, 10, 8],
    * getMaxLength(2) will return 2, since we can make the subsequence 2, 6. Also,
    * getMaxLength(4) will return 1, since we cannot create a longer subsequence that ends with 8.
    */
   private static int getMaxLength(int idx)
   {
      if (idx == 0) //Base case
         return 1;
      if (dp[idx] >= 0) //Avoid recalculating the answer if we've already found it
         return dp[idx];
      int max = 1; //It is always possible to form a subsequence of length 1
      for (int i = 0; i < pow2.length; i++)
      {
         if (pair[idx][i] >= 0)
            max = Math.max(max, 1 + getMaxLength(pair[idx][i])); //We can add frequency[idx] to the longest subsequence ending at index pair[idx][i]
      }
      
      return dp[idx] = max; //Memoize our answer
   }
}
