
#include <bits/stdc++.h>

using namespace std;

int main() {
    //read in the value for the number of days we have homework
    int d;
    cin >> d;
    
    //loop through each day
    for(int day = 1; day <= d; ++day) {
        //see how many problems the professor has said to do
        int p;
        cin >> p;
        
        //let's sort the problems by number and also take unique problems
        //both of these things can be done elegantly using a "set" from the standard library
        set<int> st;
        for(int i = 0; i < p; ++i) {
            int x;
            cin >> x;
            st.insert(x);
        }
        
        //now we need to have each section of contiguous problems in their own "block"
        vector < vector<int> > blocks;
        
        //this is the current "block" that we are adding to
        vector<int> block;
        
        //let's loop through each unique, sorted element in our set
        for(int x : st) {
            if(block.empty()) { //in the case that our current "block" is empty, we can just add the current element to this block
                block.push_back(x);
            } else if(block[block.size() - 1] != x - 1) { //in the case that our "block" is not empty, but the last problem is NOT one before our current problem number
                //in this case, we want to finish the previous "block" and add it to the list of "blocks" and clear the list
                blocks.push_back(block);
                block.clear();
                //now we add the new problem to it's own block
                block.push_back(x);
            } else {
                //if all's well and our current problem number is one above the last problem number in the "block",
                //then we can just add the current problem to the end of the "block"
                block.push_back(x);
            }
        }
        //we didn't add the very last block, so let's add it here
        blocks.push_back(block);
        
        //use a string stream to make outputing and formatting easier
        stringstream ans;
        
        //go through each "block"
        for(auto bl : blocks) {
            if(bl.size() == 1) { //if there's only one problem in the block, then it should be displayed on it's own
                ans << bl[0] << ", ";
            } else { //otherwise, if there're more than one 
                ans << bl[0] << "-" << bl[bl.size() - 1] << ", ";
            }
        }
        string str = ans.str();
        int size = str.length();
        cout << "Day #" << day << ": ";
        for(int i = 0; i < size - 2; ++i) {
            cout << str[i];
        }
        cout << endl << endl;
    }
    
    return 0;
}
