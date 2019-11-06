#include "SixMensMorrisBoard.h" 	  			 	 
#include <cctype>
#include <iostream>
#include <sstream>

CSixMensMorrisBoard::CSixMensMorrisBoard(){         //Makes an empty Morris Board
    DTurn = SIX_MENS_MORRIS_PLAYER_R;
    for(int Index = 0; Index < SIX_MENS_MORRIS_PLAYERS/*2*/; Index++){
        DUnplacedPieces[Index] = SIX_MENS_MORRIS_PIECES/*6*/;
    }
    for(int Index = 0; Index < SIX_MENS_MORRIS_POSITIONS; Index++){
        DPositions[Index] = SIX_MENS_MORRIS_EMPTY;
        DPreviousPositions[Index] = SIX_MENS_MORRIS_EMPTY;
    }
}

//Makes a board with the peiece at each position, player turn, the number of unplaced pieces, and previous board 
CSixMensMorrisBoard::CSixMensMorrisBoard(char turn, const int unplaced[SIX_MENS_MORRIS_PLAYERS], const char positions[SIX_MENS_MORRIS_POSITIONS], const char previous[SIX_MENS_MORRIS_POSITIONS]){
    DTurn = turn;   //Player Turn
    for(int Index = 0; Index < SIX_MENS_MORRIS_PLAYERS; Index++){
        DUnplacedPieces[Index] = unplaced[Index];
    }
    for(int Index = 0; Index < SIX_MENS_MORRIS_POSITIONS; Index++){
        DPositions[Index] = positions[Index];
        DPreviousPositions[Index] = previous[Index];
    }
}

//checks if a mill is created
bool CSixMensMorrisBoard::MillCreated(char player){
    int PotentialMills[8][3] = {{0x0, 0x1, 0x2},
                                {0x3, 0x4, 0x5},
                                {0xA, 0xB, 0xC},
                                {0xD, 0xE, 0xF},
                                {0x0, 0x6, 0xD},
                                {0x3, 0x7, 0xA},
                                {0x5, 0x8, 0xC},
                                {0x2, 0x9, 0xF}};
    for(int Index = 0; Index < 8; Index++){
        bool CurrentMill = true;
        bool PastMill = true;
        char CurrentFirst = DPositions[PotentialMills[Index][0]];
        char PastFirst = DPreviousPositions[PotentialMills[Index][0]];
        if((CurrentFirst != PastFirst) or (CurrentFirst != player)){
            continue;
        }
        for(int Inner = 1; Inner < 3; Inner++){
            if(CurrentFirst != DPositions[PotentialMills[Index][Inner]]){
                CurrentMill = false;
                break;
            }
            if(PastFirst != DPreviousPositions[PotentialMills[Index][Inner]]){
                PastMill = false;
            }
        }
        if(CurrentMill and not PastMill){    
            return true;
        }
    }
    return false;
}

bool CSixMensMorrisBoard::AdjacentPositions(int from, int to){
    int Adjacents[SIX_MENS_MORRIS_POSITIONS] = {0x0042, 0x0015, 0x0202, 0x0090,             //
                                                0x002A, 0x0110, 0x2081, 0x0448,
                                                0x1220, 0x8104, 0x0880, 0x5400,
                                                0x0900, 0x4040, 0xA800, 0x4200};
    
    return Adjacents[from] & (1<<to);
}

// Rsets the board to initial state.
void CSixMensMorrisBoard::ResetBoard(){
    for(int Index = 0; Index < SIX_MENS_MORRIS_PLAYERS; Index++){
        DUnplacedPieces[Index] = SIX_MENS_MORRIS_PIECES;
    }
    for(int Index = 0; Index < SIX_MENS_MORRIS_POSITIONS; Index++){
        DPositions[Index] = SIX_MENS_MORRIS_EMPTY;
        DPreviousPositions[Index] = SIX_MENS_MORRIS_EMPTY;
    }
    DTurn = SIX_MENS_MORRIS_PLAYER_R;
}

