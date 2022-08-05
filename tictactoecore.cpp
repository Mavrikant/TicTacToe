#include "tictactoecore.h"
#include <QDebug>
#include <algorithm>
#include <chrono>
#include <thread>

TicTacToeCore::TicTacToeCore() { clearBoard(); }

void TicTacToeCore::computerPlay()
{
    std::this_thread::sleep_for(std::chrono::microseconds((3 - m_gameDifficulty) / 3 * 1000000));
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
    float alpha = -INFINITY;
    float beta = +INFINITY;
    for (int i = 0; i < 7; ++i)
    {
        for (int j = 0; j < 7; ++j)
        {
            if (m_board[i][j] == ' ')
            {
                m_board[i][j] = 'O';
                int res;
                if (res = minimax(false, 4, alpha, beta), value < res)
                {
                    value = res;
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
    float value = -INFINITY;
    int a = 0;
    int b = 0;
    float alpha = -INFINITY;
    float beta = +INFINITY;
    for (int i = 0; i < 7; ++i)
    {
        for (int j = 0; j < 7; ++j)
        {
            if (m_board[i][j] == ' ')
            {
                m_board[i][j] = 'O';
                float res;
                if (res = minimax(false, 10, alpha, beta), value < res)
                {
                    value = res;
                    a = i;
                    b = j;
                }
                m_board[i][j] = ' ';
            }
        }
    }
    m_board[a][b] = 'O';
}

float TicTacToeCore::minimax(bool maximizingPlayer, int dept, float alpha, float beta)
{
    gameState gameresult = gameStatus(m_board);

    if (gameresult == gameState::FINISHED)
    {
        return (maximizingPlayer ? -80 : +80) - dept;
    }
    else if (gameresult == gameState::TIE)
    {
        return (maximizingPlayer ? -30 : +30) - dept;
    }
    else if (dept == 0)
    {
        return (maximizingPlayer ? -10 : +10) - dept;
    }

    if (maximizingPlayer) // Computer
    {
        float value = -99;
        for (int i = 0; i < 7; ++i)
        {
            for (int j = 0; j < 7; ++j)
            {
                if (m_board[i][j] == ' ')
                {
                    m_board[i][j] = 'O';
                    value = std::max(value, minimax(false, dept - 1, alpha, beta));
                    m_board[i][j] = ' ';
                    if (value > alpha)
                    {
                        alpha = value;
                    }
                    if (alpha >= beta)
                    {
                        i = 99;
                        j = 99;
                    };
                }
            }
        }
        return alpha;
    }
    else // Human
    {
        float value = +99;
        for (int i = 0; i < 7; ++i)
        {
            for (int j = 0; j < 7; ++j)
            {
                if (m_board[i][j] == ' ')
                {
                    m_board[i][j] = 'X';
                    value = std::min(value, minimax(true, dept - 1, alpha, beta));
                    m_board[i][j] = ' ';
                    if (value < beta)
                    {
                        beta = value;
                    }
                    if (alpha >= beta)
                    {
                        i = 99;
                        j = 99;
                    }
                }
            }
        }
        return beta;
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
