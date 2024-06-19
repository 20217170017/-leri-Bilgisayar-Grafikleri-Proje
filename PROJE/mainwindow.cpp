#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    my3DWidget = new My3DWidget(this);
    setCentralWidget(my3DWidget);
}

MainWindow::~MainWindow()
{
    delete ui;
}