//Return the Player Turn
char CSixMensMorrisBoard::PlayerTurn() const{  
    return toupper(DTurn);
}

//if valid, return the player at position. Else, return \0.
char CSixMensMorrisBoard::PlayerAtPosition(int position) const{
    if((0 <= position) and (position <= SIX_MENS_MORRIS_POSITIONS)){
        return DPositions[position];   
    }
    return '\0';
}

//if player is valid, returns the number of pieces left to place (6-pieces on board). Else -1. 
int CSixMensMorrisBoard::UnplacedPieces(char player) const{
    if(SIX_MENS_MORRIS_PLAYER_R == player){
        return DUnplacedPieces[0];
    }
    if(SIX_MENS_MORRIS_PLAYER_W == player){
        return DUnplacedPieces[1];
    }
    return -1;
}

//Checks if game is over
bool CSixMensMorrisBoard::GameOver() const{
    int RCount = 0, WCount = 0;
    for(int i = 0; i < SIX_MENS_MORRIS_POSITIONS; i++){
        if(PlayerAtPosition(i) == SIX_MENS_MORRIS_PLAYER_R){
            RCount++;
        } else if(PlayerAtPosition(i) == SIX_MENS_MORRIS_PLAYER_W){
            WCount++;
        }
    }
    if ((RCount == 2 and DUnplacedPieces[0] == 0) or (WCount == 2 and DUnplacedPieces[1] == 0)){
        return true;
    }
    return false;
}

//Returns the game as a string
std::string CSixMensMorrisBoard::ToString() const{
    std::stringstream OutStream;
    int CapturedR, CapturedW;
    
    CapturedR = SIX_MENS_MORRIS_PIECES - DUnplacedPieces[0];
    CapturedW = SIX_MENS_MORRIS_PIECES - DUnplacedPieces[1];
    for(int Index = 0; Index < SIX_MENS_MORRIS_POSITIONS; Index++){
        if(DPositions[Index] == SIX_MENS_MORRIS_PLAYER_R){
            CapturedR--;   
        }
        else if(DPositions[Index] == SIX_MENS_MORRIS_PLAYER_W){
            CapturedW--;   
        } 
    }
    OutStream<<(DTurn == SIX_MENS_MORRIS_PLAYER_R ? ">RU:" : " RU:")<<DUnplacedPieces[0]<<" RC:"<<CapturedW<<(DTurn == SIX_MENS_MORRIS_PLAYER_W ? " >WU:" : "  WU:")<<DUnplacedPieces[1]<<" WC:"<<CapturedR<<std::endl;
    OutStream<<DPositions[0x0]<<"---------"<<DPositions[0x1]<<"---------"<<DPositions[0x2]<<"      0---1---2"<<std::endl;
    OutStream<<"|         |         |      | 3-4-5 |"<<std::endl;
    OutStream<<"|         |         |      6-7   8-9"<<std::endl;
    OutStream<<"|    "<<DPositions[0x3]<<"----"<<DPositions[0x4]<<"----"<<DPositions[0x5]<<"    |      | A-B-C |"<<std::endl;
    OutStream<<"|    |         |    |      D---E---F"<<std::endl;
    OutStream<<"|    |         |    |        LEGEND"<<std::endl;
    OutStream<<DPositions[0x6]<<"----"<<DPositions[0x7]<<"         "<<DPositions[0x8]<<"----"<<DPositions[0x9]<<std::endl;
    OutStream<<"|    |         |    |"<<std::endl;
    OutStream<<"|    |         |    |"<<std::endl;
    OutStream<<"|    "<<DPositions[0xA]<<"----"<<DPositions[0xB]<<"----"<<DPositions[0xC]<<"    |"<<std::endl;
    OutStream<<"|         |         |"<<std::endl;
    OutStream<<"|         |         |"<<std::endl;
    OutStream<<DPositions[0xD]<<"---------"<<DPositions[0xE]<<"---------"<<DPositions[0xF]<<std::endl;
    
    return OutStream.str();
}

