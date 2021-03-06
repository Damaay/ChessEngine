#include "MovePick.h"
#include "Threads.h"

MovePick::MovePick(ScoredMove* allMoves, int initLength, Move pref, Move prev, Move* killers, ChessBoard& cb) {
    moves = allMoves;
    length = initLength;
    if (prev) {
        counter = cb.thisThread->counterMoves[cb.pieceOn(getTo(prev))][getTo(prev)];
    }
    score(cb, pref, killers);
    buildHeap();
}

Move MovePick::getNext() {
    if (length == 0) return NOMOVE;
    Move ret = moves[0].move;
    swap(0, --length);
    heapifyDown(0);
    return ret;
}

void MovePick::score(ChessBoard& cb, Move pref, Move* killers) {
    for (int i = 0; i < length; i++) {
        Move move = moves[i].move;
        PieceType capt = typeOf(cb.pieceOn(getTo(move)));
        if (capt) {
            PieceType pc = typeOf(cb.pieceOn(getFrom(move)));
            moves[i].score = pieceVals[capt].mg+ cb.thisThread->captureHistory[pc][getTo(move)][capt];
        } else if (getFlag(move) == PROMOTION) {
            moves[i].score = pieceVals[getProm(move)].mg;
        }  else if (move == counter) {
            moves[i].score = 95;
        } else if (move == killers[0]) {
            moves[i].score = 90;
        } else if (move == killers[1]) {
            moves[i].score = 80;
        } else {
            moves[i].score = cb.thisThread->history[cb.colourToMove()][getFrom(move)][getTo(move)];
        }
        if (move == pref) {
            moves[i].score = Infinity;
        }
    }
}

void MovePick::buildHeap() {
    for (int i = (length / 2) - 1; i >= 0; i--) {
        heapifyDown(i);
    }
}

void MovePick::heapifyDown(int start) {
    int largest = start;
    int leftChild = getLeftChild(start);
    int rightChild = getRightChild(start);
    if (leftChild < length && moves[largest] < moves[leftChild]) {
        largest = leftChild;
    }
    if (rightChild < length && moves[largest] < moves[rightChild]) {
        largest = rightChild;
    }
    if (largest != start) {
        swap(start, largest);
        heapifyDown(largest);
    }
}

inline int MovePick::getLeftChild(int parent) {
    return 2 * parent + 1;
}

inline int MovePick::getRightChild(int parent) {
    return 2 * parent + 2;
}

void MovePick::swap(int ind1, int ind2) {
    ScoredMove temp = moves[ind1];
    moves[ind1] = moves[ind2];
    moves[ind2] = temp;
}