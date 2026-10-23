#pragma once

#include <cstddef>

#include <QPushButton>
#include <QString>
#include <QWidget>

namespace aliceB {
	class KeyBoardButton : public QPushButton {
		Q_OBJECT
		
		private:
			int code;
			
		public:
			KeyBoardButton(const QString& text = "", QWidget* parent = nullptr);
			
			int get_code() const noexcept { return code; }
	};
}
