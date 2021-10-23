#include <bits/stdc++.h>

using namespace std;

//We run a dp to solve for the best difference we can get between our opponent's score and our score
//The locations that have been X'd can be thought of as a bitmask.
//For example: X..X     1001
//             X...  -> 1000 -> 1001100000100000 -> 38944, meaning we can easily memoize upon this value.
//             ..X.     0010
//             ....     0000

//There are 2^16 possible different masks, meaning we only have to process these 2^16 different possible board states.
int grid[4][4];
int board[4][4];
int boardbit;
int dp[1<<26];
int bonus3, bonus4;

//We need to know if we have completed a 3-in-a-row or a 4-in-a-row
//To do so, we check how much our most recent move completes
int check(int x, int y){
    if(board[y][x]==0)return 0;
    int amt = 0;
    //vertical, diagonal down, horizontal, diagonal up
    int dx[] = {0,1,1,1};
    int dy[] = {1,-1,0,1};
    for(int dir = 0; dir < 4; dir++){
        //for a given point, need to check in both directions along the row/col/diagonal
        //i.e -x--, has 1 - on the left and 2 on the right, for 4 total
        int first = 0;
        int second = 0;
        for(int i = 1; i < 4; i++){
            //stay within the bounds of the board
            if(x+dx[dir]*i>=4)break;
            if(x+dx[dir]*i<0)break;
            if(y+dy[dir]*i>=4)break;
            if(y+dy[dir]*i<0)break;

            //stop when no longer on an X
            if(board[y+dy[dir]*i][x+dx[dir]*i]!=1)break;
            first = max(first,i);
        }
        for(int i = 1; i < 4; i++){
            if(x-dx[dir]*i>=4)break;
            if(x-dx[dir]*i<0)break;
            if(y-dy[dir]*i>=4)break;
            if(y-dy[dir]*i<0)break;
            if(board[y-dy[dir]*i][x-dx[dir]*i]!=1)break;
            second = max(second,i);
        }
        amt = max(amt,1+first+second);
    }
    return amt;
}

int canwin() {
    //check if we have visited this state before, if so simply return this value
    if(dp[boardbit]!=1000000000)return dp[boardbit];

    int ans = 1000000000;
    int tried= 0;
    //try all possible moves
    for(int x = 0; x < 4; x++){
        for(int y = 0; y < 4; y++){
            //if we have already used this spot, don't place an X here
            if(board[y][x]!=0)continue;
            tried++;
            int oldbonus3 = bonus3;
            int oldbonus4 = bonus4;
            //place an X here
            board[y][x]=1;
            //mark it as used in our bitmask as well
            boardbit^=(1<<(y*4+x));
            int newinarow = 0;
            //only need to bother checking if there is a bonus to be recieved
            if(bonus4>0||bonus3>0){
                newinarow=check(x,y);
            }
            int got3 = 0;
            int got4 = 0;
            if(newinarow>=3){
                got3=1;
            }
            if(newinarow>=4){
                got4=1;
            }

            //bonus for each _-in-a-row if we are the first to do so, and the value of the square
            int score = got3*bonus3+got4*bonus4+grid[y][x];

            //set bonus for future moves to zero if we have already recieved this bonus
            if(got3){
                bonus3=0;
            }
            if(got4){
                bonus4=0;
            }

            //move represents the opponents score - our score, so we subtract out the value of the move as well
            int move = canwin()-score;

            //minimize opp score - our score (in order to maximize our score)
            ans=min(ans,move);

            //reset values so that when we try the next square things are not broken
            bonus3=oldbonus3;
            bonus4=oldbonus4;
            board[y][x]=0;
            boardbit^=(1<<(y*4+x));
        }
    }
    if(tried==0){
        ans=0;
    }
    return dp[boardbit]=-ans;
}


int main() {
    int games;
    cin >> games;
    for(int game = 1; game<= games; game++){
        //read in the bonus scores
        cin >> bonus3;
        cin >> bonus4;

        //read in grid
        for(int y = 0; y < 4; y++){
            for(int x = 0; x < 4; x++){
                cin >> grid[y][x];
            }
        }

        //initialize our dynamic programming memoization table
        for(int i = 0; i< 1<<26; i++){
            dp[i]=1000000000;
        }

        //initialize the board
        for(int i = 0 ; i < 4; i++){
            for(int j = 0; j < 4; j++){
                board[i][j]=0;
            }
        }
        boardbit = 0;

        //canwin represents difference in score, so a higher number means alex will win
        int answer = canwin();
        cout<<"Game #"<<game<<": ";
        if(answer==0){
            cout<<"It's a draw.";
        }
        if(answer<0){
            cout<<"Barb wins.";
        }
        if(answer>0){
            cout<<"Alex wins.";
        }
        cout<<"\n";
    }
    return 0;
}
