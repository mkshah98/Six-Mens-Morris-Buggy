#include <gtest/gtest.h> 	  			 	 
#include "SixMensMorrisBoard.h"
#include <iostream>

TEST(SixMensMorrisBoardTest, DefaultBoardTest){
    CSixMensMorrisBoard EmptyBoard;
    EXPECT_EQ(EmptyBoard.PlayerTurn(),SIX_MENS_MORRIS_PLAYER_R);
    for (int i = 0; i < SIX_MENS_MORRIS_POSITIONS; i++)
    {
        EXPECT_EQ(EmptyBoard.PlayerAtPosition(i),SIX_MENS_MORRIS_EMPTY);
    }
    EXPECT_EQ(EmptyBoard.UnplacedPieces(EmptyBoard.PlayerTurn()),SIX_MENS_MORRIS_PIECES);
    EXPECT_EQ(EmptyBoard.UnplacedPieces(SIX_MENS_MORRIS_PLAYER_W), SIX_MENS_MORRIS_PIECES);
    EXPECT_FALSE(EmptyBoard.GameOver());
    EXPECT_EQ(EmptyBoard.ToString(),">RU:6 RC:0  WU:6 WC:0\n" 
                                    "o---------o---------o      0---1---2\n" 
                                    "|         |         |      | 3-4-5 |\n"
                                    "|         |         |      6-7   8-9\n"
                                    "|    o----o----o    |      | A-B-C |\n"
                                    "|    |         |    |      D---E---F\n"
                                    "|    |         |    |        LEGEND\n"
                                    "o----o         o----o\n"
                                    "|    |         |    |\n"
                                    "|    |         |    |\n"
                                    "|    o----o----o    |\n"
                                    "|         |         |\n"
                                    "|         |         |\n"
                                    "o---------o---------o\n");
}

TEST(SixMensMorrisBoardTest, SetBoardTest){
    char turn = SIX_MENS_MORRIS_PLAYER_W;
    const int unplaced[SIX_MENS_MORRIS_PLAYERS] = {3,4};
    const char positions[SIX_MENS_MORRIS_POSITIONS] = {SIX_MENS_MORRIS_PLAYER_R,SIX_MENS_MORRIS_PLAYER_W,SIX_MENS_MORRIS_PLAYER_R,
                                                        SIX_MENS_MORRIS_EMPTY,SIX_MENS_MORRIS_EMPTY,SIX_MENS_MORRIS_EMPTY,
                                                        SIX_MENS_MORRIS_EMPTY,SIX_MENS_MORRIS_EMPTY,SIX_MENS_MORRIS_EMPTY,SIX_MENS_MORRIS_PLAYER_W,
                                                        SIX_MENS_MORRIS_EMPTY,SIX_MENS_MORRIS_EMPTY,SIX_MENS_MORRIS_EMPTY,
                                                        SIX_MENS_MORRIS_EMPTY,SIX_MENS_MORRIS_EMPTY,SIX_MENS_MORRIS_PLAYER_R};

    const char previous[SIX_MENS_MORRIS_POSITIONS] = {SIX_MENS_MORRIS_PLAYER_R,SIX_MENS_MORRIS_PLAYER_W,SIX_MENS_MORRIS_PLAYER_R,
                                                        SIX_MENS_MORRIS_EMPTY,SIX_MENS_MORRIS_EMPTY,SIX_MENS_MORRIS_EMPTY,
                                                        SIX_MENS_MORRIS_EMPTY,SIX_MENS_MORRIS_EMPTY,SIX_MENS_MORRIS_EMPTY,SIX_MENS_MORRIS_PLAYER_W,
                                                        SIX_MENS_MORRIS_EMPTY,SIX_MENS_MORRIS_EMPTY,SIX_MENS_MORRIS_EMPTY,
                                                        SIX_MENS_MORRIS_EMPTY,SIX_MENS_MORRIS_EMPTY,SIX_MENS_MORRIS_EMPTY};
    CSixMensMorrisBoard board(turn, unplaced,positions, previous);
    EXPECT_EQ(board.PlayerTurn(), SIX_MENS_MORRIS_PLAYER_W);
    for (size_t i = 0; i < SIX_MENS_MORRIS_POSITIONS; i++)
    {
        EXPECT_EQ(board.PlayerAtPosition(i), positions[i]);
    }
    EXPECT_EQ(board.UnplacedPieces(SIX_MENS_MORRIS_PLAYER_R),unplaced[0]);
    EXPECT_EQ(board.UnplacedPieces(SIX_MENS_MORRIS_PLAYER_W), unplaced[1]);
    EXPECT_FALSE(board.GameOver());
    EXPECT_EQ(board.ToString(),
		    		                " RU:3 RC:0 >WU:4 WC:0\n" 
                                    "R---------W---------R      0---1---2\n" 
                                    "|         |         |      | 3-4-5 |\n"
                                    "|         |         |      6-7   8-9\n"
                                    "|    o----o----o    |      | A-B-C |\n"
                                    "|    |         |    |      D---E---F\n"
                                    "|    |         |    |        LEGEND\n"
                                    "o----o         o----W\n"
                                    "|    |         |    |\n"
                                    "|    |         |    |\n"
                                    "|    o----o----o    |\n"
                                    "|         |         |\n"
                                    "|         |         |\n"
                                    "o---------o---------R\n");
    EXPECT_EQ(board.operator std::string(),board.ToString());
}

