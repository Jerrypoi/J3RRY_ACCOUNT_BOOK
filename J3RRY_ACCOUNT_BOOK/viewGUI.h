#ifndef VIEWGUI_H
#define VIEWGUI_H
#ifdef __cplusplus
extern "C"{

#endif
	typedef enum keystroke {
		UP = 72,
		DOWN = 80,
		LEFT = 75,
		RIGHT = 77,
		ENTER = 13,
		ESC = 27,
		BACKSPACE = 8
	} keystroke;
	void ACCOUNT_BOOK_GUI_MAIN_LOOP();

#ifdef __cplusplus
}
#endif

#endif
