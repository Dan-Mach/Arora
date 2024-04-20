#ifndef DEFS_H
#define DEFS_H

#include <stdlib.h>

//#define DEBUG
#ifndef DEBUG
#define ASSERT(n)
#else
#define ASSERT(n) \
if(!(n)) { \
printf("%s - Failed", #n);\
printf("On %s", __DATE__); \
printf("At %s", __TIME__); \
printf("In File %s ", __FILE__); \
printf("At line %d \n", __LINE__); \
exit(1);}

#endif

typedef unsigned long long U64;

#define NAME "ARORA 2.0"
#define BRD_SQ_NUM 120

#define MAXGAMEMOVE 2048

#define START_FEN "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1"

enum { EMPTY, wP, wN, wB, wR, wQ, wK, bP, bN, bB, bR, bQ, bK };
enum {file_A, file_B, file_C, file_D, file_E, file_F, file_G, file_H, file_NONE};
enum {rank_1, rank_2, rank_3, rank_4, rank_5, rank_6, rank_7, rank_8, rank_NONE};
enum { WHITE, BLACK, BOTH};

enum {
    A1 = 21, B1, C1, D1, E1, F1, G1, H1,
    A2 = 31, B2, C2, D2, E2, F2, G2, H2,
    A3 = 41, B3, C3, D3, E3, F3, G3, H3,
    A4 = 51, B4, C4, D4, E4, F4, G4, H4,
    A5 = 61, B5, C5, D5, E5, F5, G5, H5,
    A6 = 71, B6, C6, D6, E6, F6, G6, H6,
    A7 = 81, B7, C7, D7, E7, F7, G7, H7,
    A8 = 91, B8, C8, D8, E8, F8, G8, H8, NO_SQ, OFFBOARD
   
};

enum {TRUE , FALSE};

enum {WKCA = 1, WQCA = 2, BKCA = 4, BQCA = 8};


typedef struct {
    int move;
    int castlePerm;
    int fiftyMove;
    int enPer;
    U64 posKey;
}undo;

//board structure
typedef struct {
    int pieces [BRD_SQ_NUM];
    U64 pawns[3];
    int KingSq[2];
    int side;
    int enPass;
    int fifty_Move;
    int ply;
    int hisply; 
    int castlePerm;

    U64 posKey;

    int pceNum [13];
    int bigPce[2];
    int majPce[2];
    int minPce[2];
    int material[2];

    undo history[MAXGAMEMOVE];

    //piece list
    int pList[13][10];


}C_board;

//MACROS
#define FR2SQ(f,r) ((21 + (f)) + ((r) * 10))
#define SQ64(sq120) (SQ120toSQ64[(sq120)])
#define SQ120(sq64) (SQ64toSQ120[(sq64)])
#define POP(b) popBit(b)
#define CNT(b) countBit(b)
#define CLRBIT(bb,sq) ((bb) &= clearMask [(sq)])
#define SETBIT(bb,sq) ((bb) |= setMask [(sq)])


// GLOBAL 
extern int SQ120toSQ64[BRD_SQ_NUM];
extern int SQ64toSQ120[64];
extern U64 setMask[64];
extern U64 clearMask[64];
extern U64 pieceKeys[13][120];
extern U64 sideKey;
extern U64 castleKey[16];
extern char pceChar[];
extern char sideChar[];
extern char fileChar[];
extern char rankChar[];
extern int fileBrd[BRD_SQ_NUM];
extern int rankBrd[BRD_SQ_NUM];


//boolean
extern int pieceBig[13];
extern int pieceMaj[13];
extern int pieceMin[13];
extern int pieceVal[13];
extern int pieceCol[13];


/*functions*/

//board.c
extern  void resetBoard( C_board *pos);
extern int parse_fen( char *fen, C_board *pos);
extern void printBoard(const C_board *pos);
extern void updatelist_Material (C_board *pos);

//hashKey.c
extern U64 GeneratePosKey (const C_board *pos);

//init.c
extern void Allinit();

//bit board
extern void PrintBitBoard (U64 bb);
extern int popBit( U64 *bb);
extern int countBit(U64 b);

#endif

