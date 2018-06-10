#include <string>

#include "GameBoard.h"
#include "unit_test_util.h"

using std::string;
using std::get;

//static bool test1(){
////	GameBoard<12, 7, string, 4> board;
////	int i = 0;
////	for (int row = 0; row < 12; row++){
////		for(int col =0; col < 7; col++){
////			board.setPiece(row, col, "Piece", i);
////			i = (i+1)%4;
////		}
////	}
////	int occurence[4]= {0,0,0,0};
////	for(auto pieceInfo : board){
////		occurence[get<3>(pieceInfo)]++;
////	}
////	for(int i = 0;i<4;i++){
////		if (occurence[i] != 21){
////			return false;
////		}
////	}
////	return true;
//}

int main(){
	//RUN_TEST(test1);
    GameBoard<5, 5, string, 2> g;
    g.setPiece(0, 0, "a", 0);
    g.setPiece(0, 1, "b", 0);
    g.setPiece(1, 0, "a", 1);
    g.setPiece(1, 1, "b", 1);

    cout << g.getPiece(0, 0)->first << endl;
    cout << g.getPiece(0, 0)->second << endl;
    cout << "@@@@@@@@@@@@@@@@@@" << endl;
    for (auto pieceInfo : g) {
        cout << "row: " << get<0>(pieceInfo) << endl;
        cout << "col: " << std::get<1>(pieceInfo) << endl;
        cout << "piece: " << std::get<2>(pieceInfo) << endl; // we assume here that GAME_PIECE implemented <<
        cout << "player: " << std::get<3>(pieceInfo) << endl;
    }
    cout << "@@@@@@@@@@@@@@@@@@" << endl;
    for (auto pieceInfo : g.allPiecesOfPlayer(1)) {
        cout << "row: " << get<0>(pieceInfo) << endl;
        cout << "col: " << std::get<1>(pieceInfo) << endl;
        cout << "piece: " << std::get<2>(pieceInfo) << endl; // we assume here that GAME_PIECE implemented <<
        cout << "player: " << std::get<3>(pieceInfo) << endl;
    }
    cout << "@@@@@@@@@@@@@@@@@@" << endl;
    for (auto pieceInfo : g.allOccureneceOfPiece("a")) {
        cout << "row: " << get<0>(pieceInfo) << endl;
        cout << "col: " << std::get<1>(pieceInfo) << endl;
        cout << "piece: " << std::get<2>(pieceInfo) << endl; // we assume here that GAME_PIECE implemented <<
        cout << "player: " << std::get<3>(pieceInfo) << endl;
    }
    cout << "@@@@@@@@@@@@@@@@@@" << endl;
    for (auto pieceInfo : g.allOccureneceOfPieceForPlayer("a", 1)) {
        cout << "row: " << get<0>(pieceInfo) << endl;
        cout << "col: " << std::get<1>(pieceInfo) << endl;
        cout << "piece: " << std::get<2>(pieceInfo) << endl; // we assume here that GAME_PIECE implemented <<
        cout << "player: " << std::get<3>(pieceInfo) << endl;
    }
    return 0;
}
