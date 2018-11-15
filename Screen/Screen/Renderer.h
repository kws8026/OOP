#ifndef RENDERER_H_
#define RENDERER_H_

#include <iostream>
#include "Utils.h"

using namespace std;

class Renderer {

	static const int screenWidth = 119;
    static const int screenHeight = 25;

	char		display[screenWidth + 1 + 1][screenHeight];
	Position	origin;

	Renderer() : origin(Borland::wherex(), Borland::wherey()) {
		// ���� ���� �������� �õ尪�� 10���� �����Ͽ� ������ ���� ���ڰ� �����ǵ��� ����.
		// ����� ����.
		// release�ÿ��� time(nullptr)�� �ٲپ� �õ尪�� ���������� �����ؾ� ��.
		srand(10);
	}

public:
	static Renderer& getInstance() {
		static Renderer instance;
		return instance;
	}	

	bool checkRange(const string& shape, Position pos)
	{
		int sz = shape.size();
		if (pos.x > 0) {
            if (pos.x + sz < screenWidth) return true;
		}
        if (pos.y > 0) {
            if (pos.y + sz < screenHeight-1) return true;
        }
		return false;
	}

	bool checkRange(int pos)
	{
		return pos >= 0 && pos < (screenWidth - 1);
	}

	void clear()
	{
		memset(display, ' ', (screenWidth + 1 + 1 )*screenHeight);
        for(int i = 0; i < screenHeight; i++){
		    display[screenWidth][i] = '\n';
		    display[screenWidth + 1][i] = '\0';
        }
	}

	bool draw(const string& shape, Position pos)
	{
		if (checkRange(shape, pos) == false) return false;
		memcpy(&display[pos.x][pos.y], shape.c_str(), shape.size());
        return true;
	}

	void render()
	{
		// make sure it should end with proper ending characters.
        for (int i = 0; i < screenHeight; i++) {
            display[screenWidth][i] = '\n';
            display[screenWidth + 1][i] = '\0';
        }

		Borland::gotoxy(&origin);
		cout << display;
		Borland::gotoxy(&origin);
	}

	int getScreenLength() { return screenWidth; }
    Position getScreenSize() { return {screenWidth,screenHeight}; }
};

#endif 