TEST(SixMensMorrisBoardTest, ResetBoardTest){
	char turn = SIX_MENS_MORRIS_PLAYER_W;
    int unplaced[SIX_MENS_MORRIS_PLAYERS] = {3,4};
    const char positions[SIX_MENS_MORRIS_POSITIONS] = {SIX_MENS_MORRIS_PLAYER_R,SIX_MENS_MORRIS_PLAYER_W,SIX_MENS_MORRIS_PLAYER_R,
                                                        SIX_MENS_MORRIS_EMPTY,SIX_MENS_MORRIS_EMPTY,SIX_MENS_MORRIS_EMPTY,
                                                        SIX_MENS_MORRIS_EMPTY,SIX_MENS_MORRIS_EMPTY,SIX_MENS_MORRIS_EMPTY,SIX_MENS_MORRIS_PLAYER_W,
                                                        SIX_MENS_MORRIS_EMPTY,SIX_MENS_MORRIS_EMPTY,SIX_MENS_MORRIS_EMPTY,
                                                        SIX_MENS_MORRIS_EMPTY,SIX_MENS_MORRIS_EMPTY,SIX_MENS_MORRIS_PLAYER_R};

    const char previous[SIX_MENS_MORRIS_POSITIONS] = {SIX_MENS_MORRIS_PLAYER_R,SIX_MENS_MORRIS_PLAYER_W,SIX_MENS_MORRIS_PLAYER_R,
                                                        SIX_MENS_MORRIS_EMPTY,SIX_MENS_MORRIS_EMPTY,SIX_MENS_MORRIS_EMPTY,
                                                        SIX_MENS_MORRIS_EMPTY,SIX_MENS_MORRIS_EMPTY,SIX_MENS_MORRIS_EMPTY,SIX_MENS_MORRIS_PLAYER_W,
                                                        SIX_MENS_MORRIS_EMPTY,SIX_MENS_MORRIS_EMPTY,SIX_MENS_MORRIS_EMPTY,
                                                        SIX_MENS_MORRIS_EMPTY,SIX_MENS_MORRIS_EMPTY,SIX_MENS_MORRIS_EMPTY};
    CSixMensMorrisBoard board(turn, unplaced,positions, previous);
    board.ResetBoard();
    EXPECT_EQ(board.PlayerTurn(),SIX_MENS_MORRIS_PLAYER_R);
    for (int i = 0; i < SIX_MENS_MORRIS_POSITIONS; i++)
    {
        EXPECT_EQ(board.PlayerAtPosition(i),SIX_MENS_MORRIS_EMPTY);
    }
    EXPECT_EQ(board.UnplacedPieces(board.PlayerTurn()),SIX_MENS_MORRIS_PIECES);
    EXPECT_EQ(board.UnplacedPieces(SIX_MENS_MORRIS_PLAYER_W), SIX_MENS_MORRIS_PIECES);
    EXPECT_FALSE(board.GameOver());
    EXPECT_EQ(board.ToString(),     
                                ">RU:6 RC:0  WU:6 WC:0\n" 
                                "o---------o---------o      0---1---2\n" 
                                "|         |         |      | 3-4-5 |\n"
                                "|         |         |      6-7   8-9\n"
                                "|    o----o----o    |      | A-B-C |\n"
                                "|    |         |    |      D---E---F\n"
                                "|    |         |    |        LEGEND\n"
                                "o----o         o----o\n"
                                "|    |         |    |\n"
                                "|    |         |    |\n"
                                "|    o----o----o    |\n"
                                "|         |         |\n"
                                "|         |         |\n"
                                "o---------o---------o\n");
}

