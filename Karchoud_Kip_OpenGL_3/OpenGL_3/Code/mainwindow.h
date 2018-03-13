#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

    Ui::MainWindow *ui;

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_ResetRotationButton_clicked(bool checked);
    void on_RotationDialX_sliderMoved(int value);
    void on_RotationDialY_sliderMoved(int value);
    void on_RotationDialZ_sliderMoved(int value);

    void on_ResetScaleButton_clicked(bool checked);
    void on_ScaleSlider_sliderMoved(int value);

    void on_PhongButton_toggled(bool checked);
    void on_NormalButton_toggled(bool checked);
    void on_GouraudButton_toggled(bool checked);
    void on_CellButton_toggled(bool checked);

    void on_RLight_valueChanged(int value);
    void on_GLight_valueChanged(int value);
    void on_BLight_valueChanged(int value);

    void on_RMaterial_valueChanged(int value);
    void on_GMaterial_valueChanged(int value);
    void on_BMaterial_valueChanged(int value);

    void on_KAmbient_sliderMoved(int value);
    void on_KDiffuse_sliderMoved(int value);
    void on_KSpecular_sliderMoved(int value);
    void on_KP_sliderMoved(int value);

};

#endif // MAINWINDOW_H
