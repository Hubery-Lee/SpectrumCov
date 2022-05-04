/********************************************************************************
** Form generated from reading UI file 'help.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_HELP_H
#define UI_HELP_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_help
{
public:
    QGridLayout *gridLayout;
    QTextBrowser *textBrowser;

    void setupUi(QWidget *help)
    {
        if (help->objectName().isEmpty())
            help->setObjectName(QString::fromUtf8("help"));
        help->resize(640, 229);
        gridLayout = new QGridLayout(help);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        textBrowser = new QTextBrowser(help);
        textBrowser->setObjectName(QString::fromUtf8("textBrowser"));

        gridLayout->addWidget(textBrowser, 0, 0, 1, 1);


        retranslateUi(help);

        QMetaObject::connectSlotsByName(help);
    } // setupUi

    void retranslateUi(QWidget *help)
    {
        help->setWindowTitle(QCoreApplication::translate("help", "Form", nullptr));
        textBrowser->setHtml(QCoreApplication::translate("help", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Ubuntu'; font-size:11pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:18pt;\">SpectrumCov</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">        SpectrumCov(Spectrum Conversion)\351\200\232\350\277\207\350\276\223\345\205\245\347\224\261Geant4\346\250\241\346\213\237\350\256\241\347\256\227\347\232\204root\346\225\260\346\215\256,\347\273\230\345\210\266\344\270\255\345\255\220\346\210\226\344\274\275\351\251\254\347\232\204\350\203\275\350\260\261\357\274\214\345\271\266\351\200\232\350\277\207\350\203\275"
                        "\351\207\217\346\263\250\351\207\217\350\275\254\346\215\242\347\263\273\346\225\260\350\275\254\346\215\242\346\210\220\350\276\220\345\260\204\351\230\262\346\212\244\351\207\217\343\200\202\344\275\277\347\224\250\346\255\245\351\252\244\345\246\202\344\270\213\357\274\232</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">        1\357\274\211\346\211\223\345\274\200\345\276\205\345\244\204\347\220\206root\346\226\207\344\273\266\357\274\233</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">        2\357\274\211\347\273\230\345\210\266\344\274\275\351\251\254\346\210\226\350\200\205\344\270\255\345\255\220\350\203\275\350\260\261\357\274\233</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">        3\357\274\211\347\273\230\345\210\266\350\203\275\351\207\217\346\263\250\351"
                        "\207\217\350\275\254\346\215\242\350\276\220\345\260\204\351\230\262\346\212\244\351\207\217\347\263\273\346\225\260\357\274\233</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">        4\357\274\211\350\256\241\347\256\227\350\275\254\346\215\242\347\273\223\346\236\234\357\274\233</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">        5\357\274\211\344\277\235\345\255\230\350\275\254\346\215\242\347\273\223\346\236\234\345\210\260\346\226\207\344\273\266\343\200\202</p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p></body></html>", nullptr));
    } // retranslateUi

};

namespace Ui {
    class help: public Ui_help {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HELP_H
