// perft.c

#include "defs.h"
#include  <stdio.h>

long leafNodes;

void perft(int depth, C_board *pos){

    ASSERT(CheckBoard);

    if(depth == 0){
        leafNodes++;
        return;
    }

    S_MOVELIST list[1];
    GenerateAllMoves(pos, list);

    int MoveNum = 0;
    
    for( MoveNum = 0 ; MoveNum < list->count; ++MoveNum){

        if( !MakeMove(pos,list->moves[MoveNum].move)){
            continue;
        }

        perft(depth - 1, pos);
        TakeMove(pos);
    }

    return;
}

void PerftTest(int depth, C_board *pos){

    ASSERT(CheckBoard);

    printBoard(pos);
    printf("\n Startitng test to depth: %d \n", depth);
    leafNodes = 0;

    S_MOVELIST list[1];
    GenerateAllMoves(pos, list);

    int move;
    int MoveNum;

    for( MoveNum = 0; MoveNum < list->count; ++MoveNum){
        move = list->moves[MoveNum].move;

        if(!MakeMove(pos, move)){
            continue;
        }

        long cumnodes = leafNodes;

        perft(depth - 1, pos);
        TakeMove(pos);

        long oldnodes = leafNodes - cumnodes;
        printf("\n move %d: %s : %ld \n ", MoveNum + 1, PrMove(move), oldnodes);

    }

    printf("\n Test complete: %ld nodes visited \n ", leafNodes);

    return;
}