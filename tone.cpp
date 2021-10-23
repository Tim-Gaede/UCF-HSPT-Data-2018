#include <bits/stdc++.h>

#define MAX 1000000000000000000ll
#define ll long long
using namespace std;


int main() {
   ll notes[100001];
   int n, t;
   cin >> t;
   for(int song = 1; song <= t; song++) {
      // Read in the input
      cin >> n;
      for (int i = 0; i < n; i++) {
         cin >> notes[i];
      }

      // Keep a hashmap for our DP table
      unordered_map<ll, int> memo;
      int ans = 0;

      // Loop over the notes in order
      for(int i = 0; i < n; i++) {
         ll note = notes[i];
         int best = 0;
         // Brute force the power of 2 we combine to
         for(ll pow2 = 1; pow2 - note <= MAX; pow2 *= 2) {
            // Figure out what note we need in order to get this power of 2
            ll neededNote = pow2 - note;

            // If we have seen it before,
            if(memo.count(neededNote)) {
               // we can add ourself to their best chain, so this is a candidate
               best = max(best, memo[neededNote]);
            }
         }

         // +1 for ourself
         best++;

         // Store this in the memo table
         // We will always be better than whatever was there before,
         // so we can just overwrite 
         memo[note] = best;

         // We can end the chain here, so offer this into our global answer
         ans = max(ans, best);
      }
      printf("Song #%d: %d\n", song, ans);
   }
   return 0;
}
