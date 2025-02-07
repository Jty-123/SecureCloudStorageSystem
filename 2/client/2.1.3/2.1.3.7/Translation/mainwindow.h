#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTranslator>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
protected:
//    void changeEvent(QEvent *e);

private:
    Ui::MainWindow *ui;
    QTranslator *translator {translator=nullptr};

private slots:
    void On_Chinese();
    void On_English();
};

#endif // MAINWINDOW_H
