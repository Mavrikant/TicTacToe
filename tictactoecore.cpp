#include "tictactoecore.h"
#include <QDebug>
#include "unistd.h"

TicTacToeCore::TicTacToeCore()
{

}

void TicTacToeCore::computerPlay()
{
    switch (m_gameDifficulty)
    {
    case 0:
        computerPlayRandom();
        break;
    case 1:
        computerPlaySmart();
        break;
    }
}


gameState TicTacToeCore::gameStatus() const
{
    for (int i = 0; i < 3; ++i)
    {
        if ((m_board[i][0] != ' ') && (m_board[i][0] == m_board[i][1]) && (m_board[i][1] == m_board[i][2])) //check rows
        {
            return gameState::FINISHED;
        }
        if ((m_board[0][i] != ' ') && (m_board[0][i] == m_board[1][i]) && (m_board[1][i] == m_board[2][i]))//check colomn
        {
            return gameState::FINISHED;
        }
    }


    if ((m_board[0][0] != ' ') && (m_board[0][0] == m_board[1][1]) && (m_board[1][1] == m_board[2][2])) //check diagonal
    {
        return gameState::FINISHED;
    }

    if ((m_board[0][2] !=  ' ' ) && (m_board[0][2] == m_board[1][1] ) && (m_board[1][1] == m_board[2][0])) //check diagonal
    {
        return gameState::FINISHED;
    }

    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            if (m_board[i][j] == ' ')
            {
                return gameState::CONTINUES;
            }
        }
    }
    return gameState::TIE;
}

void TicTacToeCore::clearBoard()
{
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            m_board[i][j] = ' ';
        }
    }
}

void TicTacToeCore::changeGameDifficulty(int gameDifficulty)
{
    m_gameDifficulty = gameDifficulty;
}

void TicTacToeCore::computerPlayRandom()
{
    usleep(500000);
    while (1)
    {
        int i = rand() % 3;
        int j = rand() % 3;
        if (m_board[i][j] == ' ')
        {
            m_board[i][j] = 'O';
            return;
        }
    }
}

void TicTacToeCore::computerPlaySmart()
{
    sleep(200000);
    //TODO prevent win
    computerPlayRandom();
}

QDebug operator<<(QDebug stream, const TicTacToeCore &TTT)
{
    QDebugStateSaver saver(stream);
    for (int i = 0; i < 3; ++i)
    {
        stream.nospace() << TTT.m_board[i][0] << "|" << TTT.m_board[i][1] << "|" << TTT.m_board[i][2] << "\n";
    }
    return stream;
}

