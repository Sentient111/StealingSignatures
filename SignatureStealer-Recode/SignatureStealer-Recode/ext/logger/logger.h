#pragma once
#include <string>
#include <Windows.h>

namespace logger {

	enum e_logtype : int {
		success = 0,
		info = 1,
		error = 2
	};


	inline void log(e_logtype type, std::string msg, ...) {

		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		const char* prefix = "";

		switch (type) {
		case e_logtype::success:
			SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
			prefix = "[#]";
			break;
		case e_logtype::info:
			SetConsoleTextAttribute(hConsole, FOREGROUND_WHITE | FOREGROUND_WHITE | FOREGROUND_INTENSITY);
			prefix = "[+]";
			break;
		case e_logtype::error:
			SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
			prefix = "[!]";
			break;
		}
		std::string final_string = prefix + msg + "\n";
		va_list args;
		va_start(args, msg);
		std::vprintf(final_string.c_str(), args);
		va_end(args);
		SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

	}

}

/*
SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
*/