TEST(SixMensMorrisBoardTest, PlacementTest){
    char turn = SIX_MENS_MORRIS_PLAYER_R;
    int unplaced[SIX_MENS_MORRIS_PLAYERS] = {3,3};
    const char positions[SIX_MENS_MORRIS_POSITIONS] = {SIX_MENS_MORRIS_PLAYER_R,SIX_MENS_MORRIS_PLAYER_W,SIX_MENS_MORRIS_EMPTY,
                                                        SIX_MENS_MORRIS_EMPTY,SIX_MENS_MORRIS_EMPTY,SIX_MENS_MORRIS_PLAYER_R,
                                                        SIX_MENS_MORRIS_EMPTY,SIX_MENS_MORRIS_EMPTY,SIX_MENS_MORRIS_EMPTY,SIX_MENS_MORRIS_PLAYER_W,
                                                        SIX_MENS_MORRIS_EMPTY,SIX_MENS_MORRIS_PLAYER_W,SIX_MENS_MORRIS_EMPTY,
                                                        SIX_MENS_MORRIS_EMPTY,SIX_MENS_MORRIS_EMPTY,SIX_MENS_MORRIS_PLAYER_R};
    
    const char previous[SIX_MENS_MORRIS_POSITIONS] = {SIX_MENS_MORRIS_PLAYER_R,SIX_MENS_MORRIS_EMPTY,SIX_MENS_MORRIS_EMPTY,
                                                        SIX_MENS_MORRIS_EMPTY,SIX_MENS_MORRIS_EMPTY,SIX_MENS_MORRIS_PLAYER_R,
                                                        SIX_MENS_MORRIS_EMPTY,SIX_MENS_MORRIS_EMPTY,SIX_MENS_MORRIS_EMPTY,SIX_MENS_MORRIS_PLAYER_W,
                                                        SIX_MENS_MORRIS_EMPTY,SIX_MENS_MORRIS_PLAYER_W,SIX_MENS_MORRIS_EMPTY,
                                                        SIX_MENS_MORRIS_EMPTY,SIX_MENS_MORRIS_EMPTY,SIX_MENS_MORRIS_PLAYER_R};
    CSixMensMorrisBoard board(turn, unplaced,positions, previous);
    EXPECT_EQ(board.PlayerTurn(), SIX_MENS_MORRIS_PLAYER_R);
    EXPECT_TRUE(board.Place(SIX_MENS_MORRIS_PLAYER_R, 2));
    EXPECT_EQ(board.UnplacedPieces(SIX_MENS_MORRIS_PLAYER_R),2);
    EXPECT_EQ(board.PlayerTurn(), SIX_MENS_MORRIS_PLAYER_W);
    EXPECT_FALSE(board.Place(SIX_MENS_MORRIS_PLAYER_W, 5));
    EXPECT_EQ(board.UnplacedPieces(SIX_MENS_MORRIS_PLAYER_W), 3);
    EXPECT_EQ(board.PlayerTurn(), SIX_MENS_MORRIS_PLAYER_W);
    EXPECT_TRUE(board.Place(SIX_MENS_MORRIS_PLAYER_W, 3));
    EXPECT_EQ(board.UnplacedPieces(SIX_MENS_MORRIS_PLAYER_W),2);
    EXPECT_EQ(board.PlayerTurn(), SIX_MENS_MORRIS_PLAYER_R);
    EXPECT_EQ(board.ToString(),
                                    ">RU:2 RC:0  WU:2 WC:0\n" 
                                    "R---------W---------R      0---1---2\n" 
                                    "|         |         |      | 3-4-5 |\n"
                                    "|         |         |      6-7   8-9\n"
                                    "|    W----o----R    |      | A-B-C |\n"
                                    "|    |         |    |      D---E---F\n"
                                    "|    |         |    |        LEGEND\n"
                                    "o----o         o----W\n"
                                    "|    |         |    |\n"
                                    "|    |         |    |\n"
                                    "|    o----W----o    |\n"
                                    "|         |         |\n"
                                    "|         |         |\n"
                                    "o---------o---------R\n");
}

