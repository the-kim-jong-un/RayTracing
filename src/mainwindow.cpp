//
// Created by adrien on 18/09/2020.
//
#include <thread>
#include <cmath>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "SceneManager.h"
#include "iostream"
#include "Renderer.h"
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow){
    ui->setupUi(this);
    setWindowTitle("Ray Tracing");
    initWindow();
    initArrowButtons();
    displayImage();
    qDebug()<< "Preselected scene : " << ui->sceneCombo->currentIndex();
    std::thread SC(&SceneManager::loadPremadeScene,0);
    SC.detach();
}

void MainWindow::initWindow(){
    QRect rec = QApplication::desktop()->screenGeometry();
    desktopWidth = rec.width();
    desktopHeight = rec.height();

    this->setPalette(QColor(50,50,50));

    windowWIdth = desktopWidth/4*3;
    windowHeight = desktopHeight/4*3;
    this->setFixedSize(QSize(windowWIdth,windowHeight));

    initComboBox();
    initSliders();
    initButtons();
}
void MainWindow::initSliders(){
    //detail slider
    ui->sliderLabel->setText("Detail level : ");
    ui->sliderLabel->setGeometry(QRect(QPoint(windowWIdth/40+120, windowHeight/40-20), QSize(100,25)));
    ui->sliderLabel->setScaledContents(true);
    ui->speedSlider->setPalette(QColor(100,100,100));
    ui->speedSlider->setGeometry(QRect(QPoint(windowWIdth/40+110, windowHeight/40), QSize(100,25)));
    ui->speedSlider->setRange(0, 14);
    connect(ui->speedSlider, SIGNAL(sliderReleased()), SLOT(sliderValue()));
}

void MainWindow::initButtons(){
    //shading button
    ui->shadingButton->setText("Shading");
    ui->shadingButton->setPalette(QColor(100,100,100));
    ui->shadingButton->setGeometry(QRect(QPoint(windowWIdth/40+220, windowHeight/40), QSize(100,25)));
    connect(ui->shadingButton, SIGNAL(clicked()), SLOT(shading()));

    //sphere marching button
    ui->sphereMarchingButton->setText("Render");
    ui->sphereMarchingButton->setPalette(QColor(100,100,100));
    ui->sphereMarchingButton->setGeometry(QRect(QPoint(windowWIdth/40+330, windowHeight/40), QSize(100,25)));
    //connect(ui->sphereMarchingButton, SIGNAL(clicked()), SLOT(sphereMarching()));
    connect(ui->sphereMarchingButton, SIGNAL(clicked()), SLOT(renderImage()));

    //download button
    ui->downloadButton->setText("Download");
    ui->downloadButton->setPalette(QColor(70,150,70));
    ui->downloadButton->setGeometry(QRect(QPoint(windowWIdth-110, windowHeight/40), QSize(100,25)));
    connect(ui->downloadButton, SIGNAL(clicked()), SLOT(downloadImage()));
}

void MainWindow::initComboBox(){
    //scene comboBox
    QStringList commands = { "Scene 1", "Scene 2", "Scene 3"};
    ui->sceneCombo->addItems(commands);
    ui->sceneCombo->setPalette(QColor(100,100,100));
    ui->sceneCombo->setGeometry(QRect(QPoint(windowWIdth/40, windowHeight/40), QSize(100,25)));
    connect(ui->sceneCombo, &QComboBox::currentTextChanged, this, &MainWindow::sceneChoice);
}

void MainWindow::displayImage(){
    QImage image("../data/render0_1.ppm");
    ui->displayLabel->setPixmap(QPixmap::fromImage(image));
    ui->displayLabel->setGeometry(windowWIdth*0.28,windowHeight*0.08, windowHeight*0.8,windowHeight*0.8);
    ui->displayLabel->setScaledContents(true);
}

void MainWindow::initArrowButtons(){
    ui->arrowLeft->setIcon(style()->standardIcon(QStyle::SP_ArrowLeft));
    ui->arrowRight->setIcon(style()->standardIcon(QStyle::SP_ArrowRight));
    ui->arrowDown->setIcon(style()->standardIcon(QStyle::SP_ArrowDown));
    ui->arrowUp->setIcon(style()->standardIcon(QStyle::SP_ArrowUp));

    ui->arrowLeft->setGeometry(QRect(QPoint(windowWIdth/2-155, windowHeight*0.92), QSize(100,25)));
    ui->arrowRight->setGeometry(QRect(QPoint(windowWIdth/2+55, windowHeight*0.92), QSize(100,25)));
    ui->arrowUp->setGeometry(QRect(QPoint(windowWIdth/2-50, windowHeight*0.90), QSize(100,25)));
    ui->arrowDown->setGeometry(QRect(QPoint(windowWIdth/2-50, windowHeight*0.94), QSize(100,25)));

    ui->arrowLeft->setPalette(QColor(170,170,170));
    ui->arrowRight->setPalette(QColor(170,170,170));
    ui->arrowUp->setPalette(QColor(160,160,160));
    ui->arrowDown->setPalette(QColor(160,160,160));
}

void MainWindow::sliderValue(){
    qDebug() << std::pow(2,ui->speedSlider->value());
}
void MainWindow::shading(){
}
void MainWindow::renderImage() {

    if(ui->speedSlider->value() > 0){
        Renderer::sampleAcuracy = std::pow(2,ui->speedSlider->value());
    }
    else{
        Renderer::sampleAcuracy= 0;
    }
    qDebug()<<"render from button with accuracy : "<<Renderer::sampleAcuracy;
    std::thread ren(&Renderer::render,Renderer::self);
    ren.detach();
}
void MainWindow::sceneChoice(){
    int id = ui->sceneCombo->currentIndex();
    qDebug() << "Selected scene : "<< id;
    std::thread SC(&SceneManager::loadPremadeScene,id);
    SC.detach();
}
void MainWindow::downloadImage(){
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"), "/home/adrien/Pictures/Wallpapers/untitled.jpg", tr("Images (*.png *.jpg)"));
}

MainWindow::~MainWindow(){
    delete ui;
}

void MainWindow::updateImage(const Vector3f * pix) {
    QImage image("../data/render0_0.ppm");
    auto* img = new QImage(Renderer::width, Renderer::height, QImage::Format_RGB32);


    for (int i = 0; i < Renderer::width; ++i) {
        for (int j = 0; j < Renderer::height; ++j) {
            int ind = i*Renderer::height+j;
            //std::cout<<pix[ind].x<<"/"<<pix[ind].y<<"/"<<pix[ind].z<<'\n';


            //QRgb rgb = qRgb((int)pix[ind].x,(int)pix[ind].y,(int)pix[ind].z/10);
            //QColor col = QColor(rgb);
            img->setPixelColor(j,i,QColor((int)pix[ind].x,(int)pix[ind].y,(int)pix[ind].z));
            //img->setPixelColor(i,j,QColor(0,200,0));
            //img->setPixelColor(i,j,col);
        }
    }

    //img->loadFromData(*Renderer::Qarr,"ppm");
    //ui->displayLabel->setPixmap(QPixmap::loadFromData(Renderer::Qarr,"ppm"));

    ui->displayLabel->setPixmap(QPixmap::fromImage(*img));
    delete img;
}



