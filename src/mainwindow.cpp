//
// Created by adrien on 18/09/2020.
//

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "iostream"
#include "Renderer.h"
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow){
    ui->setupUi(this);
    setWindowTitle("Ray Tracing");
    initWindow();
    displayImage();
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
    ui->speedSlider->setRange(0, 100);
    connect(ui->speedSlider, SIGNAL(sliderReleased()), SLOT(sliderValue()));
}

void MainWindow::initButtons(){
    //shading button
    ui->shadingButton->setText("Shading");
    ui->shadingButton->setPalette(QColor(100,100,100));
    ui->shadingButton->setGeometry(QRect(QPoint(windowWIdth/40+220, windowHeight/40), QSize(100,25)));
    connect(ui->shadingButton, SIGNAL(clicked()), SLOT(shading()));

    //sphere marching button
    ui->sphereMarchingButton->setText("S Marching");
    ui->sphereMarchingButton->setPalette(QColor(100,100,100));
    ui->sphereMarchingButton->setGeometry(QRect(QPoint(windowWIdth/40+330, windowHeight/40), QSize(100,25)));
    connect(ui->sphereMarchingButton, SIGNAL(clicked()), SLOT(sphereMarching()));

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
    QImage image("../data/render0_0.ppm");
    ui->displayLabel->setPixmap(QPixmap::fromImage(image));
    ui->displayLabel->setGeometry(windowWIdth*0.28,windowHeight*0.08, windowHeight*0.8,windowHeight*0.8);
    ui->displayLabel->setScaledContents(true);
}

void MainWindow::sliderValue(){
    qDebug() << ui->speedSlider->value();
}
void MainWindow::shading(){
}
void MainWindow::sphereMarching(){
}
void MainWindow::sceneChoice(){
}
void MainWindow::downloadImage(){
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"), "/home/adrien/Pictures/Wallpapers/untitled.jpg", tr("Images (*.png *.jpg)"));
    //image.save(name);
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

