#include "Game.h"


Game::Game() {
    restart();
}

void Game::restart() {
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            _boardState[i][j] = CELL_EMPTY;
        }
    }
    _gameState = HUMAN_TURN;
    _turnsPassed = 0;
}
