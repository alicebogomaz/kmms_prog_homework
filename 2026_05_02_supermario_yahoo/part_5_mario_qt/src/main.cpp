#include <QApplication>
#include "qt_game_window.hpp"

int main(int argc, char* argv[]) {
	QApplication app(argc, argv);

	biv::QtGameWindow window;
	window.showMaximized();

	return app.exec();
}
