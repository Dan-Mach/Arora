#include "defs.h"
#include "stdlib.h"
#include "stdio.h"

#define RAND_64 (   (U64)rand() | \
                    (U64)rand() << 15 | \
                    (U64)rand() << 30 | \
                    (U64)rand() << 45 | \
                    ((U64)rand() & 0xff) << 60 )
    
int SQ120toSQ64[BRD_SQ_NUM];
int SQ64toSQ120[64];


U64 setMask [64];
U64 clearMask[64];

U64 pieceKeys[13][120];
U64 sideKey;
U64 castleKey[16];

int fileBrd[BRD_SQ_NUM];
int rankBrd[BRD_SQ_NUM];

U64 BlackPassedMask[64];
U64 WhitePassedMask[64];
U64 IsolatedMask[64];

S_OPTIONS EngineOptions[1];

void InitEvalMasks() {

	int sq, tsq, r, f;

	for(sq = 0; sq < 8; ++sq) {
        FileBBMask[sq] = 0ULL;
		RankBBMask[sq] = 0ULL;
	}

	for(r = rank_8; r >= rank_1; r--) {
        for (f = file_A; f <= file_H; f++) {
            sq = r * 8 + f;
            FileBBMask[f] |= (1ULL << sq);
            RankBBMask[r] |= (1ULL << sq);
        }
	}

	for(sq = 0; sq < 64; ++sq) {
		IsolatedMask[sq] = 0ULL;
		WhitePassedMask[sq] = 0ULL;
		BlackPassedMask[sq] = 0ULL;
    }

	for(sq = 0; sq < 64; ++sq) {
		tsq = sq + 8;

        while(tsq < 64) {
            WhitePassedMask[sq] |= (1ULL << tsq);
            tsq += 8;
        }

        tsq = sq - 8;
        while(tsq >= 0) {
            BlackPassedMask[sq] |= (1ULL << tsq);
            tsq -= 8;
        }

        if(filesBrd[SQ120(sq)] > file_A) {
            IsolatedMask[sq] |= FileBBMask[filesBrd[SQ120(sq)] - 1];

            tsq = sq + 7;
            while(tsq < 64) {
                WhitePassedMask[sq] |= (1ULL << tsq);
                tsq += 8;
            }

            tsq = sq - 9;
            while(tsq >= 0) {
                BlackPassedMask[sq] |= (1ULL << tsq);
                tsq -= 8;
            }
        }

        if(filesBrd[SQ120(sq)] < file_H) {
            IsolatedMask[sq] |= FileBBMask[filesBrd[SQ120(sq)] + 1];

            tsq = sq + 9;
            while(tsq < 64) {
                WhitePassedMask[sq] |= (1ULL << tsq);
                tsq += 8;
            }

            tsq = sq - 7;
            while(tsq >= 0) {
                BlackPassedMask[sq] |= (1ULL << tsq);
                tsq -= 8;
            }
        }
	}
}
void fileRankBrd(){

    int index = 0;
    int file = file_A;
    int rank = rank_1;
    int sq = A1;
    int sq64 = 0;

    for( index = 0; index <  BRD_SQ_NUM; ++index){

        fileBrd[index] = OFFBOARD;
        rankBrd[index] = OFFBOARD;

    }

    for (rank = rank_1; rank <= rank_8; ++rank){
        for(file = file_A; file <= file_H; ++file){
            sq = FR2SQ(file,rank);
            fileBrd[sq] = file;
            rankBrd[sq] = rank;
        }
    }

    /*printf("FileBrd \n");
    for(index = 0; index < BRD_SQ_NUM; ++index){
        if(index %10 == 0  && index != 0) printf("\n");
        printf("%4d", fileBrd[index]);
    }

    printf("\n\n ");
    printf("RanksBrd \n");
    for( index = 0; index < BRD_SQ_NUM; ++index){
        if(index %10 == 0 && index != 0 ) printf("\n");
        printf("%4d", rankBrd[index]);
    }*/
}

void initHashKeys(){

    int index = 0;
    int index2 = 0;

    for (index = 0 ; index < 13 ; ++index){
        for( index2 = 0; index2 < 120; ++index2){
            pieceKeys[index][index2] = RAND_64;
        }
    }

    sideKey = RAND_64;
    for(index = 0; index < 16; ++index){
        castleKey[index] = RAND_64;
    }

}

// has an error
void initBitMasks(){
    int index = 0;

    for (index = 0; index < 64; index++){
        setMask[index] = 0ULL;
        clearMask[index] = 0ULL;
    }

    for( index = 0;index < 64 ; index ++){
        setMask[index] |= (1ULL << index);
        clearMask[index] = ~setMask[index]; 
    }
}
void InitSQ120to64 (){
    int index = 0;
    int file = file_A;
    int rank = rank_1;
    int sq = A1;
    int sq64 = 0;

    for( index = 0; index < BRD_SQ_NUM; ++index ){
        SQ120toSQ64[index] = 65;

    }
    for( index = 0 ; index < 64; ++index ){
        SQ64toSQ120[index] = 120;
    }

    for( rank = rank_1; rank <= rank_8; ++rank){
        for( file = file_A; file <= file_H; ++file ){
            
            sq = FR2SQ(file, rank);
            SQ64toSQ120[sq64] = sq;
            SQ120toSQ64[sq] = sq64;
            sq64++;
        }
    }
}
void Allinit (){

    InitSQ120to64();
    initBitMasks();
    initHashKeys();
    fileRankBrd();
    InitEvalMasks();
    InitMvvLva();
    InitPolyBook();
    
  
}