TEST(SixMensMorrisBoardTest, PlacementMillTest){
    char turn = SIX_MENS_MORRIS_PLAYER_R;
    int unplaced[SIX_MENS_MORRIS_PLAYERS] = {3,3};
    const char positions[SIX_MENS_MORRIS_POSITIONS] = {SIX_MENS_MORRIS_PLAYER_R,SIX_MENS_MORRIS_EMPTY,SIX_MENS_MORRIS_PLAYER_R,
                                                        SIX_MENS_MORRIS_PLAYER_W,SIX_MENS_MORRIS_EMPTY,SIX_MENS_MORRIS_PLAYER_R,
                                                        SIX_MENS_MORRIS_EMPTY,SIX_MENS_MORRIS_EMPTY,SIX_MENS_MORRIS_EMPTY,SIX_MENS_MORRIS_PLAYER_W,
                                                        SIX_MENS_MORRIS_EMPTY,SIX_MENS_MORRIS_PLAYER_W,SIX_MENS_MORRIS_EMPTY,
                                                        SIX_MENS_MORRIS_EMPTY,SIX_MENS_MORRIS_EMPTY,SIX_MENS_MORRIS_EMPTY};
    
    const char previous[SIX_MENS_MORRIS_POSITIONS] = {SIX_MENS_MORRIS_PLAYER_R,SIX_MENS_MORRIS_EMPTY,SIX_MENS_MORRIS_PLAYER_R,
                                                        SIX_MENS_MORRIS_EMPTY,SIX_MENS_MORRIS_EMPTY,SIX_MENS_MORRIS_PLAYER_R,
                                                        SIX_MENS_MORRIS_EMPTY,SIX_MENS_MORRIS_EMPTY,SIX_MENS_MORRIS_EMPTY,SIX_MENS_MORRIS_PLAYER_W,
                                                        SIX_MENS_MORRIS_EMPTY,SIX_MENS_MORRIS_PLAYER_W,SIX_MENS_MORRIS_EMPTY,
                                                        SIX_MENS_MORRIS_EMPTY,SIX_MENS_MORRIS_EMPTY,SIX_MENS_MORRIS_EMPTY};
    CSixMensMorrisBoard board(turn, unplaced,positions, previous);
    board.Place(turn, 1);
    EXPECT_EQ(board.UnplacedPieces(turn), 2);
    EXPECT_TRUE(board.CanRemove(turn));
    EXPECT_FALSE(board.CanRemove(SIX_MENS_MORRIS_PLAYER_W));
    EXPECT_FALSE(board.Remove(turn, 15));
    EXPECT_FALSE(board.Remove(turn, 14));
    EXPECT_FALSE(board.Remove(turn, 5));
    EXPECT_TRUE(board.Remove(turn, 9));
    EXPECT_EQ(board.PlayerAtPosition(9),SIX_MENS_MORRIS_EMPTY);
    EXPECT_EQ(board.PlayerTurn(), SIX_MENS_MORRIS_PLAYER_W);
    EXPECT_EQ(board.ToString(),
                                    " RU:2 RC:1 >WU:3 WC:0\n" 
                                    "R---------R---------R      0---1---2\n" 
                                    "|         |         |      | 3-4-5 |\n"
                                    "|         |         |      6-7   8-9\n"
                                    "|    W----o----R    |      | A-B-C |\n"
                                    "|    |         |    |      D---E---F\n"
                                    "|    |         |    |        LEGEND\n"
                                    "o----o         o----o\n"
                                    "|    |         |    |\n"
                                    "|    |         |    |\n"
                                    "|    o----W----o    |\n"
                                    "|         |         |\n"
                                    "|         |         |\n"
                                    "o---------o---------o\n");
}

