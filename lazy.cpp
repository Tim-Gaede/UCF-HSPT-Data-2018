#include <bits/stdc++.h>

typedef long long ll;

struct edge {
   ll first, second;
   bool used;
};

typedef std::vector<std::vector<edge>> adj_list;

static void dfs(const ll& curr, const ll& goal, std::vector<ll>& paths,
                adj_list& graph, const ll& len) {

   /* we reached the end, so we stop. */
   if (curr == goal) {
      paths.push_back(len);
      return;
   }

   /*
      Go to all neighbors of the current node...
      but only if there is an unused edge to there.
   */
   for (auto& next : graph[curr]) {
      /* If this node is used, skip it */
      if (next.used) continue;

      /* mark edge as used */
      next.used = true;

      /* call depth first search to go to our children */
      dfs(next.first, goal, paths, graph, len + next.second);

      /* unmark edge for next dfs */
      next.used = false;
   }
}

/* code for one test case. */
static void one_case() {
   ll n,m,r;
   std::scanf("%lld %lld %lld", &n, &m, &r);

   /* create graph */
   adj_list graph(n);
   for (ll i = 0,a,b,c; i < r; ++i) {
      std::scanf("%lld %lld %lld",&a,&b,&c);
      --a; --b;

      /* input DIRECTED edge. */
      graph[a].push_back({b,c, false});
   }

   /* make dfs stuff */
   std::vector<ll> paths(1, m); /* start with the only path being the new one */

   /* do the dfs and record the path lengths. */
   dfs(0, n-1, paths, graph, 0);

   /* sort the path lengths */
   std::sort(paths.begin(), paths.end());

   /* variable to hold the sum of all the proportions */
   double prob = 0;

   /* proportionalize the paths against the smallest path */
   double first = paths.front();
   for (ll i = 0; i < paths.size(); ++i) {
      prob += first / paths[i];
   }
   double addition = first / m;

   /* output result */
   std::printf("%.3lf%%\n", 100 * addition / prob);
}

int main(void) {
   /* handles each test case. */
   ll t;
   std::scanf("%lld",&t);
   for (ll i = 1; i <= t && std::printf("City #%lld: ",i); ++i) one_case();
   return 0;
}
