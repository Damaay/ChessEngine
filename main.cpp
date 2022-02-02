#include "GameState.h"
#include "Zobrist.h"

int main(int argc, char** argv) {
    BitBoards::precomputeAttackSets();
    Evaluation::init();
    Zobrist::init();
    GameState gs = GameState();
    gs.start();

    return 0;
}