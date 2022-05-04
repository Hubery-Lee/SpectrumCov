/*
 * @Description: 
 * @version: 
 * @Author: Hubery-Lee
 * @E-mail: hrbeulh@126.com
 * @Date: 2021-12-13 16:01:12
 * @LastEditTime: 2021-12-14 11:08:32
 * @LastEditors: Hubery-Lee
 */
#ifndef ReadCoefficients_H
#define ReadCoefficients_H

#include "TH1D.h"
#include "fstream"
#include "cctype"
#include "vector"
#include "sstream"
#include "iostream"
#include "string"
#include "TString.h"

using namespace std;

class ReadCoefficients
{
public:
    ReadCoefficients(string CoefName);
    ~ ReadCoefficients();

    // methods
    void DrawGamConvCoeff(string AType);
    void DrawNeuConvCoeff();
    inline void SetX(TString ytitle){Ytitle=ytitle;}

    vector<double> Get_Bins(){return bins;}
    vector<double> Get_Values(){return vals;}

private:
    // methods
    void ReadGamConvCoeff();
    void ReadNeuConvCoeff();

    // parameters
    string Coefname;
    vector<double>bins;
    vector<double>vals;

    TString Ytitle; 
};

#endif // ReadCoefficients_H
