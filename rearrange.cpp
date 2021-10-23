/*
 * To solve this problem I will be using a modified version of the Trie data structure.
 *
 * In general, to solve this problem we need to develop a data structure capable of
 * "resorting" in O(1) and querying for the Kth lexicographical element in O(1).
 *
 * In a Trie, querying for the Kth lexicographical element is normally an O(N) operation,
 * where N is the total number of nodes in the trie. This is because we must traverse the
 * Trie in pre-order until we hit the Kth item. However, we can speed this up quite easily
 * by storing some more information. Lets have each node of the Trie store one addition
 * piece of data: the number of strings contained in the nodes sub-tree (Aka the sum of all
 * counts in the subtree). Using this, we can ensure that we only go down the tree directly
 * to the Kth item by iterating over all the children in order until we find the one that
 * contains the Kth element.  This improves the runtime of our query to O(A*L) where A is
 * the alphabet size and L is the maximum string length. In this problem A is 26 and L is
 * at most 50, so our query will easily run in time.
 *
 * To "resort" the Trie in O(1) we simply change the order that we iterate over the
 * children of each node.  We can swap two characters by swapping their position in the
 * traversal order.
 */

#include <bits/stdc++.h>
using namespace std;

struct Node{
   Node *next[26];
   int count;      // This is number is the number of strings that "end here"
   int below;      // This is the number of strings that end in the subtree rooted at
                   // this node

   Node(){
      for(int i=0; i<26; i++)
         next[i] = nullptr;
      count = 0;
      below = 0;
   }

   ~Node(){
      for(int i=0; i<26; i++)
         if(next[i] != nullptr)
            delete next[i];
   }
};

int main(){
   int runs; cin >> runs;

   for(int r=0; r<runs; r++){
      Node head;

      int n, q;
      cin >> n >> q;

      /*
       * Here I read in the labels and build the Trie. I only allocate nodes that are actually
       * used in order the make the Trie fit into memory.
       */
      for(int i=0; i<n; i++){
         string next;
         cin >> next;

         Node *cur = &head;

         for(int i=0; i<next.length(); i++){
            if(cur->next[next.at(i)-'a'] == nullptr)
               cur->next[next.at(i)-'a'] = new Node();

            cur->below++;
            cur = cur->next[next.at(i)-'a'];
         }
         cur->below++;
         cur->count++;
      }

      /*
       * Here I initialize the traversal order for the Trie. The "swapIndex" array allows us to
       * quickly find where a character is in the current traversal order to make swapping truly
       * O(1). However, since the alphabet is only 26 characters, you can also just iterate over
       * the traversal array to find each character to swap.
       */
      int swapIndex[26];
      int traversal[26];

      for(int i=0; i<26; i++){
         swapIndex[i] = i;
         traversal[i] = i;
      }

      /*
       * Here we begin processing the queries.
       */
      cout << "Gift Exchange #" << r+1 << ":" << endl;
      for(int i=0; i<q; i++){
         int type; cin >> type;

         /*
          * If it is a swap query, first find the position in the traversal order for our two
          * Characters using the swapIndex array. Then swap their positions in the traversal
          * array. Finally, swap their values (aka their positions) in the swapIndex array.
          */
         if(type == 1){
            char a, b;
            cin >> a >> b;

            int ai = swapIndex[a-'a'];
            int bi = swapIndex[b-'a'];

            traversal[ai] = b-'a';
            traversal[bi] = a-'a';

            swapIndex[a-'a'] = bi;
            swapIndex[b-'a'] = ai;
         }

         /*
          * If it is a find query, we must traverse the Trie to find our string. The process is this:
          *
          *    1. Begin iterating over the traversal array in order.
          *    2. At each iteration, check the number of nodes in the subtree of the current node given
          *       by the traversal array.
          *      2a. If the number of nodes in the subtree is < K, our answer is not in this subtree,
          *          so decrease K by the number of nodes in this subtree and continue iterating from 2.
          *      2b. If the number of nodes in the subtree is >= K, our answer is in this subtree
          *         2ba. If the count of this node >= K, our answer is this node! Add it to the output
          *              string and return out of out search.
          *         2bb. If the count of this node < K, our answer is below this node.  But since this
          *              is a Trie, the answer includes this nodes character so add it the output string.
          *              Then, decrement K by the count of the current node, into the node, and restart
          *              the process from 1.
          */
         else{
            int k;
            cin >> k;

            Node *cur = &head;

            // This char array will store our output string that we build as we traverse the Trie
            int outputIdx = 0;
            char output[51];

            bool completed = false;
            while(!completed){

               // Begin iterating over the traversal array in order
               for(int i=0; i<26; i++){
                  if(cur->next[traversal[i]] == nullptr) continue;

                  // Our target is not in this subtree, skip it
                  // (node->below is number of strings in the subtree)
                  if(cur->next[traversal[i]]->below < k){
                     k -= cur->next[traversal[i]]->below;
                  }

                  // We are looking for this node! Break out and print
                  else if(cur->next[traversal[i]]->count >= k){
                     output[outputIdx++] = traversal[i]+'a';
                     completed = true;
                     break;
                  }

                  // We are looking for a child of this node, go into it
                  else{
                     k -= cur->next[traversal[i]]->count;
                     output[outputIdx++] = traversal[i]+'a';
                     cur = cur->next[traversal[i]];
                     break;
                  }
               }
            }

            // Don't forget to add the null terminator for C style strings
            output[outputIdx] = '\0';
            cout << output << endl;
         }
      }
      cout << endl;
   }
   return 0;
}
