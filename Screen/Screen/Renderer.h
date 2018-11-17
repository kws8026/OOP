#ifndef RENDERER_H_
#define RENDERER_H_

#include <iostream>
#include "Utils.h"

using namespace std;

class Renderer {

	static const int screenWidth = 119;
    static const int screenHeight = 20;

	char		display[screenHeight][screenWidth + 1 + 1];
	Position	origin;

	Renderer() : origin(Borland::wherex(), Borland::wherey()) {
		srand(10);
	}

public:
	static Renderer& getInstance() {
		static Renderer instance;
		return instance;
	}	

	bool checkRange(const string& shape, Position pos)
	{
		int sz = (int)shape.size();
		if (pos.x < 0 || pos.x + sz > screenWidth ||
			pos.y < 0 || pos.y + sz > screenHeight)
        return false;
		return true;
	}

	bool checkRange(int pos)
	{
		return pos >= 0 && pos < (screenWidth - 1);
	}

	void clear()
	{
		memset(display, ' ', (screenWidth + 1 + 1 )*screenHeight);
        for(int i = 0; i < screenHeight; i++){
		    display[i][screenWidth] = '\n';
			if(i == screenHeight-1)
				display[i][screenWidth + 1] = '\0';
			else
				display[i][screenWidth + 1] = '\r';
        }
	}

	bool draw(const string& shape, Position pos)
	{
		if (checkRange(shape, pos) == false) return false;
		memcpy(display[pos.y] + pos.x, shape.c_str(), shape.size());
        return true;
	}

	void render()
	{
		// make sure it should end with proper ending characters.
		for (int i = 0; i < screenHeight; i++) {
			display[i][screenWidth] = '\n';
			if (i == screenHeight - 1)
				display[i][screenWidth + 1] = '\0';
			else
				display[i][screenWidth + 1] = '\r';
		}

		Borland::gotoxy(&origin);
		cout << *display;
		Borland::gotoxy(&origin);
	}

	int getScreenLength() { return screenWidth; }
    Position getScreenSize() { return {screenWidth,screenHeight}; }
};

#endif 
