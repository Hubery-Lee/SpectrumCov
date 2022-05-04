/*
 * @Description: 
 * @version: 
 * @Author: Hubery-Lee
 * @E-mail: hrbeulh@126.com
 * @Date: 2021-12-11 12:47:49
 * @LastEditTime: 2021-12-13 22:44:38
 * @LastEditors: Hubery-Lee
 */
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStandardItemModel>
#include "TObject.h"

#include "TH1D.h"
#include "fstream"
#include "cctype"
#include "vector"
#include "sstream"
#include "iostream"
#include "string"

#include <QTimer>
namespace Ui {
class MainWindow;
}

using namespace std;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
     Ui::MainWindow *ui;

private slots:
     // Must be run on a timer - forces update of ROOT event loop
     void handleROOTEvents();

     void on_change_file_clicked();
     void on_checkGam_clicked();
     void on_checkNeu_clicked();
     void on_radioButtonH_10_clicked();
     void on_radioButtonHp10_clicked();
     void on_radioButtonX_clicked();
     void on_save_file_clicked();
     void on_Cal_button_clicked();

     void AboutShow();
     void HelpShow();

private:
    QTimer rootTimer;
    string afilename;
    TH1D *hSpec;
    string H_10,Hp10,X;//H*(10),Hp(10),X照射量
    // Copy/pasted from rootlogon.C - sets canvas, hist styles, etc
    void setROOTLogon();
    void ReadSpectrum(string AA);//AA表示坐标轴类型
    bool saveToFile(const QString &aFileName);
};

#endif // MAINWINDOW_H
