#include "keyboard_window.hpp"
#include "keyboard_data.hpp"

#include <QHBoxLayout>
#include <QLabel>
#include <QPixmap>
#include <QVBoxLayout>

using aliceB::KeyBoardWindow;

KeyBoardWindow::KeyBoardWindow(QWidget* parent) : QWidget(parent) {
	const int keyboard_width = 1160;
	resize(keyboard_width, 710);
    setWindowTitle("Хороший Клавик");
	
	QPixmap pixmap("img/klavik.jpg");
	QLabel* image = new QLabel(this);
	image->setFixedSize(200, 200);
	image->setPixmap(pixmap);
	image->setScaledContents(true);
	
	QHBoxLayout* smail_layout = new QHBoxLayout();
	smail_layout->addWidget(image);

    display = new QLineEdit();
	display->setMinimumHeight(80);
	display->setFont(QFont("Roboto", 40));
    display->setReadOnly(true);
	display->setText("гав.......");

	keyboard = new KeyBoard(keyboard_width);
	
	connect(keyboard, &KeyBoard::key_clicked, this, &KeyBoardWindow::on_key_clicked);

    QVBoxLayout* main_layout = new QVBoxLayout(this);
	main_layout->addLayout(smail_layout);
    main_layout->addWidget(display);
    main_layout->addWidget(keyboard);
}


void KeyBoardWindow::keyPressEvent(QKeyEvent* event) {
    QString text = event->text();
    KeyBoardData data;
    int code = data.get_code(text);

    if (keyboard->is_key_allowed(code)) {
        display->setText(display->text() + text.toUpper());
        keyboard->animate_button(code);
    }
}


void KeyBoardWindow::on_key_clicked(int code) {
    if (!keyboard->is_key_allowed(code)) {
        return;
    }
    display->setText(display->text() + keyboard->get_key_text(code));
    keyboard->animate_button(code);
}
