#ifndef ITEMS_H_
#define ITEMS_H_

#include "Item.h"
#include <algorithm>
#include <vector>

class Items {
	Renderer&			renderer;
	vector<Item*>		container;

	const unsigned int max_Items;
	Items()
		: renderer(Renderer::getInstance()), max_Items(150)
	{
		Position screenSize = renderer.getScreenSize();
		bool*  board;
		board = (bool*)calloc(screenSize.x*screenSize.y, sizeof(bool));
		memset(board, false, screenSize.x*screenSize.y);
		while (container.size() != max_Items) {
			Position temp = { rand() % screenSize.x,rand() % screenSize.y };
			if (board[screenSize.x*temp.y + temp.x] == true)
				continue;
			else {
				board[screenSize.x*temp.y + temp.x] = true;
				container.push_back(new Item({ temp.x,temp.y }));
			}
		}
		free(board);
	}

public:
	
	static Items& getInstance() {
		static Items instance;
		return instance;
	}
	void update()
	{
		for (auto Item : container) Item->update();
		container.erase(remove_if(container.begin(), container.end(),
			[](Item* item) {
			if (item->isAlive() == false) {
				delete item; // you need to free the dynamically allocated enemies.
				return true;
			}
			return false;
		}), container.end());
	}

	void draw()
	{
		for (auto Item : container) Item->draw();
		Borland::gotoxy(0, 20); printf("# of Items = %3d", (int)container.size());
	}
	int absorbed(const GameObject& target)
	{
		int count = 0;
		for (auto Item : container) 
			if(Item->absorbed(target))
				count++;
		return count;
	}

	bool empty() {
		return container.empty();
	}
};


#endif