TEST(SixMensMorrisBoardTest, MoveTest){
    char turn = SIX_MENS_MORRIS_PLAYER_R;
    int unplaced[SIX_MENS_MORRIS_PLAYERS] = {0,0}; //all pieces on the board
    const char positions[SIX_MENS_MORRIS_POSITIONS] = {SIX_MENS_MORRIS_PLAYER_R,SIX_MENS_MORRIS_PLAYER_W,SIX_MENS_MORRIS_EMPTY,
                                                        SIX_MENS_MORRIS_EMPTY,SIX_MENS_MORRIS_EMPTY,SIX_MENS_MORRIS_PLAYER_R,
                                                        SIX_MENS_MORRIS_EMPTY,SIX_MENS_MORRIS_EMPTY,SIX_MENS_MORRIS_EMPTY,SIX_MENS_MORRIS_PLAYER_W,
                                                        SIX_MENS_MORRIS_EMPTY,SIX_MENS_MORRIS_PLAYER_W,SIX_MENS_MORRIS_EMPTY,
                                                        SIX_MENS_MORRIS_EMPTY,SIX_MENS_MORRIS_EMPTY,SIX_MENS_MORRIS_PLAYER_R};
    
    const char previous[SIX_MENS_MORRIS_POSITIONS] = {SIX_MENS_MORRIS_PLAYER_R,SIX_MENS_MORRIS_PLAYER_W,SIX_MENS_MORRIS_PLAYER_W,
                                                        SIX_MENS_MORRIS_EMPTY,SIX_MENS_MORRIS_EMPTY,SIX_MENS_MORRIS_PLAYER_R,
                                                        SIX_MENS_MORRIS_EMPTY,SIX_MENS_MORRIS_EMPTY,SIX_MENS_MORRIS_EMPTY,SIX_MENS_MORRIS_EMPTY,
                                                        SIX_MENS_MORRIS_EMPTY,SIX_MENS_MORRIS_PLAYER_W,SIX_MENS_MORRIS_EMPTY,
                                                        SIX_MENS_MORRIS_EMPTY,SIX_MENS_MORRIS_EMPTY,SIX_MENS_MORRIS_PLAYER_R};

    CSixMensMorrisBoard board(turn, unplaced, positions, previous);
    EXPECT_EQ(board.PlayerAtPosition(0), SIX_MENS_MORRIS_PLAYER_R);
    EXPECT_TRUE(board.CanMove(SIX_MENS_MORRIS_PLAYER_R,0)); 
    EXPECT_TRUE(board.Move(SIX_MENS_MORRIS_PLAYER_R,0,6)); 
    
    //Switch players after a successful move
    EXPECT_EQ(board.PlayerTurn(), SIX_MENS_MORRIS_PLAYER_W);

    //checking if you can move a white piece
    EXPECT_TRUE(board.CanMove(SIX_MENS_MORRIS_PLAYER_W,1));
    EXPECT_TRUE(board.Move(SIX_MENS_MORRIS_PLAYER_W,1,0)); 
    EXPECT_EQ(board.PlayerAtPosition(0), SIX_MENS_MORRIS_PLAYER_W);
    
    EXPECT_TRUE(board.CanMove(SIX_MENS_MORRIS_PLAYER_R,15)); 
    EXPECT_TRUE(board.Move(SIX_MENS_MORRIS_PLAYER_R, 15, 14));
    EXPECT_FALSE(board.Move(SIX_MENS_MORRIS_PLAYER_R,14,15)); // Cannot move since not R's turn 

    //Trying to move from an empty place, and flying pieces
    EXPECT_FALSE(board.CanMove(SIX_MENS_MORRIS_PLAYER_W,8));
    EXPECT_TRUE(board.CanMove(SIX_MENS_MORRIS_PLAYER_W, 9));
    EXPECT_FALSE(board.Move(SIX_MENS_MORRIS_PLAYER_R, 9,10)); //Cannot fly from 8 to 10 and not R's turn
    EXPECT_FALSE(board.Move(SIX_MENS_MORRIS_PLAYER_W, 9,12));
    EXPECT_EQ(board.ToString(),
                                    " RU:0 RC:3 >WU:0 WC:3\n" 
                                    "W---------o---------o      0---1---2\n" 
                                    "|         |         |      | 3-4-5 |\n"
                                    "|         |         |      6-7   8-9\n"
                                    "|    o----o----R    |      | A-B-C |\n"
                                    "|    |         |    |      D---E---F\n"
                                    "|    |         |    |        LEGEND\n"
                                    "R----o         o----W\n"
                                    "|    |         |    |\n"
                                    "|    |         |    |\n"
                                    "|    o----W----o    |\n"
                                    "|         |         |\n"
                                    "|         |         |\n"
                                    "o---------R---------o\n");
}

