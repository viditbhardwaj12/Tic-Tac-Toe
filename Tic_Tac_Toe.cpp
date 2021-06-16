#include<bits/stdc++.h>
using namespace std;
#define int long
const long N=10;

// ok=0 means first player (X)
// ok=1 means second player (O)

int ok=0;
vector<char> grid(N);
char Human,Bot;

void initilize_board(){
    for(int i=1;i<N;i++){
        grid[i]=('0'+i);
    }
}

bool is_continue(){
    // check grid is full or not
    for(int i=1;i<N;i++){
        if(grid[i]!='X' and grid[i]!='O')return true;
    }
    return false;
}

void print_board(){
    cout<<endl;
    for(int i=1;i<N;i++){
        if( i!=1 and (i-1)%3==0){
            cout<<endl; 
            cout<<"---------";
            cout<<endl;
        }
        cout<<grid[i];
        if(i%3!=0) cout<<" | ";
    }cout<<endl;
}

bool is_valid_move(int response){
    if(response<N and response>0 and (grid[response]!='X' or grid[response]!='O')){
        return true;
    }
    return false;
}

int is_win(){

    for(int i=1;i<N;i+=3){
        if(grid[i]=='X' and grid[i+1]=='X' and grid[i+2]=='X') return -10;
        if(grid[i]=='O' and grid[i+1]=='O' and grid[i+2]=='O') return 10;
    }

    for(int i=1;i<=3;i++){
        if(grid[i]=='X' and grid[i+3]=='X' and grid[i+6]=='X') return -10;
        if(grid[i]=='O' and grid[i+3]=='O' and grid[i+6]=='O') return 10;
    }

    if(grid[1]=='X' and grid[5]=='X' and grid[9]=='X') return -10;
    if(grid[1]=='O' and grid[5]=='O' and grid[9]=='O') return 10;

    if(grid[3]=='X' and grid[5]=='X' and grid[7]=='X') return -10;
    if(grid[3]=='O' and grid[5]=='O' and grid[7]=='O') return 10;
    
    return 0;
}

int minimax_Algo(bool ismax){

    int score=is_win();
    if(score==10 or score==-10) return score;
    if(!is_continue()) return 0;

    if(ismax){
        // computer
        int best=-1e5;

        for(int i=1;i<N;i++){
            if(grid[i]!='X' and grid[i]!='O'){
                char initially=grid[i];

                grid[i]=Bot;
                best=max(best,minimax_Algo(!ismax));

                grid[i]=initially;

            }
        }
        return best;
    }
    else{
        // player
        int best=1e5;

        for(int i=1;i<N;i++){
            if(grid[i]!='X' and grid[i]!='O'){
                char initially=grid[i];

                grid[i]=Human;
                best=min(best,minimax_Algo(!ismax));

                grid[i]=initially;

            }
        }
        return best;
    }
}

int computer(){

    int best=-1e6;
    int index=-1;

    for(int i=1;i<N;i++){
        if(grid[i]!='X' and grid[i]!='O'){
            char initially=grid[i];

            grid[i]=Bot;
            int curr_move_score=minimax_Algo(false);

            // undo step
            grid[i]=initially;

            if(curr_move_score>best){
                best=curr_move_score;
                index=i;
            }
        }
    }

    return index;
}

void perform_move(){

    while(true){

        int take_response;

        if(!ok){
            cout<<"Your Turn: ";
            cin>>take_response;
        }
        else{
            cout<<"Computer Turn: ";
            take_response=computer();
            cout<<take_response;
        }

        if(!is_valid_move(take_response)){
            cout<<"Invalid Move, Enter again!!";cout<<endl;
        }
        else{
            grid[take_response]=(ok==0?Human:Bot);
            break;
        }
    }

    ok=1-ok;
}


void solve(){


    initilize_board();
    print_board();
    
    while(is_continue()){

        perform_move();
        print_board();

        if(is_win()==10){
            cout<<"COMPUTER WIN!!";cout<<endl; 
            print_board();return;
        }
        else if(is_win()==-10){
            cout<<"YOU WIN!!";cout<<endl;
            print_board(); return;
        }
        
    }

    cout<<"GAME DRAW!!"<<endl;

    print_board();
}

signed main(){

    cout<<"Which symbol (X or O, X goes first)? ";
    cin>>Human;

    ok=(Human=='X'?0:1);

    Bot=(Human=='X'?'O':'X');
    
    solve();
}
