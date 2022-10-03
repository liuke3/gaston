#include "console+vts.hpp"

void setCursorPosition(short x, short y)
{
    // Ottengo l'output standard.
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    // Ottengo le informazioni del buffer dello screen.
    GetConsoleScreenBufferInfo(hOut, &csbi);
    // Imposto la posizione del cursore.
    SetConsoleCursorPosition(hOut, COORD{ (short)x, (short)y });
}

COORD getCursorPosition()
{
    // Ottengo l'output standard.
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    // Ottengo le informazioni del buffer dello screen.
    GetConsoleScreenBufferInfo(hOut, &csbi);
    // Ottengo la posizione del cursore.
    return COORD{ csbi.dwCursorPosition.X, csbi.dwCursorPosition.Y };
}

// Imposto il colore di primo piano.
string fC(int r, int g, int b)
{
	stringstream t;
	t << "\x1b[38;2;" << r << ";" << g << ";" << b << "m";
	return t.str();
}

string fC(int c)
{
	return fC(c, c, c);
}

string fC(RGB rgb)
{
	return fC(rgb.r, rgb.g, rgb.b);
}

// Imposto il colore di secondo piano.
string bC(int r, int g, int b)
{
	stringstream t;
	t << "\x1b[48;2;" << r << ";" << g << ";" << b << "m";
	return t.str();
}

string bC(int c)
{
	return bC(c, c, c);
}

string bC(RGB rgb)
{
	return bC(rgb.r, rgb.g, rgb.b);
}

