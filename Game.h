#ifndef __GAME_H__
#define __GAME_H__

enum CELL_STATE { CELL_EMPTY, CELL_O, CELL_X };
enum GAME_STATE { X_TURN, O_TURN, X_WON, O_WON, DRAW };

class Game {
public:
    Game();

    CELL_STATE getCellState(int x, int y);
    GAME_STATE getGameState();

    bool makeMove(int x, int y);
    bool makeRandomMove();
    void restart();
private:
    CELL_STATE _boardState[3][3];
    GAME_STATE _gameState;
    int _turnsPassed;

    void _checkForEnd();
};

inline CELL_STATE Game::getCellState(int x, int y) {
    return _boardState[x][y];
}

inline GAME_STATE Game::getGameState() {
    return _gameState;
}

#endif // __GAME_H__
