/********************************************************************************
** Form generated from reading UI file 'about.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ABOUT_H
#define UI_ABOUT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_About
{
public:
    QGridLayout *gridLayout;
    QTextBrowser *textBrowser;

    void setupUi(QWidget *About)
    {
        if (About->objectName().isEmpty())
            About->setObjectName(QString::fromUtf8("About"));
        About->resize(838, 535);
        gridLayout = new QGridLayout(About);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        textBrowser = new QTextBrowser(About);
        textBrowser->setObjectName(QString::fromUtf8("textBrowser"));
        textBrowser->setStyleSheet(QString::fromUtf8("font: 75 11pt \"Microsoft JhengHei\";"));

        gridLayout->addWidget(textBrowser, 0, 0, 1, 1);


        retranslateUi(About);

        QMetaObject::connectSlotsByName(About);
    } // setupUi

    void retranslateUi(QWidget *About)
    {
        About->setWindowTitle(QCoreApplication::translate("About", "Form", nullptr));
        textBrowser->setHtml(QCoreApplication::translate("About", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Microsoft JhengHei'; font-size:11pt; font-weight:72; font-style:normal;\">\n"
"<p align=\"center\" style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'SimSun'; font-size:9pt; font-weight:400;\"><br /></p>\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'SimSun'; font-size:18pt; font-weight:400;\">\345\205\263\344\272\216SpectrumCov</span></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'SimSun'; font-size:9pt; font-w"
                        "eight:400;\"><br /></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'SimSun'; font-size:9pt; font-weight:400;\">    </span><span style=\" font-family:'SimSun'; font-size:12pt; font-weight:400;\">SpectrumCov\346\230\257\344\270\200\346\254\276\347\224\250\344\272\216\350\203\275\350\260\261\350\275\254\346\215\242\350\276\220\345\260\204\351\230\262\346\212\244\351\207\217\347\232\204\350\275\254\346\215\242\350\256\241\347\256\227\345\267\245\345\205\267\343\200\202\347\224\261\344\270\255\345\233\275\350\276\220\345\260\204\351\230\262\346\212\244\347\240\224\347\251\266\351\231\242\346\240\270\344\270\216\350\276\220\345\260\204\345\211\215\346\262\277\346\212\200\346\234\257\347\240\224\347\251\266\344\270\255\345\277\203\346\240\270\346\216\242\346\265\213\344\270\216\346\210\220\345\203\217\347\240\224\347\251\266\345\256\244\346\211\200\345\274\200\345\217\221\357\274\214\344\275\277\347\224\250\350"
                        "\277\207\347\250\213\344\270\255\345\246\202\351\201\207\344\273\273\344\275\225\351\227\256\351\242\230\357\274\214\345\217\257\351\200\232\350\277\207</span><a href=\"hrbeulh@126.com\"><span style=\" font-family:'SimSun'; font-size:12pt; font-weight:400; text-decoration: underline; color:#0000ff;\">hrbeulh@126.com</span></a><span style=\" font-family:'SimSun'; font-size:12pt; font-weight:400;\">\350\201\224\347\263\273\345\274\200\345\217\221\344\272\272\345\221\230\343\200\202\346\255\244\350\275\257\344\273\266\347\232\204\350\216\267\345\217\226\351\200\224\345\276\204\351\231\244\351\202\256\344\273\266\350\201\224\347\263\273\345\244\226\350\277\230\346\234\211\344\270\244\347\247\215\357\274\2141\357\274\211\351\200\232\350\277\207\345\276\256\344\277\241</span><a href=\"HuberyLeeNB\"><span style=\" font-family:'SimSun'; font-size:12pt; font-weight:400; text-decoration: underline; color:#0000ff;\">HuberyLeeNB</span></a><span style=\" font-family:'SimSun'; font-size:12pt; font-weight:400;\">\350\201\224"
                        "\347\263\273\344\275\234\350\200\205\357\274\2332\357\274\211\351\200\232\350\277\207</span><a href=\"https://github.com/Hubery-Lee/SWNS\"><span style=\" font-family:'SimSun'; font-size:12pt; font-weight:400; text-decoration: underline; color:#0000ff;\">https://github.com/Hubery-Lee/SpectrumCov </span></a><a href=\"https://github.com/Hubery-Lee/SWNS\"><span style=\" font-family:'SimSun'; font-size:12pt; font-weight:400; text-decoration: underline; color:#000000;\">\344\270\213\350\275\275\350\275\257\344\273\266</span></a></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'SimSun'; font-size:12pt; font-weight:400; text-decoration: underline; color:#000000;\"><br /></p>\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><img src=\":/images/logo.png\" /></p>\n"
"<p align=\"center\" style=\" margin-top:0px; marg"
                        "in-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><img src=\":/images/scanCode.png\" /></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'SimSun'; font-size:9pt; font-weight:400; text-decoration: underline; color:#000000;\"><br /></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'SimSun'; font-size:9pt; font-weight:400; color:#000000;\"><br /></p></body></html>", nullptr));
    } // retranslateUi

};

namespace Ui {
    class About: public Ui_About {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ABOUT_H
