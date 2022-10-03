#pragma once

#include "libs.hpp"

#define WDSX 4
#define WDSY 2

struct RGB
{
	short r;
	short g;
	short b;	
};

const RGB defaultFC = { 240, 240, 240 };
const RGB defaultBC = { 12, 12, 12 };
const RGB opzioneAbilitata = { 240, 240, 240 };
const RGB opzioneDisabilitata = { 100, 100, 100 };
const RGB opzioneCorrente = { 0, 100, 0 };

void setCursorPosition(short x, short y);
COORD getCursorPosition();
string fC(int r, int g, int b);
string fC(int c);
string fC(RGB rgb);
string bC(int r, int g, int b);
string bC(int c);
string bC(RGB rgb);