//return ToSring()
CSixMensMorrisBoard::operator std::string() const{
    std::stringstream OutStream;
    int CapturedR, CapturedW;
    
    CapturedR = SIX_MENS_MORRIS_PIECES - DUnplacedPieces[0];
    CapturedW = SIX_MENS_MORRIS_PIECES - DUnplacedPieces[1];
    for(int Index = 0; Index < SIX_MENS_MORRIS_POSITIONS; Index++){
        if(DPositions[Index] == SIX_MENS_MORRIS_PLAYER_R){
            CapturedR--;   
        }
        else if(DPositions[Index] == SIX_MENS_MORRIS_PLAYER_W){
            CapturedW--;   
        }
    }
    OutStream<<(DTurn == SIX_MENS_MORRIS_PLAYER_R ? ">RU:" : " RU:")<<DUnplacedPieces[0]<<" RC:"<<CapturedW<<(DTurn == SIX_MENS_MORRIS_PLAYER_W ? " >WU:" : "  WU:")<<DUnplacedPieces[1]<<" WC:"<<CapturedR<<std::endl;
    OutStream<<DPositions[0x0]<<"---------"<<DPositions[0x1]<<"---------"<<DPositions[0x2]<<"      0---1---2"<<std::endl;
    OutStream<<"|         |         |      | 3-4-5 |"<<std::endl;
    OutStream<<"|         |         |      6-7   8-9"<<std::endl;
    OutStream<<"|    "<<DPositions[0x3]<<"----"<<DPositions[0x4]<<"----"<<DPositions[0x5]<<"    |      | A-B-C |"<<std::endl;
    OutStream<<"|    |         |    |      D---E---F"<<std::endl;
    OutStream<<"|    |         |    |        LEGEND"<<std::endl;
    OutStream<<DPositions[0x6]<<"----"<<DPositions[0x7]<<"         "<<DPositions[0x8]<<"----"<<DPositions[0x9]<<std::endl;
    OutStream<<"|    |         |    |"<<std::endl;
    OutStream<<"|    |         |    |"<<std::endl;
    OutStream<<"|    "<<DPositions[0xA]<<"----"<<DPositions[0xB]<<"----"<<DPositions[0xC]<<"    |"<<std::endl;
    OutStream<<"|         |         |"<<std::endl;
    OutStream<<"|         |         |"<<std::endl;
    OutStream<<DPositions[0xD]<<"---------"<<DPositions[0xE]<<"---------"<<DPositions[0xF]<<std::endl;
    
    return OutStream.str();
}

//checks if a placement is correct. If incorrect or not players turn, return false
bool CSixMensMorrisBoard::Place(char player, int where){
    int UnplacedIndex = player == SIX_MENS_MORRIS_PLAYER_R ? 0 : 1;
    if((player == DTurn) and DUnplacedPieces[UnplacedIndex]){
        if((0 <= where) and (where < SIX_MENS_MORRIS_POSITIONS)){
            if(SIX_MENS_MORRIS_EMPTY == DPositions[where]){
                for(int Index = 0; Index < SIX_MENS_MORRIS_POSITIONS; Index++){
                    DPreviousPositions[Index] = DPositions[Index];       
                }
                DPositions[where] = player;
                if(MillCreated(player)){
                    DTurn = player;
                    DUnplacedPieces[UnplacedIndex]--;
                } else{
                DTurn = DTurn == SIX_MENS_MORRIS_PLAYER_R ? SIX_MENS_MORRIS_PLAYER_W : SIX_MENS_MORRIS_PLAYER_R;
                DUnplacedPieces[UnplacedIndex]--;
                }
                return true;
            }
        }
    }
    return false;
}

//checks if a player can remove a piece(mill formed and pice at position is oponent's peice)
// and not empty. Return false if invalid player or oponent's turn.
bool CSixMensMorrisBoard::CanRemove(char player){
    return ((DTurn == player) and MillCreated(DTurn));
}

