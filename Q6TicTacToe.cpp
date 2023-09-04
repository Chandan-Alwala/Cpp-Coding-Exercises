#include <bits/stdc++.h>
using namespace std;

enum Pawn{white,black,empty};
struct position{  
    int x;
    int y;
    position(int a,int b){
        x = a;
        y = b;
    }
};

int evaluatePosition(Pawn (&inputGameState)[3][3]){
    //horizontal check
    for(int i = 0; i<3; i++){
        if(inputGameState[i][1] != empty && inputGameState[i][0] == inputGameState[i][1] && inputGameState[i][1] == inputGameState[i][2]){
            if(inputGameState[i][1] == white){return 1;}else{return -1;}
        }
    }
    // vertical check
    for(int i = 0; i<3; i++){
        if(inputGameState[1][i] != empty && inputGameState[0][i] == inputGameState[1][i] && inputGameState[1][i] == inputGameState[2][i]){
            if(inputGameState[1][i] == white){return 1;}else{return -1;}
        }
    }
    // diagonal check
    if(inputGameState[1][1] != empty  && inputGameState[0][0] == inputGameState[1][1] && inputGameState[1][1] == inputGameState[2][2]){
        if(inputGameState[1][1] == white){return 1;}else{return -1;}
    }
    if(inputGameState[1][1] != empty && inputGameState[2][0] == inputGameState[1][1] && inputGameState[1][1] == inputGameState[0][2]){
         if(inputGameState[1][1] == white){return 1;}else{return -1;}
    }
    return 0;
}
int getTotalMoves(Pawn (&inputGameState)[3][3]){
    int moves = 0;
    for(int i = 0; i<3; i++){
        for(int j = 0; j<3; j++){
            if(inputGameState[i][j] != empty){
                    moves++;
            }
        }
    }
    return moves;
}
// game completes when one of the player wins / or both run out of moves.
bool isGameOver(Pawn (&inputGameState)[3][3]){
    int score = evaluatePosition(inputGameState);
    if(score == 1 || score == -1){return true;}
    if(getTotalMoves(inputGameState) == 9){return true;}
    return false;
}

vector<position> getPossibleMoves(Pawn (&inputGameState)[3][3]){
    vector<position> rv{};
    if(isGameOver(inputGameState)){return rv;}
    else{
        for(int i = 0; i<3; i++){
            for(int j = 0; j<3; j++){
                if(inputGameState[i][j] == empty){
                    position p(i,j);
                    rv.push_back(p);
                }
            }
        }
    }
    return rv;
}

void playMove(Pawn (&inputGameState)[3][3],position valid_move,bool isWhiteMove){
    Pawn p = isWhiteMove? white:black;
    inputGameState[valid_move.x][valid_move.y] = p;
}
void unPlayMove(Pawn (&inputGameState)[3][3],position valid_move){
    inputGameState[valid_move.x][valid_move.y] = empty;
}

// returns best score attainable for a given position(positive for whites negative for black)
// takes evaluation function as a parameter too
int minMax(Pawn (&inputGameState)[3][3],int depth,int searhDepth,int (&evaluator)(Pawn (&inputGameState)[3][3])){
    if(searhDepth == depth){
        return 0;
    }
    int CurrentScore = evaluator(inputGameState);
    if(isGameOver(inputGameState)){return CurrentScore;}
    vector<position> possible_moves = getPossibleMoves(inputGameState);
    bool isWhiteMove = (depth%2 == 0);
    int initializedScore = isWhiteMove ? -1:1;
    int score = initializedScore;
    //Following for loop with recursive calls uses min-max tree based algo
    for(auto m:possible_moves){
        playMove(inputGameState,m,isWhiteMove);
        int expectedScore = minMax(inputGameState,depth+1,searhDepth,evaluator);
        //if white is playing maximize the score, else minimize the score
        if(isWhiteMove){
            score = expectedScore >= score? expectedScore:score; 
        }else{
            score = expectedScore <= score? expectedScore:score;
        }
        unPlayMove(inputGameState,m);
        if(initializedScore  == -score ){break;}
    }        
    return score;
}

vector<position> getBestMove(Pawn (&inputGameState)[3][3]){
    int searhDepth = 9;
    vector<position> rv{};
    if(isGameOver(inputGameState)){return rv;}
    vector<position> possible_moves = getPossibleMoves(inputGameState);
    if(possible_moves.size() == 0){return rv;}
    int moves = getTotalMoves(inputGameState);
    bool isWhiteMove = (moves%2 == 0);
    // find a move that maximizes the score if it is whites else find a move that minimizes the score.
    int initializedScore = isWhiteMove ? -1:1;
    int score = initializedScore;
    position bestMove = possible_moves[0];
    for(auto m:possible_moves){
        playMove(inputGameState,m,isWhiteMove);
        int expectedScore = minMax(inputGameState,moves+1,searhDepth,evaluatePosition);
        if(isWhiteMove){
            if(expectedScore >= score){
                score = expectedScore;
                bestMove = m;
            }  
        }else{
            if(expectedScore <= score){
                score = expectedScore;
                bestMove = m;
            }
        }
        unPlayMove(inputGameState,m);
        if(initializedScore  == -score ){break;}
    }
    rv.push_back(bestMove);
    return rv;
}





