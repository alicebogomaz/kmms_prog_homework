#include <QApplication>

#include "welcome_window.hpp"
#include "keyboard_window.hpp"

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    biv::WelcomeWindow welcome;
    biv::KeyBoardWindow keyboard_window;

    QObject::connect(&welcome, &biv::WelcomeWindow::open_keyboard,
                     &keyboard_window, &biv::KeyBoardWindow::show);
    QObject::connect(&welcome, &biv::WelcomeWindow::open_keyboard,
                     &welcome, &biv::WelcomeWindow::hide);

    welcome.show();

    return app.exec();
}
