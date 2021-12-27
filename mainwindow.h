#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <mode.h>
#include<QString>
#include<QPainter>
#include<QWidget>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void road_Read();
    void road_Read2();
    void change_mode1();
    void change_mode2();
    void change_mode3();
    void key_enter();
    void en();
    void deen();
    void read_Password();
    void timerEvent(QTimerEvent *);
    void cipherText();


private:
    Mode * mode;
    Ui::MainWindow *ui;
    int select;
    QString path;
    QString path_cipher;
    QString key_;
};
#endif // MAINWINDOW_H
