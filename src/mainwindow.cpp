// Qt includes
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "about.h"
#include "help.h"

#include "map"
#include "QFileDialog"
#include "QFile"
#include "QString"
#include "QStandardItemModel"
#include "QAbstractItemModel"
#include "QString"
#include "QButtonGroup"
#include "QMessageBox"

// ROOT Includes
#include "TCanvas.h"
#include "TFrame.h"
#include "TH1F.h"
#include "TH1D.h"
#include "TBrowser.h"
#include "TFile.h"
#include "TTree.h"
#include "TString.h"
#include "TLegend.h"
#include "TTreeReader.h"
#include "TTreeReaderArray.h"

#include <TSystem.h>
#include <TStyle.h>
#include <TGaxis.h>
#include <TROOT.h>
#include <TMath.h>
#include <TString.h>

#include "cstring"
#include "bits/stdc++.h"
#include "cstdio"

#include "ReadCoefficients.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent),
                                          ui(new Ui::MainWindow)
{
    // setting the ui
    ui->setupUi(this);

    // Set the ROOT event timer, which allows ROOT to process its events
    // periodically. Should be done in the window you expect to be the last
    // one closed
    connect(&rootTimer, SIGNAL(timeout()),
            this, SLOT(handleROOTEvents()));
    rootTimer.start(20); // ms
    // 设置按键互斥
    QButtonGroup *buttonGround = new QButtonGroup();
    buttonGround->addButton(ui->checkGam);
    buttonGround->addButton(ui->checkNeu);
    buttonGround->setExclusive(true);

    // 设置窗口显示
    setWindowTitle("SpectrumCov");
    show();

    afilename = "";
    hSpec = 0;
    H_10 = "", Hp10 = "", X = "";

    // 设置菜单栏
    // 关于
    connect(ui->action_about,SIGNAL(triggered()),this,SLOT(AboutShow()));
    // 使用说明
    connect(ui->action_help,SIGNAL(triggered()),this,SLOT(HelpShow()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::AboutShow()
{
    About *ab=new About();
    ab->show();
}

void MainWindow::HelpShow()
{
    help *ab=new help();
    ab->show();
}

//------------------------------------
void MainWindow::on_change_file_clicked()
{
    QString curPath = QDir::currentPath(); //获取系统当前目录;
    QString dlgTitle = "open a file";      //对话框标题;
    const QString filter = "ROOT file (*.root*)";
    QString aFileName = QFileDialog::getOpenFileName(this, dlgTitle, curPath, filter);

    afilename = aFileName.toStdString();
}

/*! Force ROOT to process its events. */
void MainWindow::handleROOTEvents()
{
    gSystem->ProcessEvents();
    return;
}

void MainWindow::on_checkGam_clicked()
{
    ReadSpectrum("Log");
}

void MainWindow::on_checkNeu_clicked()
{
    ReadSpectrum("Log");
}
//----------------------------------------------------------------------------
//
void MainWindow::on_radioButtonH_10_clicked()
{
    if (!hSpec)
    {
        QMessageBox msgBox;
        msgBox.setText("请先打开待处理文件,输出能谱！");
        ui->radioButtonH_10->setCheckable(false);
        ui->radioButtonH_10->setCheckable(true);
        msgBox.exec();
        return;
    }
    ReadCoefficients *rp;
    vector<double> bins;
    vector<double> vals;
    if (ui->checkGam->isChecked())
    {
        rp = new ReadCoefficients("H*(10)_gamma_ConversionCoefficients.txt");
        rp->SetX("H^{*}(10)/{\\Phi}(pSv cm^{2})");
        rp->DrawGamConvCoeff("Log");
        bins = rp->Get_Bins();
        vals = rp->Get_Values();
        //! 打印数据
        string a_print = "# Photon energy(MeV)\tH*(10)/Φ(pSv cm2)";
        ui->textEdit->append(QString(a_print.c_str()));
        for (int i = 0; i < bins.size(); i++)
        {
            a_print = to_string(bins[i]) + "\t" + to_string(vals[i]);
            ui->textEdit->append(QString(a_print.c_str()));
        }
    }

    if (ui->checkNeu->isChecked())
    {
        rp = new ReadCoefficients("H*(10)_neutron_ConversionCoefficients.txt");
        rp->SetX("H^{*}(10)/{\\Phi}(pSv cm^{2})");
        rp->DrawNeuConvCoeff();
        bins = rp->Get_Bins();
        vals = rp->Get_Values();
        //! 打印数据
        string a_print = "# Neutron energy(eV)\tH*(10)/Φ(pSv cm2)";
        ui->textEdit->append(QString(a_print.c_str()));
        for (int i = 0; i < bins.size(); i++)
        {
            if (i != bins.size() - 1)
            {
                a_print = to_string(bins[i]) + "\t" + to_string(vals[i]);
                ui->textEdit->append(QString(a_print.c_str()));
            }
            else
            {
                a_print = to_string(bins[i]);
                ui->textEdit->append(QString(a_print.c_str()));
            }
        }
    }

    //! 计算转换量
    double dose = 0;
    for (int i = 1; i < hSpec->GetSize(); i++)
    {
        double xx = hSpec->GetBinCenter(i);
        if (ui->checkNeu->isChecked())
            xx = xx * 1e6;
        double yy = hSpec->GetBinContent(i);

        double val = 0;
        for (int j = 0; j < int(bins.size() - 1); j++)
        {
            /* code */
            if (xx >= bins[j] && xx < bins[j + 1])
            {
                val = vals[j] + (vals[j + 1] - vals[j]) / (log(bins[j + 1]) - log(bins[j])) * (log(xx) - log(bins[j]));
                dose += (yy * val); // Area 面积为cm2
                break;
            }
        }
    }

    double rms = 1. / sqrt(hSpec->GetEntries());
    H_10 = "周围剂量当量H*(10)：" + to_string(dose) + "(pSv/s)\t统计误差：" + to_string(rms);
}
//----------------------------------------------------------------------------
//
void MainWindow::on_radioButtonHp10_clicked()
{
    if (!hSpec)
    {
        QMessageBox msgBox;
        msgBox.setText("请先打开待处理文件,输出能谱！");
        ui->radioButtonHp10->setCheckable(false);
        ui->radioButtonHp10->setCheckable(true);
        msgBox.exec();
        return;
    }
    ReadCoefficients *rp;
    vector<double> bins;
    vector<double> vals;
    if (ui->checkGam->isChecked())
    {
        rp = new ReadCoefficients("Hp(10)_gamma_ConversionCoefficients.txt");
        rp->SetX("H_{p}(10)/{\\Phi}(pSv cm^{2})");
        rp->DrawGamConvCoeff("Log");
        bins = rp->Get_Bins();
        vals = rp->Get_Values();
        //! 打印数据
        string a_print = "# Photon energy(MeV)\tHp(10,0°)/Φ(pGy cm2)";
        ui->textEdit->append(QString(a_print.c_str()));
        for (int i = 0; i < bins.size(); i++)
        {
            a_print = to_string(bins[i]) + "\t" + to_string(vals[i]);
            ui->textEdit->append(QString(a_print.c_str()));
        }
    }

    if (ui->checkNeu->isChecked())
    {
        rp = new ReadCoefficients("Hp(10)_neutron_ConversionCoefficients.txt");
        rp->SetX("H_{p}(10)/{\\Phi}(pSv cm^{2})");
        rp->DrawNeuConvCoeff();
        bins = rp->Get_Bins();
        vals = rp->Get_Values();
        //! 打印数据
        string a_print = "# Neutron energy(eV)\tHp(10,0°)/Φ(pGy cm2)";
        ui->textEdit->append(QString(a_print.c_str()));
        for (int i = 0; i < bins.size(); i++)
        {
            if (i != bins.size() - 1)
            {
                a_print = to_string(bins[i]) + "\t" + to_string(vals[i]);
                ui->textEdit->append(QString(a_print.c_str()));
            }
            else
            {
                a_print = to_string(bins[i]);
                ui->textEdit->append(QString(a_print.c_str()));
            }
        }
    }
    //! 计算转换量
    double dose = 0;
    for (int i = 1; i < hSpec->GetSize(); i++)
    {
        double xx = hSpec->GetBinCenter(i);
        if (ui->checkNeu->isChecked())
            xx = xx * 1e6;
        double yy = hSpec->GetBinContent(i);

        double val = 0;
        for (int j = 0; j < int(bins.size() - 1); j++)
        {
            /* code */
            if (xx >= bins[j] && xx < bins[j + 1])
            {
                val = vals[j] + (vals[j + 1] - vals[j]) / (log(bins[j + 1]) - log(bins[j])) * (log(xx) - log(bins[j]));
                dose += (yy * val); // Area 面积为cm2
                break;
            }
        }
    }

    double rms = 1. / sqrt(hSpec->GetEntries());
    Hp10 = "个人剂量当量Hp(10,0)：" + to_string(dose) + "(pSv/s)\t统计误差：" + to_string(rms);
}

void MainWindow::on_radioButtonX_clicked()
{
    if (!hSpec)
    {
        QMessageBox msgBox;
        msgBox.setText("请先打开待处理文件,输出能谱！");
        ui->radioButtonX->setCheckable(false);
        ui->radioButtonX->setCheckable(true);
        msgBox.exec();
        return;
    }
    ReadCoefficients *rp;
    vector<double> bins;
    vector<double> vals;
    if (ui->checkGam->isChecked())
    {
        rp = new ReadCoefficients("Exposure_gamma_ConversionCoefficients.txt");
        rp->SetX(TString::Format("X/{\\Phi}(pGy cm^{2})"));
        rp->DrawGamConvCoeff("Log");
        bins = rp->Get_Bins();
        vals = rp->Get_Values();
        //! 打印数据
        string a_print = "# Photon energy(MeV)\tHp(10,0°)/Φ(pGy cm2)";
        ui->textEdit->append(QString(a_print.c_str()));
        for (int i = 0; i < bins.size(); i++)
        {
            a_print = to_string(bins[i]) + "\t" + to_string(vals[i]);
            ui->textEdit->append(QString(a_print.c_str()));
        }
    }

    if (ui->checkNeu->isChecked())
    {
        QMessageBox msgBox;
        msgBox.setText("中子暂无照射量转换系数！");
        ui->radioButtonX->setCheckable(false);
        ui->radioButtonX->setCheckable(true);
        ui->checkNeu->setCheckable(false);
        ui->checkNeu->setCheckable(true);
        msgBox.exec();
        return;

        // rp = new ReadCoefficients("Hp(10)_neutron_ConversionCoefficients.txt");
        // rp->DrawNeuConvCoeff();
        // bins = rp->Get_Bins();
        // vals = rp->Get_Values();
        // //! 打印数据
        // string a_print = "# Neutron energy(eV)\tHp(10,0°)/Φ(Gy cm2)";
        // ui->textEdit->append(QString(a_print.c_str()));
        // for (int i = 0; i < bins.size(); i++)
        // {
        //     if (i != bins.size() - 1)
        //     {
        //         a_print = to_string(bins[i]) + "\t" + to_string(vals[i]);
        //         ui->textEdit->append(QString(a_print.c_str()));
        //     }
        //     else
        //     {
        //         a_print = to_string(bins[i]);
        //         ui->textEdit->append(QString(a_print.c_str()));
        //     }
        // }
    }
    //! 计算转换量
    double dose = 0;
    for (int i = 1; i < hSpec->GetSize(); i++)
    {
        double xx = hSpec->GetBinCenter(i);
        if (ui->checkNeu->isChecked())
            xx = xx * 1e6;
        double yy = hSpec->GetBinContent(i);

        double val = 0;
        for (int j = 0; j < int(bins.size() - 1); j++)
        {
            /* code */
            if (xx >= bins[j] && xx < bins[j + 1])
            {
                val = vals[j] + (vals[j + 1] - vals[j]) / (log(bins[j + 1]) - log(bins[j])) * (log(xx) - log(bins[j]));
                dose += (yy * val); // Area 面积为cm2
                break;
            }
        }
    }

    double rms = 1. / sqrt(hSpec->GetEntries());
    X = "照射量X(空气吸收剂量Gy/s)：" + to_string(dose) + "(pGy/s)\t统计误差：" + to_string(rms);
}

//----------------------------------------------------------------------------
//
// 计算照射量
//

void MainWindow::ReadSpectrum(string AA = "Log")
{
    //-----------------------------
    //读入能谱数据
    // 读入文件
    TFile *f = new TFile(afilename.c_str());

    TTreeReader fReader("Det", f); //! the tree reader
    // Readers to access the data (delete the ones you do not need).
    TTreeReaderArray<Char_t> SDName = {fReader, "SDName"};
    TTreeReaderArray<Char_t> PName = {fReader, "PName"};
    // TTreeReaderArray<Char_t> SDName(fReader, "SDName"); //! 另一种写法
    TTreeReaderValue<Int_t> CopyNumberID = {fReader, "CopyNumberID"};
    // TTreeReaderValue<Int_t> MotherCopyNumberID = {fReader, "MotherCopyNumberID"};
    TTreeReaderValue<Int_t> EventID = {fReader, "EventID"};
    TTreeReaderValue<Int_t> ParentID = {fReader, "ParentID"};
    TTreeReaderValue<Int_t> TrackID = {fReader, "TrackID"};
    TTreeReaderValue<Int_t> StepID = {fReader, "StepID"};
    TTreeReaderValue<Double_t> Edep = {fReader, "Edep"};
    TTreeReaderValue<Double_t> PosX = {fReader, "PosX"};
    TTreeReaderValue<Double_t> PosY = {fReader, "PosY"};
    TTreeReaderValue<Double_t> PosZ = {fReader, "PosZ"};
    TTreeReaderValue<Double_t> GlobalT = {fReader, "GlobalT"};
    TTreeReaderValue<Double_t> LocalT = {fReader, "LocalT"};
    TTreeReaderValue<Double_t> ProperT = {fReader, "ProperT"};
    TTreeReaderValue<Double_t> Ekin = {fReader, "Ekin"};
    TTreeReaderValue<Double_t> Velocity = {fReader, "Velocity"};
    TTreeReaderValue<Double_t> MomentX = {fReader, "MomentX"};
    TTreeReaderValue<Double_t> MomentY = {fReader, "MomentY"};
    TTreeReaderValue<Double_t> MomentZ = {fReader, "MomentZ"};
    TTreeReaderArray<Char_t> ProC = {fReader, "ProC"};

    if (AA == "Lin")
    {
        // ?设置坐标
        // 定义直方图
        TH1D *h1 = new TH1D("Ekin", "Ekin", 1000, 1e-3, 20);

        // 填充直方图
        while (fReader.Next())
        {
            if (ui->checkGam->isChecked())
            {
                if (PName[0] == 'g' && PName[1] == 'a')
                {
                    h1->Fill(*Ekin);
                }
            }

            if (ui->checkNeu->isChecked())
            {
                if (PName[0] == 'n' && PName[5] == 'o')
                {
                    h1->Fill(*Ekin);
                }
            }
        }

        int color = 25;
        double width_ = 0.4;

        string outfile = "#E(MeV)\tPhi(cm^-2)";
        ui->textEdit->append(QString(outfile.c_str()));

        for (int i = 1; i <= 1000; i++)
        {
            double xx = h1->GetBinCenter(i);
            double yy = h1->GetBinContent(i);
            outfile = to_string(xx) + "\t" + to_string(yy);
            ui->textEdit->append(QString(outfile.c_str()));
        }

        //--------------------------
        // 绘制能谱
        // h1->Scale(1. / (5e8));
        // h1->SetLineColor(kRed);
        if (ui->checkGam->isChecked())
            h1->SetTitle("Gamma Energy Spectrum;E(MeV);{\\Phi}(cm^{-2})"); //设置表头与坐标轴
        if (ui->checkNeu->isChecked())
            h1->SetTitle("Neutron Energy Spectrum;E(MeV);{\\Phi}(cm^{-2})"); //设置表头与坐标轴

        h1->GetXaxis()->SetTitleOffset(1.2);

        //! 画candlex Error Bar图
        // h1->SetBarWidth(width_+=0.05);
        // h1->SetBarOffset(0.25);
        // h1->SetLineColor(kRed);
        // h1->SetFillColor(kRed);
        if (h1->GetEntries())
        {
            gStyle->SetOptStat(0); //右上角统计
            TCanvas *cc;
            if (ui->checkGam->isChecked())
            {
                cc = new TCanvas("gamma_spectrum", "gamma_spectrum", 600, 500);
            }
            if (ui->checkNeu->isChecked())
            {
                cc = new TCanvas("neutron_spectrum", "neutron_spectrum", 600, 500);
            }
            cc->SetLogx();
            cc->SetLogy();
            // cc->SetGrid();
            cc->SetTicks();
            h1->Draw("][");
            hSpec = (TH1D *)h1->Clone();
        }
        else
        {
            QMessageBox msgBox;
            msgBox.setText("未探测到此粒子");
            ui->radioButtonX->setCheckable(false);
            ui->radioButtonX->setCheckable(true);
            msgBox.exec();
            return;
        }
        // TString tname = "candlex";
        // h1->DrawCopy(tname);
    }
    else if (AA == "Log")
    {
        // ?设置对数坐标
        //
        //--------对数坐标变化--------
        double low = 1.0e-3;
        double up = 2e1;
        double nbin = 38;
        Double_t xAxis[39];

        for (int i = 0; i <= nbin; i++)
        {
            double val_bin = low * std::pow(10., i * std::log10(up / low) / nbin);
            double exp_10 = 4. - int(std::log10(val_bin));
            double factor = std::pow(10., exp_10);
            val_bin = int(factor * val_bin) / factor;
            xAxis[i] = val_bin;
        }

        // 定义直方图
        TH1D *h1 = new TH1D("Ekin", "Ekin", nbin, xAxis);

        // 填充直方图
        while (fReader.Next())
        {
            if (ui->checkGam->isChecked())
            {
                if (PName[0] == 'g' && PName[1] == 'a')
                {
                    h1->Fill(*Ekin);
                }
            }

            if (ui->checkNeu->isChecked())
            {
                if (PName[0] == 'n' && PName[5] == 'o')
                {
                    h1->Fill(*Ekin);
                }
            }
        }
        double width_ = 0.4;

        string outfile = "#E(MeV)\tPhi(cm^-2)";
        ui->textEdit->append(QString(outfile.c_str()));

        for (int i = 1; i <= nbin; i++)
        {
            double xx = h1->GetBinCenter(i);
            double yy = h1->GetBinContent(i);
            outfile = to_string(xx) + "\t" + to_string(yy);
            ui->textEdit->append(QString(outfile.c_str()));
        }

        //--------------------------
        // 绘制能谱
        // h1->Scale(1. / (5e8));
        // h1->SetLineColor(kRed);
        if (ui->checkGam->isChecked())
            h1->SetTitle("Gamma Energy Spectrum;E(MeV);{\\Phi}(cm^{-2})"); //设置表头与坐标轴
        if (ui->checkNeu->isChecked())
            h1->SetTitle("Neutron Energy Spectrum;E(MeV);{\\Phi}(cm^{-2})"); //设置表头与坐标轴
        h1->GetXaxis()->SetTitleOffset(1.2);

        //! 画candlex Error Bar图
        // h1->SetBarWidth(width_+=0.05);
        // h1->SetBarOffset(0.25);
        // h1->SetLineColor(kRed);
        // h1->SetFillColor(kRed);
        if (h1->GetEntries())
        {
            gStyle->SetOptStat(0); //右上角统计
            TCanvas *cc;
            if (ui->checkGam->isChecked())
            {
                cc = new TCanvas("gamma_spectrum", "gamma_spectrum", 600, 500);
            }
            if (ui->checkNeu->isChecked())
            {
                cc = new TCanvas("neutron_spectrum", "neutron_spectrum", 600, 500);
            }
            cc->SetLogx();
            cc->SetLogy();
            // cc->SetGrid();
            cc->SetTicks();

            h1->Draw("][");
            hSpec = (TH1D *)h1->Clone();
        }
        else
        {
            QMessageBox msgBox;
            msgBox.setText("未探测到此粒子");
            ui->radioButtonX->setCheckable(false);
            ui->radioButtonX->setCheckable(true);
            msgBox.exec();
            return;
        }
        // TString tname = "candlex";
        // h1->DrawCopy(tname);
    }
}

void MainWindow::on_Cal_button_clicked()
{
    string pname;
    if (ui->checkGam->isChecked())
    {
        pname = "gamma ";
        if (ui->radioButtonH_10->isChecked())
        {
            ui->textEdit->append(QString((pname + H_10).c_str()));
        }
        if (ui->radioButtonHp10->isChecked())
        {
            ui->textEdit->append(QString((pname + Hp10).c_str()));
        }
        if (ui->radioButtonX->isChecked())
        {
            ui->textEdit->append(QString((pname + X).c_str()));
        }
    }

    if (ui->checkNeu->isChecked())
    {
        pname = "neutron ";
        if (ui->radioButtonH_10->isChecked())
        {
            ui->textEdit->append(QString((pname + H_10).c_str()));
        }
        if (ui->radioButtonHp10->isChecked())
        {
            ui->textEdit->append(QString((pname + Hp10).c_str()));
        }
        if (ui->radioButtonX->isChecked())
        {
            ui->textEdit->append(QString((pname + X).c_str()));
        }
    }
}
//----------------------------------------------------------------------------
//

void MainWindow::on_save_file_clicked()
{
    QString curPath = QDir::currentPath();    //获取系统当前目录;
    QString dlgTitle = "save a file";         //对话框标题;
    QString filter = "text(*.txt);;all(*.*)"; //文件过滤器
    QString aFileName = QFileDialog::getSaveFileName(this, dlgTitle, curPath, filter);

    if (aFileName.isEmpty())
    {
        return;
    }
    aFileName += ".txt";
    saveToFile(aFileName);
}
//----------------------------------------------------------------------------
//
bool MainWindow::saveToFile(const QString &aFileName)
{
    QFile aFile(aFileName);
    if (!aFile.open(QIODevice::WriteOnly | QIODevice::Text))
        return false;
    QString str = ui->textEdit->toPlainText(); //整个内容作为字符串
    QByteArray strBytes = str.toUtf8();        //转换为字节数组
    aFile.write(strBytes, strBytes.length());  //写入文件
    aFile.close();
    return true;
}
