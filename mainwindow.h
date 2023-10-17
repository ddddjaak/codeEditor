#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void New();
    void open();
    void save();
    void saveAs();
    void print();
    void cut();
    void paste();
    void undo();
    void redo();
    void selectFont();
    void about();
    void copy();
    void exit();
private:
    Ui::MainWindow *ui;
    QString currentfile;
};
#endif // MAINWINDOW_H
