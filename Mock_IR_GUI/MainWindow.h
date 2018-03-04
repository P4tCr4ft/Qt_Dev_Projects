#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_radioButton_clicked();

    void on_radioButton_toggled(bool checked);

    void on_radioButton_2_toggled(bool checked2);

    void on_radioButton_2_clicked();

private:
    Ui::MainWindow *ui;
    QWidget *some_widget;
};

#endif // MAINWINDOW_H