class TicTacToe {
    private:
    bool ComputerPlaysBlack = true;

    bool isValidInput(int x, int y){
        if(x>2 || y>2 || x<0 || y<0){
            return false;
        }
        if(this->state[x][y] != empty){
            printf("Position is already occupied!");
        return false;
        }
    return true;
    }
    public:
    void printTicTacToe(Pawn (&inputGameState)[3][3]){
    printf("  0 1 2 \n");
    for(int i = 0; i<3; i++){
        printf("%d|",i);
        for(int j = 0; j<3 ; j++){
            
            if(inputGameState[i][j] == white){
                printf("X|");
            }
            if(inputGameState[i][j] == black){
                printf("O|");
            }
            if(inputGameState[i][j] == empty){
                printf("_|");
            }
        }
        printf("\n");
    }
    }
    

    public:
    Pawn state[3][3];
    TicTacToe(bool ComputerPlaysBlack = true){
        this->ComputerPlaysBlack = ComputerPlaysBlack;
        this->resetGame();
    }
    bool computerPlaysBlack(){
        return this->ComputerPlaysBlack;
    }
    void resetGame(){
        for(int i = 0; i<3;i++){
            for(int j = 0; j<3; j++){
                this->state[i][j] = empty;
            }
        }
    }
    
    position readInputFromConsole(){
    int x = -1;
    int y = -1;
    bool validInput = false;
    while(!validInput){
        printf("\nInput Row:");
        scanf ("%d",&x);
        printf("\nInput Column:");
        scanf ("%d",&y);
        validInput = this->isValidInput(x,y);
        if(!validInput){printf("\nPlease provide valid input");}
    }
    return position(x,y);
    }
    public:
    void printBoard(){
        int cellWidth = 5;
        int H = cellWidth*3+2;
        char A[cellWidth*3+2][cellWidth*3+2];
        for(int i = 0; i<H;i++){
            for(int j = 0; j<H;j++){
                A[i][j] = ' ';
            }
        }
        for(int i = 0;i<3;i++){
            for(int j = 0; j<3 ; j++){
                char cellChar = ' ';
                if(this->state[i][j] == white){
                    cellChar = '#';
                }
                if(this->state[i][j] == black){
                   cellChar ='.';
                }
                for(int k = i*(cellWidth+1);(k <H) && (k<(i+1)*(cellWidth+1));k++){
                    for(int l = j*(cellWidth+1);(l <H) && (l<(j+1)*(cellWidth+1));l++){
                    A[k][l] = cellChar;
                    }
                }
            }
        }

        for(int i = cellWidth; i<H;i += (cellWidth+1)){
            for(int j = 0; j<H;j++){
                A[i][j] = '_';
            }
        }
        for(int j = cellWidth; j<H;j += (cellWidth+1)){
            for(int i = 0; i<H;i++){
                A[i][j] = '|';
            }
        }
        for(int i = 0; i<3;i++){
            for(int j = 0; j<cellWidth;j++){
                printf("  ");
            }
            printf("%d",i);
        }
        printf("\n");
        for(int i = 0; i<H;i++){
            if(i%(cellWidth+1)==0){
                printf("%d|",i/(cellWidth+1));
            }else{
                printf(" |");
            }
            for(int j = 0; j<H;j++){
                printf("%c ",A[i][j]);
            }
            printf("\n");
        }
    }

    void renderGame(){
    system("CLS");
    this->printBoard();
    if(isGameOver(this->state)){
        int currentScore = evaluatePosition(this->state);
        if(currentScore == 1){
            printf("White wins.\n");
        }
        if(currentScore == -1){
            printf("Black wins.\n");
        }
        if(currentScore == 0){
            printf("Draw! \n");
        }
    }
}
};

void play(){
    system("CLS");
    printf("press 1 to play as whites, 0 to play as black\n");
    int t;
    scanf("%d",&t);
    TicTacToe Game(t == 1);
    while(!isGameOver(Game.state)){
        if(Game.computerPlaysBlack()){
           Game.renderGame();
           //Take move from user input
           position input_position = Game.readInputFromConsole();
           playMove(Game.state,input_position,true);
           Game.renderGame();
           vector<position> best_moves = getBestMove(Game.state);
           if(best_moves.size() != 0){
              // computer plays as black.
              playMove(Game.state,best_moves[0],false);
            }
        }else{
            Game.renderGame();
            vector<position> best_moves = getBestMove(Game.state);
            if(best_moves.size() != 0){
              // computer plays as black.
              playMove(Game.state,best_moves[0],true);
            }
             Game.renderGame();
            //Take move from user input
            position input_position = Game.readInputFromConsole();
            playMove(Game.state,input_position,false);
        }
    }
    Game.renderGame();
}
int main(){
    play();
    return 0;
}