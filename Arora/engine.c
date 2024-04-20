#include "defs.h"
#include <stdlib.h>
#include <stdio.h>


#define FEN_4 "r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq - 0 1"


int main () {

    Allinit ();

    C_board board[1];

    parse_fen(START_FEN, board);
    printBoard(board);

    printf("\nwP: \n");
    PrintBitBoard(board->pawns[WHITE]);

    printf("\nbP: \n");
    PrintBitBoard(board->pawns[BLACK]);

    printf("\n All: P: \n");
    PrintBitBoard(board->pawns[BOTH]);

    return 0;
}
