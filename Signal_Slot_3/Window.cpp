#include "Window.h"
#include "ui_Window.h"

Window::Window(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Window)
{
    ui->setupUi(this);

    editor = new QTextEdit();
    QPushButton *sendButton = new QPushButton("&Send message");

    connect(sendButton, SIGNAL(clicked()), this, SLOT(sendMessage()));

    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->addStretch();
    buttonLayout->addWidget(sendButton);
    buttonLayout->addStretch();

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(editor);
    layout->addLayout(buttonLayout);

    setWindowTitle("Custom Type Sending");
}

Window::~Window()
{
    delete ui;
}

void Window::sendMessage(){
    thisMessage = Message(editor->toPlainText(), thisMessage.headers());
    emit messageSent(thisMessage);
}

void Window::setMessage(const Message &message){
    thisMessage = message;
    editor->setPlainText(thisMessage.body());
}
