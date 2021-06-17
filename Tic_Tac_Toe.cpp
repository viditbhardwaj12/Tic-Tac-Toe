#include<bits/stdc++.h>
using namespace std;

#define endl    "\n"
const int N=10;
int ok=0;

char Human,Bot;
vector<char> grid(N);

void initilize_grid(){
    for(int i=1;i<N;i++){
        grid[i]=(char(i+'0'));
    }
}

void print_grid(){
    cout<<endl;
    cout<<grid[1]<<" | "<<grid[2]<<" | "<<grid[3]<<endl;
    cout<<"---------"<<endl;

    cout<<grid[4]<<" | "<<grid[5]<<" | "<<grid[6]<<endl;
    cout<<"---------"<<endl;

    cout<<grid[7]<<" | "<<grid[8]<<" | "<<grid[9]<<endl;
    cout<<endl;
}

bool is_Continue(){
    for(int i=1;i<N;i++){
        if(grid[i]!='X' && grid[i]!='O') return true;
    }

    return false;
}

int is_win(){
    for(int i=1;i<N;i+=3){
        if(grid[i]==Human && grid[i+1]==Human && grid[i+2]==Human) return (-10);
        if(grid[i]==Bot && grid[i+1]==Bot && grid[i+2]==Bot) return (10);
    }

    for(int i=1;i<=3;i++){
        if(grid[i]==Human && grid[i+3]==Human && grid[i+6]==Human) return (-10);
        if(grid[i]==Bot && grid[i+3]==Bot && grid[i+6]==Bot) return (10);
    }

    if(grid[1]==Human && grid[5]==Human && grid[9]==Human) return (-10);
    if(grid[1]==Bot && grid[5]==Bot && grid[9]==Bot) return (10);

    if(grid[3]==Human && grid[5]==Human && grid[7]==Human) return (-10);
    if(grid[3]==Bot && grid[5]==Bot && grid[7]==Bot) return (10);

    return 0;
}

int Minimax_Algo(bool Is_Max){

    int score=is_win();
    if(score==(10) || score==(-10)) return score;
    if(!is_Continue()) return 0;

    if(Is_Max){
        int best_score=INT_MIN;

        for(int i=1;i<N;i++){
            if(grid[i]!='X' && grid[i]!='O'){

                char store=grid[i];

                grid[i]=Bot;
                best_score=max(best_score,Minimax_Algo(!Is_Max));

                grid[i]=store;
            }
        }

        return best_score;

    }else{
        int best_score=INT_MAX;

        for(int i=1;i<N;i++){
            if(grid[i]!='X' && grid[i]!='O'){

                char store=grid[i];

                grid[i]=Human;
                best_score=min(best_score,Minimax_Algo(!Is_Max));

                grid[i]=store;
            }
        }

        return best_score;
    }
}

int Computer_turn(){

    int best_score=INT_MIN,position=-1;

    for(int i=1;i<N;i++){
        if(grid[i]!='X' && grid[i]!='O'){

            char store=grid[i];

            grid[i]=Bot;
            int curr_score=Minimax_Algo(false);

            grid[i]=store;

            if(curr_score>best_score){
                best_score=curr_score;
                position=(i);
            }
        }
    }

    return position;
}

bool valid_move(int position){
    return (position<N && position>0 && grid[position]!='X' && grid[position]!='O');
}

void Perform_move(){
    while(true){

        int take_response;

        if(!ok){
            cout<<"YOUR TURN: ";
            cin>>take_response;
        }else{
            cout<<"COMPUTER TURN: ";
            take_response=Computer_turn();
            cout<<take_response;
        }

        if(!valid_move(take_response)){
            cout<<"INVALID MOVE, ENTER AGAIN!!"<<endl;
        }else{
            if(ok) grid[take_response]=Bot;
            else grid[take_response]=Human;
            break;
        }
    }

    ok=1-ok;
}

void Tic_Tac_Toe(){

    initilize_grid();
    print_grid();

    while(is_Continue()){

        Perform_move();
        print_grid();

        if(is_win()==(10)){
            cout<<"COMPUTER WINS!"<<endl;
            print_grid();
            return;
        }

        if(is_win()==(-10)){
            cout<<"YOU WIN!"<<endl;
            print_grid();
            return;
        }
    }

    cout<<"GAME DRAW!"<<endl;

    print_grid();
    return;
}

int main(){

    cout<<"Which symbol (X or O, X goes first)? ";
    cin>>Human;

    if(Human=='O') ok=1,Bot='X';
    else Bot='O';

    Tic_Tac_Toe();

    return 0;
}
