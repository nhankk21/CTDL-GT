//#include <winbgim.h>
#include <graphics.h>
#include <windows.h>
#include <iostream>
#include <conio.h>
//#include <string>
#include <string.h>
#include <cstring>
#include<ios> 
#include<limits> 


#define KEY_HOME 71
#define KEY_UP 72
#define KEY_PGUP 73
#define KEY_LEFT 75
#define KEY_CENTER 76
#define KEY_RIGHT 77
#define KEY_END 79
#define KEY_DOWN 80
#define KEY_PGDN 81
#define KEY_INSERT 82
#define KEY_F1 59
#define KEY_F2 60
#define KEY_F3 61
#define KEY_F4 62
#define KEY_F5 63
#define KEY_F6 64
#define KEY_F7 65
#define KEY_F8 66
#define KEY_F9 67

using namespace std;
 
int currentTab = 1;

string reverseString(string s){
	string res = "";
	for (int i = 0; i < s.length(); ++i){
		res = s[i] + res;
	}
	return res;
}
string toString(char* text){
	string s = "";
	for (int i = 0; text[i] != NULL; ++i){
		s += text[i];
	}
	return s;
}
char* toCString(string s){
	char *c_string;
	c_string = new char[s.length()];
	for (int i = 0; i < s.length(); ++i){
    	c_string[i] = s[i];
	}
	c_string[s.length()] = '\0';
	return c_string;
}

void box(int l, int r, int t, int b, int color){
	setfillstyle(20, color);
	bar(l, t, r, b);
	rectangle(l - 1, t - 1, r + 1, b + 1); 
	setbkcolor(color);
}

