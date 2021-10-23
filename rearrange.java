import java.io.IOException;
import java.io.PrintWriter;
import java.util.HashMap;
import java.util.Scanner;

/* 
 * The crux of this solution is a data structure called a Trie, which is a tree-like construct.
 * The children of a node correspond to letters in an alphabet. It's an efficient way to store
 * a large number of strings by recycling nodes that correspond to the same prefix.
 *
 * You can read more about Tries here: https://en.wikipedia.org/wiki/Trie
 *
 */

public class rearrange {
   private static class Solver {

      class Node {
         char l;
         boolean term = false;
         int size = 0;
         HashMap<Integer, Node> children = new HashMap<>();

         // Creates a new node with letter value ll.
         // Sets this node's character (l) to the character represented by ll.
         Node(int ll) {
            l = (char) (ll + 'a');
         }

         // This method pushes the word down the trie
         void push(int[] w, int at) {
            // We found another letter which exists on this node, so increment its size
            size++;
            // We're on the last letter in this word, so mark it as a terminal node and
            // return
            if (at == w.length) {
               term = true;
               return;
            }
            // If we don't have an edge pointing to the next letter in this word, set a node
            // up for it
            if (!children.containsKey(w[at]))
               children.put(w[at], new Node(w[at]));
            // Push the rest of this word to the next node
            // we use (at + 1) to indicate that we're looking at the at'th letter on
            children.get(w[at]).push(w, at + 1);
         }

         // Returns the n'th largest string relative to this node
         String solve(int num) {
            // If we're looking for the 1st word in the list, and thsi is a terminal node,
            // then we've found
            // the final letter. Return an empty string because there is nothing further to
            // build.
            if (num == 1 && term)
               return "";
            // If this node is a terminal node, then we must count it as a word.
            // "pick" will contain the number of word's we've seen so far.
            int pick = term ? 1 : 0;
            // This will iterate over the characters in the alphabet in whatever order the
            // rearrange-inator has
            // placed them so far.
            for (int i : order) {
               // If this node has no children with this letter, skip this letter
               if (!children.containsKey(i))
                  continue;
               Node c = children.get(i);
               // If we've seen "pick" words, and skipping past all of this child's words would
               // put us
               // past the num'th word, then we know that the num'th word is down this branch.
               // So,
               // return the character corresponding to this branch PLUS whatever word is (num
               // - pick)'th
               // down this branch.
               if (pick + c.size >= num)
                  return c.l + c.solve(num - pick);
               // We've seen c.size more words, so increment pick.
               pick += c.size;
            }
            // This return statement shouldn't ever be called.
            return "";
         }
      }

      int N, Q;
      Node root;
      int[] order;

      // This method locates a and b in the order array, then swaps them.
      void flip(int a, int b) {
         int u = 0, v = 0;
         for (int i = 0; i < 26; i++)
            if (order[i] == a)
               u = i;
            else if (order[i] == b)
               v = i;
         // At this point, u is the location of a, and v is the location of b.
         // The line below will swap the items at locations u and v.
         order[u] = order[v] ^ order[u] ^ (order[v] = order[u]);
      }

      void solve(int testNumber, Scanner s, PrintWriter out) {

         // Set up an array which maintains the order of our alphabet
         // 0 is A, 1 is B, etc.
         order = new int[26];
         for (int i = 0; i < 26; i++)
            order[i] = i;

         // Build the root node in our trie. It doesn't have a specific letter, so we
         // will give it a value of -1.
         root = new Node(-1);

         // Read input.
         N = s.nextInt();
         Q = s.nextInt();
         for (int i = 0; i < N; i++) {
            char[] word = s.next().toCharArray();
            // This turns our array of letters into an array of corresponding integers.
            // For example: ['b', 'e', 's', 's', 'i', 'e'] -> [1, 4, 18, 18, 8, 4]
            int[] ww = new int[word.length];
            for (int j = 0; j < ww.length; j++)
               ww[j] = word[j] - 'a';
            // Push this word down down through the trie, starting at the root node.
            root.push(ww, 0);
         }

         // Print the case header
         out.printf("Gift Exchange #%d:%n", testNumber);
         // Process each query
         for (int i = 0; i < Q; i++) {
            switch (s.nextInt()) {
            case 1:
               // Again, convert the incoming characters to integers.
               int a = s.next().charAt(0) - 'a', b = s.next().charAt(0) - 'a';
               // Swap these two integers in our order array.
               flip(a, b);
               break;
            case 2:
               // Read in the rank of the number we seek and print the answer starting from the
               // root node.
               int rank = s.nextInt();
               out.println(root.solve(rank));
               break;
            }
         }
                        out.println();

      }

   }

   // Set up input/output, and read in number of cases.
   // Solver.solve will process each case individually.
   public static void main(String[] args) throws IOException {
      Scanner s = new Scanner(System.in);
      PrintWriter out = new PrintWriter(System.out);
      Solver solver = new Solver();
      int T = s.nextInt();
      for (int t = 1; t <= T; t++)
         solver.solve(t, s, out);
      s.close();
      out.close();
   }

}
