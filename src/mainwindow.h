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
    ///\brief mise a jour de l'image en temps reel
    void updateImage(const Vector3f * pix);
    ///\brief affichage de la scene
    void displayImage();
    enum ShowedMap{
        RENDER,
        DEPTH_MAP,
        GI_MAP
    };
    ShowedMap currentlyShown;

private slots :
    ///\brief initialisation globale de la fenetre QT, appelle les autres fonctions initXXX()
    void initWindow();
    ///\brief intialisation des boutons de la fenetrre QT
    void initButtons();
    ///\brief initialisation du slider "detail Level"
    void initSliders();
    ///\brief initialisation de la fenetre QT
    void initComboBox();


    ///\brief choix de la scene 
    void sceneChoice();
    ///\brief recuperere la valeu du slider du niveau de detail
    void sliderValue();


    ///\brief creer une depthMap de la scene choisi
    void shading();
    ///\brief lance le rendu de l'image apres avoir pris en compte la scene choisi et le niveau de detail
    void renderImage();
    ///\brief energistrement de l'image 
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