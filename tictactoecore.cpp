#include "tictactoecore.h"
#include "unistd.h"
#include <QDebug>
#include <algorithm>

TicTacToeCore::TicTacToeCore() {}

void TicTacToeCore::computerPlay()
{
    usleep((3 - m_gameDifficulty) / 3 * 1000000); // wait for it
    switch (m_gameDifficulty)
    {
    case 0:
        computerPlayEasy();
        break;
    case 1:
        computerPlayMedium();
        break;
    case 2:
        computerPlayHard();
        break;
    }
}

gameState TicTacToeCore::gameStatus() { return gameStatus(m_board); }

gameState TicTacToeCore::gameStatus(char (&board)[7][7])
{
    for (int i = 0; i < 7; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            if ((board[i][0 + j] != ' ') && (board[i][0 + j] == board[i][1 + j]) && (board[i][1 + j] == board[i][2 + j]) && (board[i][2 + j] == board[i][3 + j])) // check rows
            {
                return gameState::FINISHED;
            }

            if ((board[0 + j][i] != ' ') && (board[0 + j][i] == board[1 + j][i]) && (board[1 + j][i] == board[2 + j][i]) && (board[2 + j][i] == board[3 + j][i])) // check colomn
            {
                return gameState::FINISHED;
            }
        }
    }

    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            if ((board[i + 0][j + 0] != ' ') && (board[i + 0][j + 0] == board[i + 1][j + 1]) && (board[i + 1][j + 1] == board[i + 2][j + 2]) && (board[i + 2][j + 2] == board[i + 3][j + 3])) // check diagonal
            {
                return gameState::FINISHED;
            }
        }
    }

    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            if ((board[i + 0][j + 3] != ' ') && (board[i + 0][j + 3] == board[i + 1][j + 2]) && (board[i + 1][j + 2] == board[i + 2][j + 1]) && (board[i + 2][j + 1] == board[i + 3][j + 0])) // check diagonal
            {
                return gameState::FINISHED;
            }
        }
    }

    for (int i = 0; i < 7; ++i)
    {
        for (int j = 0; j < 7; ++j)
        {
            if (board[i][j] == ' ')
            {
                return gameState::CONTINUES;
            }
        }
    }
    return gameState::TIE;
}

void TicTacToeCore::clearBoard()
{
    for (int i = 0; i < 7; ++i)
    {
        for (int j = 0; j < 7; ++j)
        {
            m_board[i][j] = ' ';
        }
    }
}

void TicTacToeCore::changeGameDifficulty(int gameDifficulty) { m_gameDifficulty = gameDifficulty; }

void TicTacToeCore::computerPlayEasy()
{
    while (1)
    {
        int i = rand() % 7;
        int j = rand() % 7;
        if (m_board[i][j] == ' ')
        {
            m_board[i][j] = 'O';
            return;
        }
    }
}

void TicTacToeCore::computerPlayMedium()
{
    int value = -99;
    int a = 0;
    int b = 0;
    for (int i = 0; i < 7; ++i)
    {
        for (int j = 0; j < 7; ++j)
        {
            if (m_board[i][j] == ' ')
            {
                m_board[i][j] = 'O';
                if (value < minimax(false, 3))
                {
                    value = minimax(false, 3);
                    a = i;
                    b = j;
                }
                m_board[i][j] = ' ';
            }
        }
    }
    m_board[a][b] = 'O';
}

void TicTacToeCore::computerPlayHard()
{
    int value = -99;
    int a = 0;
    int b = 0;
    for (int i = 0; i < 7; ++i)
    {
        for (int j = 0; j < 7; ++j)
        {
            if (m_board[i][j] == ' ')
            {
                m_board[i][j] = 'O';
                if (value < minimax(false, 99))
                {
                    value = minimax(false, 99);
                    a = i;
                    b = j;
                }
                m_board[i][j] = ' ';
            }
        }
    }
    m_board[a][b] = 'O';
}

int TicTacToeCore::minimax(bool maximizingPlayer, int dept)
{
    gameState gameresult = gameStatus(m_board);

    if (gameresult == gameState::FINISHED)
    {
        return (maximizingPlayer) ? -1 : +1;
    }
    else if (gameresult == gameState::TIE || dept == 0)
    {
        return 0;
    }

    if (maximizingPlayer) // Computer
    {
        int value = -99;
        for (int i = 0; i < 7; ++i)
        {
            for (int j = 0; j < 7; ++j)
            {
                if (m_board[i][j] == ' ')
                {
                    m_board[i][j] = 'O';
                    value = std::max(value, minimax(false, dept - 1));
                    m_board[i][j] = ' ';
                }
            }
        }
        return value;
    }
    else // Human
    {
        int value = +99;
        for (int i = 0; i < 7; ++i)
        {
            for (int j = 0; j < 7; ++j)
            {
                if (m_board[i][j] == ' ')
                {
                    m_board[i][j] = 'X';
                    value = std::min(value, minimax(true, dept - 1));
                    m_board[i][j] = ' ';
                }
            }
        }
        return value;
    }
}

QDebug operator<<(QDebug stream, const TicTacToeCore &TTT)
{
    QDebugStateSaver saver(stream);
    for (int i = 0; i < 7; ++i)
    {
        stream.nospace() << TTT.m_board[i][0] << "|" << TTT.m_board[i][1] << "|" << TTT.m_board[i][2] << "|" << TTT.m_board[i][3] << "|" << TTT.m_board[i][4] << "|" << TTT.m_board[i][5] << "|" << TTT.m_board[i][6] << "\n";
    }
    return stream;
}
