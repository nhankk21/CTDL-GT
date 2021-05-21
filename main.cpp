//#include <winbgim.h>
#include <graphics.h>
#include <windows.h>
#include <iostream>
#include <string>
#include <string.h>

using namespace std;
 
int currentPage = 1;
int totalTables = 1;
int currentTable = 1;
int X = -1;
int Y = -1;
void setMenu(int x, int y);
void MaterialPage(int clr){
	
	setfillstyle(20, clr);
	bar(0, 0, 300, 50);
	rectangle(0, 0, 300, 50);
	setbkcolor(clr); 
    outtextxy(100, 15,"Vat tu");
}
void EmployeePage(int clr){
	
	setfillstyle(20, clr);
	bar(301, 0, 600, 50);
	rectangle(301, 0, 600, 50);
	setbkcolor(clr);
	outtextxy(400, 15,"Nhan vien");
}

void BillPage(int clr){
	
	setfillstyle(20, clr);
	bar(601, 0, 900, 50);
	rectangle(601, 0, 900, 50);
	setbkcolor(clr);
	outtextxy(700, 15,"Hoa don");
	
}
void MorePage(int clr){
	setfillstyle(20, clr);
	bar(901, 0, 1200, 50);
	rectangle(901, 0, 1200, 50); 
	setbkcolor(clr);
    outtextxy(1000, 15,"Them");
}
void button(int l, int r, int t, int b, char* text, int clr, int textsize){
	setfillstyle(20, clr);
	bar(l, t, r, b);
	rectangle(l - 1, t - 1, r + 1, b + 1); 
	setbkcolor(clr);
	settextstyle(10, 0, textsize);
	outtextxy(l + 1, t + 1, text);
	settextstyle (4, 0, 2);
	setbkcolor(15);
}

