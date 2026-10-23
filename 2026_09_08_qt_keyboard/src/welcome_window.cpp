#include "welcome_window.hpp"

#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>

using aliceB::WelcomeWindow;

WelcomeWindow::WelcomeWindow(QWidget* parent) : QWidget(parent) {
    setWindowTitle("Добро пожаловать!");
    resize(600, 400);

    QLabel* title = new QLabel("Клавик ждёт тебя!", this);
    title->setAlignment(Qt::AlignCenter);
    title->setFont(QFont("Roboto", 28));

    start_button = new QPushButton("Перейти к Клавику", this);
    start_button->setFont(QFont("Roboto", 20));

    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addStretch();
    layout->addWidget(title);
    layout->addSpacing(30);
    layout->addWidget(start_button, 0, Qt::AlignCenter);
    layout->addStretch();

    connect(start_button, &QPushButton::clicked,
            this, &WelcomeWindow::on_start_clicked);
}

void WelcomeWindow::on_start_clicked() {
    emit open_keyboard();
}