//checks if player can move from 'from' to 'to'(false if player or opponent at 'to' or if to-from>1)
bool CSixMensMorrisBoard::CanMove(char player, int where){
    if((SIX_MENS_MORRIS_PLAYER_R == player) or (SIX_MENS_MORRIS_PLAYER_W == player)){
        if((0 <= where) and (where < SIX_MENS_MORRIS_POSITIONS)){
            if(player == DPositions[where]){
                for(int Index = 0; Index < SIX_MENS_MORRIS_POSITIONS; Index++){     
                    if(SIX_MENS_MORRIS_EMPTY == (DPositions[Index]) and AdjacentPositions(where,Index)){
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

//false by default.Returns true if move succeeds.
bool CSixMensMorrisBoard::Move(char player, int from, int to){
    int UnplacedIndex = player == SIX_MENS_MORRIS_PLAYER_R ? 0 : 1;
    if((player == DTurn) and (0 == DUnplacedPieces[UnplacedIndex])){
        if((0 <= from) and (from < SIX_MENS_MORRIS_POSITIONS)){
            if(player == DPositions[from]){
                if((0 <= to) and (to < SIX_MENS_MORRIS_POSITIONS) and (SIX_MENS_MORRIS_EMPTY ==  DPositions[to]) and AdjacentPositions(from, to)){
                    DPositions[to] = player;
                    DPositions[from] = SIX_MENS_MORRIS_EMPTY;
                    DPreviousPositions[to] = DPositions[from];
                    DPreviousPositions[from] = SIX_MENS_MORRIS_EMPTY;
                    std::cout<<"Mill about to be created"<<std::endl;
                    if(MillCreated(player)){
                        std::cout<<"mill created for player "<<player<<std::endl;
                        DTurn = player;
                    } else{
                    DTurn = DTurn == SIX_MENS_MORRIS_PLAYER_W ? SIX_MENS_MORRIS_PLAYER_R: SIX_MENS_MORRIS_PLAYER_W;
                    }

                    return true;
                }
                else{
                    GameOver();
                    DTurn = DTurn == SIX_MENS_MORRIS_PLAYER_R ? SIX_MENS_MORRIS_PLAYER_R : SIX_MENS_MORRIS_PLAYER_W;
                    return true;
                }
            }
        }
    }
    return false;
}

//Removes opponent from 'from.' returns false if 'from' is empty or if from contains player's piece
// or if from is invalid
bool CSixMensMorrisBoard::Remove(char player, int from){
    if(CanRemove(player)and (0 <= from) and (from < SIX_MENS_MORRIS_POSITIONS)){
        char OtherPlayer = DTurn == SIX_MENS_MORRIS_PLAYER_R ? SIX_MENS_MORRIS_PLAYER_W : SIX_MENS_MORRIS_PLAYER_R;
        if(DPositions[from] == OtherPlayer){
            DPositions[from] = SIX_MENS_MORRIS_EMPTY;// removes the player from position 'from'
            int UnplacedIndex = OtherPlayer == SIX_MENS_MORRIS_PLAYER_R ? 0 : 1;
            int PlayerCount = DUnplacedPieces[UnplacedIndex];

            for(int Index = 0; Index < SIX_MENS_MORRIS_POSITIONS; Index++){
                if(DPositions[Index] == OtherPlayer){
                    PlayerCount++;
                }
            }
            if(PlayerCount <= 2){
                GameOver();
                return true;// game could be over
            }
            bool HasMove = false;
            for(int From = 0; From < SIX_MENS_MORRIS_POSITIONS; From++){
                if(DPositions[From] == OtherPlayer){
                    for(int To = 0; To < SIX_MENS_MORRIS_POSITIONS; To++){
                        if(From == To){
                            continue;    
                        }
                        if((SIX_MENS_MORRIS_EMPTY == DPositions[To]) and AdjacentPositions(From,To)){
                            HasMove = true;
                            break;
                        }
                    }
                    if(HasMove){
                        break;   
                    }
                }       
            }
            if(HasMove){
                DTurn = OtherPlayer;
            }
            else{
                DTurn = tolower(DTurn);   
            }
                return true;
        }
    }
    return false;
}
