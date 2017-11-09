#include "mainwindow.h"
#include <QCoreApplication>
#include <QSettings>
#include <QApplication>
#include <QLayout>

MainWindow::MainWindow(QWidget *parent)
 : QMainWindow(parent),
 m_pLabel(NULL),
 m_pEdit(NULL),
 m_pButton(NULL),
 m_statusBar(NULL),
  m_redLight(new QPixmap())
{
 initGui();

// m_sSettingsFile = QApplication::applicationDirPath().left(1) + ":/demosettings.ini";
 m_sSettingsFile = "C:/Temp/demosettings.ini";
// QSettings settings(m_sSettingsFile, QSettings::IniFormat);
 loadSettings();

if (m_pButton)
 {
  connect(m_pButton, SIGNAL (released()),this, SLOT (handleButton()));
 }
}

// the following code could also go inside function called saveSettings,
// and then get called in this closeEvent function
void MainWindow::closeEvent(QCloseEvent *event){
// QSettings settings(m_sSettingsFile, QSettings::IniFormat);
// settings.setValue("WidgetGeometry", saveGeometry());
// settings.setValue("widgetWindowState", saveState());
    saveSettings();
 QMainWindow::closeEvent(event);
}

void MainWindow::initGui()
{
// m_pLabel = new QLabel("Red", this);
// m_pLabel->setText("redDot");
// m_pLabel->setGeometry(0, 0, 400, 40);
 m_pEdit = new QLineEdit("", this);
 m_pEdit->setGeometry(0,40, 800,40);
 m_pButton = new QPushButton("OK", this);
 m_pButton->setGeometry(0,80, 800,40);
 m_pLabel = new QLabel("Red Light", this);
 m_pLabel2 = new QLabel("Green Light", this);
// m_pLabel->setGeometry(0, 0, 400, 40);

 m_statusBar = new QStatusBar(this);

// QString location = R"(C:/temp/redLight.png)";
// QPixmap img(location);
// m_pLabel->setPixmap(img.scaled(20, 20));


// m_redLight = new QPixmap("C:/temp/redLight.png");

 m_pLabel->setPixmap(QPixmap("C:/temp/redLight.png").scaled(25, 25));
// m_pLabel->setText("Testing");
 m_pLabel2->setPixmap(QPixmap("C:/temp/greenLight.png").scaled(25, 25));
// m_pLabel->setScaledContents(true);
// m_pLabel->setPixmap(m_redLight);

 m_statusBar->addWidget(m_pLabel);
 m_statusBar->addWidget(m_pLabel2);

//QFrame *_frame = new QFrame();
//_frame->setFrameStyle(QFrame::Panel | QFrame::Sunken);

//QWidget *widgey = new QWidget();

//QHBoxLayout *layout = new QHBoxLayout(_frame);
//layout->setContentsMargins(0, 0, 5, 5);

//QGridLayout *layout = new QGridLayout(widgey);

//row->addWidget(m_pLabel->setPixmap(QPixmap("C:/temp/redLight.png").scaled(25, 25)));
//layout->addWidget(m_pLabel,0,0,1,1,Qt::AlignVCenter);
//row->addWidget(m_pLabel2->setPixmap(QPixmap("C:/temp/greenLight.png").scaled(25, 25)));
//layout->addWidget(m_pLabel2,0,1,1,1,Qt::AlignVCenter);

//m_statusBar->addWidget(widgey, 0);

 connect(m_redLight, SIGNAL (re))
}

void MainWindow::loadSettings()
{
 QSettings settings(m_sSettingsFile, QSettings::IniFormat);
 QString sText = settings.value("text", "").toString();
 if (m_pLabel)
 {
  m_pLabel->setText(sText);
 }
 restoreGeometry(settings.value("WidgetGeometry").toByteArray());
 restoreState(settings.value("widgetWindowState").toByteArray());
}



// this save settings is only used when button pushed, bit confusing,
// so save settings for purpose of saving config file occurs in the
// closeEvent, not here.
void MainWindow::saveSettings()
{
 QSettings settings(m_sSettingsFile, QSettings::IniFormat);
 QString sText = (m_pEdit) ? m_pEdit->text() : "";
 settings.setValue("text", sText);
 settings.setValue("WidgetGeometry", saveGeometry());
 settings.setValue("widgetWindowState", saveState());
 // check file location
 QString fileLoc = QApplication::applicationDirPath();
 if (m_pLabel)
 {
//  m_pLabel->setText(sText);
  m_pLabel->setText(fileLoc);
 }
 settings.sync();
}

void MainWindow::handleButton()
{
 saveSettings();
}

MainWindow::~MainWindow()
{

}
