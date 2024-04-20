#include "stdio.h"
#include "defs.h"

void updatelist_Material (C_board *pos){

    int piece, sq, index, colour;

    for (index = 0; index < BRD_SQ_NUM; ++index){
        sq = index;
        piece = pos->pieces[index];

        if(piece != OFFBOARD && piece != EMPTY){
            colour = pieceCol[piece];

            if( pieceBig[piece] == TRUE) pos->bigPce[colour]++;
            if( pieceMin[piece] == TRUE) pos->minPce[colour]++;
            if( pieceMaj[piece] == TRUE) pos->majPce[colour]++;

            pos->material[colour] += pieceVal[piece];

            //piece list

            pos->pList[piece][pos->pceNum[piece]] = sq ;
            pos->pceNum[piece]++;

            if (piece == wK) pos->KingSq[WHITE] = sq;
            if (piece == bK) pos->KingSq[BLACK] = sq;

            if(piece == wP){
                SETBIT(pos->pawns[WHITE], SQ64(sq));
                SETBIT(pos->pawns[BOTH], SQ64(sq));
            }
            else if( piece == bP){
                SETBIT(pos->pawns[BLACK],SQ64(sq));
                SETBIT(pos->pawns[BOTH], SQ64(sq));
            }
        }
    }


}

int parse_fen( char *fen, C_board *pos){
    ASSERT(fen != NULL);
    ASSERT(pos != NULL);

    int rank = rank_8;
    int file = file_A;
    int piece = 0;
    int count = 0;
    int sq64 = 0;
    int sq120 = 0;
    int i;

    resetBoard(pos);

    while( (rank >= rank_1) && *fen){
        count = 1;

        switch(*fen){
            case 'p': piece = bP; break;
            case 'r': piece = bR; break;
            case 'n': piece = bN; break;
            case 'b': piece = bB; break;
            case 'k': piece = bK; break;
            case 'q': piece = bQ; break;
            case 'P': piece = wP; break;
            case 'R': piece = wR; break;
            case 'N': piece = wN; break;
            case 'Q': piece = wQ; break;
            case 'K': piece = wK; break;
            case 'B': piece = wB; break;

            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
                
                piece = EMPTY;
                count = *fen - '0';
                break;
            
            case '/':
            case ' ':

                rank--;
                file = file_A;
                fen++;
                continue;
            
            default:
                printf("FEN ERROR! \n");
                return -1;
        }

        for (i = 0; i < count ; i++){
            sq64 = rank * 8 + file;
            sq120 = SQ120(sq64);

            if (piece != EMPTY){
                pos->pieces[sq120] = piece;
            }

            file++;
        }
        fen++;
    }

    ASSERT(*fen == 'w'  || *fen == 'b');

    pos->side = (*fen == 'w') ? WHITE:BLACK;
    fen += 2;

    for (i = 0; i < 4; i++){
        if( *fen == ' '){
            break;
        }
        
        switch (*fen){
            case 'K': pos->castlePerm |= WKCA;  break;
            case 'Q': pos->castlePerm |= WQCA; break;
            case 'k': pos->castlePerm |= BKCA;  break;
            case 'q': pos->castlePerm |= BQCA; break;
            default: break;
        }

        fen++;
    }
    fen++;

    ASSERT(pos->castlePerm >= 0 && pos->castlePerm <= 15);
    // there is an error here
    if(*fen != '-'){
        file = fen[0] - 'a';
        rank = fen[1] - '1';

        ASSERT(file >= file_A && file <= file_H);
        ASSERT(rank >= rank_1 && rank <= rank_8);

        pos->enPass = FR2SQ(file,rank);

    }

    pos->posKey = GeneratePosKey(pos);

    return 0;
}

void resetBoard( C_board *pos){

    int index = 0;

    for(index = 0; index < BRD_SQ_NUM; ++index){
        pos-> pieces[index] = OFFBOARD;

    }

    for(index = 0 ; index < 64; ++index){
        pos->pieces[SQ120(index)] = EMPTY;
    }

    for (index = 0; index < 3; ++index){
        pos->bigPce[index] = 0;
        pos->majPce[index] = 0;
        pos->minPce[index] = 0;
        pos->pawns[index] = 0ULL;
    }

    for (index = 0 ; index < 13; ++index){
        pos->pceNum[index] = 0;
    }

    pos->KingSq[WHITE] = pos->KingSq[BLACK] = NO_SQ;

    pos->side = BOTH;
    pos->enPass = NO_SQ;
    pos->fifty_Move = 0;

    pos->ply = 0;
    pos->hisply = 0;

    pos->castlePerm = 0;

    pos->posKey = 0ULL;
    
}

void printBoard(const C_board *pos){

    int sq,file,piece, rank;

    printf("\n Board:\n");
    printf("\n");
    for (rank = rank_8; rank >= rank_1; --rank){
        printf("%d ", rank + 1);
        for(file = file_A; file <= file_H; ++file){
            sq = FR2SQ(file,rank);
            piece = pos->pieces[sq];
            printf("%3c", pceChar[piece]);
        }
        printf("\n");
    }

    printf("\n  ");
    for(file = file_A; file <= file_H; file++){

        printf("%3c", 'a' + file);
    }
    printf("\n");

    printf("side: %c \n", sideChar[pos->side]);
    printf("enPas: %d \n", pos->enPass);

    printf("Castle Permission: %c %c %c %c\n",
            pos->castlePerm & WKCA ? 'K' : '-',
            pos->castlePerm & WQCA ? 'Q' : '-',
            pos->castlePerm & BKCA ? 'k' : '-',
            pos->castlePerm & BQCA ? 'q' : '-'
        );

    printf("PosKey: %llX\n", pos->posKey); 
}