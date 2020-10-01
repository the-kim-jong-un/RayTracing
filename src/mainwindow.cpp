#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow){
    ui->setupUi(this);
    setWindowTitle("Ray Tracing");

    initWindow();
    initArrowButtons();
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
    QImage image("/home/adrien/wallpaper.jpg");
    ui->displayLabel->setPixmap(QPixmap::fromImage(image));
    ui->displayLabel->setGeometry(windowWIdth*0.1,windowHeight*0.08, windowWIdth*0.8,windowHeight*0.8);
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