void textBox(int l, int r, int t, int b, int bgrColor, int textSize, char* text){
	setfillstyle(20, bgrColor);
	setbkcolor(bgrColor);
	bar(l, t, r, b);
	rectangle(l , t, r, b); 
	string s = toString(text);
	int widthString = textwidth((char*)s.c_str());
	while (textwidth((char*)s.c_str()) > r - l){
		s.resize(s.length() - 1);
		s[s.length() - 1] = '.';
		s[s.length() - 2] = '.';
		s[s.length() - 3] = '.';
	}
	settextstyle(10, 0, textSize);
	outtextxy(l + 5, t + 5, (char*)s.c_str());
	setbkcolor(bgrColor);
}
void textLine(int l, int r, int t, int textSize, char* text){
	setfillstyle(20, 15);
	setbkcolor(15);
	string s = toString(text);
	int widthString = textwidth((char*)s.c_str());
	while (textwidth((char*)s.c_str()) > r - l){
		s.resize(s.length() - 1);
		s[s.length() - 1] = '.';
		s[s.length() - 2] = '.';
		s[s.length() - 3] = '.';
	}
	settextstyle(10, 0, textSize);
	outtextxy(l, t, (char*)s.c_str());
	setbkcolor(15);
}
void blankBox(int l, int r, int t, int b){
	setfillstyle(20, 15);
	bar(l - 1, t - 1, r + 1, b + 1);
	setbkcolor(15);
}
void editText(int l, int r, int t, int b, string s = ""){
	const int KEY_ARROW_CHAR1 = 224;
	const int KEY_ARROW_UP = 72;
	const int KEY_ARROW_DOWN = 80;
	const int KEY_ARROW_LEFT = 75;
	const int KEY_ARROW_RIGHT = 77;
	setfillstyle(20, 15);
	setbkcolor(15);
	bar(l, t, r, b);
	rectangle(l , t, r, b);
	int x = l + 5;
	int y = t + 5;
	int re = 0;
	bool typing = true;
	string s2 = s + "|";
	outtextxy(x, y, (char*)s2.c_str());
	while(typing) {
		if(kbhit()){
			unsigned char c = _getch();	
			if (c == KEY_ARROW_CHAR1)
			{
    			// Some Arrow key was pressed, determine which?
    			unsigned char ch2 = _getch();
    			switch (ch2) 
    			{
    			case KEY_ARROW_UP:
        			// code for arrow up
        			cout << "KEY_ARROW_UP" << endl;
        			break;
    			case KEY_ARROW_DOWN:
	        		// code for arrow down
    	   			cout << "KEY_ARROW_DOWN" << endl;
        			break;
    			case KEY_ARROW_LEFT:
	        		// code for arrow right
    	   			cout << "KEY_ARROW_LEFT" << endl;
        			break;
    			case KEY_ARROW_RIGHT:
        			// code for arrow left
        			cout << "KEY_ARROW_RIGHT" << endl;
        			break;
	    		}
			}
			else{
				if (c == 13){
				typing = false;
				blankBox(x, r - 1, y, b - 1);
				string s1 = s;
				s1.resize(s1.length() - re);
				string ss = s1;
				outtextxy(x, y, (char*)ss.c_str());
				} else if (c == 8){
					if (s.length() >= 1){
						blankBox(x, r - 1, y, b - 1);
						s.resize(s.length() - 1);	
						string ss = s + "|";
						int widthString = textwidth((char*)ss.c_str());
						if (widthString + 5 >= r - l){
							--re;
							string s1 = reverseString(s);
							s1.resize(s1.length() - re);
							s1 = reverseString(s1);
							ss = s1 + "|";
						} else{
							re = 0;
						}
						outtextxy(x, y, (char*)ss.c_str());
					}
				} else if (c >= 32 && c <= 126){
					s += c;
					string ss = s + "|"; 
					int widthString = textwidth((char*)ss.c_str());
					if (widthString + 5 >= r - l){
						++re;
						string s1 = reverseString(s);
						s1.resize(s1.length() - re);
						s1 = reverseString(s1);
						ss = s1 + "|";
					} else{
						re = 0;
					}
					outtextxy(x, y, (char*)ss.c_str());
				}
			}
			
		} 
		if (ismouseclick(WM_LBUTTONDOWN)){
			int xx, yy;
			getmouseclick(WM_LBUTTONDOWN, xx, yy);	
			if(!(xx >= l && xx <= r && yy >= t && yy <= b)){
				typing = false;
				blankBox(x, r - 1, y, b - 1);
				string s1 = s;
				s1.resize(s1.length() - re);
				string ss = s1;
				outtextxy(x, y, (char*)ss.c_str());
			}
		}
	}
	
	setbkcolor(15);
		
}
void topBar(int tab = 1){
	int mTab = 11, eTab = 11, bTab = 11, aTab = 11;
	if(tab == 1){
		mTab = 15;
	} else if(tab == 2){
		eTab = 15;
	} else if(tab == 3){
		bTab = 15;
	} else{
		aTab = 15;
	}
	textBox(1, 300, 1, 40, mTab, 3, "        Vat tu");
	textBox(301, 600, 1, 40, eTab, 3, "       Nhan vien");
	textBox(601, 900, 1, 40, bTab, 3, "       Hoa don");
	textBox(901, 1200, 1, 40, aTab, 3, "       Thong ke");
}
void eTab();
void bTab();
void aTab();
void mTab(){
	box(1, 1200, 41, 700, 15);
	box(1, 750, 150, 650, 15);
	box(800, 1199, 100, 670, 15);
	textLine(900, 1200, 60, 3, "THONG TIN VAT TU");
	textLine(810, 1180, 110, 3,  "Ten vat tu: ");
	textBox(810, 1180, 145, 180, 15, 3, "");
	textLine(810, 1180, 190, 3, "Ma vat tu: ");
	textBox(810, 1180, 225, 260, 15, 3, "");
	textLine(810, 1180, 270, 3, "Don vi tinh: ");
	textBox(810, 1180, 305, 340, 15, 3, "");
	textLine(810, 1180, 350, 3, "So luong ton kho: ");
	textBox(810, 1180, 385, 420, 15, 3, "");
	textLine(810, 1180, 430, 3, "Ngay nhap kho: ");
	textBox(810, 1180, 465, 500, 15, 3, "");
	textBox(810, 865, 520, 555, 7, 3, "XOA");
	textBox(880, 935, 520, 555, 7, 3, "LUU");
	textBox(950, 1090, 520, 555, 7, 3, "CHINH SUA");
	textBox(1105, 1180, 520, 555, 7, 3, "THEM");
	
	while(1){
		delay(1);
		int x, y;
		
		if(kbhit()){
			char key = getch();
			//if(key == 0) return;
		}
		
		if (ismouseclick(WM_LBUTTONDOWN)){
			getmouseclick(WM_LBUTTONDOWN, x, y);
			if(x >= 301 && x <= 600 && y >= 1 && y <= 40){
				topBar(2);
				eTab();
			} else if(x >= 601 && x <= 900 && y >= 1 && y <= 40){
				topBar(3);
				bTab();
			} else if(x >= 901 && x <= 1200 && y >= 1 && y <= 40){
				topBar(4);
				aTab();
			} else if(x >= 950 && x <= 1090 && y >= 520 && y <= 555){
				textBox(950, 1090, 520, 555, 15, 3, "CHINH SUA");
				blankBox(810, 1180, 570, 650);
				textLine(850, 1180, 600, 3, "Moi nhap ten vat tu!");
				editText(810, 1180, 145, 180, "hehe");
				blankBox(810, 1180, 570, 650);
				textLine(850, 1180, 600, 3, "Moi nhap ma vat tu!");
				editText(810, 1180, 225, 260, "");
				blankBox(810, 1180, 570, 650);
				textLine(850, 1180, 600, 3, "Moi nhap don vi tinh!");
				editText(810, 1180, 305, 340, "");
				blankBox(810, 1180, 570, 650);
				textLine(850, 1180, 600, 3, "Moi nhap so luong ton!");
				editText(810, 1180, 385, 420, "kuku");
				blankBox(810, 1180, 570, 650);
				textLine(850, 1180, 600, 3, "Moi nhap ngay nhap kho!");
				editText(810, 1180, 465, 500, "");
				blankBox(810, 1180, 570, 650);
				textLine(850, 1180, 580, 3, "Da xong!");
				textLine(850, 1180, 630, 3, "Bam LUU de luu vat tu!");
				textBox(950, 1090, 520, 555, 7, 3, "CHINH SUA");
				textBox(880, 935, 520, 555, 15, 3, "LUU");	
			} else if(x >= 880 && x <= 935 && y >= 520 && y <= 555){
				blankBox(810, 1180, 570, 650);
				textLine(850, 1180, 600, 3, "Da Luu!");
				textBox(880, 935, 520, 555, 7, 3, "LUU");
			} else if (x >= 810 && x <= 865 && y >= 520 && y <=  555){
				textBox(810, 865, 520, 555, 15, 3, "XOA");
				blankBox(810, 1180, 570, 650);
				textLine(850, 1180, 570, 3, "Ban co muon xoa?");
				textBox(850, 890, 610, 645, 15, 3, "CO");
				textBox(920, 1000, 610, 645, 7, 3, "KHONG");
				bool isYES = true;
				bool choosing = true;
				while(choosing){
					delay(1);
					if(kbhit()){
						char key = getch();
						if (key == 13){
							if(isYES){
								choosing = false;
								blankBox(810, 1180, 570, 650);
								textLine(850, 1180, 600, 3, "Da xoa!");	
							} else{
								choosing = false;
								blankBox(810, 1180, 570, 650);	
							}
						} else if (1){
						}
					}
				}
			}
		}
	}
}
void eTab(){
	box(1, 1200, 41, 700, 15);
	box(1, 750, 70, 650, 15);
	textBox(50, 200, 150, 250, 15, 2, "Nhan vien");
	while(1){
		delay(1);
		if(kbhit()){
			char key = getch();
			//if(key == 0) return;
		}
		int x, y;
		if (ismouseclick(WM_LBUTTONDOWN)){
			getmouseclick(WM_LBUTTONDOWN, x, y);
			if(x >= 1 && x <= 300 && y >= 1 && y <= 40){
				topBar(1);
				mTab();
			} else if(x >= 601 && x <= 900 && y >= 1 && y <= 40){
				topBar(3);
				bTab();
			} else if(x >= 901 && x <= 1200 && y >= 1 && y <= 40){
				topBar(4);
				aTab();
			}
		}
	}
}
void bTab(){
	box(1, 1200, 41, 700, 15);
	box(1, 750, 70, 650, 15);
	textBox(50, 200, 150, 250, 15, 2, "Hoa don");
	while(1){
		delay(1);
		if(kbhit()){
			char key = getch();
			//if(key == 0) return;
		}
		int x, y;
		if (ismouseclick(WM_LBUTTONDOWN)){
			getmouseclick(WM_LBUTTONDOWN, x, y);
			if(x >= 301 && x <= 600 && y >= 1 && y <= 40){
				topBar(2);
				eTab();
			} else if(x >= 1 && x <= 300 && y >= 1 && y <= 40){
				topBar(1);
				mTab();
			} else if(x >= 901 && x <= 1200 && y >= 1 && y <= 40){
				topBar(4);
				aTab();
			}
		}
	}
}
void aTab(){
	box(1, 1200, 41, 700, 15);
	box(1, 750, 70, 650, 15);
	textBox(50, 200, 150, 250, 15, 2, "Thong ke");
	while(1){
		delay(1);
		if(kbhit()){
			char key = getch();
			//if(key == 0) return;
		}
		int x, y;
		if (ismouseclick(WM_LBUTTONDOWN)){
			getmouseclick(WM_LBUTTONDOWN, x, y);
			if(x >= 301 && x <= 600 && y >= 1 && y <= 40){
				topBar(2);
				eTab();
			} else if(x >= 601 && x <= 900 && y >= 1 && y <= 40){
				topBar(3);
				bTab();
			} else if(x >= 1 && x <= 300 && y >= 1 && y <= 40){
				topBar(1);
				mTab();
			}
		}
	}
}


void init(){
	initwindow(1200, 700);          
    setbkcolor(WHITE);                  
    cleardevice();
    setcolor(0);     
	cleardevice(); 
	settextstyle (4, 0, 2);
	currentTab = 1;
	topBar(currentTab);
	if(currentTab == 1){
		mTab();
	} else if(currentTab == 2){
		eTab();
	} else if(currentTab == 3){
		bTab();
	} else {
		aTab();
	}
}
int main(int argc, char *argv[])
{
	init();  
	while(!kbhit()) delay(1);   
    return 0;
}
