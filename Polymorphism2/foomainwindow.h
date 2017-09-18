#ifndef FOOMAINWINDOW_H
#define FOOMAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class FooMainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::FooMainWindow *ui;
};

#endif // FOOMAINWINDOW_H
