/*
 * @Description: 
 * @version: 
 * @Author: Hubery-Lee
 * @E-mail: hrbeulh@126.com
 * @Date: 2021-12-15 20:46:25
 * @LastEditTime: 2021-12-15 22:16:41
 * @LastEditors: Hubery-Lee
 */
#include "about.h"
#include "ui_about.h"

About::About(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::About)
{
    ui->setupUi(this);
    setWindowTitle("About");
}

About::~About()
{
    delete ui;
}
