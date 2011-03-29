#ifndef __GAME_H__
#define __GAME_H__

enum CELL_STATE { CELL_EMPTY, CELL_O, CELL_X };
enum GAME_STATE { HUMAN_TURN, AI_TURN, HUMAN_WON, AI_WON, DRAW };

class Game {
public:
    Game();

    CELL_STATE getCellState(int x, int y);
    GAME_STATE getGameState();

    void restart();
private:
    CELL_STATE _boardState[3][3];
    GAME_STATE _gameState;
    int _turnsPassed;
};

inline CELL_STATE Game::getCellState(int x, int y) {
    return _boardState[x][y];
}

inline GAME_STATE Game::getGameState() {
    return _gameState;
}

#endif // __GAME_H__
