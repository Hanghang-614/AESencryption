#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QPushButton>
#include<QRadioButton>
#include<QDebug>
#include<QFileDialog>
#include<mode.h>
#include<aes.h>
#include<QIODevice>
#include <QLineEdit>
#include<QProgressBar>
#include<QTimerEvent>
#include<string>
#include<QLineEdit>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->mode = new Mode(this);
    setFixedSize(600,400);//固定窗口大小
    setWindowIcon(QIcon(":/res/0.png"));//设置图标
    setWindowTitle("文件加密");
    ui->progressBar->setVisible(false);
    ui->progressBar->setRange(0,0);
    ui->lineEdit->setEchoMode(QLineEdit::Password);
    ui->lineEdit->setMaxLength(16);

    connect(ui->radioButton1,&QRadioButton::clicked,this,&MainWindow::change_mode1);
    connect(ui->radioButton2,&QRadioButton::clicked,this,&MainWindow::change_mode2);
    connect(ui->radioButton3,&QRadioButton::clicked,this,&MainWindow::change_mode3);
    connect(ui->fileButton,&QPushButton::clicked,this,&MainWindow::road_Read);
    connect(ui->lineEdit,&QLineEdit::editingFinished,this,&MainWindow::key_enter);
    connect(ui->enfilebt,&QPushButton::clicked,this,&MainWindow::road_Read2);
    //connect(ui->passwordButton,&QPushButton::clicked,this,&MainWindow::read_Password);




    connect(ui->enbt,&QPushButton::clicked,this,&MainWindow::en);
    connect(ui->deenbt,&QPushButton::clicked,this,&MainWindow::deen);
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::change_mode1(){
    select = 1;
    qDebug()<<"mode="<<select;
}
void MainWindow::change_mode2(){
    select = 2;
    qDebug()<<"mode="<<select;
}
void MainWindow::change_mode3(){
    select = 3;
    qDebug()<<"mode="<<select;
}
void MainWindow::key_enter(){
    key_ = ui->lineEdit->text();
    ui->lineEdit->clear();
    qDebug()<<key_;
}
void MainWindow::en(){
    startTimer(1000);
    ui->progressBar->setVisible(true);
    QByteArray ba = key_.toLatin1();
    char *key = ba.data();
    QFile file(path);
    file.open(QIODevice::ReadOnly);
    QByteArray array = file.readAll();
    char *plain = array.data();
    file.close();

    if(select==1){
    mode->ECB(plain,key);
    }
    if(select==2){
    mode->CBC(plain,key);
    }
    if(select==3){
    mode->CTR(plain,key);
    }

    QFile File(path_cipher);
    File.open(QIODevice::WriteOnly);
    File.write(plain);
    File.close();

    File.open(QIODevice::ReadOnly);
    QByteArray T = File.readAll();
    ui->textEdit_2->setText(T);
    File.close();
}
void MainWindow::deen(){
    startTimer(1000);
    ui->progressBar->setVisible(true);
    QByteArray ba = key_.toLatin1();
    char *key = ba.data();
    QFile file(path_cipher);
    file.open(QIODevice::ReadOnly);
    QByteArray array = file.readAll();
    char *plain = array.data();
    file.close();
    int len = strlen(plain);
    if(select==1){
    mode->deECB(plain,key,len);}
    if(select==2){
    mode->deCBC(plain,key,len);}
    if(select==3){
    mode->deCTR(plain,key,len);}
    file.open(QIODevice::WriteOnly);
    file.write(plain);
    file.close();
    file.open(QIODevice::ReadOnly);
    QByteArray T = file.readAll();
    ui->textEdit_2->setText(T);
    file.close();
}
void MainWindow::road_Read(){
    path =QFileDialog::getOpenFileName(this,"打开文件","C:\\Users\\Hang\\Desktop\\");
    //将路径放入LineEdit
    ui->pathEdit->setText(path);

    //读取内容 放入TextEdit
    //QFile默认支持的格式是utf-8
    QFile File(path);
    File.open(QIODevice::ReadOnly);
    QByteArray T = File.readAll();
    ui->textEdit->setText(T);
    File.close();
}
void MainWindow::road_Read2(){
    path_cipher =QFileDialog::getOpenFileName(this,"打开文件","C:\\Users\\Hang\\Desktop\\");
    ui->lineEdit_2->setText(path_cipher);
    QFile File(path_cipher);
    File.open(QIODevice::ReadOnly);
    QByteArray T = File.readAll();
    ui->textEdit_2->setText(T);
    File.close();
}
void MainWindow::read_Password(){
    QString road =QFileDialog::getOpenFileName(this,"打开文件","C:\\Users\\Hang\\Desktop\\");
    QFile File(road);
    File.open(QIODevice::ReadOnly);
    QByteArray a = File.readAll();
    key_ = QString(a);
}
void MainWindow::timerEvent(QTimerEvent *){
    ui->progressBar->setVisible(false);
}
void MainWindow::cipherText(){
    QString p =QFileDialog::getOpenFileName(this,"打开文件","C:\\Users\\Hang\\Desktop\\");
    QFile File(p);
    File.open(QIODevice::ReadOnly);
    QByteArray a = File.readAll();
    key_ = QString(a);
}
