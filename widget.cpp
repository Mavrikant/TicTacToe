#include "widget.h"
#include "tictactoecore.h"
#include "ui_widget.h"
#include <QDebug>
#include <chrono>
#include <thread>

using namespace std::literals;

Widget::Widget(QWidget *parent) : QWidget(parent), ui(new Ui::Widget)
{
    ui->setupUi(this);
    pushButtons[0] = ui->button_1_1;
    pushButtons[1] = ui->button_1_2;
    pushButtons[2] = ui->button_1_3;
    pushButtons[3] = ui->button_1_4;
    pushButtons[4] = ui->button_1_5;
    pushButtons[5] = ui->button_1_6;
    pushButtons[6] = ui->button_1_7;
    pushButtons[7] = ui->button_2_1;
    pushButtons[8] = ui->button_2_2;
    pushButtons[9] = ui->button_2_3;
    pushButtons[10] = ui->button_2_4;
    pushButtons[11] = ui->button_2_5;
    pushButtons[12] = ui->button_2_6;
    pushButtons[13] = ui->button_2_7;
    pushButtons[14] = ui->button_3_1;
    pushButtons[15] = ui->button_3_2;
    pushButtons[16] = ui->button_3_3;
    pushButtons[17] = ui->button_3_4;
    pushButtons[18] = ui->button_3_5;
    pushButtons[19] = ui->button_3_6;
    pushButtons[20] = ui->button_3_7;
    pushButtons[21] = ui->button_4_1;
    pushButtons[22] = ui->button_4_2;
    pushButtons[23] = ui->button_4_3;
    pushButtons[24] = ui->button_4_4;
    pushButtons[25] = ui->button_4_5;
    pushButtons[26] = ui->button_4_6;
    pushButtons[27] = ui->button_4_7;
    pushButtons[28] = ui->button_5_1;
    pushButtons[29] = ui->button_5_2;
    pushButtons[30] = ui->button_5_3;
    pushButtons[31] = ui->button_5_4;
    pushButtons[32] = ui->button_5_5;
    pushButtons[33] = ui->button_5_6;
    pushButtons[34] = ui->button_5_7;
    pushButtons[35] = ui->button_6_1;
    pushButtons[36] = ui->button_6_2;
    pushButtons[37] = ui->button_6_3;
    pushButtons[38] = ui->button_6_4;
    pushButtons[39] = ui->button_6_5;
    pushButtons[40] = ui->button_6_6;
    pushButtons[41] = ui->button_6_7;
    pushButtons[42] = ui->button_7_1;
    pushButtons[43] = ui->button_7_2;
    pushButtons[44] = ui->button_7_3;
    pushButtons[45] = ui->button_7_4;
    pushButtons[46] = ui->button_7_5;
    pushButtons[47] = ui->button_7_6;
    pushButtons[48] = ui->button_7_7;

    for (int i = 0; i < 49; ++i)
    {
        connect(pushButtons[i], SIGNAL(clicked()), this, SLOT(userPlayed()));
    }
    updateGUI();
}

Widget::~Widget() { delete ui; }

void Widget::updateGUI()
{
    for (int i = 0; i < 7; ++i)
    {
        for (int j = 0; j < 7; ++j)
        {
            QPushButton *button = pushButtons[i * 7 + j];
            button->setText(QString(TTT.m_board[i][j]));

            switch (TTT.m_board[i][j])
            {
            case 'X':
                button->setDisabled(true);
                button->setStyleSheet("background-color: rgb(252, 175, 62);color: red;");
                break;
            case 'O':
                button->setDisabled(true);
                button->setStyleSheet("background-color: rgb(252, 175, 62);color: blue;");
                break;
            default:
                button->setEnabled(true);
                button->setStyleSheet("background-color: rgb(252, 175, 62);");
                break;
            }
        }
    }
    ui->labelScorePlayer->setStyleSheet("color: red;");
    ui->labelScoreTie->setStyleSheet("color: orange;");
    ui->labelScoreComputer->setStyleSheet("color: blue;");

    ui->labelScorePlayer->setNum(m_score.player);
    ui->labelScoreTie->setNum(m_score.tie);
    ui->labelScoreComputer->setNum(m_score.computer);

    this->repaint();
}

void Widget::gameFinishedPlayerWon()
{
    m_score.player++;
    ui->labelScorePlayer->setNum(m_score.player);
    ui->labelScorePlayer->setStyleSheet("color: red;font-weight:bold;font-size:30px;");
    this->repaint();
    std::this_thread::sleep_for(1000ms);
    TTT.clearBoard();
    updateGUI();
    // todo add animation
    // todo add sound
}

void Widget::gameFinishedTieWon()
{
    m_score.tie++;
    ui->labelScoreTie->setNum(m_score.tie);
    ui->labelScoreTie->setStyleSheet("color: orange;font-weight:bold;font-size:30px;");
    this->repaint();
    std::this_thread::sleep_for(1000ms);
    TTT.clearBoard();
    updateGUI();
    // todo add animation
    // todo add sound
}

void Widget::gameFinishedComputerWon()
{
    m_score.computer++;
    ui->labelScoreComputer->setNum(m_score.computer);
    ui->labelScoreComputer->setStyleSheet("color: blue;font-weight:bold;font-size:30px;");
    this->repaint();
    std::this_thread::sleep_for(1000ms);
    TTT.clearBoard();
    updateGUI();
    // todo add animation
    // todo add sound
}

void Widget::userPlayed() // TODO too long
{
    {
        int i = sender()->objectName().split("_")[1].toInt();
        int j = sender()->objectName().split("_")[2].toInt();
        TTT.m_board[i - 1][j - 1] = 'X';
    }
    updateGUI();

    switch (TTT.gameStatus())
    {
    case gameState::FINISHED:
        gameFinishedPlayerWon();
        break;
    case gameState::TIE:
        gameFinishedTieWon();
        break;
    case gameState::CONTINUES:
        break;
    }

    TTT.computerPlay();
    updateGUI();
    switch (TTT.gameStatus())
    {
    case gameState::FINISHED:
        gameFinishedComputerWon();
        break;
    case gameState::TIE:
        gameFinishedTieWon();
        break;
    case gameState::CONTINUES:
        break;
    }
    updateGUI();
}
