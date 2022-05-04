/*
 * @Description: 
 * @version: 
 * @Author: Hubery-Lee
 * @E-mail: hrbeulh@126.com
 * @Date: 2021-12-15 21:10:58
 * @LastEditTime: 2021-12-15 22:16:59
 * @LastEditors: Hubery-Lee
 */
#include "help.h"
#include "ui_help.h"

help::help(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::help)
{
    ui->setupUi(this);
    setWindowTitle("Help");
}

help::~help()
{
    delete ui;
}
