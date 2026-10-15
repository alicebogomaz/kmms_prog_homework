#pragma once

#include <QWidget>

class QPushButton;

namespace biv {
	class WelcomeWindow : public QWidget {
		Q_OBJECT

public:
    explicit WelcomeWindow(QWidget* parent = nullptr);

	signals:
		void open_keyboard();

	private slots:
		void on_start_clicked();

	private:
		QPushButton* start_button;
	};
}
