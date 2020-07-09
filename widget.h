#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "tictactoecore.h"
#include <QPushButton>

QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    struct score
    {
        int player = 0;
        int tie = 0;
        int computer = 0;
    } m_score;
    Ui::Widget *ui;
    TicTacToeCore TTT;
    QPushButton *pushButtons[9];
    void updateGUI();
    void gameFinishedPlayerWon();
    void gameFinishedTieWon();
    void gameFinishedComputerWon();

private slots:
    void userPlayed();
};
#endif // WIDGET_H
