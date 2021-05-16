//#include <winbgim.h>
#include <graphics.h>
#include <windows.h>
 
int currentPage = 1;
int X = -1;
int Y = -1;
void InsertMat();
void DeleteMat();
void EditMat();
void MaterialPage(int clr){
	
	setfillstyle(20, clr);
	bar(0, 0, 300, 50);
	rectangle(0, 0, 300, 50);
	setbkcolor(clr); 
    outtextxy(100, 15,"Vat tu");
    /*InsertMat();
    DeleteMat();
    EditMat();*/
}
void InsertEmp();
void PrintEmp();
void DeleteEmp();
void EditEmp();
void EmployeePage(int clr){
	
	setfillstyle(20, clr);
	bar(301, 0, 600, 50);
	rectangle(301, 0, 600, 50);
	setbkcolor(clr);
	outtextxy(400, 15,"Nhan vien");
	/*InsertEmp();
	PrintEmp();
	DeleteEmp();
	EditEmp();*/
}

void CreatBil();
void PrintBil();
void DeleteBil();
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
void setFunctionMaterial(int x, int y){
	
}
void MaterialMenu(){
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
void EmployeeMenu(){
	setfillstyle(20, 15);
	bar(0, 51, 1200, 700);
	setcolor(0);
	rectangle(0, 51, 1200, 700);
    outtextxy(600, 350,"This is EmployeePage");
}
void BillMenu(){
	setfillstyle(20, 15);
	bar(0, 51, 1200, 700);
	setcolor(0);
	rectangle(0, 51, 1200, 700);
	//setbkcolor(15); 
    outtextxy(600, 350,"This is BillPage");
}
void MoreMenu(){
	setfillstyle(20, 15);
	bar(0, 51, 1200, 700);
	setcolor(0);
	rectangle(0, 51, 1200, 700);
	//setbkcolor(15); 
    outtextxy(600, 350,"This is MoreDetailPage");
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

void setClickedMenu(int x, int y){
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
			setClickedMenu(x, y);
			
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
