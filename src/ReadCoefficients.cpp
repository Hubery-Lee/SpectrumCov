/*
 * @Description: 
 * @version: 
 * @Author: Hubery-Lee
 * @E-mail: hrbeulh@126.com
 * @Date: 2021-12-13 09:37:58
 * @LastEditTime: 2021-12-14 11:06:39
 * @LastEditors: Hubery-Lee
 */
#include "ReadCoefficients.h"
#include "fstream"
#include "cctype"
#include "vector"
#include "sstream"
#include "iostream"
#include "string"

using namespace std;

#include "QMessageBox"

#include "TH1D.h"
#include "TCanvas.h"
#include "TMath.h"
#include "TStyle.h"

ReadCoefficients::ReadCoefficients(/*string fName,*/string CoefName)
{
    Coefname= CoefName;
    Ytitle="";
    bins.clear();
    vals.clear();
}

ReadCoefficients::~ ReadCoefficients()
{

}
//----------------------------------------------------------------------------
//
void ReadCoefficients::ReadGamConvCoeff()
{
    //-----------------------------
    // 读入转换函数
    ifstream in(Coefname);

    if(!in.good())
    {
        QMessageBox msgBox;
        msgBox.setText("未找到转换系数文件！");
        msgBox.exec();
        return;
    }

    // bins.push_back(1e-3);
    double x = 0., y = 0.;

    std::string cbf; //读取注释
    char chd;        //注释标志符号

    while (!in.eof())
    {
        chd = in.peek();
        if (chd == '#' || chd == 0x20 || chd == 0xA)
        {                     //修复空行带来的bug,空行可能是" "或者"\n"
            getline(in, cbf); //一次读取一行
        }else if (in.eof())
        {
            break;
        }else
        {
            in >> x >> y;
            bins.push_back(x);
            vals.push_back(y);
        }
    }

    in.close();
}

//----------------------------------------------------------------------------
//
// 画出转换系数
// Lin 线性坐标, Log 对数坐标
void ReadCoefficients::DrawGamConvCoeff(string AType="Log")
{
    gStyle->SetOptStat(0); 
    ReadGamConvCoeff();
    if (AType=="Log")
    {
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
        TH1D *histConversion = new TH1D("gamma conversion coefficients(Log)", "gamma conversion coefficients(Log)", nbin, xAxis);

        for (int i = 1; i <= nbin; i++)
        {
            double xx = histConversion->GetBinLowEdge(i);
            double yy = histConversion->GetBinContent(i);
            double val = 0;
            for (int j = 0; j < int(bins.size() - 1); j++)
            {
                /* code */
                if (xx >= bins[j] && xx < bins[j + 1])
                {
                    val = vals[j] + (vals[j + 1] - vals[j]) / (log(bins[j + 1]) - log(bins[j])) * (log(xx) - log(bins[j]));
                    histConversion->SetBinContent(i, val);
                    break;
                }
            }
        }

        TCanvas *c1 = new TCanvas();
        c1->SetLogx();
        c1->SetLogy();
        c1->SetTicks();
        histConversion->SetXTitle("Photon energy(MeV)");
        // histConversion->SetYTitle("H^{*}(10)/{\\Phi}(pSv cm^{2})");
        histConversion->SetYTitle(Ytitle);
        // histConversion->SetFillColor(kBlue);
        histConversion->Draw("][");
    }
    else if (AType=="Lin")
    {
        // 定义直方图
        TH1D *h1 = new TH1D("gamma conversion coefficients", "gamma conversion coefficients", 1000, 1e-3, 20);
        for (int i = 1; i <= 1000; i++)
        {
            // double xx = h1->GetBinCenter(i);
            double xx = h1->GetBinLowEdge(i);
            double yy = h1->GetBinContent(i);
            double val = 0;
            for (int j = 0; j < int(bins.size() - 1); j++)
            {
                /* code */
                if (xx >= bins[j] && xx < bins[j + 1])
                {
                    val = vals[j] + (vals[j + 1] - vals[j]) / (bins[j + 1] - bins[j]) * (xx - bins[j]);
                    // dose += yy * val; //Area 面积为cm2
                    h1->SetBinContent(i, val);
                    break;
                }
            }
        }
        TCanvas *c1 = new TCanvas();
        c1->SetLogx();
        c1->SetLogy();
        c1->SetTicks();
        h1->SetXTitle("Photon energy(MeV)");
        h1->SetYTitle(Ytitle);
        // h1->SetFillColor(kBlue);
        h1->Draw("][");
    }

}

//----------------------------------------------------------------------------
// 横坐标比纵坐标多个数
void ReadCoefficients::ReadNeuConvCoeff()
{
    //-----------------------------
    // 读入转换函数
    ifstream in(Coefname);
    if (!in.good())
    {
        QMessageBox msgBox;
        msgBox.setText("未找到转换系数文件！");
        msgBox.exec();
        return;
    }

    double x = 0., y = 0.;

    std::string cbf; //读取注释
    char chd;        //注释标志符号

    while (!in.eof())
    {
        chd = in.peek();
        if (chd == '#' || chd == 0x20 || chd == 0xA)
        {                     //修复空行带来的bug,空行可能是" "或者"\n"
            getline(in, cbf); //一次读取一行
        }
        else if (in.eof())
        {
            break;
        }
        else
        {
            if (in >> x >> y)
            {
                bins.push_back(x);
                vals.push_back(y);
            }
            else 
            {
                in>>x;
                bins.push_back(x);
            }
        }
    }

    in.close();

}
//
// 画出转换系数
//
void ReadCoefficients::DrawNeuConvCoeff()
{
    ReadNeuConvCoeff();
    double *buffer = new double[bins.size()];
    //将vector转换为数组
    if (!bins.empty())
    {
        memcpy(buffer, &bins[0], bins.size() * sizeof(double));
    }

    TH1D *histConversion = new TH1D("neutron conversion coefficients(Log) ", "neutron conversion coefficients(Log)", int(vals.size()), buffer);

    for (int i = 1; i <=vals.size(); i++)
    {
        histConversion->SetBinContent(i, vals[i]);
    }

    TCanvas *c1 = new TCanvas();
    c1->SetLogy();
    c1->SetLogx();
    c1->SetTicks();
    histConversion->SetXTitle("Neutron energy(eV)");
    histConversion->SetYTitle(Ytitle);
    // histConversion->SetFillColor(kBlue);
    histConversion->Draw("][");
}
