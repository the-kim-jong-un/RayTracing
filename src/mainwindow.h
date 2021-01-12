//
// Created by adrien on 18/09/2020.
//

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDebug>
#include <QLabel>
#include <QSlider>
#include <QComboBox>
#include <QLineEdit>
#include <QMainWindow>
#include <QPushButton>
#include <QFileDialog>
#include <QCommonStyle>
#include <QDesktopWidget>
#include <QApplication>
#include "Vector.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

///\brief Classe de la fenetre QT
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    ///\brief Constructeur de la fenetre
    MainWindow(QWidget *parent = nullptr);

    ///\brief Destructeur de la fenetre
    ~MainWindow();

    static QPixmap * QPM;
    void updateImage(const Vector3f * pix);
    void displayImage();

private slots :
    void initWindow();
    void initButtons();
    void initSliders();
    void initComboBox();


    void sceneChoice();
    void sliderValue();


    void shading();
    void renderImage();
    void downloadImage();


private:
    Ui::MainWindow * ui;
    QSlider * speedSlider;
    QLabel * displayLabel, * sliderLabel, * downloadLabel;
    QComboBox * sceneCombo;
    QLineEdit * downloadFileName;
    QPushButton * sphereMarchingButton, * shadingButton, * downloadButton;

    int windowHeight, windowWIdth;
    int desktopHeight, desktopWidth;


};
#endif // MAINWINDOW_H