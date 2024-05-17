#ifndef DEFS_H
#define DEFS_H

#include <stdlib.h>
#include <stdio.h>



//#define DEBUG

#define MAX_HASH 1024
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
#define MAXPOSITIONMOVES 256
#define MAXDEPTH 64

#define START_FEN "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1"

#define INFINITE 30000
#define ISMATE (INFINITE - MAXDEPTH)

enum { EMPTY, wP, wN, wB, wR, wQ, wK, bP, bN, bB, bR, bQ, bK };
enum {file_A, file_B, file_C, file_D, file_E, file_F, file_G, file_H, file_NONE};
enum {rank_1, rank_2, rank_3, rank_4, rank_5, rank_6, rank_7, rank_8, rank_NONE};

enum { WHITE, BLACK, BOTH};
enum { UCIMODE, XBOARDMODE, CONSOLEMODE};

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
	int score;
} S_MOVE;

typedef struct {
	S_MOVE moves[MAXPOSITIONMOVES];
	int count;
} S_MOVELIST;

enum {  HFNONE, HFALPHA, HFBETA, HFEXACT};

typedef struct {
	U64 posKey;
	int move;
	int score;
	int depth;
	int flags;
} S_HASHENTRY;

typedef struct {
	S_HASHENTRY *pTable;
	int numEntries;
	int newWrite;
	int overWrite;
	int hit;
	int cut;
} S_HASHTABLE;

typedef struct {
    int move;
    int castlePerm;
    int fiftyMove;
    int enPass;
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

    S_HASHTABLE HashTable[1];
    int PvArray[MAXDEPTH];

    int searchHistory[13][BRD_SQ_NUM];
    int searchKillers[2][MAXDEPTH];


}C_board;

typedef struct {

	int starttime;
	int stoptime;
	int depth;
	int timeset;
	int movestogo;

	long nodes;

	int quit;
	int stopped;

	float fh;
	float fhf;
	int nullCut;

	int GAME_MODE;
	int POST_THINKING;

} S_SEARCHINFO;

typedef struct {
	int UseBook;
} S_OPTIONS;


#define FROMSQ(m) ((m) & 0x7F)
#define TOSQ(m) (((m)>>7) & 0x7F)
#define CAPTURED(m) (((m)>>14) & 0xF)
#define PROMOTED(m) (((m)>>20) & 0xF)

#define MFLAGEP 0x40000
#define MFLAGPS 0x80000
#define MFLAGCA 0x1000000

#define MFLAGCAP 0x7C000
#define MFLAGPROM 0xF00000

#define NOMOVE 0


//MACROS
#define FR2SQ(f,r) ((21 + (f)) + ((r) * 10))
#define SQ64(sq120) (SQ120toSQ64[(sq120)])
#define SQ120(sq64) (SQ64toSQ120[(sq64)])
#define POP(b) popBit(b)
#define CNT(b) countBit(b)
#define CLRBIT(bb,sq) ((bb) &= clearMask [(sq)])
#define SETBIT(bb,sq) ((bb) |= setMask [(sq)])

#define IsBQ(p) (pieceBishopQueen[(p)])
#define IsRQ(p) (pieceRookQueen[(p)])
#define IsKn(p) (pieceKnight[(p)])
#define IsKi(p) (pieceKing[(p)])


#define MIRROR64(sq) (Mirror64[(sq)])



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

//boolean
extern int pieceBig[13];
extern int pieceMaj[13];
extern int pieceMin[13];
extern int pieceVal[13];
extern int pieceCol[13];


extern int filesBrd[BRD_SQ_NUM];
extern int ranksBrd[BRD_SQ_NUM];

extern int piecePawn[13];
extern int pieceKnight[13];
extern int pieceKing[13];
extern int pieceRookQueen[13];
extern int pieceBishopQueen[13];
extern int pieceSlides[13];

extern int Mirror64[64];

extern U64 FileBBMask[8];
extern U64 RankBBMask[8];

extern U64 BlackPassedMask[64];
extern U64 WhitePassedMask[64];
extern U64 IsolatedMask[64];

extern S_OPTIONS EngineOptions[1];


/*functions*/

//board.c
extern  void ResetBoard( C_board *pos);
extern int parse_fen( char *fen, C_board *pos);
extern void printBoard(const C_board *pos);
extern void UpdateListsMaterial (C_board *pos);
extern int CheckBoard(const C_board *pos);
extern void MirrorBoard( C_board *pos);
extern int PceListOk(const C_board* pos);

//hashKey.c
extern U64 GeneratePosKey (const C_board *pos);

//attack.c
extern int SqAttacked(const int sq, const int side, const C_board *pos);


// io.c
extern char *PrMove(const int move);
extern char *PrSq(const int sq);
extern void PrintMoveList(const S_MOVELIST *list);
extern int ParseMove(char *ptrChar, C_board *pos);


//validate.c
extern int SqOnBoard(const int sq);
extern int SideValid(const int side);
extern int FileRankValid(const int fr);
extern int PieceValidEmpty(const int pce);
extern int PieceValid(const int pce);
extern void MirrorEvalTest(C_board *pos);
extern int SqIs120(const int sq);
extern int PceValidEmptyOffbrd(const int pce);
extern int MoveListOk(const S_MOVELIST *list,  const C_board *pos);
extern void DebugAnalysisTest(C_board *pos, S_SEARCHINFO *info);

// movegen.c
extern void GenerateAllMoves(const C_board *pos, S_MOVELIST *list);
extern void GenerateAllCaps(const C_board *pos, S_MOVELIST *list);
extern int MoveExists(C_board *pos, const int move);
extern void InitMvvLva();

// makemove.c
extern int MakeMove(C_board *pos, int move);
extern void TakeMove(C_board *pos);
extern void MakeNullMove(C_board *pos);
extern void TakeNullMove(C_board *pos);

// perft.c
extern void PerftTest(int depth, C_board *pos);

// search.c
extern void SearchPosition(C_board *pos, S_SEARCHINFO *info);

// misc.c
extern int GetTimeMs();
extern void ReadInput(S_SEARCHINFO *info);

// pvtable.c
extern void InitHashTable(S_HASHTABLE *table, const int MB);
extern void StoreHashEntry(C_board *pos, const int move, int score, const int flags, const int depth);
extern int ProbeHashEntry(C_board *pos, int *move, int *score, int alpha, int beta, int depth);
extern int ProbePvMove(const C_board *pos);
extern int GetPvLine(const int depth, C_board *pos);
extern void ClearHashTable(S_HASHTABLE *table);

// evaluate.c
extern int EvalPosition(const C_board *pos);
extern void MirrorEvalTest(C_board *pos) ;

// uci.c
extern void Uci_Loop(C_board *pos, S_SEARCHINFO *info);
extern void ParseGo(char* line, S_SEARCHINFO* info, C_board* pos);

// xboard.c
extern void XBoard_Loop(C_board *pos, S_SEARCHINFO *info);
extern void Console_Loop(C_board *pos, S_SEARCHINFO *info);

// polybook.c
extern int GetBookMove(C_board *board);
extern void CleanPolyBook();
extern void InitPolyBook() ;

//bitboard.c
extern void PrintBitBoard (U64 bb);
extern int popBit( U64 *bb);
extern int countBit(U64 b);


//init.c
extern void Allinit();

#endif