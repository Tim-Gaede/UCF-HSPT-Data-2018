import java.util.ArrayList;
import java.util.Scanner;

public class lazy {
   static ArrayList<Road>[] adj;
   static int N, M, R;

   public static void main(String[] args) {
      // Read in number of cities
      Scanner scan = new Scanner(System.in);
      int T = scan.nextInt();

      // Loop over each city
      for(int t=1;t<=T;t++) {
         // Read in case
         N = scan.nextInt();
         M = scan.nextInt();
         R = scan.nextInt();
         
         // Built an adjacency list for the roads connecting
         adj = new ArrayList[N];
         for(int i=0;i<N;i++)adj[i] = new ArrayList<>();
         for(int i=0;i<R;i++) {
            Road r = new Road(scan.nextInt()-1, scan.nextInt()-1,scan.nextInt());
            adj[r.u].add(r);
         }
         
         // Seach over graph using Depth First Search
         ArrayList<Integer> paths = new ArrayList<>();
         paths.add(M);
         dfs(0,paths,0);

         // Go over each path and sum them up
         double sum = 0;
         for(int i : paths)
            sum += (double)M/(double)i;
         
         // Print out probability
         System.out.printf("City #%d: %.3f%%\n", t, 100*(1.0/sum));
      }
   }
   
   private static void dfs(int idx, ArrayList<Integer> paths, int sum) {
      // We reach the end so count this as one path
      if(idx == N-1) {
         paths.add(sum);
         return;
      }
      
      // Go over each road and see if we can go somehwere we haven't been yet
      for(Road r : adj[idx]) {
         if(r.used)continue;
         r.used = true;
         dfs(r.v, paths, sum+r.w);
         r.used = false;
      }
   }

   private static class Road {
      int u, v, w;
      boolean used;
      public Road(int u, int v, int w) {
         this.u=u;
         this.v=v;
         this.w=w;
      }
   }
}
