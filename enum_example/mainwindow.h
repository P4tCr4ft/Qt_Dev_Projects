#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSettings>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    enum LAYOUT { LAYOUT_CASCADE, LAYOUT_TILED, LAYOUT_TABBED};

    LAYOUT current_layout = LAYOUT_TILED; // default

    // for this example will just use mainwindow commands,
    // keep in mind command for subwindow slightly different
    // where have to stipulate saveGeometry call with subwindow obj
    void loadConfiguration(QSettings &settings){
        current_layout = settings.value("subWindowLayout", current_layout);
        switch (current_layout){
            case LAYOUT_CASCADE:
                restoreGeometry(settings.value("Geometry").toByteArray()); break;
            case LAYOUT_TILED:
                restoreGeometry(settings.value("Geometry").toByteArray()); break;
            case LAYOUT_TABBED:
                QString nothin = "Do nothing ..."; break;
        }
    }

    void saveConfiguration(QSettings &settings){
        settings.setValue("subWindowLayout", current_layout);
    }




private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