TEST(SixMensMorrisBoardTest, MoveMillTest){
    char player = SIX_MENS_MORRIS_PLAYER_R;
    const int unplaced[SIX_MENS_MORRIS_PLAYERS] = {0,0};
    const char positions[SIX_MENS_MORRIS_POSITIONS] = {SIX_MENS_MORRIS_EMPTY,SIX_MENS_MORRIS_PLAYER_R,SIX_MENS_MORRIS_PLAYER_R,
                                                        SIX_MENS_MORRIS_EMPTY,SIX_MENS_MORRIS_PLAYER_W,SIX_MENS_MORRIS_PLAYER_R,
                                                        SIX_MENS_MORRIS_PLAYER_R,SIX_MENS_MORRIS_PLAYER_W,SIX_MENS_MORRIS_EMPTY,SIX_MENS_MORRIS_EMPTY,
                                                        SIX_MENS_MORRIS_EMPTY,SIX_MENS_MORRIS_PLAYER_W,SIX_MENS_MORRIS_PLAYER_W,
                                                        SIX_MENS_MORRIS_EMPTY,SIX_MENS_MORRIS_EMPTY,SIX_MENS_MORRIS_PLAYER_W};

    const char previous[SIX_MENS_MORRIS_POSITIONS] = {SIX_MENS_MORRIS_EMPTY,SIX_MENS_MORRIS_PLAYER_R,SIX_MENS_MORRIS_PLAYER_R,
                                                        SIX_MENS_MORRIS_EMPTY,SIX_MENS_MORRIS_PLAYER_W,SIX_MENS_MORRIS_PLAYER_R,
                                                        SIX_MENS_MORRIS_PLAYER_R,SIX_MENS_MORRIS_EMPTY,SIX_MENS_MORRIS_PLAYER_W,SIX_MENS_MORRIS_EMPTY,
                                                        SIX_MENS_MORRIS_EMPTY,SIX_MENS_MORRIS_PLAYER_W,SIX_MENS_MORRIS_PLAYER_W,
                                                        SIX_MENS_MORRIS_EMPTY,SIX_MENS_MORRIS_EMPTY,SIX_MENS_MORRIS_PLAYER_W};
    CSixMensMorrisBoard board(player, unplaced, positions, previous);
    EXPECT_TRUE(board.CanMove(player, 6));
    EXPECT_TRUE(board.Move(player, 6, 0));
    EXPECT_TRUE(board.CanRemove(player));
    EXPECT_TRUE(board.Remove(SIX_MENS_MORRIS_PLAYER_R, 15));
    EXPECT_EQ(board.ToString(),     " RU:0 RC:2 >WU:0 WC:2\n" 
                                    "R---------R---------R      0---1---2\n" 
                                    "|         |         |      | 3-4-5 |\n"
                                    "|         |         |      6-7   8-9\n"
                                    "|    o----W----R    |      | A-B-C |\n"
                                    "|    |         |    |      D---E---F\n"
                                    "|    |         |    |        LEGEND\n"
                                    "o----W         o----o\n"
                                    "|    |         |    |\n"
                                    "|    |         |    |\n"
                                    "|    o----W----W    |\n"
                                    "|         |         |\n"
                                    "|         |         |\n"
                                    "o---------o---------o\n");
}
                                       
