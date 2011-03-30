#include "Game.h"

#include <cstdlib>


Game::Game() {
    restart();
}

void Game::restart() {
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            _boardState[i][j] = CELL_EMPTY;
        }
    }
    _gameState = X_TURN;
    _turnsPassed = 0;
}

bool Game::makeMove(int x, int y) {
    GAME_STATE nextState;
    CELL_STATE curPlayerCell;

    if(_gameState == O_TURN) {
        curPlayerCell = CELL_O;
        nextState = X_TURN;
    } else if(_gameState == X_TURN) {
        curPlayerCell = CELL_X;
        nextState = O_TURN;
    } else {
        return false;
    }

    if(_boardState[x][y] != CELL_EMPTY) {
        return false;
    }

    _boardState[x][y] = curPlayerCell;
    _turnsPassed++;
    _gameState = nextState;

    _checkForEnd();
    return true;
}

bool Game::makeRandomMove() {
    GAME_STATE nextState;
    CELL_STATE curPlayerCell;

    if(_gameState == O_TURN) {
        curPlayerCell = CELL_O;
        nextState = X_TURN;
    } else if(_gameState == X_TURN) {
        curPlayerCell = CELL_X;
        nextState = O_TURN;
    } else {
        return false;
    }

    int nFreeCells = 0;
    int freeCells[9][2];
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            if(_boardState[i][j] == CELL_EMPTY) {
                freeCells[nFreeCells][0] = i;
                freeCells[nFreeCells][1] = j;
                nFreeCells++;
            }
        }
    }

    if(nFreeCells == 0) {
        return false;
    }

    int choice = rand() % nFreeCells;
    int x = freeCells[choice][0];
    int y = freeCells[choice][1];

    _boardState[x][y] = curPlayerCell;
    _turnsPassed++;
    _gameState = nextState;

    _checkForEnd();
    return true;
}

void Game::_checkForEnd() {
    if(_turnsPassed == 9) {
        _gameState = DRAW;
    }

    CELL_STATE winningCell = CELL_EMPTY;

    for(int i = 0; i < 3; i++) {
        if((_boardState[i][0] == _boardState[i][1]) &&
                (_boardState[i][1] == _boardState[i][2]) &&
                (_boardState[i][0] != CELL_EMPTY)) {
            winningCell = _boardState[i][0];
        }
    }
    for(int i = 0; i < 3; i++) {
        if((_boardState[0][i] == _boardState[1][i]) &&
                (_boardState[1][i] == _boardState[2][i]) &&
                (_boardState[0][1] != CELL_EMPTY)) {
            winningCell = _boardState[0][i];
        }
    }
    if((_boardState[0][0] == _boardState[1][1]) &&
            (_boardState[1][1] == _boardState[2][2]) &&
            (_boardState[0][0] != CELL_EMPTY)) {
        winningCell = _boardState[0][0];
    }
    if((_boardState[2][0] == _boardState[1][1]) &&
            (_boardState[1][1] == _boardState[0][2]) &&
            (_boardState[2][0] != CELL_EMPTY)) {
        winningCell = _boardState[2][0];
    }

    if(winningCell == CELL_X) {
        _gameState = X_WON;
    } else if(winningCell == CELL_O) {
        _gameState = O_WON;
    }
}
