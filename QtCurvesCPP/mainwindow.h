#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

// namespace
// MainWindow declared in the Ui namespace is not
// the same type as MainWindow from the
// global namespace!
// MainWindow owns a Ui::MainWindow
namespace Ui {
class MainWindow;
}

// class declaration and inheritance?
// Qmainwindow as our baseclass and our
// MainWindow which inherits from it.
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    // constructor prototype
    explicit MainWindow(QWidget *parent = 0);

    // deconstructor
    ~MainWindow();


    // Interesting part, this pointer to MainWindow in
    // the Ui namespace. This pointer is the object
    // that we will use to access our user interface
    // elements from the code that we write.
    // From code, we will access a push button on the
    // the design, via the ui object (whose type
    // is Ui::MainWindow)

    // more function prototypes
private slots:
    void on_btnAstroid_clicked();

    void on_btnCycloid_clicked();

    void on_btnHuygens_clicked();

    void on_btnHypo_clicked();


    // declaring pointer
private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
