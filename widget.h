#ifndef WIDGET_H
#define WIDGET_H

#include "tictactoecore.h"
#include <QPushButton>
#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui
{
class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

  public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    TicTacToeCore TTT;
    void resetScore()
    {
        m_score = {0};
        TTT.clearBoard();
        updateGUI();
    }

  private:
    struct score
    {
        int player = 0;
        int tie = 0;
        int computer = 0;
    } m_score;
    Ui::Widget *ui;

    QPushButton *pushButtons[7 * 7];
    void updateGUI();
    void gameFinishedPlayerWon();
    void gameFinishedTieWon();
    void gameFinishedComputerWon();

  private slots:
    void userPlayed();
};
#endif // WIDGET_H
