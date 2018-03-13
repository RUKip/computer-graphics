/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDial>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <mainview.h>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout;
    QGroupBox *settingsBox;
    QFormLayout *formLayout;
    QGroupBox *rotationBox;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QDial *RotationDialX;
    QDial *RotationDialY;
    QDial *RotationDialZ;
    QPushButton *ResetRotationButton;
    QGroupBox *scalingBox;
    QVBoxLayout *verticalLayout_4;
    QSlider *ScaleSlider;
    QPushButton *ResetScaleButton;
    QGroupBox *RGBLight;
    QVBoxLayout *verticalLayout_3;
    QSpinBox *RLight;
    QSpinBox *GLight;
    QSpinBox *BLight;
    QGroupBox *RGBMaterial;
    QVBoxLayout *verticalLayout_5;
    QSpinBox *RMaterial;
    QSpinBox *GMaterial;
    QSpinBox *BMaterial;
    QGroupBox *Kcoefficient_1;
    QVBoxLayout *verticalLayout_7;
    QSlider *KAmbient;
    QGroupBox *Kcoefficient_2;
    QVBoxLayout *verticalLayout_6;
    QSlider *KDiffuse;
    QGroupBox *Kcoefficient_3;
    QVBoxLayout *verticalLayout_8;
    QSlider *KSpecular;
    QGroupBox *Kcoefficient_4;
    QVBoxLayout *verticalLayout_9;
    QSlider *KP;
    QGroupBox *shadingBox;
    QRadioButton *PhongButton;
    QRadioButton *NormalButton;
    QRadioButton *GouraudButton;
    QRadioButton *CellButton;
    MainView *mainView;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1272, 973);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        horizontalLayout = new QHBoxLayout(centralWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        settingsBox = new QGroupBox(centralWidget);
        settingsBox->setObjectName(QStringLiteral("settingsBox"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(settingsBox->sizePolicy().hasHeightForWidth());
        settingsBox->setSizePolicy(sizePolicy);
        settingsBox->setMinimumSize(QSize(220, 0));
        settingsBox->setMaximumSize(QSize(220, 16777215));
        formLayout = new QFormLayout(settingsBox);
        formLayout->setSpacing(6);
        formLayout->setContentsMargins(11, 11, 11, 11);
        formLayout->setObjectName(QStringLiteral("formLayout"));
        formLayout->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);
        rotationBox = new QGroupBox(settingsBox);
        rotationBox->setObjectName(QStringLiteral("rotationBox"));
        sizePolicy.setHeightForWidth(rotationBox->sizePolicy().hasHeightForWidth());
        rotationBox->setSizePolicy(sizePolicy);
        rotationBox->setMinimumSize(QSize(205, 0));
        rotationBox->setMaximumSize(QSize(205, 16777215));
        verticalLayout = new QVBoxLayout(rotationBox);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        RotationDialX = new QDial(rotationBox);
        RotationDialX->setObjectName(QStringLiteral("RotationDialX"));
        RotationDialX->setMaximum(359);
        RotationDialX->setWrapping(true);
        RotationDialX->setNotchTarget(12);
        RotationDialX->setNotchesVisible(true);

        horizontalLayout_2->addWidget(RotationDialX);

        RotationDialY = new QDial(rotationBox);
        RotationDialY->setObjectName(QStringLiteral("RotationDialY"));
        RotationDialY->setMaximum(359);
        RotationDialY->setWrapping(true);
        RotationDialY->setNotchTarget(12);
        RotationDialY->setNotchesVisible(true);

        horizontalLayout_2->addWidget(RotationDialY);

        RotationDialZ = new QDial(rotationBox);
        RotationDialZ->setObjectName(QStringLiteral("RotationDialZ"));
        RotationDialZ->setMaximum(359);
        RotationDialZ->setWrapping(true);
        RotationDialZ->setNotchTarget(12);
        RotationDialZ->setNotchesVisible(true);

        horizontalLayout_2->addWidget(RotationDialZ);


        verticalLayout->addLayout(horizontalLayout_2);

        ResetRotationButton = new QPushButton(rotationBox);
        ResetRotationButton->setObjectName(QStringLiteral("ResetRotationButton"));

        verticalLayout->addWidget(ResetRotationButton);


        formLayout->setWidget(0, QFormLayout::LabelRole, rotationBox);

        scalingBox = new QGroupBox(settingsBox);
        scalingBox->setObjectName(QStringLiteral("scalingBox"));
        sizePolicy.setHeightForWidth(scalingBox->sizePolicy().hasHeightForWidth());
        scalingBox->setSizePolicy(sizePolicy);
        scalingBox->setMinimumSize(QSize(205, 0));
        scalingBox->setMaximumSize(QSize(205, 16777215));
        verticalLayout_4 = new QVBoxLayout(scalingBox);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        ScaleSlider = new QSlider(scalingBox);
        ScaleSlider->setObjectName(QStringLiteral("ScaleSlider"));
        ScaleSlider->setMinimum(1);
        ScaleSlider->setMaximum(200);
        ScaleSlider->setValue(100);
        ScaleSlider->setOrientation(Qt::Horizontal);
        ScaleSlider->setInvertedAppearance(false);
        ScaleSlider->setInvertedControls(false);
        ScaleSlider->setTickPosition(QSlider::NoTicks);

        verticalLayout_4->addWidget(ScaleSlider);

        ResetScaleButton = new QPushButton(scalingBox);
        ResetScaleButton->setObjectName(QStringLiteral("ResetScaleButton"));

        verticalLayout_4->addWidget(ResetScaleButton);


        formLayout->setWidget(1, QFormLayout::LabelRole, scalingBox);

        RGBLight = new QGroupBox(settingsBox);
        RGBLight->setObjectName(QStringLiteral("RGBLight"));
        RGBLight->setMinimumSize(QSize(205, 0));
        RGBLight->setMaximumSize(QSize(205, 16777215));
        verticalLayout_3 = new QVBoxLayout(RGBLight);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        RLight = new QSpinBox(RGBLight);
        RLight->setObjectName(QStringLiteral("RLight"));
        RLight->setMinimum(1);
        RLight->setMaximum(255);
        RLight->setValue(255);

        verticalLayout_3->addWidget(RLight);

        GLight = new QSpinBox(RGBLight);
        GLight->setObjectName(QStringLiteral("GLight"));
        GLight->setMinimum(1);
        GLight->setMaximum(255);
        GLight->setValue(255);

        verticalLayout_3->addWidget(GLight);

        BLight = new QSpinBox(RGBLight);
        BLight->setObjectName(QStringLiteral("BLight"));
        BLight->setMinimum(1);
        BLight->setMaximum(255);
        BLight->setValue(255);

        verticalLayout_3->addWidget(BLight);


        formLayout->setWidget(3, QFormLayout::LabelRole, RGBLight);

        RGBMaterial = new QGroupBox(settingsBox);
        RGBMaterial->setObjectName(QStringLiteral("RGBMaterial"));
        RGBMaterial->setMinimumSize(QSize(205, 0));
        RGBMaterial->setMaximumSize(QSize(205, 16777215));
        verticalLayout_5 = new QVBoxLayout(RGBMaterial);
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setContentsMargins(11, 11, 11, 11);
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        verticalLayout_5->setContentsMargins(1, 1, 1, 1);
        RMaterial = new QSpinBox(RGBMaterial);
        RMaterial->setObjectName(QStringLiteral("RMaterial"));
        RMaterial->setMinimum(1);
        RMaterial->setMaximum(255);
        RMaterial->setValue(255);

        verticalLayout_5->addWidget(RMaterial);

        GMaterial = new QSpinBox(RGBMaterial);
        GMaterial->setObjectName(QStringLiteral("GMaterial"));
        GMaterial->setMinimum(1);
        GMaterial->setMaximum(255);
        GMaterial->setValue(255);

        verticalLayout_5->addWidget(GMaterial);

        BMaterial = new QSpinBox(RGBMaterial);
        BMaterial->setObjectName(QStringLiteral("BMaterial"));
        BMaterial->setMinimum(1);
        BMaterial->setMaximum(255);
        BMaterial->setValue(255);

        verticalLayout_5->addWidget(BMaterial);


        formLayout->setWidget(7, QFormLayout::LabelRole, RGBMaterial);

        Kcoefficient_1 = new QGroupBox(settingsBox);
        Kcoefficient_1->setObjectName(QStringLiteral("Kcoefficient_1"));
        verticalLayout_7 = new QVBoxLayout(Kcoefficient_1);
        verticalLayout_7->setSpacing(6);
        verticalLayout_7->setContentsMargins(11, 11, 11, 11);
        verticalLayout_7->setObjectName(QStringLiteral("verticalLayout_7"));
        KAmbient = new QSlider(Kcoefficient_1);
        KAmbient->setObjectName(QStringLiteral("KAmbient"));
        KAmbient->setMinimum(1);
        KAmbient->setMaximum(200);
        KAmbient->setValue(40);
        KAmbient->setOrientation(Qt::Horizontal);

        verticalLayout_7->addWidget(KAmbient);


        formLayout->setWidget(9, QFormLayout::SpanningRole, Kcoefficient_1);

        Kcoefficient_2 = new QGroupBox(settingsBox);
        Kcoefficient_2->setObjectName(QStringLiteral("Kcoefficient_2"));
        verticalLayout_6 = new QVBoxLayout(Kcoefficient_2);
        verticalLayout_6->setSpacing(6);
        verticalLayout_6->setContentsMargins(11, 11, 11, 11);
        verticalLayout_6->setObjectName(QStringLiteral("verticalLayout_6"));
        KDiffuse = new QSlider(Kcoefficient_2);
        KDiffuse->setObjectName(QStringLiteral("KDiffuse"));
        KDiffuse->setMinimum(1);
        KDiffuse->setMaximum(200);
        KDiffuse->setValue(200);
        KDiffuse->setSliderPosition(200);
        KDiffuse->setOrientation(Qt::Horizontal);

        verticalLayout_6->addWidget(KDiffuse);


        formLayout->setWidget(10, QFormLayout::SpanningRole, Kcoefficient_2);

        Kcoefficient_3 = new QGroupBox(settingsBox);
        Kcoefficient_3->setObjectName(QStringLiteral("Kcoefficient_3"));
        verticalLayout_8 = new QVBoxLayout(Kcoefficient_3);
        verticalLayout_8->setSpacing(6);
        verticalLayout_8->setContentsMargins(11, 11, 11, 11);
        verticalLayout_8->setObjectName(QStringLiteral("verticalLayout_8"));
        KSpecular = new QSlider(Kcoefficient_3);
        KSpecular->setObjectName(QStringLiteral("KSpecular"));
        KSpecular->setMinimum(1);
        KSpecular->setMaximum(50);
        KSpecular->setOrientation(Qt::Horizontal);

        verticalLayout_8->addWidget(KSpecular);


        formLayout->setWidget(12, QFormLayout::SpanningRole, Kcoefficient_3);

        Kcoefficient_4 = new QGroupBox(settingsBox);
        Kcoefficient_4->setObjectName(QStringLiteral("Kcoefficient_4"));
        verticalLayout_9 = new QVBoxLayout(Kcoefficient_4);
        verticalLayout_9->setSpacing(6);
        verticalLayout_9->setContentsMargins(11, 11, 11, 11);
        verticalLayout_9->setObjectName(QStringLiteral("verticalLayout_9"));
        KP = new QSlider(Kcoefficient_4);
        KP->setObjectName(QStringLiteral("KP"));
        KP->setMinimum(1);
        KP->setMaximum(100);
        KP->setOrientation(Qt::Horizontal);

        verticalLayout_9->addWidget(KP);


        formLayout->setWidget(13, QFormLayout::SpanningRole, Kcoefficient_4);

        shadingBox = new QGroupBox(settingsBox);
        shadingBox->setObjectName(QStringLiteral("shadingBox"));
        sizePolicy.setHeightForWidth(shadingBox->sizePolicy().hasHeightForWidth());
        shadingBox->setSizePolicy(sizePolicy);
        shadingBox->setMinimumSize(QSize(205, 100));
        shadingBox->setMaximumSize(QSize(205, 16777215));
        PhongButton = new QRadioButton(shadingBox);
        PhongButton->setObjectName(QStringLiteral("PhongButton"));
        PhongButton->setGeometry(QRect(17, 25, 66, 22));
        PhongButton->setChecked(true);
        NormalButton = new QRadioButton(shadingBox);
        NormalButton->setObjectName(QStringLiteral("NormalButton"));
        NormalButton->setGeometry(QRect(17, 53, 72, 22));
        GouraudButton = new QRadioButton(shadingBox);
        GouraudButton->setObjectName(QStringLiteral("GouraudButton"));
        GouraudButton->setGeometry(QRect(17, 81, 79, 22));
        CellButton = new QRadioButton(shadingBox);
        CellButton->setObjectName(QStringLiteral("CellButton"));
        CellButton->setGeometry(QRect(110, 80, 79, 22));

        formLayout->setWidget(2, QFormLayout::FieldRole, shadingBox);


        horizontalLayout->addWidget(settingsBox);

        mainView = new MainView(centralWidget);
        mainView->setObjectName(QStringLiteral("mainView"));

        horizontalLayout->addWidget(mainView);

        MainWindow->setCentralWidget(centralWidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        settingsBox->setTitle(QApplication::translate("MainWindow", "Settings", Q_NULLPTR));
        rotationBox->setTitle(QApplication::translate("MainWindow", "Rotation", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        RotationDialX->setToolTip(QApplication::translate("MainWindow", "<html><head/><body><p>Rotation along the X-axis</p></body></html>", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        RotationDialY->setToolTip(QApplication::translate("MainWindow", "<html><head/><body><p>Rotation along the Y-axis</p></body></html>", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        RotationDialZ->setToolTip(QApplication::translate("MainWindow", "<html><head/><body><p>Rotation along the Z-axis</p></body></html>", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        ResetRotationButton->setText(QApplication::translate("MainWindow", "Reset Rotation", Q_NULLPTR));
        scalingBox->setTitle(QApplication::translate("MainWindow", "Scaling", Q_NULLPTR));
        ResetScaleButton->setText(QApplication::translate("MainWindow", "Reset Scaling", Q_NULLPTR));
        RGBLight->setTitle(QApplication::translate("MainWindow", "RGB light", Q_NULLPTR));
        RGBMaterial->setTitle(QApplication::translate("MainWindow", "Color material", Q_NULLPTR));
        Kcoefficient_1->setTitle(QApplication::translate("MainWindow", "Ambient Material", Q_NULLPTR));
        Kcoefficient_2->setTitle(QApplication::translate("MainWindow", "Diffuse material", Q_NULLPTR));
        Kcoefficient_3->setTitle(QApplication::translate("MainWindow", "Speculalar Material", Q_NULLPTR));
        Kcoefficient_4->setTitle(QApplication::translate("MainWindow", "P Material", Q_NULLPTR));
        shadingBox->setTitle(QApplication::translate("MainWindow", "Shading", Q_NULLPTR));
        PhongButton->setText(QApplication::translate("MainWindow", "Pho&ng", Q_NULLPTR));
        NormalButton->setText(QApplication::translate("MainWindow", "Nor&mal", Q_NULLPTR));
        GouraudButton->setText(QApplication::translate("MainWindow", "&Gouraud", Q_NULLPTR));
        CellButton->setText(QApplication::translate("MainWindow", "&Cell", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
