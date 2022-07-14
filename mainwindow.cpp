#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  ui->actionEasy->setChecked(true);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::on_actionEasy_triggered() {
  ui->centralwidget->TTT.changeGameDifficulty(0);
  ui->actionMedium->setChecked(false);
  ui->actionHard->setChecked(false);
}

void MainWindow::on_actionMedium_triggered() {
  ui->centralwidget->TTT.changeGameDifficulty(1);
  ui->actionEasy->setChecked(false);
  ui->actionHard->setChecked(false);
}

void MainWindow::on_actionHard_triggered() {
  ui->centralwidget->TTT.changeGameDifficulty(2);
  ui->actionEasy->setChecked(false);
  ui->actionMedium->setChecked(false);
}