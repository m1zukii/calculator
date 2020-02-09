#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include<stack>
#include<vector>
#include<cmath>
#include <QMainWindow>
#include<stdlib.h>
#include<iostream>
#include<QMessageBox>
#include<exception>
using namespace std;
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QString getText();
    void setText(QString text);
    int getPriority(string opt);
    void calculate(stack<double> &opdStack,string opt);
    vector<string> prePossess(const char* str);
    double getNumber(string source) ;
    bool isMatch(const char* str);
    double calculator(char *exp) ;
private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_17_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_18_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_10_clicked();

    void on_pushButton_11_clicked();

    void on_pushButton_12_clicked();

    void on_pushButton_19_clicked();

    void on_pushButton_13_clicked();

    void on_pushButton_14_clicked();

    void on_pushButton_23_clicked();

    void on_pushButton_16_clicked();

    void on_pushButton_20_clicked();

    void on_pushButton_15_clicked();

    void on_pushButton_21_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
