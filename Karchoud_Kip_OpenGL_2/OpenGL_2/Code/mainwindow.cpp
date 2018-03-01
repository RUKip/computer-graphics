#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "math.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

// --- Functions that listen for widget events
// forewards to the mainview

void MainWindow::on_ResetRotationButton_clicked(bool checked)
{
    Q_UNUSED(checked);
    ui->RotationDialX->setValue(0);
    ui->RotationDialY->setValue(0);
    ui->RotationDialZ->setValue(0);
    ui->RLight->setValue(255);
    ui->GLight->setValue(0);
    ui->BLight->setValue(0);
    ui->RMaterial->setValue(0);
    ui->GMaterial->setValue(0);
    ui->BMaterial->setValue(255);
    ui->mainView->setRotation(0, 0, 0);
    ui->KAmbient->setScale(0);
    ui->KDiffuse->setScale(0);
    ui->KSpecular->setScale(0);
    ui->KP->setScale(0);
}

void MainWindow::on_RotationDialX_sliderMoved(int value)
{
    ui->mainView->setRotation(value,
                              ui->RotationDialY->value(),
                              ui->RotationDialZ->value());
}

void MainWindow::on_RotationDialY_sliderMoved(int value)
{
    ui->mainView->setRotation(ui->RotationDialX->value(),
                              value,
                              ui->RotationDialZ->value());
}

void MainWindow::on_RotationDialZ_sliderMoved(int value)
{
    ui->mainView->setRotation(ui->RotationDialX->value(),
                              ui->RotationDialY->value(),
                              value);
}

void MainWindow::on_ResetScaleButton_clicked(bool checked)
{
    Q_UNUSED(checked);
    ui->ScaleSlider->setValue(100);
    ui->mainView->setScale(100);
}

void MainWindow::on_ScaleSlider_sliderMoved(int value)
{
    ui->mainView->setScale(value);
}

void MainWindow::on_PhongButton_toggled(bool checked)
{
    if (checked)
    {
        ui->mainView->setShadingMode(MainView::PHONG);
        ui->mainView->update();
    }
}

void MainWindow::on_NormalButton_toggled(bool checked)
{
    if (checked)
    {
        ui->mainView->setShadingMode(MainView::NORMAL);
        ui->mainView->update();
    }
}

void MainWindow::on_GouraudButton_toggled(bool checked)
{
    if (checked)
    {
        ui->mainView->setShadingMode(MainView::GOURAUD);
        ui->mainView->update();
    }
}

void MainWindow::on_RLight_valueChanged(int value)
{
    ui->mainView->setRLight(value);
}

void MainWindow::on_GLight_valueChanged(int value)
{
    ui->mainView->setGLight(value);
}

void MainWindow::on_BLight_valueChanged(int value)
{
    ui->mainView->setBLight(value);
}

void MainWindow::on_RMaterial_valueChanged(int value)
{
    ui->mainView->setRMaterial(value);
}

void MainWindow::on_GMaterial_valueChanged(int value)
{
    ui->mainView->setGMaterial(value);
}

void MainWindow::on_BMaterial_valueChanged(int value)
{
    ui->mainView->setBMaterial(value);
}

void MainWindow::on_KAmbient_sliderMoved(int value)
{
    ui->mainView->setKAmbient(value);
}

void MainWindow::on_KDiffuse_sliderMoved(int value)
{
    ui->mainView->setKDiffuse(value);
}

void MainWindow::on_KSpecular_sliderMoved(int value)
{
    ui->mainView->setKSpecular(value);
}

void MainWindow::on_KP_sliderMoved(int value)
{
    ui->mainView->setKP(value);
}