TEST(SixMensMorrisBoardTest, TwoPieceGameOverTest){
    char player = SIX_MENS_MORRIS_PLAYER_W;
    const int unplaced[SIX_MENS_MORRIS_PLAYERS] = {0,0};
    const char positions[SIX_MENS_MORRIS_POSITIONS] = {SIX_MENS_MORRIS_PLAYER_R,SIX_MENS_MORRIS_EMPTY,SIX_MENS_MORRIS_PLAYER_R,
                                                        SIX_MENS_MORRIS_PLAYER_W,SIX_MENS_MORRIS_EMPTY,SIX_MENS_MORRIS_EMPTY,
                                                        SIX_MENS_MORRIS_EMPTY,SIX_MENS_MORRIS_PLAYER_W,SIX_MENS_MORRIS_EMPTY,SIX_MENS_MORRIS_EMPTY,
                                                        SIX_MENS_MORRIS_EMPTY,SIX_MENS_MORRIS_PLAYER_W,SIX_MENS_MORRIS_EMPTY,
                                                        SIX_MENS_MORRIS_EMPTY,SIX_MENS_MORRIS_EMPTY,SIX_MENS_MORRIS_PLAYER_R};

    const char previous[SIX_MENS_MORRIS_POSITIONS] = {SIX_MENS_MORRIS_PLAYER_R,SIX_MENS_MORRIS_EMPTY,SIX_MENS_MORRIS_EMPTY,
                                                        SIX_MENS_MORRIS_PLAYER_W,SIX_MENS_MORRIS_EMPTY,SIX_MENS_MORRIS_EMPTY,
                                                        SIX_MENS_MORRIS_EMPTY,SIX_MENS_MORRIS_PLAYER_W,SIX_MENS_MORRIS_EMPTY,SIX_MENS_MORRIS_PLAYER_R,
                                                        SIX_MENS_MORRIS_EMPTY,SIX_MENS_MORRIS_PLAYER_W,SIX_MENS_MORRIS_EMPTY,
                                                        SIX_MENS_MORRIS_EMPTY,SIX_MENS_MORRIS_EMPTY,SIX_MENS_MORRIS_PLAYER_R};
    CSixMensMorrisBoard board(player, unplaced, positions, previous);
    EXPECT_TRUE(board.CanMove(SIX_MENS_MORRIS_PLAYER_W, 11));
    EXPECT_TRUE(board.Move(SIX_MENS_MORRIS_PLAYER_W,11,10));
    EXPECT_TRUE(board.CanRemove(SIX_MENS_MORRIS_PLAYER_W));
    EXPECT_TRUE(board.Remove(SIX_MENS_MORRIS_PLAYER_W,15));
    EXPECT_TRUE(board.GameOver());
}

TEST(SixMensMorrisBoardTest, NoMoveGameOverTest){
    const int unplaced[SIX_MENS_MORRIS_PLAYERS] = {0,0};
    char turn = SIX_MENS_MORRIS_PLAYER_W;
    const char positions[SIX_MENS_MORRIS_POSITIONS] = {SIX_MENS_MORRIS_PLAYER_W,SIX_MENS_MORRIS_PLAYER_R,SIX_MENS_MORRIS_PLAYER_R,
                                                        SIX_MENS_MORRIS_EMPTY,SIX_MENS_MORRIS_PLAYER_W,SIX_MENS_MORRIS_EMPTY,
                                                        SIX_MENS_MORRIS_EMPTY,SIX_MENS_MORRIS_EMPTY,SIX_MENS_MORRIS_PLAYER_W,SIX_MENS_MORRIS_PLAYER_R,
                                                        SIX_MENS_MORRIS_EMPTY,SIX_MENS_MORRIS_EMPTY,SIX_MENS_MORRIS_EMPTY,
                                                        SIX_MENS_MORRIS_EMPTY,SIX_MENS_MORRIS_PLAYER_W,SIX_MENS_MORRIS_EMPTY};
    const char previous[SIX_MENS_MORRIS_POSITIONS] = {SIX_MENS_MORRIS_PLAYER_W,SIX_MENS_MORRIS_PLAYER_R,SIX_MENS_MORRIS_PLAYER_R,
                                                        SIX_MENS_MORRIS_EMPTY,SIX_MENS_MORRIS_PLAYER_W,SIX_MENS_MORRIS_EMPTY,
                                                        SIX_MENS_MORRIS_EMPTY,SIX_MENS_MORRIS_EMPTY,SIX_MENS_MORRIS_PLAYER_W,SIX_MENS_MORRIS_EMPTY,
                                                        SIX_MENS_MORRIS_EMPTY,SIX_MENS_MORRIS_EMPTY,SIX_MENS_MORRIS_EMPTY,
                                                        SIX_MENS_MORRIS_EMPTY,SIX_MENS_MORRIS_PLAYER_W,SIX_MENS_MORRIS_PLAYER_R};
    CSixMensMorrisBoard board(turn, unplaced, positions, previous);
    EXPECT_TRUE(board.CanMove(turn, 14));
    EXPECT_TRUE(board.Move(SIX_MENS_MORRIS_PLAYER_W,14,15)); // on board 15 to 16
    
    EXPECT_FALSE(board.CanMove(SIX_MENS_MORRIS_PLAYER_R,1));
    EXPECT_FALSE(board.CanMove(SIX_MENS_MORRIS_PLAYER_R,2));
    EXPECT_FALSE(board.CanMove(SIX_MENS_MORRIS_PLAYER_R,9));
    EXPECT_TRUE(board.GameOver());
}

