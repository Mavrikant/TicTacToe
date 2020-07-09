#ifndef TICTACTOECORE_H
#define TICTACTOECORE_H
#include <QDebug>
enum class gameState {FINISHED, TIE, CONTINUES};

class TicTacToeCore
{
public:
    TicTacToeCore();
    void computerPlay();
    gameState gameStatus() const;
    void clearBoard();
    void changeGameDifficulty(int gameDifficulty);
    char m_board[3][3] = {{' ', ' ', ' '}, {' ', ' ', ' '}, {' ', ' ', ' '}};
    friend QDebug operator<<(QDebug stream, const TicTacToeCore &TTT);

private:
    void computerPlayRandom();
    void computerPlaySmart();
    int m_gameDifficulty = 0;
};
#endif // TICTACTOECORE_H
