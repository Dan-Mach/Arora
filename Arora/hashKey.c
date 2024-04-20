#include "stdio.h"
#include "defs.h"


U64 GeneratePosKey (const C_board *pos){

    int sq = 0;
    U64 finalKey = 0;
    int piece = EMPTY;

    for( sq = 0; sq <BRD_SQ_NUM; ++sq){
        piece = pos ->pieces[sq];
        // There is an error here
        if(piece != NO_SQ && piece != EMPTY && piece != OFFBOARD){
            ASSERT(piece >= wP &&  piece <= bK);
            finalKey ^= pieceKeys[piece][sq];
        }
    }

    if(pos ->side == WHITE){
        finalKey ^= sideKey;
    }

    if(pos ->enPass != NO_SQ){
        ASSERT(pos->enPass >= 0 && pos ->enPass <BRD_SQ_NUM);
        finalKey ^= pieceKeys[EMPTY][pos->enPass];
    }

    ASSERT(pos ->castlePerm >= 0 && pos ->castlePerm);
    finalKey ^= castleKey[pos->castlePerm];

    return finalKey;
}