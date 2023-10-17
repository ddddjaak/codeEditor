#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QFile>
#include <QMessageBox>
#include <QTextStream>
#include <QLabel>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //QPushButton *button1 = new QPushButton("&Download", this);

    //this->setCentralWidget(ui->textEdit);
//    QPixmap pixmap;//定义QPixmap对象
//    pixmap.load(":/images/girl");//加载图片
//    QLabel *my_label= new QLabel(this);
//   // my_label->resize(64,64);
//    my_label->move(200,200);
//    my_label->setPixmap(pixmap);   //图片设置到QLabel中
   // ui->label1->setPixmap(QPixmap("/images/girl"));
    connect(ui->actionnew,&QAction::triggered,this,&MainWindow::New);
    connect(ui->actionopen,&QAction::triggered,this,&MainWindow::open);
    connect(ui->actionsave,&QAction::triggered,this,&MainWindow::save);
    connect(ui->actioncopy,&QAction::triggered,this,&MainWindow::copy);
    connect(ui->pushButton,&QPushButton::clicked,this,&MainWindow::yes);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::New()
{
    currentfile.clear();
    ui->textEdit->setText(QString());
}

void MainWindow::open()
{
    QString fileName = QFileDialog::getOpenFileName(this,"Open the file");
    QFile file(fileName);
    currentfile = fileName;
    if (!file.open(QIODevice::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this,"Warning","Cannot open file: " + file.errorString());
        return;
    }

    setWindowTitle(fileName);
    QTextStream in(&file);
    QString text = in.readAll();
    ui->textEdit->setText(text);
    file.close();
}

void MainWindow::save()
{
    QString fileName;
    if (currentfile.isEmpty()) {
        fileName = QFileDialog::getSaveFileName(this,"Save");
        currentfile = fileName;
    } else {
        fileName = currentfile;
    }

    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this,"Warning","Cannot save file:"+file.errorString());
        return;
    }
    setWindowTitle(fileName);
    QTextStream out(&file);
    QString text = ui->textEdit->toPlainText();
    out << text;
    file.close();
}

void MainWindow::copy()
{

}

void MainWindow::yes()
{
    QPixmap pixmap;//定义QPixmap对象
    pixmap.load(":/images/life.png");//加载图片
    //QLabel *my_label= new QLabel(this);
    // my_label->resize(64,64);
    //my_label->move(200,200);
    //my_label->setPixmap(pixmap);   //图片设置到QLabel中
    ui->label->setPixmap(pixmap);
}
