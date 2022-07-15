#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui
{
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

  public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

  private slots:
    void on_actionEasy_triggered();
    void on_actionMedium_triggered();
    void on_actionHard_triggered();

    void on_actionReset_triggered();

    void on_actionBuild_Info_triggered();

  private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
