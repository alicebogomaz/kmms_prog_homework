#include <QApplication>

#include "welcome_window.hpp"
#include "keyboard_window.hpp"

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    aliceB::WelcomeWindow welcome;
    aliceB::KeyBoardWindow keyboard_window;

    QObject::connect(&welcome, &aliceB::WelcomeWindow::open_keyboard,
                     &keyboard_window, &aliceB::KeyBoardWindow::show);
    QObject::connect(&welcome, &aliceB::WelcomeWindow::open_keyboard,
                     &welcome, &aliceB::WelcomeWindow::hide);

    welcome.show();

    return app.exec();
}
