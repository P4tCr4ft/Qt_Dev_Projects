#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QStatusBar>
#include <QPixmap>

namespace Ui {
  class MainWindow;
}

class MainWindow : public QMainWindow
{
 Q_OBJECT
public:

 explicit MainWindow(QWidget *parent = 0);
 virtual ~MainWindow();

 void closeEvent(QCloseEvent *event);

private:

 void initGui();

 void loadSettings();

 void saveSettings();

private slots:

 void handleButton();

private:

 QString m_sSettingsFile;
 QLabel* m_pLabel;
 QLabel* m_pLabel2;
 QLineEdit* m_pEdit;
 QPushButton* m_pButton;

 QStatusBar *m_statusBar;
 QPixmap *m_redLight;
// QPixmap *m_greenLight;
// QPixmap *m_orangeLight;
// QPixmap *m_greyLight;

};

#endif // MAINWINDOW_H