void box(int l, int r, int t, int b, int clr){
	setfillstyle(20, clr);
	bar(l, t, r, b);
	rectangle(l - 1, t - 1, r + 1, b + 1); 
	setbkcolor(clr);
}
void textfield(int l, int t, int size, char* text){
	settextstyle(10, 0, size);
	outtextxy(l + 1, t + 1, text);
	settextstyle (4, 0, 2);
}
void edittext(int l, int t);
void MaterialMenu(){
	setfillstyle(20, 15);
	bar(0, 51, 1200, 700);
	setcolor(0);
	rectangle(0, 51, 1200, 700);
	button(20, 170, 80, 105, "IN DANH SACH", 7, 2);
	button(760, 820, 80, 105, " TIM", 7, 2);
	box(20, 750, 140, 620, 15);
	textfield(305, 630, 2, "Trang:");
	button(150, 275, 650, 675, "Trang truoc", 7, 1);
	button(405, 510, 650, 675, "Trang sau", 7, 1);
	textfield(315, 650, 2, "1");
	textfield(345, 650, 2, "/");
	textfield(360, 650, 2, "5");
	box(770, 1170, 140, 670, 15);
	box(790, 1155, 500, 650, 15);
	
	button(20, 110, 140, 170, "  STT", 7, 2);
	button(110, 350, 140, 170, "      MA VAT TU", 7, 2);
	button(350, 750, 140, 170, "           TEN VAT TU", 7, 2);
	for (int i = 1; i <= 15; ++i){
		box(20, 110, 140 + 30 * i, 170 + 30 * i, 15);
		box(110, 350, 140 + 30 * i, 170 + 30 * i, 15);	
		box(350, 750, 140 + 30 * i, 170 + 30 * i, 15);
	}
	box(305, 750, 75, 110, 15);
	textfield(190, 80, 2, "TIM KIEM:");
	textfield(875, 100, 2, "THONG TIN VAT TU");
	
	textfield(790, 150, 3, "Ten vat tu: ");
	textfield(810, 175, 3, "This is name!");
	textfield(790, 210, 3, "Ma vat tu: ");
	textfield(810, 235, 3, "This is code!");
	textfield(790, 270, 3, "Don vi tinh: ");
	textfield(810, 295, 3, "This is unit!");
	textfield(790, 330, 3, "So luong ton kho: ");
	textfield(810, 355, 3, "This is stock!");
	textfield(790, 390, 3, "Ngay nhap kho: ");
	textfield(810, 415, 3, "This is date!");
	
	button(790, 850, 455, 480, " XOA", 7, 1);
	button(870, 930, 455, 480, " LUU", 7, 1);
	button(950, 1070, 455, 480, " CHINH SUA", 7, 1);
	button(1090, 1155, 455, 480, " THEM", 7, 1);
	
	
	
	
}
void EmployeeMenu(){
	setfillstyle(20, 15);
	bar(0, 51, 1200, 700);
	setcolor(0);
	rectangle(0, 51, 1200, 700);
    
    button(20, 170, 80, 105, "IN DANH SACH", 7, 2);
	button(760, 820, 80, 105, " TIM", 7, 2);
	box(20, 750, 140, 670, 15);
	box(770, 1170, 140, 670, 15);
	box(790, 1155, 500, 650, 15);
	box(305, 750, 75, 110, 15);
	textfield(190, 80, 2, "TIM KIEM:");
	textfield(875, 100, 2, "THONG TIN VAT TU");
	
	textfield(790, 150, 3, "Ten vat tu: ");
	textfield(810, 175, 3, "This is name!");
	textfield(790, 210, 3, "Ma vat tu: ");
	textfield(810, 235, 3, "This is code!");
	textfield(790, 270, 3, "Don vi tinh: ");
	textfield(810, 295, 3, "This is unit!");
	textfield(790, 330, 3, "So luong ton kho: ");
	textfield(810, 355, 3, "This is stock!");
	textfield(790, 390, 3, "Ngay nhap kho: ");
	textfield(810, 415, 3, "This is date!");
	
	button(790, 850, 455, 480, " XOA", 7, 1);
	button(870, 930, 455, 480, " LUU", 7, 1);
	button(950, 1070, 455, 480, " CHINH SUA", 7, 1);
	button(1090, 1155, 455, 480, " THEM", 7, 1);
	
	
}
void BillMenu(){
	setfillstyle(20, 15);
	bar(0, 51, 1200, 700);
	setcolor(0);
	rectangle(0, 51, 1200, 700);
	
	button(20, 170, 80, 105, "IN DANH SACH", 7, 2);
	button(760, 820, 80, 105, " TIM", 7, 2);
	box(20, 750, 140, 640, 15);
	box(770, 1170, 140, 670, 15);
	box(790, 1155, 500, 650, 15);
	box(305, 750, 75, 110, 15);
	textfield(190, 80, 2, "TIM KIEM:");
	textfield(875, 100, 2, "THONG TIN VAT TU");
	
	textfield(790, 150, 3, "Ten vat tu: ");
	textfield(810, 175, 3, "This is name!");
	textfield(790, 210, 3, "Ma vat tu: ");
	textfield(810, 235, 3, "This is code!");
	textfield(790, 270, 3, "Don vi tinh: ");
	textfield(810, 295, 3, "This is unit!");
	textfield(790, 330, 3, "So luong ton: ");
	textfield(810, 355, 3, "This is stock!");
	textfield(790, 390, 3, "Ngay nhap kho: ");
	textfield(810, 415, 3, "This is date!");
	
	button(790, 850, 455, 480, " XOA", 7, 1);
	button(870, 930, 455, 480, " LUU", 7, 1);
	button(950, 1070, 455, 480, " CHINH SUA", 7, 1);
	button(1090, 1155, 455, 480, " THEM", 7, 1);
}
void MoreMenu(){
	setfillstyle(20, 15);
	bar(0, 51, 1200, 700);
	setcolor(0);
	rectangle(0, 51, 1200, 700);
	
	button(20, 170, 80, 105, "IN DANH SACH", 7, 2);
	button(760, 820, 80, 105, " TIM", 7, 2);
	box(20, 750, 140, 670, 15);
	box(770, 1170, 140, 670, 15);
	box(790, 1155, 500, 650, 15);
	box(305, 750, 75, 110, 15);
	textfield(190, 80, 2, "TIM KIEM:");
	textfield(875, 100, 2, "THONG TIN VAT TU");
	
	textfield(790, 150, 3, "Ten vat tu: ");
	textfield(810, 175, 3, "This is name!");
	textfield(790, 210, 3, "Ma vat tu: ");
	textfield(810, 235, 3, "This is code!");
	textfield(790, 270, 3, "Don vi tinh: ");
	textfield(810, 295, 3, "This is unit!");
	textfield(790, 330, 3, "So luong ton: ");
	textfield(810, 355, 3, "This is stock!");
	textfield(790, 390, 3, "Ngay nhap kho: ");
	textfield(810, 415, 3, "This is date!");
	
	button(790, 850, 455, 480, " XOA", 7, 1);
	button(870, 930, 455, 480, " LUU", 7, 1);
	button(950, 1070, 455, 480, " CHINH SUA", 7, 1);
	button(1090, 1155, 455, 480, " THEM", 7, 1);
	
}
void init(){
	
	initwindow(1200, 700);          
    setbkcolor(WHITE);                  
    cleardevice();
    setcolor(0);     
	cleardevice(); 
	settextstyle (4, 0, 2);
	MaterialPage(15);
	MaterialMenu();
	currentPage = 1;
	X = 0;
	Y = 0;
	EmployeePage(11);
	BillPage(11);
	MorePage(11);
	
}
void MaterialFunction(int X, int Y){
	string name = "";
	string code = "";
	string unit = "";
	string date = "";
	if (X >= 950 && X <= 1070 && Y >= 455 && Y <= 480){
		box(810, 1120, 180, 205, 15);
		box(810, 1120, 240, 265, 15);
		box(810, 1120, 300, 325, 15);
		box(810, 1120, 420, 445, 15);
		bool isTyping = true;
		while(1){
			delay(1);
			int x, y;
			if (ismouseclick(WM_LBUTTONDOWN)){
				getmouseclick(WM_LBUTTONDOWN, x, y);
				if (x >= 810 && x <= 1120 && y >= 180 && y <= 205){
					bool isTyping = true;
					while(isTyping){
						if (kbhit()){
							char c = getch();
							if (c >= 'a' && c <= 'z'){
								name += c;
							}
						}
						textfield(815, 180, 1, (char*)name.c_str());
						if(ismouseclick(WM_LBUTTONDOWN)){
							getmouseclick(WM_LBUTTONDOWN, x, y);
							if (!(x >= 810 && x <= 1120 && y >= 180 && y <= 205)){
								isTyping = false;
							}
						}
					}
				} else if (x >= 810 && x <= 1120 && y >= 240 && y <= 265){
					bool isTyping = true;
					while(isTyping){
						if (kbhit()){
							char c = getch();
							if (c >= 'a' && c <= 'z'){
								code += c;
							}
						}
						textfield(815, 240, 1, (char*)code.c_str());
						if(ismouseclick(WM_LBUTTONDOWN)){
							getmouseclick(WM_LBUTTONDOWN, x, y);
							if (!(x >= 810 && x <= 1120 && y >= 240 && y <= 265)){
								isTyping = false;
							}
						}
					}	
				} else{
					break;
				}
			}
		}
			
	} else if (X >= 1090 && X <= 1155 && Y >= 455 && Y <= 480){
		box(810, 1120, 180, 205, 15);
		box(810, 1120, 240, 265, 15);
		box(810, 1120, 300, 325, 15);
		box(810, 1120, 360, 385, 15);
		box(810, 1120, 420, 445, 15);	
	}
}
void EmployeeFunction(int x, int y);
void BillFunction(int x, int y);
void MoreFunction(int x, int y);
void setFunction(int x, int y){
	if (currentPage == 1){
		MaterialFunction(x, y);
	} 
}
void setMenu(int x, int y){
	if (x >= 0 && x <= 300 && y >= 0 & y <= 50) {
		MaterialPage(15);
		currentPage = 1;
		MaterialMenu();
		EmployeePage(11);
		BillPage(11);
		MorePage(11);
	} else if (x >= 301 && x <= 600 && y >= 0 & y <= 50){
		MaterialPage(11);
		EmployeePage(15);
		currentPage = 2;
		EmployeeMenu();
		BillPage(11);
		MorePage(11);
	} else if(x >= 601 && x <= 900 && y >= 0 & y <= 50){
		MaterialPage(11);
		EmployeePage(11);
		BillPage(15);
		currentPage = 3;
		BillMenu();
		MorePage(11);
	} else if (x >= 901 && x <= 1200 && y >= 0 & y <= 50){
		MaterialPage(11);
		EmployeePage(11);
		BillPage(11);
		MorePage(15);
		currentPage = 4;
		MoreMenu();	
	}
}

void Processing(){
	while(1){
		delay(1);
		int x, y;
		if (ismouseclick(WM_LBUTTONDOWN)){
			getmouseclick(WM_LBUTTONDOWN, x, y);
			setMenu(x, y);
			setFunction(x, y);
		}
	}
}
int main(int argc, char *argv[])
{
	init();  
	Processing();
	while(!kbhit()) delay(1);   
    return 0;
}
