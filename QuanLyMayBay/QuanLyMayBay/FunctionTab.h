#pragma once
#include<iostream>
#include"define.h"
#include"Button.h"

class FunctionTab {
protected:
	int currentMenu, currentPage, maxPage;
	char title[30], instruction[30];
public:
	FunctionTab() {
		currentMenu = 0;
		currentPage = maxPage = 1;
		strcpy_s(title, "");
		strcpy_s(instruction, "");
	}
	//Ve tieu de cho tab
	void drawTitle(char text[30]) {
		strcpy_s(title, text);
		setbkcolor(SUBWINDOW_BACKGROUND);
		setcolor(BLACK);
		outtextxy((SUBWINDOW_LEFT + SUBWINDOW_RIGHT - textwidth(title)) / 2, SUBWINDOW_TOP + 10, title);

	}
	//Ve huong dan
	void drawInstruction(char text[30]) {
		strcpy_s(instruction, text);
		setbkcolor(SUBWINDOW_BACKGROUND);
		setcolor(GREEN);
		outtextxy(LEFT_BORDER, BOTTOM_BORDER + 50, instruction);
	}

	void drawBackground() {
		setcolor(TAB_ON_SELECTED_BACKGROUND);
		rectangle(SUBWINDOW_LEFT, SUBWINDOW_TOP, SUBWINDOW_RIGHT, SUBWINDOW_BOTTOM);
		setfillstyle(SOLID_FILL, SUBWINDOW_BACKGROUND);
		bar(SUBWINDOW_LEFT + 1, SUBWINDOW_TOP + 1, SUBWINDOW_RIGHT - 1,
			SUBWINDOW_BOTTOM - 1);

	}


	//-------HAM XU LI SO TRANG
	void onButtonPage(int page, bool isMinus, int limit) {
		switch (isMinus) {

		case true: {
			if (page <= 1)
				break;

			(this->currentPage) -= 1;
			delay(100);
			break;
		}
				
		case false: {
			if (page >= limit + 1)
				return;


			(this->currentPage) += 1;
			delay(100);
			break;
		}



		}
	}
	void showPage(int x, int y, int page, int limit)
	{
		setcolor(PAGE_COLOR);
		setbkcolor(SUBWINDOW_BACKGROUND);
		char s[5] = "";
		sprintf_s(s, "%d", page);
		outtextxy(x, y, s);
		x += textwidth(s);
		strcpy_s(s, " / ");
		outtextxy(x, y, s);
		x += textwidth(s);
		sprintf_s(s, "%d", limit);
		outtextxy(x, y, s);
	}

	//-------XU LI INPUT
	int getInput() {
		for (int i = 65; i <= 90; i++) {
			if (GetAsyncKeyState((char)(i)) & 1) {
				return i;
			}
		}
		for (int i = 97; i <= 122; i++) {
			if (GetAsyncKeyState((char)(i)) & 1) {
				return i - 32;
			}
		}
		//So
		for (int i = 48; i <= 57; i++) {
			if (GetAsyncKeyState((char)i) & 1) {
				return i;
			}
		}
		if (GetAsyncKeyState(VK_BACK) & 1) return -1;
		if (GetAsyncKeyState(VK_SPACE) & 1) return ' ';
		if (GetAsyncKeyState(VK_TAB) & 1) return  (int)'\t';
		if (GetAsyncKeyState(VK_UP) & 1) return 1;
		if (GetAsyncKeyState(VK_DOWN) & 1) return 2;
		if (GetAsyncKeyState(VK_RETURN) & 1) return 3;
		return 0;
	}
	bool isPointed(int left,int top,int right, int bottom) {
		if (mousex() <= right && mousex() >= left && mousey() <= bottom && mousey() >= top) {
			return true;
		}
		return false;
	}
	bool  isLeftMouseClicked(int left,int top,int right,int bottom) {
		if (isPointed(left,top,right,bottom) && GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
			return true;
		}
		return false;
	}
	bool  isRightMouseClicked(int left, int top, int right, int bottom) {
		if (isPointed(left, top, right, bottom) && GetAsyncKeyState(VK_RBUTTON) & 0x8000) {
			return true;
		}
		return false;
	}

	void virtual initEdittext() = 0;
	void virtual initButton() = 0;
	void virtual drawUI() = 0;

};
