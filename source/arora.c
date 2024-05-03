#include "defs.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define WAC1 "r1b1k2r/ppppnppp/2n2q2/2b5/3NP3/2P1B3/PP3PPP/RN1QKB1R w KQkq - 0 1"
#define PERFT "r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq - 0 1"
#define PAWNMOVE "rnbqk1r/pp1p1ppPp/8/2p1pP2/1P1P4/3P3P/P1P1P3/RNBQKBNR w KQkq e6 0 1"

int main (){

	Allinit();

	int move = 0;
	int from = A2; int to = H7;
	int cap = wR;  int prom = bR;

	move = ((from) | (to << 7) | ( cap << 14 ) | (prom << 20));
	
	printf("\n from: %d to: %d cap:%d prom:%d \n",
		FROMSQ(move), TOSQ(move), CAPTURED(move),
		PROMOTED(move));

	printf("\n Algebraic from: %s", PrSq(from));
	printf("\n Algebraic to : %s", PrSq(to));
	printf("\n Algebraic move: %s", PrMove(move));

    return 0;
}
