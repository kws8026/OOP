#ifndef UTILS_H_
#define UTILS_H_

#include <Windows.h>



struct Position {
	int x;
	int y;
	Position(int x=0, int y=0) : x(x), y(y) {}
    Position operator+(Position &ref){
        return Position(x+ref.x,y+ref.y);}
    Position operator+(int &ref) {
        return Position(x + ref, y + ref);}
    Position operator-(Position &ref){
        return Position(x - ref.x, y - ref.y);}
    Position operator-(int &ref) {
        return Position(x - ref, y - ref);}
};

class Borland {

public:
	static int wherex()
	{
		CONSOLE_SCREEN_BUFFER_INFO  csbiInfo;
		GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbiInfo);
		return csbiInfo.dwCursorPosition.X;
	}
	static int wherey()
	{
		CONSOLE_SCREEN_BUFFER_INFO  csbiInfo;
		GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbiInfo);
		return csbiInfo.dwCursorPosition.Y;
	}
	static void gotoxy(int x, int y)
	{
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), _COORD{ (SHORT)x, (SHORT)y });
	}
	static void gotoxy(const Position* pos)
	{
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), _COORD{ (SHORT)pos->x, (SHORT)pos->y });
	}
};

#endif 
