#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_botonNuevaPartida_clicked()
{
    mywindownuevapartida = new windownuevapartida();
    mywindownuevapartida->show();
    this->hide();
}

void MainWindow::on_toolButton_2_clicked()
{
    QString directory = QFileDialog::getOpenFileName(this, "Seleccione el archivo que desea cargar", "/", NULL);
    qDebug() << directory;
    if(!directory.isEmpty()){
        //Primero carga del archivo todas las estructuras del juego
        mywindownuevapartida = new windownuevapartida();
        mywindownuevapartida->show();
        this->hide();
    }
}