TEST(SixMensMorrisBoardTest, BadParametersTest){
    // done and good
    char turn = SIX_MENS_MORRIS_PLAYER_R;
    int unplaced[SIX_MENS_MORRIS_PLAYERS] = {3,3};
    const char positions[SIX_MENS_MORRIS_POSITIONS] = {SIX_MENS_MORRIS_PLAYER_R,SIX_MENS_MORRIS_PLAYER_W,SIX_MENS_MORRIS_EMPTY,
                                                        SIX_MENS_MORRIS_EMPTY,SIX_MENS_MORRIS_EMPTY,SIX_MENS_MORRIS_PLAYER_R,
                                                        SIX_MENS_MORRIS_EMPTY,SIX_MENS_MORRIS_EMPTY,SIX_MENS_MORRIS_EMPTY,SIX_MENS_MORRIS_PLAYER_W,
                                                        SIX_MENS_MORRIS_EMPTY,SIX_MENS_MORRIS_PLAYER_W,SIX_MENS_MORRIS_EMPTY,
                                                        SIX_MENS_MORRIS_EMPTY,SIX_MENS_MORRIS_EMPTY,SIX_MENS_MORRIS_PLAYER_R};
    
    const char previous[SIX_MENS_MORRIS_POSITIONS] = {SIX_MENS_MORRIS_PLAYER_R,SIX_MENS_MORRIS_EMPTY,SIX_MENS_MORRIS_EMPTY,
                                                        SIX_MENS_MORRIS_EMPTY,SIX_MENS_MORRIS_EMPTY,SIX_MENS_MORRIS_PLAYER_R,
                                                        SIX_MENS_MORRIS_EMPTY,SIX_MENS_MORRIS_EMPTY,SIX_MENS_MORRIS_EMPTY,SIX_MENS_MORRIS_PLAYER_W,
                                                        SIX_MENS_MORRIS_EMPTY,SIX_MENS_MORRIS_PLAYER_W,SIX_MENS_MORRIS_EMPTY,
                                                        SIX_MENS_MORRIS_EMPTY,SIX_MENS_MORRIS_EMPTY,SIX_MENS_MORRIS_PLAYER_R};
    CSixMensMorrisBoard board(turn, unplaced,positions, previous);
    EXPECT_EQ(board.PlayerAtPosition(21),'\0');
    EXPECT_EQ(board.PlayerAtPosition(35),'\0');
    EXPECT_EQ(board.PlayerAtPosition(-1),'\0');
    EXPECT_EQ(board.PlayerAtPosition(-35),'\0');
    EXPECT_EQ(board.PlayerAtPosition(100),'\0');
    EXPECT_EQ(board.UnplacedPieces('P'),-1);
    EXPECT_EQ(board.UnplacedPieces('Z'),-1);
    EXPECT_EQ(board.UnplacedPieces('A'),-1);
    EXPECT_EQ(board.UnplacedPieces('Q'),-1);
    EXPECT_FALSE(board.CanRemove('Q'));
    EXPECT_FALSE(board.CanRemove('C'));
    EXPECT_FALSE(board.CanMove('Q',20));
    EXPECT_FALSE(board.CanMove('V',15));
    EXPECT_FALSE(board.CanMove('R',19));
    EXPECT_FALSE(board.CanMove('W',50));
}
