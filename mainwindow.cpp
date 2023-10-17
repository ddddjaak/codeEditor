#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QFile>
#include <QMessageBox>
#include <QTextStream>
#include <QFontDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setCentralWidget(ui->textEdit);

    connect(ui->actionnew,&QAction::triggered,this,&MainWindow::New);
    connect(ui->actionopen,&QAction::triggered,this,&MainWindow::open);
    connect(ui->actionsave,&QAction::triggered,this,&MainWindow::save);
    connect(ui->actioncopy,&QAction::triggered,this,&MainWindow::copy);
    connect(ui->actionsaveAs,&QAction::triggered,this,&MainWindow::saveAs);
    connect(ui->actionabout,&QAction::triggered,this,&MainWindow::about);
    connect(ui->actioncut,&QAction::triggered,this,&MainWindow::cut);
    connect(ui->actionexit,&QAction::triggered,this,&MainWindow::exit);
    connect(ui->actionredo,&QAction::triggered,this,&MainWindow::redo);
    connect(ui->actionundo,&QAction::triggered,this,&MainWindow::undo);
    connect(ui->actionprint,&QAction::triggered,this,&MainWindow::print);
    connect(ui->actionselectFont,&QAction::triggered,this,&MainWindow::selectFont);
    connect(ui->actionpaste,&QAction::triggered,this,&MainWindow::paste);

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
#if QT_CONFIG(clipboard)
    ui->textEdit->copy();
#endif
}


void MainWindow::exit()
{
    QCoreApplication::quit();
}

void MainWindow::paste()
{
#if QT_CONFIG(clipboard)
    ui->textEdit->paste();
#endif
}

void MainWindow::selectFont()
{
    bool fontSelected;
    QFont font = QFontDialog::getFont(&fontSelected, this);
    if (fontSelected)
        ui->textEdit->setFont(font);
}

void MainWindow::print()
{
#if defined(QT_PRINTSUPPORT_LIB) && QT_CONFIG(printer)
    QPrinter printDev;
#if QT_CONFIG(printdialog)
    QPrintDialog dialog(&printDev,this);
    if (dialog.exec() == QDialog::Rejected)
        return;
#endif
    ui->textEdit->print(&printDev);
#endif
}

void MainWindow::undo()
{
    ui->textEdit->undo();
}

void MainWindow::redo()
{
    ui->textEdit->redo();
}

void MainWindow::cut()
{
#if QT_CONFIG(clipboard)
    ui->textEdit->cut();
#endif
}

void MainWindow::about()
{

}

void MainWindow::saveAs()
{
    QString fileName = QFileDialog::getSaveFileName(this,"Save as");
    QFile file(fileName);

    if(!file.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this,"Warning","Cannot save file: " + file.errorString());
        return;
    }
    currentfile = fileName;
    setWindowTitle(fileName);
    QTextStream out(&file);
    QString text = ui->textEdit->toPlainText();
    out << text;
    file.close();
}
