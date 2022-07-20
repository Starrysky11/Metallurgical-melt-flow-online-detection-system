/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 5.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <sliderclick.h>
#include "qchartview.h"

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QGridLayout *gridLayout_2;
    QGridLayout *gridLayout;
    QGroupBox *groupBox;
    QHBoxLayout *horizontalLayout_2;
    QTextEdit *logInfoText;
    QGroupBox *VideoGroup;
    QHBoxLayout *horizontalLayout;
    QWidget *widget;
    QHBoxLayout *horizontalLayout_3;
    QLabel *camVideo;
    QGroupBox *InfoLayout;
    QVBoxLayout *verticalLayout;
    QFrame *showQFrame;
    QHBoxLayout *horizontalLayout_4;
    QLabel *showQTitle;
    QLabel *showQText;
    QChartView *showQChart;
    QFrame *line_5;
    QFrame *showVFrame;
    QHBoxLayout *horizontalLayout_5;
    QLabel *showVTitle;
    QLabel *showVText;
    QChartView *showVChart;
    SliderClick *timeSlider;
    QGroupBox *verticalGroupBox;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *TextLayout;
    QFrame *frame;
    QHBoxLayout *horizontalLayout_7;
    QLabel *capFpsTitle;
    QLabel *capFPSText;
    QFrame *line;
    QFrame *frame_2;
    QHBoxLayout *horizontalLayout_8;
    QLabel *showFpsTitle;
    QLabel *showFPSText;
    QFrame *line_2;
    QFrame *frame_3;
    QHBoxLayout *horizontalLayout_9;
    QLabel *label;
    QLabel *stateText;
    QFrame *line_3;
    QToolButton *toolButton;
    QFrame *line_4;
    QHBoxLayout *horizontalLayout_6;
    QPushButton *openCamBtn;
    QPushButton *closeCamBtn;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QString::fromUtf8("Widget"));
        Widget->resize(950, 700);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Ignored);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(Widget->sizePolicy().hasHeightForWidth());
        Widget->setSizePolicy(sizePolicy);
        gridLayout_2 = new QGridLayout(Widget);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        groupBox = new QGroupBox(Widget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setMinimumSize(QSize(0, 180));
        groupBox->setMaximumSize(QSize(16777215, 180));
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        groupBox->setFont(font);
        groupBox->setAutoFillBackground(false);
        groupBox->setStyleSheet(QString::fromUtf8("background-color:rgba(0,0,0,0);"));
        horizontalLayout_2 = new QHBoxLayout(groupBox);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        logInfoText = new QTextEdit(groupBox);
        logInfoText->setObjectName(QString::fromUtf8("logInfoText"));
        QFont font1;
        font1.setPointSize(8);
        font1.setBold(false);
        font1.setWeight(50);
        logInfoText->setFont(font1);
        logInfoText->setAutoFillBackground(true);
        logInfoText->setStyleSheet(QString::fromUtf8("background-color: rgba(38, 38, 48,150);\n"
"color: rgb(255, 255, 255);"));
        logInfoText->setReadOnly(true);

        horizontalLayout_2->addWidget(logInfoText);


        gridLayout->addWidget(groupBox, 2, 0, 1, 1);

        VideoGroup = new QGroupBox(Widget);
        VideoGroup->setObjectName(QString::fromUtf8("VideoGroup"));
        VideoGroup->setMinimumSize(QSize(450, 300));
        VideoGroup->setFont(font);
        VideoGroup->setStyleSheet(QString::fromUtf8(""));
        VideoGroup->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        VideoGroup->setFlat(true);
        VideoGroup->setCheckable(false);
        horizontalLayout = new QHBoxLayout(VideoGroup);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        widget = new QWidget(VideoGroup);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setStyleSheet(QString::fromUtf8("background-color: rgba(38, 38, 48,200);"));
        horizontalLayout_3 = new QHBoxLayout(widget);
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        camVideo = new QLabel(widget);
        camVideo->setObjectName(QString::fromUtf8("camVideo"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(camVideo->sizePolicy().hasHeightForWidth());
        camVideo->setSizePolicy(sizePolicy1);
        camVideo->setMinimumSize(QSize(400, 300));
        camVideo->setStyleSheet(QString::fromUtf8("background-color: rgba(0,0,0,0);"));
        camVideo->setAlignment(Qt::AlignCenter);
        camVideo->setMargin(0);

        horizontalLayout_3->addWidget(camVideo);


        horizontalLayout->addWidget(widget);


        gridLayout->addWidget(VideoGroup, 0, 0, 2, 1);

        InfoLayout = new QGroupBox(Widget);
        InfoLayout->setObjectName(QString::fromUtf8("InfoLayout"));
        InfoLayout->setFont(font);
        verticalLayout = new QVBoxLayout(InfoLayout);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        showQFrame = new QFrame(InfoLayout);
        showQFrame->setObjectName(QString::fromUtf8("showQFrame"));
        showQFrame->setMaximumSize(QSize(16777215, 30));
        showQFrame->setFrameShape(QFrame::Panel);
        showQFrame->setFrameShadow(QFrame::Sunken);
        horizontalLayout_4 = new QHBoxLayout(showQFrame);
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(0, 0, 0, 0);
        showQTitle = new QLabel(showQFrame);
        showQTitle->setObjectName(QString::fromUtf8("showQTitle"));
        QSizePolicy sizePolicy2(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(showQTitle->sizePolicy().hasHeightForWidth());
        showQTitle->setSizePolicy(sizePolicy2);
        showQTitle->setMinimumSize(QSize(90, 30));
        showQTitle->setMaximumSize(QSize(90, 30));

        horizontalLayout_4->addWidget(showQTitle);

        showQText = new QLabel(showQFrame);
        showQText->setObjectName(QString::fromUtf8("showQText"));
        sizePolicy1.setHeightForWidth(showQText->sizePolicy().hasHeightForWidth());
        showQText->setSizePolicy(sizePolicy1);
        showQText->setMaximumSize(QSize(16777215, 30));
        QFont font2;
        font2.setBold(false);
        font2.setWeight(50);
        showQText->setFont(font2);
        showQText->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        showQText->setMargin(2);

        horizontalLayout_4->addWidget(showQText);


        verticalLayout->addWidget(showQFrame);

        showQChart = new QChartView(InfoLayout);
        showQChart->setObjectName(QString::fromUtf8("showQChart"));
        showQChart->setMinimumSize(QSize(200, 150));
        showQChart->setStyleSheet(QString::fromUtf8("background-color: rgba(0,0,0,0);"));
        showQChart->setFrameShape(QFrame::StyledPanel);

        verticalLayout->addWidget(showQChart);

        line_5 = new QFrame(InfoLayout);
        line_5->setObjectName(QString::fromUtf8("line_5"));
        line_5->setFrameShape(QFrame::HLine);
        line_5->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(line_5);

        showVFrame = new QFrame(InfoLayout);
        showVFrame->setObjectName(QString::fromUtf8("showVFrame"));
        showVFrame->setMaximumSize(QSize(16777215, 30));
        showVFrame->setFrameShape(QFrame::Panel);
        showVFrame->setFrameShadow(QFrame::Sunken);
        horizontalLayout_5 = new QHBoxLayout(showVFrame);
        horizontalLayout_5->setSpacing(7);
        horizontalLayout_5->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        horizontalLayout_5->setContentsMargins(0, 0, 0, 0);
        showVTitle = new QLabel(showVFrame);
        showVTitle->setObjectName(QString::fromUtf8("showVTitle"));
        sizePolicy2.setHeightForWidth(showVTitle->sizePolicy().hasHeightForWidth());
        showVTitle->setSizePolicy(sizePolicy2);
        showVTitle->setMinimumSize(QSize(90, 30));
        showVTitle->setMaximumSize(QSize(90, 30));

        horizontalLayout_5->addWidget(showVTitle);

        showVText = new QLabel(showVFrame);
        showVText->setObjectName(QString::fromUtf8("showVText"));
        sizePolicy1.setHeightForWidth(showVText->sizePolicy().hasHeightForWidth());
        showVText->setSizePolicy(sizePolicy1);
        showVText->setMaximumSize(QSize(16777215, 30));
        showVText->setFont(font2);
        showVText->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        showVText->setMargin(2);

        horizontalLayout_5->addWidget(showVText);


        verticalLayout->addWidget(showVFrame);

        showVChart = new QChartView(InfoLayout);
        showVChart->setObjectName(QString::fromUtf8("showVChart"));
        showVChart->setMinimumSize(QSize(200, 150));
        showVChart->setStyleSheet(QString::fromUtf8("background-color: rgba(0, 0,0, 0);"));

        verticalLayout->addWidget(showVChart);

        timeSlider = new SliderClick(InfoLayout);
        timeSlider->setObjectName(QString::fromUtf8("timeSlider"));
        timeSlider->setOrientation(Qt::Horizontal);

        verticalLayout->addWidget(timeSlider);

        verticalLayout->setStretch(1, 6);
        verticalLayout->setStretch(4, 6);

        gridLayout->addWidget(InfoLayout, 0, 1, 6, 1);

        verticalGroupBox = new QGroupBox(Widget);
        verticalGroupBox->setObjectName(QString::fromUtf8("verticalGroupBox"));
        verticalGroupBox->setStyleSheet(QString::fromUtf8("QGroupBox{\n"
"	border:1px solid lightgray;\n"
"	margin-top:0px;\n"
"}\n"
"QGroupBox::title{\n"
"	subcontrol-origin:margin;\n"
"	subcontrol-position: top left;\n"
"	margin-top:0px;\n"
"	margin-left:0px;\n"
"	margin-bottom:11px;\n"
"}"));
        verticalGroupBox->setFlat(true);
        verticalLayout_2 = new QVBoxLayout(verticalGroupBox);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 11);
        TextLayout = new QHBoxLayout();
        TextLayout->setSpacing(0);
        TextLayout->setObjectName(QString::fromUtf8("TextLayout"));
        frame = new QFrame(verticalGroupBox);
        frame->setObjectName(QString::fromUtf8("frame"));
        sizePolicy1.setHeightForWidth(frame->sizePolicy().hasHeightForWidth());
        frame->setSizePolicy(sizePolicy1);
        frame->setMinimumSize(QSize(140, 30));
        frame->setMaximumSize(QSize(150, 30));
        frame->setFrameShape(QFrame::Panel);
        frame->setFrameShadow(QFrame::Sunken);
        horizontalLayout_7 = new QHBoxLayout(frame);
        horizontalLayout_7->setSpacing(0);
        horizontalLayout_7->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        horizontalLayout_7->setContentsMargins(0, 0, 0, 0);
        capFpsTitle = new QLabel(frame);
        capFpsTitle->setObjectName(QString::fromUtf8("capFpsTitle"));
        capFpsTitle->setMinimumSize(QSize(80, 30));
        capFpsTitle->setMaximumSize(QSize(80, 30));
        capFpsTitle->setFont(font);
        capFpsTitle->setFrameShape(QFrame::NoFrame);
        capFpsTitle->setFrameShadow(QFrame::Plain);

        horizontalLayout_7->addWidget(capFpsTitle);

        capFPSText = new QLabel(frame);
        capFPSText->setObjectName(QString::fromUtf8("capFPSText"));
        sizePolicy1.setHeightForWidth(capFPSText->sizePolicy().hasHeightForWidth());
        capFPSText->setSizePolicy(sizePolicy1);
        capFPSText->setMinimumSize(QSize(60, 0));
        capFPSText->setFrameShape(QFrame::NoFrame);
        capFPSText->setFrameShadow(QFrame::Plain);
        capFPSText->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_7->addWidget(capFPSText);


        TextLayout->addWidget(frame);

        line = new QFrame(verticalGroupBox);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShape(QFrame::VLine);
        line->setFrameShadow(QFrame::Sunken);

        TextLayout->addWidget(line);

        frame_2 = new QFrame(verticalGroupBox);
        frame_2->setObjectName(QString::fromUtf8("frame_2"));
        sizePolicy1.setHeightForWidth(frame_2->sizePolicy().hasHeightForWidth());
        frame_2->setSizePolicy(sizePolicy1);
        frame_2->setMinimumSize(QSize(120, 30));
        frame_2->setMaximumSize(QSize(130, 30));
        frame_2->setFrameShape(QFrame::Panel);
        frame_2->setFrameShadow(QFrame::Sunken);
        horizontalLayout_8 = new QHBoxLayout(frame_2);
        horizontalLayout_8->setSpacing(0);
        horizontalLayout_8->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        horizontalLayout_8->setContentsMargins(0, 0, 0, 0);
        showFpsTitle = new QLabel(frame_2);
        showFpsTitle->setObjectName(QString::fromUtf8("showFpsTitle"));
        showFpsTitle->setMinimumSize(QSize(80, 30));
        showFpsTitle->setFont(font);
        showFpsTitle->setFrameShape(QFrame::NoFrame);
        showFpsTitle->setFrameShadow(QFrame::Plain);

        horizontalLayout_8->addWidget(showFpsTitle);

        showFPSText = new QLabel(frame_2);
        showFPSText->setObjectName(QString::fromUtf8("showFPSText"));
        sizePolicy1.setHeightForWidth(showFPSText->sizePolicy().hasHeightForWidth());
        showFPSText->setSizePolicy(sizePolicy1);
        showFPSText->setMinimumSize(QSize(60, 30));
        showFPSText->setFrameShape(QFrame::NoFrame);
        showFPSText->setFrameShadow(QFrame::Plain);
        showFPSText->setScaledContents(false);
        showFPSText->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        showFPSText->setWordWrap(true);

        horizontalLayout_8->addWidget(showFPSText);


        TextLayout->addWidget(frame_2);

        line_2 = new QFrame(verticalGroupBox);
        line_2->setObjectName(QString::fromUtf8("line_2"));
        line_2->setFrameShape(QFrame::VLine);
        line_2->setFrameShadow(QFrame::Sunken);

        TextLayout->addWidget(line_2);

        frame_3 = new QFrame(verticalGroupBox);
        frame_3->setObjectName(QString::fromUtf8("frame_3"));
        sizePolicy1.setHeightForWidth(frame_3->sizePolicy().hasHeightForWidth());
        frame_3->setSizePolicy(sizePolicy1);
        frame_3->setMinimumSize(QSize(140, 30));
        frame_3->setMaximumSize(QSize(200, 30));
        frame_3->setFrameShape(QFrame::Panel);
        frame_3->setFrameShadow(QFrame::Sunken);
        horizontalLayout_9 = new QHBoxLayout(frame_3);
        horizontalLayout_9->setSpacing(0);
        horizontalLayout_9->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
        horizontalLayout_9->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(frame_3);
        label->setObjectName(QString::fromUtf8("label"));
        label->setMinimumSize(QSize(80, 30));
        label->setFont(font);
        label->setFrameShape(QFrame::NoFrame);
        label->setFrameShadow(QFrame::Plain);

        horizontalLayout_9->addWidget(label);

        stateText = new QLabel(frame_3);
        stateText->setObjectName(QString::fromUtf8("stateText"));
        sizePolicy1.setHeightForWidth(stateText->sizePolicy().hasHeightForWidth());
        stateText->setSizePolicy(sizePolicy1);
        stateText->setMinimumSize(QSize(80, 30));
        stateText->setMaximumSize(QSize(16777215, 40));
        stateText->setStyleSheet(QString::fromUtf8("color: rgb(18, 117, 3);"));
        stateText->setFrameShape(QFrame::NoFrame);
        stateText->setFrameShadow(QFrame::Plain);
        stateText->setAlignment(Qt::AlignCenter);

        horizontalLayout_9->addWidget(stateText);


        TextLayout->addWidget(frame_3);

        line_3 = new QFrame(verticalGroupBox);
        line_3->setObjectName(QString::fromUtf8("line_3"));
        line_3->setFrameShape(QFrame::VLine);
        line_3->setFrameShadow(QFrame::Sunken);

        TextLayout->addWidget(line_3);

        toolButton = new QToolButton(verticalGroupBox);
        toolButton->setObjectName(QString::fromUtf8("toolButton"));
        QSizePolicy sizePolicy3(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(toolButton->sizePolicy().hasHeightForWidth());
        toolButton->setSizePolicy(sizePolicy3);
        toolButton->setMinimumSize(QSize(100, 30));
        toolButton->setPopupMode(QToolButton::MenuButtonPopup);
        toolButton->setToolButtonStyle(Qt::ToolButtonTextOnly);
        toolButton->setArrowType(Qt::DownArrow);

        TextLayout->addWidget(toolButton);

        TextLayout->setStretch(0, 3);
        TextLayout->setStretch(2, 3);
        TextLayout->setStretch(4, 3);
        TextLayout->setStretch(6, 2);

        verticalLayout_2->addLayout(TextLayout);

        line_4 = new QFrame(verticalGroupBox);
        line_4->setObjectName(QString::fromUtf8("line_4"));
        line_4->setMaximumSize(QSize(16777215, 2));
        line_4->setFrameShape(QFrame::HLine);
        line_4->setFrameShadow(QFrame::Sunken);

        verticalLayout_2->addWidget(line_4);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        openCamBtn = new QPushButton(verticalGroupBox);
        openCamBtn->setObjectName(QString::fromUtf8("openCamBtn"));
        sizePolicy1.setHeightForWidth(openCamBtn->sizePolicy().hasHeightForWidth());
        openCamBtn->setSizePolicy(sizePolicy1);

        horizontalLayout_6->addWidget(openCamBtn);

        closeCamBtn = new QPushButton(verticalGroupBox);
        closeCamBtn->setObjectName(QString::fromUtf8("closeCamBtn"));
        sizePolicy1.setHeightForWidth(closeCamBtn->sizePolicy().hasHeightForWidth());
        closeCamBtn->setSizePolicy(sizePolicy1);

        horizontalLayout_6->addWidget(closeCamBtn);

        horizontalLayout_6->setStretch(0, 1);
        horizontalLayout_6->setStretch(1, 1);

        verticalLayout_2->addLayout(horizontalLayout_6);


        gridLayout->addWidget(verticalGroupBox, 4, 0, 1, 1);

        gridLayout->setRowStretch(0, 2);
        gridLayout->setColumnStretch(0, 3);
        gridLayout->setColumnStretch(1, 2);

        gridLayout_2->addLayout(gridLayout, 0, 0, 1, 1);


        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QApplication::translate("Widget", "\345\206\266\351\207\221\347\206\224\344\275\223\346\265\201\351\207\217\345\234\250\347\272\277\346\231\272\350\203\275\346\204\237\347\237\245\347\263\273\347\273\237", nullptr));
        groupBox->setTitle(QApplication::translate("Widget", "\346\227\245\345\277\227\344\277\241\346\201\257", nullptr));
        VideoGroup->setTitle(QApplication::translate("Widget", "\347\233\270\346\234\272\345\233\276\345\203\217", nullptr));
        camVideo->setText(QString());
        InfoLayout->setTitle(QApplication::translate("Widget", "\345\206\266\351\207\221\347\206\224\344\275\223\344\277\241\346\201\257", nullptr));
        showQTitle->setText(QApplication::translate("Widget", "\345\275\223\345\211\215\346\265\201\351\207\217\357\274\232", nullptr));
        showQText->setText(QString());
        showVTitle->setText(QApplication::translate("Widget", "\347\264\257\347\247\257\346\265\201\351\207\217\357\274\232", nullptr));
        showVText->setText(QString());
        verticalGroupBox->setTitle(QString());
        capFpsTitle->setText(QApplication::translate("Widget", "\351\207\207\351\233\206\345\270\247\347\216\207\357\274\232", nullptr));
        capFPSText->setText(QApplication::translate("Widget", "200fps", nullptr));
        showFpsTitle->setText(QApplication::translate("Widget", "\346\230\276\347\244\272\345\270\247\347\216\207\357\274\232", nullptr));
        showFPSText->setText(QApplication::translate("Widget", "30fps", nullptr));
        label->setText(QApplication::translate("Widget", "\345\275\223\345\211\215\347\212\266\346\200\201\357\274\232", nullptr));
        stateText->setText(QApplication::translate("Widget", "\346\255\243\345\270\270", nullptr));
        toolButton->setText(QApplication::translate("Widget", "...", nullptr));
        openCamBtn->setText(QApplication::translate("Widget", "\346\211\223\345\274\200\347\233\270\346\234\272", nullptr));
        closeCamBtn->setText(QApplication::translate("Widget", "\345\205\263\351\227\255\347\233\270\346\234\272", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
