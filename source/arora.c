#include "defs.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//#define WAC1 "r1b1k2r/ppppnppp/2n2q2/2b5/3NP3/2P1B3/PP3PPP/RN1QKB1R w KQkq - 0 1"
//#define PERFT "r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq - 0 1"
#define PAWNMOVE "rnbqk1r/pp1p1ppPp/8/2p1pP2/1P1P4/3P3P/P1P1P3/RNBQKBNR b KQkq e6 0 1"
//#define CASTLE1 "r3k2r/8/8/8/8/8/8/R3K2R w KQkq - 0 1"
//#define CASTLE2 "3rk2r/8/8/8/8/8/6p1/R3K2R  w KQkq - 0 1"

void showSqAtByside(const int side, const C_board *pos){
	int rank = 0;
	int file = 0;
	int sq = 0;

	printf("\n\n Squares attacked by: %c \n  ", sideChar[side]);
	for(rank = rank_8; rank >= rank_1; ++rank){
		for(file = file_A; file <= file_H; ++file){
			sq = FR2SQ(file,rank);
			if(SqAttacked(sq,side,pos) == TRUE){
				printf("X");

			}
			else{
				printf("-");
			}
		}
		printf("\n");
	}
	printf("\n\n");
}
int main (){

	Allinit();

	C_board board[1];

	parse_fen(PAWNMOVE, board);
	printBoard(board);

	printf("\n White Attacking: \n");
	showSqAtByside(WHITE, board);

	printf("\n Black Attacking: \n");
	showSqAtByside(BLACK,board);

    return 0;
}
