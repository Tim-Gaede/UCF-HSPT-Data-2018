import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.List;
import java.util.PriorityQueue;
import java.util.Scanner;

public class radios 
{
   static class Edge implements Comparable<Edge>
   {
      int source, sink, weight;
   
      Edge(int from, int to, int dist)
      {
         source = from;
         sink   = to;
         weight = dist;
      }
      
      public int compareTo(Edge e) 
      {
         return weight - e.weight;
      }
   }
   
   static class DisjointSet 
   {
      int[] s;
      
      public DisjointSet(int n) {
         Arrays.fill(s = new int[n], -1);
      }
      
      public int find(int i) {
         return s[i] < 0 ? i : (s[i] = find(s[i]));
      }
      
      public boolean union(int a, int b) {
         if ((a = find(a)) == (b = find(b))) return false;
         if(s[a] == s[b]) s[a]--;
         if(s[a] <= s[b]) s[b] = a; else s[a] = b;
         return true;
      }
   }
   
   static int t, n;
   static int[][] loc, dist;
   static PriorityQueue<Edge> edgeQueue;

   public static void main(String[] args) 
   {
      // Read in number of islands
      Scanner scan = new Scanner(System.in);
      t = scan.nextInt();
      
      // Loop over islands
      for (int island = 1; island <= t; island++)
      {
         // read in how many radios on this island
         n = scan.nextInt();
         
         // create arrays to store location and distance
         loc = new int[2][n];
         dist = new int[n][n];
         
         // save the x and y coordinates for each radio
         for (int radio = 0; radio < n; radio++)
         {
            loc[0][radio] = scan.nextInt();
            loc[1][radio] = scan.nextInt();
         }
            
         List<Edge> edges = new ArrayList<Edge>();
         
         // create edges between the radios based upon their distance
         for (int source = 0; source < n; source++)
         {
            for (int sink = 0; sink < n; sink++)
            {
               // do not create cycling edges
               if (source == sink) continue;

               // when we create the edges, ceil the distance for the proper int value
               int dist = (int) Math.ceil(Math.sqrt(Math.pow(loc[0][source]-loc[0][sink], 2) 
                     + Math.pow(loc[1][source]-loc[1][sink], 2)));
               edges.add(new Edge(source, sink, dist));
            }
         }
         
         // Sort the edges based upon their weights
         Collections.sort(edges);
         
         // Create a disjoint set for the min spanning tree
         DisjointSet set = new DisjointSet(n);
         int maxDist = 0, count = 0;
         
         // Loop through all the edges
         for (Edge e : edges)
         {
            // find which set each radio on the edge
            // belongs to to ensure we can add the edge
            int root1 = set.find(e.source);
            int root2 = set.find(e.sink);
            
            if (root1 == root2) continue;
            
            // We are looking for maximum of the min
            // spanning tree, so continuously save the
            // max weight when we add an edge
            maxDist = Math.max(e.weight, maxDist);
            set.union(e.source, e.sink);
         }
         
         // print out the result
         System.out.println("Island #" + island + ": " + maxDist);
      }
   }
}
