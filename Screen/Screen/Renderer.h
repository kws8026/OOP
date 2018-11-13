#ifndef RENDERER_H_
#define RENDERER_H_

#include <iostream>
#include "Utils.h"

using namespace std;

class Renderer {

	static const int screenSize = 119;
	char		display[screenSize + 1 + 1];
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

	bool checkRange(const string& shape, int pos)
	{
		int sz = shape.size();
		if (pos < 0) {
			if (pos + sz >= 0) return true;
		}
		else {
			if (pos + sz < screenSize) return true;
		}
		return false;
	}

	bool checkRange(int pos)
	{
		return pos >= 0 && pos < (screenSize - 1);
	}

	void clear()
	{
		memset(display, ' ', screenSize);
		display[screenSize] = '\n';
		display[screenSize + 1] = '\0';
	}

	void draw(const string& shape, Position pos)
	{
        Position dest_pos = pos;
		if (checkRange(shape, pos.x) == false) return;

		const char* source = shape.c_str();
		int len = shape.size();
		if (pos.x < 0) {
			source -= pos.x;
			len += pos.x;
			dest_pos.x = 0;
		}
		else if (pos.x + shape.size() > screenSize - 1) {
			len = screenSize - pos.x;
		}
		memcpy(display + dest_pos.x, source, len);
	}

	void render()
	{
		// make sure it should end with proper ending characters.
		display[screenSize] = '\n';
		display[screenSize + 1] = '\0';

		Borland::gotoxy(&origin);
		cout << display;
		Borland::gotoxy(&origin);
	}

	int getScreenLength() { return screenSize; }
};

#endif 
