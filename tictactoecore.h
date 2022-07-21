#ifndef TICTACTOECORE_H
#define TICTACTOECORE_H
#include <QDebug>
enum class gameState
{
    FINISHED,
    TIE,
    CONTINUES
};

class TicTacToeCore
{
  public:
    TicTacToeCore();
    void computerPlay();
    gameState gameStatus();
    gameState gameStatus(char (&board)[7][7]);
    void clearBoard();
    void changeGameDifficulty(int gameDifficulty);
    char m_board[7][7];
    friend QDebug operator<<(QDebug stream, const TicTacToeCore &TTT);

  private:
    void computerPlayEasy();
    void computerPlayMedium();
    void computerPlayHard();
    float minimax(bool maximizingPlayer, int dept, float alpha, float beta);
    int m_gameDifficulty = 0;
};
#endif // TICTACTOECORE_H
