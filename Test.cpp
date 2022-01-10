#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "MoveGenerator.h"
#include "ChessBoard.h"
#include <bitset>

TEST_CASE("ChessBoard::FenString constructor", "[Weight=1][part=ChessBoard]") {
    std::string startingFen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
    ChessBoard cb = ChessBoard(startingFen);
    cb.printBoard(cb.allPieces);
    REQUIRE(cb.whiteToMove);
    REQUIRE(cb.whiteQueenSideCastle);
    REQUIRE(cb.whiteKingSideCastle);
    REQUIRE(cb.blackQueenSideCastle);
    REQUIRE(cb.blackKingSideCastle);
    REQUIRE(cb.countBits(cb.allPieces) == 32); 
}

TEST_CASE("MoveGenerator::InitOccMasks", "[Weight=1][part=MoveGenerator]") {
    std::string startingFen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
    ChessBoard cb = ChessBoard(startingFen);
    MoveGenerator* mg = new MoveGenerator();
    Move moves[MAXMOVES]; 
    Move* endmoves;
    endmoves = mg->generateMoves(&cb, moves);
    int length = endmoves - moves;
    REQUIRE(length == 20);
    delete mg;
}