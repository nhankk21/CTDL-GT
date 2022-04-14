//#include <winbgim.h>
//#include <algorithm>
#include <graphics.h>
#include <windows.h>
#include <iostream>
#include <conio.h>
#include <string>
#include <string.h>
#include <cstring> 
#include <stdio.h>
#include <ctype.h>
#include<ios> 
#include<limits> 
#include<fstream>
#include <iomanip>
#include <sstream>
#include "Header/BST.h"
#include "Header/Employee.h"
#include "Header/Bill.h"
using namespace std;
 
const int MAX_MATERIAL = 2e6;

string toString(char* text){
	string s = "";
	for (int i = 0; text[i] != '\0'; ++i){
		s += text[i];
	}
	return s;
}

string fillYear(string s){
	while(s.length() < 4){
		s = "0" + s;
	}
	return s;
}
string reverseString(string s){
	string res = "";
	for (int i = 0; i < s.length(); ++i){
		res = s[i] + res;
	}
	return res;
}
string intToString(long long num){
	string s = "";
	bool isNegative = false;
	if(num == 0){
		return "0";
	} else{
		if (num < 0){
			isNegative = true;
			num *= -1;
		}
	}
	while(num > 0){
		int x = num % 10;
		num /= 10;
		char c = '0' + x;
		s = c + s; 
	}
	if(isNegative){
		s = '-' + s;
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
string onlyCharacter(string s){
	string res = "";
	for(int i = 0; i < s.length(); ++i){
		if(s[i] == ' ' || (s[i] >= 'a' && s[i] <= 'z') || (s[i] >= 'A' && s[i] <= 'Z')){
			res += s[i];
		}
	}
	return res;
}

bool isOnlyNumber(string s){
	for (int i = 0; i < s.length(); ++i){
		if(!(s[i] >= '0' && s[i] <= '9')){
			return false;
		}
	}
	return true;
}
string standardizeName(string name){
	int index = 0;
	for (int i = 0; i < name.length(); ++i){
		if(name[i] != ' ') {
			index = i;
			break;	
		}
	}
	string stdName = "";
	stdName += name[index];
	for (int i = index + 1; i < name.length(); ++i){
		if(name[i] != ' '){
			if(name[i - 1] == ' ') stdName += ' ';
			stdName += name[i];
		}
	}
	if(stdName[0] >= 'a' && stdName[0] <= 'z'){
		stdName[0] = 'A' + (stdName[0] - 'a');
	}
	for (int i = 1; i <= stdName.length(); ++i){
		if(stdName[i] != ' '){
			if(stdName[i - 1] == ' '){
				if(stdName[i] >= 'a' && stdName[i] <= 'z'){
					stdName[i] = 'A' + (stdName[i] - 'a');
				}
			} else{
				if(stdName[i] >= 'A' && stdName[i] <= 'Z'){
					stdName[i] = 'a' + (stdName[i] - 'A');
				}
			}
		}
	}
	return stdName;
}

string floatToString(float num){
	ostringstream buff;
     buff << fixed << setprecision(2) << num;
     return buff.str();
}


long long toInt(string s){
	long long res = 0;
	int isNegative = 1;
	int first = 0;
	if (s[0] == '-'){
		first = 1;
		isNegative = -1;
	}
	for (int i = first; i < s.length(); ++i){
		int x = s[i] - '0';
		res = res * 10 + x;
	}
	return res * isNegative;
} 


double toFloat(string s){
	double INT = 0;
	double FLOAT = 0;
	int isNegative = 1;
	int first = 0;
	if (s[0] == '-'){
		first = 1;
		isNegative = -1;
	}
	bool isDot = false;
	double c = 1;
	for (int i = first; i < s.length(); ++i){
		if(s[i] == '.'){
			isDot = true;
		} else{
			if(!isDot){
				INT = INT * 10 + s[i] - '0';
			} else{
				c *= 10;	
				FLOAT = FLOAT * 10 + s[i] - '0';;
			}
			
		}
	}
	FLOAT = FLOAT / c;
	return ((double)INT + (double)FLOAT) * (double)isNegative;
}

class mManager {
	public: 
	materialNode* materialBST; // root
	
	materialNode** parr; // Mang de luu vat tu
	int cnt = 0; // Tong so vat tu hien tai
	

	string m_code, m_name, m_unit, m_quantity;
	
	mManager() { // Khoi tao
		parr = new materialNode* [MAX_MATERIAL];
		materialBST = NULL;
		// nodePointer = NULL;
		// Mac dinh tro vao parr[0]
		
		readMaterial();
		
	}  
	~mManager() {
		writeMaterial();
		for (int i = 0; i < cnt; ++i)
			delete parr[i];
		delete parr;
		// Giai phong cay
	}
	
	public: void addMaterial(string ma, string ten, string donvi, float soluong) {
		Material tmpmaterial = Material(ma, ten, donvi, soluong);
		materialBST = insertNode(materialBST, tmpmaterial);
		parr[cnt++] = createNode(tmpmaterial);
		writeMaterial();
	}
	
	public: void sort(){
		quickSortMaterial(parr, 0, cnt - 1, cmpM);
		writeMaterial();
	}
	public: void editMaterial(string ma, string ten, string dv) {
		materialNode* tmp = searchNode(materialBST, ma);
		tmp->data.nameMaterial = ten;
		tmp->data.unitMaterial = dv;
		writeMaterial();
	}
	public: void incQuantity(string ma, float quan){
		materialNode* tmp = searchNode(materialBST, ma);
		tmp->data.quantity += quan;
		writeMaterial();
	}
	public: void decQuantity(string ma, float quan){
		materialNode* tmp = searchNode(materialBST, ma);
		tmp->data.quantity -= quan;
		writeMaterial();
	}
	public: void deleteMaterial(string ma, string ten, string donvi, float soluong, int curPos) {
			Material tmpmaterial = Material(ma, ten, donvi, soluong);
			materialBST = deleteNode(materialBST, tmpmaterial);
			// Xoa xong dich mang qua trai
			for (int i = curPos; i < cnt - 1; i++) {
				parr[i] = parr[i+1];
			}
			--cnt;
			writeMaterial();
			// Thong bao: xoa thanh cong;
			
	}
	
	public: materialNode* findMaterialCode(string m_code) {
		return searchNode(materialBST, m_code);
	}
	
	public: string getCurrentCode() {
		string code;
		fstream f;
		f.open("materialCode.txt", ios::in);
		f >> code;
		f.close();
		return code;
	}
	public: void writeCurrentCode(string code) {
		fstream f;
		f.open("materialCode.txt", ios::out);
		f << code;
		f.close();
	}
	
	public: void LNR(materialNode* root) {
		if (root != NULL) {
			LNR(root->left);
			parr[cnt++] = root;
			LNR(root->right);
		}
		
	}
	
	public: void readMaterial() {
		fstream f;
		f.open("material.txt", ios::in);
		Material material;
		while (!f.eof() && getline(f, material.codeMaterial)) {
			fflush(stdout);
			getline(f, material.nameMaterial);
			getline(f, material.unitMaterial);
			string quan;
			getline(f, quan);
			material.quantity = toFloat(quan);
			//material.unitMaterial = toFloat(unit);
			//parr[++cnt] = insertNode(materialBST, material);
			// parr[cnt++] = createNode(material);
			materialBST = insertNode(materialBST, material);
		}
		f.close();
		LNR(materialBST);
		//quickSortMaterial(parr, 0, cnt);		
	}
	
	
	public: void writeMaterial() {
		fstream f;
		f.open("material.txt", ios::out);
		for (int i = 0; i < cnt; ++i) {
			f << parr[i]->data.codeMaterial << endl;
			f << parr[i]->data.nameMaterial << endl;
			f << parr[i]->data.unitMaterial << endl;
			string quan = floatToString(parr[i]->data.quantity);
			f << quan << endl;
		}
		f.close();
	}
	
};

class eManager {
	public:
	int cnt; // so luong emp
	Employee *emp[501];
	string e_code, e_last, e_first, e_sex;
	~eManager() {
		for (int i = 0; i < cnt; ++i) delete emp[i];
	}
	eManager() {
		cnt = 0;
		// curPos = 0; // Mac dinh tro vao emp[0]
		readEmployee();
	}
	
	public: void addEmployee(string ma, string ho, string ten, string gt) {
		emp[cnt++] = new Employee(ma, ho, ten, gt);
		writeEmployee();
	}
	
	public: void editEmployee(int curPos, string ho, string ten, string gt) {
		emp[curPos]->firstName = ten;
		emp[curPos]->lastName = ho;
		emp[curPos]->sex = gt;
		writeEmployee();
	}
	public: void sort(){
		quickSortEmployee(emp, 0, cnt - 1, cmpE);
		writeEmployee();
	}
	public: string getCurrentCode() {
		string code;
		fstream f;
		f.open("employeeCode.txt", ios::in);
		f >> code;
		f.close();
		return code;
	}
	public: void writeCurrentCode(string code) {
		fstream f;
		f.open("employeeCode.txt", ios::out);
		f << code;
		f.close();
	}
	public: void deleteEmployee(int curPos) {
		for (int k = curPos; k < cnt - 1; k++) 
			emp[k] = emp[k+1];
		cnt--;
		writeEmployee();
	}
	
	public: void readEmployee() {
		fstream f;
		f.open("employee.txt", ios::in);
		string code, last, first, sex;
		while (!f.eof() && getline(f, code)) {
			fflush(stdout);
			getline(f, last);
			getline(f, first);
			getline(f, sex);
			emp[cnt++] = new Employee(code, last ,first, sex);
		}
		f.close();
		// quickSortEmployee(emp, 0, cnt-1); // Sap xep theo ten de in ra ds
	
	
	
//		for (int j = 0; j < cnt; j++) {
//			Bill bill;
//			
//			string path = "emp/" + emp[j]->codeEmp + ".txt";
//			FILE* file = fopen((char*)path.c_str(), "r");
//			
//
//			while(!feof(file)) {
//				
//				char type;
//				char tmpbcode[21];
//				char tmpmcode[11];
//				float tmpquantity, tmpprice, tmpvat;
//				int n;
//				
//				fscanf(file, "%s %c %d/%d/%d %d \n", &tmpbcode, &type, &bill.time.date, &bill.time.month, &bill.time.year, &n);
//				bill.code = toString(tmpbcode);
//				
//				for(int i = 0; i < n; i++){
//					fscanf(file, "%s %f%f%f \n", &tmpmcode, &tmpquantity, &tmpprice, &tmpvat);
//					bill.addBillDetail(tmpbcode, tmpquantity, tmpprice, tmpvat);
//				}
//				if(feof(file)) break;
//				if(type == 'X') bill.billType = 'X';
//				else bill.billType = 'N';
//	
//				insertBill(emp[j]->billList, bill);
//				bill.resetBill();
//			}
//			fclose(file);
//		}
	}
	
//	public: void WriteData(BillNode* node, FILE* file) {
//		if (node == NULL) return;
//		WriteData(node->next, file);
//		Bill bill = node->dataBill;
//		char type;
//		if(bill.billType == 'X') type = 'X';
//		else type = 'N';
//		
//		fprintf (file, "%s %c %d/%d/%d %d \n", toCString(bill.code), type, bill.time.date, bill.time.month, bill.time.year, bill.cnt);
//		for(int i = 0; i < bill.cnt; i++) {
//
//			fprintf (file, "%s %f%f%f \n", toCString(bill.billDetail[i].code), bill.billDetail[i].quantity, bill.billDetail[i].price, bill.billDetail[i].vat);
//		}
//	}
	
	public: void writeEmployee() {
		fstream f;
		f.open("employee.txt", ios::out);
		string code, first, last, sex;
		for (int j = 0; j < cnt; j++) {
			f << emp[j]->codeEmp << endl;
			f << emp[j]->lastName << endl;
			f << emp[j]->firstName << endl;
			f << emp[j]->sex << endl;
		}
		f.close();
		
//		for (int j = 0; j < cnt; j++) {
//			string path = "emp/" + emp[j]->codeEmp + ".txt";
//			FILE* file = fopen((char*)path.c_str(), "w");
//			BillNode *k = emp[j]->billList;
//			//WriteData(k, file);
//			fclose(file);
//		}
	}
	
	int findEmployee(string code){
		for (int i = 0; i < cnt; ++i){
			if(emp[i]->codeEmp == code){
				return i;
			}
		}
		return -1;
	}
	
	
};

const int MAX_PRINT_BILL = 10000;
class bManager {
	public: 
	Bill currentBill;
	Bill* parr;
	int cnt;
	Bill billInTime[MAX_PRINT_BILL];
	int indexBillInTime = 0;
	TREE t;
	Node* arr[MAX_PRINT_BILL];
	int cntArr;
	bManager() {
		parr = new Bill[MAX_PRINT_BILL];
		cnt = 0;
		currentBill = Bill();
		//readBill();
		
		for (int i = 0; i < MAX_PRINT_BILL; ++i){
			parr[i] = Bill();
		}
	}
	
	~bManager() {
		
	}
	
	public: void resetBill() {
		currentBill.resetBill();
	}
	
	public: void RNL(TREE t){
		if(t != NULL){
			RNL(t->pRight);
			arr[cntArr++] = t;
			RNL(t->pLeft);
		}
		
	}
	public: bool isExist(string ma) {
		return (currentBill.findBillDetail(ma) != -1 ? 1 : 0);
	}
	
	public: void createBill(string mahd, string manv, Time time, char loai) {
		currentBill = Bill(mahd, manv, time, loai);
		 // Tham so manv de khi nao hoan tat hoa don roi dua vao manv do them hoa don vao dshd cua nv do
	}

	
	public: void addPayment(string mvt, float soluong, float dongia, float vat) { // Them thanh toan
		currentBill.addBillDetail(mvt, soluong, dongia, vat);
		// write data
	}
	
	public: void deletePayment(int curPos) {
		currentBill.deleteBillDetail(curPos);
		// write data
	}
	
	// Doc va viet data se xu ly o eManager (cho tien)
	
	public: string getCurrentCode() {
		string code;
		fstream f;
		f.open("billCode.txt", ios::in);
		f >> code;
		f.close();
		return code;
	}
	
	public: int searchBill(string maHD) {
		for (int i = 0; i < cnt; i++) {
			if (parr[i].code == maHD) return i;
		}
		return -1;
	}
	
	public: void writeCurrentCode(string code) {
		
		// sinh ke tiep code
		fstream f;
		f.open("billCode.txt", ios::out);
		f << code;
		f.close();
	}
	public: void addBill(){
		
		parr[cnt++] = currentBill;
		//resetBill();
	}
	
	
	public: void readBill() {
			
		FILE* file = fopen("bill.txt", "r");
		
		
		while(!feof(file)) {
			Bill bill = Bill();
			char type;
			char tmpbcode[21];
			char tmpecode[6];
			int k;
			fscanf(file, "%s\n", &tmpecode);	
			fscanf(file, "%s %c %d %d %d %d\n", &tmpbcode, &type, &bill.time.date, &bill.time.month, &bill.time.year, &k);
			bill.code = toString(tmpbcode);
			bill.empCode = toString(tmpecode);
			if(feof(file)) break;
			
			for(int i = 0; i < k; i++){
				char tmpmcode[11];
				float tmpquantity, tmpprice, tmpvat;
				fscanf(file, "%s %f %f %f\n", &tmpmcode, &tmpquantity, &tmpprice, &tmpvat);
				bill.addBillDetail(toString((char*)tmpmcode), tmpquantity, tmpprice, tmpvat);
			}
			if(type == 'X') bill.billType = 'X';
			else bill.billType = 'N';
			parr[cnt++] = bill;
			//bill.resetBill();
		}
		fclose(file);
	}

	public: void getBillInTime(Time from, Time to) {
		
		indexBillInTime = 0;
		
		for (int i = 0; i < cnt; i++) {
			if (CompareTime(from, parr[i].time) <= 0 && CompareTime(parr[i].time, to) <= 0) {
				billInTime[indexBillInTime] = parr[i];
				indexBillInTime++;
			}
		}
	}

	public: void writeData(Bill bill, FILE* file) {
		fprintf(file, "%s\n", toCString(bill.empCode));
		fprintf( file, "%s %c %d %d %d %d\n", toCString(bill.code), bill.billType, bill.time.date, bill.time.month, bill.time.year, bill.cnt);
		for (int i = 0; i < bill.cnt; i++) {
			fprintf(file, "%s %f %f %f\n", toCString(bill.billDetail[i].code), bill.billDetail[i].quantity, bill.billDetail[i].price, bill.billDetail[i].vat);
		}
	}
	
	public: void writeBill() {
		FILE* file = fopen("bill.txt", "w");
		
		for (int i = 0; i < cnt; i++) {
			writeData(parr[i], file);
		}
		fclose(file);
	}
};






string nextGenM(string s){
	if(s == "m999999999"){
		return s;
	}
	for (int i = s.length() - 1; i >= 1; --i){
		if (s[i] + 1 <= '9'){
			s[i] += 1;
			break;
		} else{
			s[i] = '0';
		}
	}
	return s;
} 
string nextGenE(string s){
	if(s == "e9999"){
		return s;
	}
	for (int i = s.length() - 1; i >= 1; --i){
		if (s[i] + 1 <= '9'){
			s[i] += 1;
			break;
		} else{
			s[i] = '0';
		}
	}
	return s;
} 
string nextGenB(string s){
	
	if(s == "b9999999999999999999"){
		return s;
	}
	for (int i = s.length() - 1; i >= 1; --i){
		if (s[i] + 1 <= '9'){
			s[i] += 1;
			break;
		} else{
			s[i] = '0';
		}
	}
	return s;
} 

bool isLeapYear(string s){
	int year = toInt(s);
	if (year % 400 == 0 || (year % 4 == 0 && year % 100 != 0)) return true;
	else return false;
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
void editText(int l, int r, int t, int b, bool onlyNum, int maxSize, string &s){
    
	setfillstyle(20, 15);
	setbkcolor(15);
	bar(l, t, r, b);
	rectangle(l , t, r, b);
	int x = l + 5;
	int y = t + 5;
	int re = 0;
	bool isDot = false;
	bool typing = true;
	string s2 = s + "|";
	outtextxy(x, y, (char*)s2.c_str());
	while(typing) {
		if(kbhit()){
			char c = getch();	
			if (c == 13){
				if((onlyNum) && (s[0] == '.' || s[s.length() - 1] == '.')){
					continue;	
				}
				typing = false;
				blankBox(x, r - 1, y, b - 1);
				string s1 = s;
				s1.resize(s1.length() - re);
				string ss = s1;
				outtextxy(x, y, (char*)ss.c_str());
			} else if (c == 8){
				if (s.length() >= 1){
					blankBox(x, r - 1, y, b - 1);
					if (s[s.length() - 1] == '.'){
						isDot = false;
					}
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
			} else if (c == 0){
				char c1 = getch();
			} else if (c >= 32 && c <= 126 && (s.length() <= maxSize - 1)){
				if (onlyNum){
					if(!((c >= '0' && c <= '9') || c == '.')){
						continue;	
					}	
				}	
				if(c == '.' && onlyNum){
					if (isDot == false){
						s += c;
						isDot = true;
					}
				} else{
					s += c;
				}			
				
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
void mOptionButton(int opt = 0){
	int aOpt = 7, eOpt = 7, dOpt = 7;
	if (opt == 1){
		dOpt = 15;
	} else if (opt == 2){
		eOpt = 15;
	} else if (opt == 3){
		aOpt = 15;
	}
	textBox(810, 865, 450, 485, dOpt, 3, "XOA");
	textBox(920, 1060, 450, 485, eOpt, 3, "CHINH SUA");
	textBox(1105, 1180, 450, 485, aOpt, 3, "THEM");
}
void eOptionButton(int opt = 0){
	int aOpt = 7, eOpt = 7, dOpt = 7;
	if (opt == 1){
		dOpt = 15;
	} else if (opt == 2){
		eOpt = 15;
	} else if (opt == 3){
		aOpt = 15;
	}
	textBox(810, 865, 440, 475, dOpt, 3, "XOA");
	textBox(920, 1060, 440, 475, eOpt, 3, "CHINH SUA");
	textBox(1105, 1180, 440, 475, aOpt, 3, "THEM");
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

void eTab(mManager &m, eManager &e, bManager &b);
void bTab(mManager &m, eManager &e, bManager &b);
void aTab(mManager &m, eManager &e, bManager &b);

void mTab(mManager &m, eManager &e, bManager &b){
	box(1, 1200, 41, 700, 15);
	box(1, 750, 100, 625, 15);
	
	int curPage = 1;
	int curItem = 0;
	//m.readMaterial();
	materialNode** temp = new materialNode* [15];
	materialNode* current;
	
	
	for (int i = 0; i < 15; ++i){
		if(i + (curPage - 1) * 15 < m.cnt){
			temp[i] = m.parr[i + (curPage - 1) * 15];	
		} else {
			materialNode* n = new materialNode;
			n->data.codeMaterial = "";
			n->data.nameMaterial = "";
			n->data.quantity = 0;
			n->data.unitMaterial = "";
			temp[i] = n;
		}
	}
	current = temp[curItem];
	textBox(1, 160, 65, 100, 15, 3, "Ma vat tu");
	textBox(161, 440, 65, 100, 15, 3, "Ten vat tu");
	textBox(441, 600, 65, 100, 15, 3, "don vi");
	textBox(601, 750, 65, 100, 15, 3, "so luong");
	
	for (int i = 0; i <= 14; ++i){
		
		textBox(1, 160, 100 + i * 35, 135 + i * 35, 15, 3, toCString(temp[i]->data.codeMaterial));
		textBox(161, 440, 100 + i * 35, 135 + i * 35,  15, 3, toCString(temp[i]->data.nameMaterial));
		textBox(441, 600, 100 + i * 35, 135 + i * 35,  15, 3, (char*)temp[i]->data.unitMaterial.c_str());
		textBox(601, 750, 100 + i * 35, 135 + i * 35,  15, 3, (char*)floatToString(temp[i]->data.quantity).c_str());
	}
	
	box(800, 1199, 100, 670, 15);
	
	textLine(900, 1200, 60, 3, "THONG TIN VAT TU");
	textLine(810, 1180, 110, 3,  "Ma vat tu: ");
	textBox(810, 1180, 145, 180, 15, 3, toCString(current->data.codeMaterial));
	textLine(810, 1180, 190, 3, "Ten vat tu: ");
	textBox(810, 1180, 225, 260, 15, 3, toCString(current->data.nameMaterial));
	textLine(810, 1180, 270, 3, "Don vi tinh: ");
	textBox(810, 1180, 305, 340, 15, 3, (char*)current->data.unitMaterial.c_str());
	textLine(810, 1180, 350, 3, "So luong ton kho: ");
	textBox(810, 1180, 385, 420, 15, 3, (char*)floatToString(current->data.quantity).c_str());
	
	string page = "Trang: "+ intToString(curPage);
	textLine(320, 490, 635, 3, toCString(page));
	textBox(120, 290, 635, 670, 7, 3, "Trang truoc");
	textBox(510, 650, 635, 670, 7, 3, "Trang sau");
	mOptionButton(0);
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
				eTab(m, e, b);
			} else if(x >= 601 && x <= 900 && y >= 1 && y <= 40){
				topBar(3);
				bTab(m, e, b);
			} else if(x >= 901 && x <= 1200 && y >= 1 && y <= 40){
				topBar(4);
				aTab(m, e, b);
			} else if(x >= 920 && x <= 1060 && y >=  450 && y <= 485){
				mOptionButton(2);
				blankBox(810, 1180, 570, 650);
				textLine(850, 1180, 600, 3, "Chinh sua ten vat tu!");
				string ten = current->data.nameMaterial;
				nameELabel:
				editText(810, 1180, 225, 260, false, 20, ten);
				if(ten.length() == 0){
					blankBox(810, 1180, 570, 650);
					textLine(850, 1180, 600, 3, "Khong duoc trong!");
					goto nameELabel;
				}
				blankBox(810, 1180, 570, 650);
				textLine(850, 1180, 600, 3, "Chinh sua don vi tinh!");
				string donvi = current->data.unitMaterial;
				unitELabel:
				editText(810, 1180, 305, 340, false, 10, donvi);
				if(donvi.length() == 0){
					blankBox(810, 1180, 570, 650);
					textLine(850, 1180, 600, 3, "Khong duoc trong!");
					goto unitELabel;
				}
				blankBox(810, 1180, 570, 650);
				textLine(850, 1180, 570, 3, "Luu chinh sua?");
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
								
								current->data.nameMaterial = ten;
								current->data.unitMaterial = donvi;
								m.parr[curItem + (curPage - 1) * 15] = current;
								textBox(1, 160, 100 + curItem * 35, 135 + curItem * 35, 15, 3, toCString(current->data.codeMaterial));
								textBox(161, 440, 100 + curItem * 35, 135 + curItem * 35,  15, 3, toCString(current->data.nameMaterial));
								textBox(441, 600, 100 + curItem * 35, 135 + curItem * 35,  15, 3, (char*)current->data.unitMaterial.c_str());
								textBox(601, 750, 100 + curItem * 35, 135 + curItem * 35,  15, 3, (char*)floatToString(current->data.quantity).c_str());
								m.editMaterial(current->data.codeMaterial, ten, donvi);
								m.writeMaterial();
								blankBox(810, 1180, 570, 650);
								textLine(850, 1180, 600, 3, "Da luu!");	
								mOptionButton(0);
							} else{
								choosing = false;
								textBox(810, 1180, 145, 180, 15, 3, toCString(current->data.codeMaterial));
								textBox(810, 1180, 225, 260, 15, 3, toCString(current->data.nameMaterial));
								textBox(810, 1180, 305, 340, 15, 3, (char*)current->data.unitMaterial.c_str());
								textBox(810, 1180, 385, 420, 15, 3, (char*)floatToString(current->data.quantity).c_str());
								blankBox(810, 1180, 570, 650);	
								mOptionButton(0);
							}
						} else if (key == 0){
							char key2 = getch();
							if (key2 == 75){
								if(!isYES){
									isYES = true;
									textBox(850, 890, 610, 645, 15, 3, "CO");
									textBox(920, 1000, 610, 645, 7, 3, "KHONG");
								}	
							} else if (key2 == 77){
								if(isYES){
									isYES = false;
									textBox(850, 890, 610, 645, 7, 3, "CO");
									textBox(920, 1000, 610, 645, 15, 3, "KHONG");
								}
							}
						}
					}
					if (ismouseclick(WM_LBUTTONDOWN)){
						int xx, yy;
						getmouseclick(WM_LBUTTONDOWN, xx, yy);
						if (xx >= 850 && xx <= 890 && yy >= 610 && yy <= 645){
							choosing = false;
							
							current->data.nameMaterial = ten;
							current->data.unitMaterial = donvi;
							m.parr[curItem + (curPage - 1) * 15] = current;
							textBox(1, 160, 100 + curItem * 35, 135 + curItem * 35, 15, 3, toCString(current->data.codeMaterial));
							textBox(161, 440, 100 + curItem * 35, 135 + curItem * 35,  15, 3, toCString(current->data.nameMaterial));
							textBox(441, 600, 100 + curItem * 35, 135 + curItem * 35,  15, 3, (char*)current->data.unitMaterial.c_str());
							textBox(601, 750, 100 + curItem * 35, 135 + curItem * 35,  15, 3, (char*)floatToString(current->data.quantity).c_str());
							m.editMaterial(current->data.codeMaterial, ten, donvi);
							m.writeMaterial();
							blankBox(810, 1180, 570, 650);
							textLine(850, 1180, 600, 3, "Da luu!");	
							mOptionButton(0);
						} else if (xx >= 930 && xx <= 1000 && yy >= 610 && yy <= 645){
							choosing = false;
							
							textBox(810, 1180, 145, 180, 15, 3, toCString(current->data.codeMaterial));
							textBox(810, 1180, 225, 260, 15, 3, toCString(current->data.nameMaterial));
							textBox(810, 1180, 305, 340, 15, 3, (char*)current->data.unitMaterial.c_str());
							textBox(810, 1180, 385, 420, 15, 3, (char*)floatToString(current->data.quantity).c_str());
							
							blankBox(810, 1180, 570, 650);	
							mOptionButton(0);
						}
					}
				}	
			} else if (x >= 810 && x <= 865 && y >= 450 && y <=  485){
				mOptionButton(1);
				blankBox(810, 1180, 570, 650);
				textLine(850, 1180, 570, 3, "Xoa vat tu?");
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
								m.deleteMaterial(current->data.codeMaterial, current->data.nameMaterial, current->data.unitMaterial, current->data.quantity, curItem + (curPage - 1) * 15);
								m.writeMaterial();
								choosing = false;
								for (int i = 0; i < 15; ++i){
									if(i + (curPage - 1) * 15 < m.cnt){
										temp[i] = m.parr[i + (curPage - 1) * 15];	
									} else {
										materialNode* n = new materialNode;
										n->data.codeMaterial = "";
										n->data.nameMaterial = "";
										n->data.quantity = 0;
										n->data.unitMaterial = "";
										temp[i] = n;
									}
								}
								for (int i = 0; i <= 14; ++i){
									textBox(1, 160, 100 + i * 35, 135 + i * 35, 15, 3, toCString(temp[i]->data.codeMaterial));
									textBox(161, 440, 100 + i * 35, 135 + i * 35,  15, 3, toCString(temp[i]->data.nameMaterial));
									textBox(441, 600, 100 + i * 35, 135 + i * 35,  15, 3, (char*)temp[i]->data.unitMaterial.c_str());
									textBox(601, 750, 100 + i * 35, 135 + i * 35,  15, 3, (char*)floatToString(temp[i]->data.quantity).c_str());
								}
								curItem = 0;
								current = temp[curItem];
								textBox(810, 1180, 145, 180, 15, 3, toCString(current->data.codeMaterial));
								textBox(810, 1180, 225, 260, 15, 3, toCString(current->data.nameMaterial));
								textBox(810, 1180, 305, 340, 15, 3, (char*)current->data.unitMaterial.c_str());
								textBox(810, 1180, 385, 420, 15, 3, (char*)floatToString(current->data.quantity).c_str());
								blankBox(810, 1180, 570, 650);
								textLine(850, 1180, 600, 3, "Da xoa!");	
								mOptionButton(0);
							} else{
								choosing = false;
								blankBox(810, 1180, 570, 650);	
								mOptionButton(0);
							}
						} else if (key == 0){
							char key2 = getch();
							if (key2 == 75){
								if(!isYES){
									isYES = true;
									textBox(850, 890, 610, 645, 15, 3, "CO");
									textBox(920, 1000, 610, 645, 7, 3, "KHONG");
								}	
							} else if (key2 == 77){
								if(isYES){
									isYES = false;
									textBox(850, 890, 610, 645, 7, 3, "CO");
									textBox(920, 1000, 610, 645, 15, 3, "KHONG");
								}
							}
						}
					}
					if (ismouseclick(WM_LBUTTONDOWN)){
						int xx, yy;
						getmouseclick(WM_LBUTTONDOWN, xx, yy);
						if (xx >= 850 && xx <= 890 && yy >= 610 && yy <= 645){
							choosing = false;
							m.deleteMaterial(current->data.codeMaterial, current->data.nameMaterial, current->data.unitMaterial, current->data.quantity, curItem + (curPage - 1) * 15);
							m.writeMaterial();
							for (int i = 0; i < 15; ++i){
								if(i + (curPage - 1) * 15 < m.cnt){
									temp[i] = m.parr[i + (curPage - 1) * 15];	
								} else {
									materialNode* n = new materialNode;
									n->data.codeMaterial = "";
									n->data.nameMaterial = "";
									n->data.quantity = 0;
									n->data.unitMaterial = "";
									temp[i] = n;
								}
							}
							for (int i = 0; i <= 14; ++i){
								textBox(1, 160, 100 + i * 35, 135 + i * 35, 15, 3, toCString(temp[i]->data.codeMaterial));
								textBox(161, 440, 100 + i * 35, 135 + i * 35,  15, 3, toCString(temp[i]->data.nameMaterial));
								textBox(441, 600, 100 + i * 35, 135 + i * 35,  15, 3, (char*)temp[i]->data.unitMaterial.c_str());
								textBox(601, 750, 100 + i * 35, 135 + i * 35,  15, 3, (char*)floatToString(temp[i]->data.quantity).c_str());
							}
							curItem = 0;
							current = temp[curItem];
							textBox(810, 1180, 145, 180, 15, 3, toCString(current->data.codeMaterial));
							textBox(810, 1180, 225, 260, 15, 3, toCString(current->data.nameMaterial));
							textBox(810, 1180, 305, 340, 15, 3, (char*)current->data.unitMaterial.c_str());
							textBox(810, 1180, 385, 420, 15, 3, (char*)floatToString(current->data.quantity).c_str());
							blankBox(810, 1180, 570, 650);
							textLine(850, 1180, 600, 3, "Da xoa!");	
							mOptionButton(0);
						} else if (xx >= 930 && xx <= 1000 && yy >= 610 && yy <= 645){
							choosing = false;
							blankBox(810, 1180, 570, 650);	
							mOptionButton(0);
						}
					}
				}
			} else if (x >= 1105 && x <= 1180 && y >= 450 && y <= 485){
				mOptionButton(3);
				
				textBox(810, 1180, 145, 180, 15, 3, "");
				textBox(810, 1180, 225, 260, 15, 3, "");
				textBox(810, 1180, 305, 340, 15, 3, "");
				textBox(810, 1180, 385, 420, 15, 3, "");
				
				blankBox(810, 1180, 570, 650);
				string ma = m.getCurrentCode();
				ma = nextGenM(ma);
				textBox(810, 1180, 145, 180, 15, 3, toCString(ma));
				textLine(850, 1180, 600, 3, "Nhap ten vat tu!");
				string ten = "";
				nameALabel:
				editText(810, 1180, 225, 260, false, 20, ten);
				if(ten.length() == 0){
					blankBox(810, 1180, 570, 650);
					textLine(850, 1180, 600, 3, "Khong duoc trong!");
					goto nameALabel;
				}
				blankBox(810, 1180, 570, 650);
				textLine(850, 1180, 600, 3, "Nhap don vi tinh!");
				string donvi = "";
				unitALabel:
				editText(810, 1180, 305, 340, false, 10, donvi);
				if(donvi.length() == 0){
					blankBox(810, 1180, 570, 650);
					textLine(850, 1180, 600, 3, "Khong duoc trong!");
					goto unitALabel;
				}
				blankBox(810, 1180, 570, 650);
				textLine(850, 1180, 600, 3, "Nhap so luong ton!");
				
				string soluong = "";
				quantityALabel:
				editText(810, 1180, 385, 420, true, 10, soluong);
				if(soluong.length() == 0){
					goto quantityALabel;
				}
				
				blankBox(810, 1180, 570, 650);
				textLine(850, 1180, 570, 3, "Them vat tu?");
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
								
								m.addMaterial(ma, ten, donvi, toFloat(soluong));
								m.writeCurrentCode(ma);
								for (int i = 0; i < 15; ++i){
									if(i + (curPage - 1) * 15 < m.cnt){
										temp[i] = m.parr[i + (curPage - 1) * 15];	
									} else {
										materialNode* n = new materialNode;
										n->data.codeMaterial = "";
										n->data.nameMaterial = "";
										n->data.quantity = 0;
										n->data.unitMaterial = "";
										temp[i] = n;
									}
								}
								for (int i = 0; i <= 14; ++i){
									textBox(1, 160, 100 + i * 35, 135 + i * 35, 15, 3, toCString(temp[i]->data.codeMaterial));
									textBox(161, 440, 100 + i * 35, 135 + i * 35,  15, 3, toCString(temp[i]->data.nameMaterial));
									textBox(441, 600, 100 + i * 35, 135 + i * 35,  15, 3, (char*)temp[i]->data.unitMaterial.c_str());
									textBox(601, 750, 100 + i * 35, 135 + i * 35,  15, 3, (char*)floatToString(temp[i]->data.quantity).c_str());
								}
								
								blankBox(810, 1180, 570, 650);
								textLine(850, 1180, 600, 3, "Da them!");	
								mOptionButton(0);
							} else{
								choosing = false;
								blankBox(810, 1180, 570, 650);	
								mOptionButton(0);
							}
						} else if (key == 0){
							char key2 = getch();
							if (key2 == 75){
								if(!isYES){
									isYES = true;
									textBox(850, 890, 610, 645, 15, 3, "CO");
									textBox(920, 1000, 610, 645, 7, 3, "KHONG");
								}	
							} else if (key2 == 77){
								if(isYES){
									isYES = false;
									textBox(850, 890, 610, 645, 7, 3, "CO");
									textBox(920, 1000, 610, 645, 15, 3, "KHONG");
								}
							}
						}
					}
					if (ismouseclick(WM_LBUTTONDOWN)){
						int xx, yy;
						getmouseclick(WM_LBUTTONDOWN, xx, yy);
						if (xx >= 850 && xx <= 890 && yy >= 610 && yy <= 645){
							choosing = false;
							
							m.addMaterial(ma, ten, donvi, toFloat(soluong));
							m.writeCurrentCode(ma);
							for (int i = 0; i < 15; ++i){
								if(i + (curPage - 1) * 15 < m.cnt){
									temp[i] = m.parr[i + (curPage - 1) * 15];	
								} else {
									materialNode* n = new materialNode;
									n->data.codeMaterial = "";
									n->data.nameMaterial = "";
									n->data.quantity = 0;
									n->data.unitMaterial = "";
									temp[i] = n;
								}
							}
							for (int i = 0; i <= 14; ++i){
								textBox(1, 160, 100 + i * 35, 135 + i * 35, 15, 3, toCString(temp[i]->data.codeMaterial));
								textBox(161, 440, 100 + i * 35, 135 + i * 35,  15, 3, toCString(temp[i]->data.nameMaterial));
								textBox(441, 600, 100 + i * 35, 135 + i * 35,  15, 3, (char*)temp[i]->data.unitMaterial.c_str());
								textBox(601, 750, 100 + i * 35, 135 + i * 35,  15, 3, (char*)floatToString(temp[i]->data.quantity).c_str());
							}
							
							blankBox(810, 1180, 570, 650);
							textLine(850, 1180, 600, 3, "Da them!");	
							mOptionButton(0);
						} else if (xx >= 930 && xx <= 1000 && yy >= 610 && yy <= 645){
							choosing = false;
							blankBox(810, 1180, 570, 650);	
							mOptionButton(0);
						}
					}
				}
			} else if(x >= 1 && x <= 750 && y >= 100 && y <= 625){
				int yy = y - 100;
				curItem = yy / 35;
				if(curItem + (curPage - 1) * 15 < m.cnt){
					current = m.parr[curItem + (curPage - 1) * 15];
					textBox(810, 1180, 145, 180, 15, 3, toCString(current->data.codeMaterial));
					textBox(810, 1180, 225, 260, 15, 3, toCString(current->data.nameMaterial));
					textBox(810, 1180, 305, 340, 15, 3, (char*)current->data.unitMaterial.c_str());
					textBox(810, 1180, 385, 420, 15, 3, (char*)floatToString(current->data.quantity).c_str());
				}
					
			} else if (x >= 120 && x <= 290 && y >= 635 && y <= 670){
				if(curPage != 1){
					--curPage;
					blankBox(320, 500, 635, 670);
					string page = "Trang: "+ intToString(curPage);
					textLine(320, 490, 635, 3, toCString(page));
					
					for (int i = 0; i < 15; ++i){
						if(i + (curPage - 1) * 15 < m.cnt){
							temp[i] = m.parr[i + (curPage - 1) * 15];	
						} else {
							materialNode* n = new materialNode;
							n->data.codeMaterial = "";
							n->data.nameMaterial = "";
							n->data.quantity = 0;
							n->data.unitMaterial = "";
							temp[i] = n;
						}
					}
					for (int i = 0; i <= 14; ++i){
						textBox(1, 160, 100 + i * 35, 135 + i * 35, 15, 3, toCString(temp[i]->data.codeMaterial));
						textBox(161, 440, 100 + i * 35, 135 + i * 35,  15, 3, toCString(temp[i]->data.nameMaterial));
						textBox(441, 600, 100 + i * 35, 135 + i * 35,  15, 3, (char*)temp[i]->data.unitMaterial.c_str());
						textBox(601, 750, 100 + i * 35, 135 + i * 35,  15, 3, (char*)floatToString(temp[i]->data.quantity).c_str());
					}
					curItem = 0;
					current = temp[curItem];
					textBox(810, 1180, 145, 180, 15, 3, toCString(current->data.codeMaterial));
					textBox(810, 1180, 225, 260, 15, 3, toCString(current->data.nameMaterial));
					textBox(810, 1180, 305, 340, 15, 3, (char*)current->data.unitMaterial.c_str());
					textBox(810, 1180, 385, 420, 15, 3, (char*)floatToString(current->data.quantity).c_str());
				}
			} else if(x >= 510 && x <= 650 && y >= 635 && y <= 670){
				if(curPage != (m.cnt/15) + 1){
					++curPage;
					string page = "Trang: "+ intToString(curPage);
					blankBox(320, 500, 635, 670);
					textLine(320, 490, 635, 3, toCString(page));
					
					for (int i = 0; i < 15; ++i){
						if(i + (curPage - 1) * 15 < m.cnt){
							temp[i] = m.parr[i + (curPage - 1) * 15];	
						} else {
							materialNode* n = new materialNode;
							n->data.codeMaterial = "";
							n->data.nameMaterial = "";
							n->data.quantity = 0;
							n->data.unitMaterial = "";
							temp[i] = n;
						}
					}
					curItem = 0;
					current = temp[curItem];
					for (int i = 0; i <= 14; ++i){
						textBox(1, 160, 100 + i * 35, 135 + i * 35, 15, 3, toCString(temp[i]->data.codeMaterial));
						textBox(161, 440, 100 + i * 35, 135 + i * 35,  15, 3, toCString(temp[i]->data.nameMaterial));
						textBox(441, 600, 100 + i * 35, 135 + i * 35,  15, 3, (char*)temp[i]->data.unitMaterial.c_str());
						textBox(601, 750, 100 + i * 35, 135 + i * 35,  15, 3, (char*)floatToString(temp[i]->data.quantity).c_str());
					}
					textBox(810, 1180, 145, 180, 15, 3, toCString(current->data.codeMaterial));
					textBox(810, 1180, 225, 260, 15, 3, toCString(current->data.nameMaterial));
					textBox(810, 1180, 305, 340, 15, 3, (char*)current->data.unitMaterial.c_str());
					textBox(810, 1180, 385, 420, 15, 3, (char*)floatToString(current->data.quantity).c_str());
				}
			}
		}
	}
}
void eTab(mManager &m, eManager &e, bManager &b){
	box(1, 1200, 41, 700, 15);
	box(1, 750, 100, 625, 15);
	int curPage = 1;
	int curItem = 0;
	
	Employee** temp = new Employee*[15];
	Employee* current;
	
	for (int i = 0; i < 15; ++i){
		if(i + (curPage - 1) * 15 < e.cnt){
			temp[i] = e.emp[i + (curPage - 1) * 15];	
		} else {
			Employee *n = new Employee;
			n->codeEmp = "";
			n->lastName = "";
			n->firstName = "";
			n->sex = "";
			temp[i] = n;
		}
	}
	
	current = temp[curItem];
	textBox(1, 80, 65, 100, 15, 3, "Ma NV");
	textBox(81, 380, 65, 100, 15, 3, "Ho");
	textBox(381, 680, 65, 100, 15, 3, "Ten");
	textBox(681, 750, 65, 100, 15, 3, "Phai");
	
	for (int i = 0; i <= 14; ++i){
		
		textBox(1, 80, 100 + i * 35, 135 + i * 35, 15, 3, toCString(temp[i]->codeEmp));
		textBox(81, 380, 100 + i * 35, 135 + i * 35,  15, 3, toCString(temp[i]->lastName));
		textBox(381, 680, 100 + i * 35, 135 + i * 35,  15, 3, toCString(temp[i]->firstName));
		textBox(681, 750, 100 + i * 35, 135 + i * 35,  15, 3, toCString(temp[i]->sex));
	}
	
	
	
	string page = "Trang: "+ intToString(curPage);
	textLine(320, 490, 635, 3, toCString(page));
	textBox(120, 290, 635, 670, 7, 3, "Trang truoc");
	textBox(510, 650, 635, 670, 7, 3, "Trang sau");
	
	
	box(800, 1199, 100, 670, 15);
	textLine(860, 1200, 60, 3, "THONG TIN NHAN VIEN");
	textLine(810, 1180, 110, 3,  "Ma nhan vien: ");
	textBox(810, 1180, 145, 180, 15, 3, toCString(current->codeEmp));
	textLine(810, 1180, 190, 3, "Ho nhan vien: ");
	textBox(810, 1180, 225, 260, 15, 3, toCString(current->lastName));
	textLine(810, 1180, 270, 3, "Ten nhan vien: ");
	textBox(810, 1180, 305, 340, 15, 3, toCString(current->firstName));
	textLine(810, 1180, 350, 3, "Gioi tinh(Nam hoac nu): ");
	textBox(950, 1025, 385, 420, 15, 3, toCString(current->sex));
	
	
	eOptionButton(0);
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
				mTab(m, e, b);
			} else if(x >= 601 && x <= 900 && y >= 1 && y <= 40){
				topBar(3);
				bTab(m, e, b);
			} else if(x >= 901 && x <= 1200 && y >= 1 && y <= 40){
				topBar(4);
				aTab(m, e, b);
			} else if(x >= 920 && x <= 1060 && y >= 440 && y <= 475){
				eOptionButton(2);
				blankBox(810, 1180, 490, 650);
				textLine(820, 1180, 510, 3, "Chinh sua ho nhan vien!");
				string ho = current->lastName;
				lastELabel: 
				editText(810, 1180, 225, 260, false, 20, ho);
				if(ho.length() == 0){
					blankBox(810, 1180, 490, 650);
					textLine(820, 1180, 510, 3, "Khong duoc trong!");
					goto lastELabel;
				}
				ho = standardizeName(ho);
				blankBox(810, 1180, 490, 650);
				textLine(820, 1180, 510, 3, "Chinh sua ten nhan vien!");
				string ten = current->firstName;
				firstELabel:
				editText(810, 1180, 305, 340, false, 20, ten);
				if(ten.length() == 0){
					blankBox(810, 1180, 490, 650);
					textLine(820, 1180, 510, 3, "Khong duoc trong!");
					goto firstELabel;	
				}
				ten = standardizeName(ten);
				blankBox(810, 1180, 490, 650);
				string gioitinh = current->sex;
				textBox(950, 1025, 385, 420, LIGHTGREEN, 3, toCString(gioitinh));
				textLine(850, 1180, 485, 3, "Chon gioi tinh!");
				textLine(865, 930, 385, 3, "--->");
				textLine(1054, 1180, 385, 3, "<---");
				textLine(850, 1180, 520, 3, "Click de doi lua chon!");
				textLine(850, 1180, 555, 3, "Nhan Enter de xac nhan!");
				if(gioitinh == "NAM"){
					textBox(850, 920, 600, 635, 15, 3, "NAM");
					textBox(970, 1040, 600, 635, 7, 3, "NU");
				} else {
					textBox(850, 920, 600, 635, 7, 3, "NAM");
					textBox(970, 1040, 600, 635, 15, 3, "NU");
				}
				
				bool choosingSex = true;
				bool isMale  = false;
				if(gioitinh == "NAM"){
					isMale = true;
				}
				while(choosingSex){
					delay(1);
					if (ismouseclick(WM_LBUTTONDOWN)){
						int xx, yy;
						getmouseclick(WM_LBUTTONDOWN, xx, yy);
						if (xx >= 950 && xx <= 1025 && yy >= 385 && yy <= 420){
							if (isMale){
								isMale = false;
								gioitinh = "NU";
								textBox(950, 1025, 385, 420, YELLOW, 3, " NU");
							} else {
								isMale = true;
								gioitinh = "NAM";
								textBox(950, 1025, 385, 420, LIGHTGREEN, 3, " NAM");
							}
							
						}
					}
					if(kbhit()){
						char key = getch();
						if (key == 13){
							if(isMale){
								gioitinh = "NAM";
								// Chon gioi tinh nam
							} else{
								gioitinh = "NU";
								//Chon gioi tinh nu	
								
							}
							blankBox(865, 930, 385, 420);
							blankBox(1054, 1180, 385, 420);
							choosingSex = false;
							eOptionButton(0);
						}else if (key == 0){
							char key2 = getch();
							if (key2 == 75){
								if(!isMale){
									isMale = true;
									textBox(850, 920, 600, 635, 15, 3, "NAM");
									textBox(970, 1040, 600, 635, 7, 3, "NU");
									textBox(950, 1025, 385, 420, LIGHTGREEN, 3, " NAM");
								}	
							} else if (key2 == 77){
								if(isMale){
									isMale = false;
									textBox(850, 920, 600, 635, 7, 3, "NAM");
									textBox(970, 1040, 600, 635, 15, 3, "NU");
									textBox(950, 1025, 385, 420, YELLOW, 3, " NU");
								}
							}
						}	 
					}
				}
				blankBox(810, 1180, 490, 650);	
				textLine(850, 1180, 510, 3, "Luu chinh sua?");
				textBox(850, 890, 550, 585, 15, 3, "CO");
				textBox(920, 1000, 550, 585, 7, 3, "KHONG");
				bool isYES = true;
				bool choosing = true;
				while(choosing){
					delay(1);
					if(kbhit()){
						char key = getch();
						if (key == 13){
							if(isYES){
								choosing = false;
								
								e.editEmployee(curItem + (curPage - 1) * 15, ho, ten, gioitinh);
								e.writeEmployee();
			
								textBox(81, 380, 100 + curItem * 35, 135 + curItem * 35,  15, 3, toCString(ho));
								textBox(381, 680, 100 + curItem * 35, 135 + curItem * 35,  15, 3, toCString(ten));
								textBox(681, 750, 100 + curItem * 35, 135 + curItem * 35,  15, 3, toCString(gioitinh));
								
								textBox(810, 1180, 225, 260, 15, 3, toCString(ho));
								textBox(810, 1180, 305, 340, 15, 3, toCString(ten));
								textBox(950, 1025, 385, 420, 15, 3, toCString(gioitinh));
								
								
								
								blankBox(810, 1180, 490, 650);
								textLine(850, 1180, 510, 3, "Da luu!");	
								eOptionButton(0);
							} else{
								choosing = false;
								
								textBox(810, 1180, 145, 180, 15, 3, toCString(current->codeEmp));
								textBox(810, 1180, 225, 260, 15, 3, toCString(current->lastName));
								textBox(810, 1180, 305, 340, 15, 3, toCString(current->firstName));
								textBox(950, 1025, 385, 420, 15, 3, toCString(current->sex));
								
								blankBox(810, 1180, 490, 650);	
								eOptionButton(0);
							}
						} else if (key == 0){
							char key2 = getch();
							if (key2 == 75){
								if(!isYES){
									isYES = true;
									textBox(850, 890, 550, 585, 15, 3, "CO");
									textBox(920, 1000, 550, 585, 7, 3, "KHONG");
								}	
							} else if (key2 == 77){
								if(isYES){
									isYES = false;
									textBox(850, 890, 550, 585, 7, 3, "CO");
									textBox(920, 1000, 550, 585, 15, 3, "KHONG");
								}
							}
						}
					}
					if (ismouseclick(WM_LBUTTONDOWN)){
						int xx, yy;
						getmouseclick(WM_LBUTTONDOWN, xx, yy);
						if (xx >= 850 && xx <= 890 && yy >= 550 && yy <= 585){
							choosing = false;
							blankBox(810, 1180, 490, 650);
							
							e.editEmployee(curItem + (curPage - 1) * 15, ho, ten, gioitinh);
							e.writeEmployee();
							
							textBox(81, 380, 100 + curItem * 35, 135 + curItem * 35,  15, 3, toCString(ho));
							textBox(381, 680, 100 + curItem * 35, 135 + curItem * 35,  15, 3, toCString(ten));
							textBox(681, 750, 100 + curItem * 35, 135 + curItem * 35,  15, 3, toCString(gioitinh));
							
							textBox(810, 1180, 225, 260, 15, 3, toCString(ho));
							textBox(810, 1180, 305, 340, 15, 3, toCString(ten));
							textBox(950, 1025, 385, 420, 15, 3, toCString(gioitinh));
							
							textLine(850, 1180, 600, 3, "Da luu!");	
							eOptionButton(0);
						} else if (xx >= 930 && xx <= 1000 && yy >= 550 && yy <= 585){
							choosing = false;
							
							textBox(810, 1180, 145, 180, 15, 3, toCString(current->codeEmp));
							textBox(810, 1180, 225, 260, 15, 3, toCString(current->lastName));
							textBox(810, 1180, 305, 340, 15, 3, toCString(current->firstName));
							textBox(950, 1025, 385, 420, 15, 3, toCString(current->sex));
								
							
							blankBox(810, 1180, 490, 650);	
							eOptionButton(0);
						}
					}
				}	
			} else if (x >= 810 && x <= 865 && y >= 440 && y <= 475){
				eOptionButton(1);
				blankBox(810, 1180, 490, 650);	
				textLine(850, 1180, 510, 3, "Xoa nhan vien?");
				textBox(850, 890, 550, 585, 15, 3, "CO");
				textBox(920, 1000, 550, 585, 7, 3, "KHONG");
				bool isYES = true;
				bool choosing = true;
				while(choosing){
					delay(1);
					if(kbhit()){
						char key = getch();
						if (key == 13){
							if(isYES){
								choosing = false;
								blankBox(810, 1180, 490, 650);
								e.deleteEmployee(curItem + (curPage - 1) * 15);
								e.writeEmployee();
								for (int i = 0; i < 15; ++i){
									if(i + (curPage - 1) * 15 < e.cnt){
										temp[i] = e.emp[i + (curPage - 1) * 15];	
									} else {
										Employee* n = new Employee;
										n->codeEmp = "";
										n->lastName = "";
										n->firstName = "";
										n->sex = "";
										temp[i] = n;
									}
								}
								for (int i = 0; i <= 14; ++i){
									textBox(1, 80, 100 + i * 35, 135 + i * 35, 15, 3, toCString(temp[i]->codeEmp));
									textBox(81, 380, 100 + i * 35, 135 + i * 35,  15, 3, toCString(temp[i]->lastName));
									textBox(381, 680, 100 + i * 35, 135 + i * 35,  15, 3, toCString(temp[i]->firstName));
									textBox(681, 750, 100 + i * 35, 135 + i * 35,  15, 3, toCString(temp[i]->sex));
								}
								curItem = 0;
								current = temp[curItem];
								textBox(810, 1180, 145, 180, 15, 3, toCString(current->codeEmp));
								textBox(810, 1180, 225, 260, 15, 3, toCString(current->lastName));
								textBox(810, 1180, 305, 340, 15, 3, toCString(current->firstName));
								textBox(950, 1025, 385, 420, 15, 3, toCString(current->sex));
								blankBox(810, 1180, 570, 650);
								textLine(850, 1180, 600, 3, "Da xoa!");	
							
								eOptionButton(0);
							} else{
								choosing = false;
								blankBox(810, 1180, 490, 650);	
								eOptionButton(0);
							}
						} else if (key == 0){
							char key2 = getch();
							if (key2 == 75){
								if(!isYES){
									isYES = true;
									textBox(850, 890, 550, 585, 15, 3, "CO");
									textBox(920, 1000, 550, 585, 7, 3, "KHONG");
								}	
							} else if (key2 == 77){
								if(isYES){
									isYES = false;
									textBox(850, 890, 550, 585, 7, 3, "CO");
									textBox(920, 1000, 550, 585, 15, 3, "KHONG");
								}
							}
						}
					}
					if (ismouseclick(WM_LBUTTONDOWN)){
						int xx, yy;
						getmouseclick(WM_LBUTTONDOWN, xx, yy);
						if (xx >= 850 && xx <= 890 && yy >= 550 && yy <= 585){
							choosing = false;
							blankBox(810, 1180, 490, 650);
							e.deleteEmployee(curItem + (curPage - 1) * 15);
							e.writeEmployee();
							for (int i = 0; i < 15; ++i){
								if(i + (curPage - 1) * 15 < e.cnt){
									temp[i] = e.emp[i + (curPage - 1) * 15];	
								} else {
									Employee* n = new Employee;
									n->codeEmp = "";
									n->lastName = "";
									n->firstName = "";
									n->sex = "";
									temp[i] = n;
								}
							}
							for (int i = 0; i <= 14; ++i){
								textBox(1, 80, 100 + i * 35, 135 + i * 35, 15, 3, toCString(temp[i]->codeEmp));
								textBox(81, 380, 100 + i * 35, 135 + i * 35,  15, 3, toCString(temp[i]->lastName));
								textBox(381, 680, 100 + i * 35, 135 + i * 35,  15, 3, toCString(temp[i]->firstName));
								textBox(681, 750, 100 + i * 35, 135 + i * 35,  15, 3, toCString(temp[i]->sex));
							}
							curItem = 0;
							current = temp[curItem];
							textBox(810, 1180, 145, 180, 15, 3, toCString(current->codeEmp));
							textBox(810, 1180, 225, 260, 15, 3, toCString(current->lastName));
							textBox(810, 1180, 305, 340, 15, 3, toCString(current->firstName));
							textBox(950, 1025, 385, 420, 15, 3, toCString(current->sex));
							blankBox(810, 1180, 570, 650);
							textLine(850, 1180, 600, 3, "Da xoa!");	
							eOptionButton(0);
						} else if (xx >= 930 && xx <= 1000 && yy >= 550 && yy <= 585){
							choosing = false;
							blankBox(810, 1180, 490, 650);	
							eOptionButton(0);
						}
					}
				}
			} else if (x >= 1105 && x <= 1180 && y >= 440 && y <= 475){
				eOptionButton(3);
				
				textBox(810, 1180, 145, 180, 15, 3, "");
				textBox(810, 1180, 225, 260, 15, 3, "");
				textBox(810, 1180, 305, 340, 15, 3, "");
				
				blankBox(810, 1180, 490, 650);
				if(e.cnt > 500){
					textLine(820, 1180, 510, 3, "Toi da 500 nhan vien!");
					continue;
				}
				
				blankBox(810, 1180, 490, 650);
				string ma = e.getCurrentCode();
				ma = nextGenE(ma);
				textBox(810, 1180, 145, 180, 15, 3, toCString(ma));
				textLine(820, 1180, 510, 3, "Nhap ho nhan vien!");
				string ho = "";
				lastALabel:
				editText(810, 1180, 225, 260, false, 20, ho);
				if(ho.length() == 0){
					blankBox(810, 1180, 490, 650);
					textLine(820, 1180, 510, 3, "Khong duoc trong!");
					goto lastALabel;
				}
				ho = standardizeName(ho);
				blankBox(810, 1180, 490, 650);
				textLine(820, 1180, 510, 3, "Nhap ten nhan vien!");
				string ten = "";
				firstALabel:
				editText(810, 1180, 305, 340, false, 20, ten);
				if(ten.length() == 0){
					blankBox(810, 1180, 490, 650);
					textLine(820, 1180, 510, 3, "Khong duoc trong!");
					goto firstALabel;
				}
				ten = standardizeName(ten);
				blankBox(810, 1180, 490, 650);
				string gioitinh = "NAM";
				textBox(950, 1025, 385, 420, LIGHTGREEN, 3, toCString(gioitinh));
				textLine(850, 1180, 485, 3, "Chon gioi tinh!");
				textLine(865, 930, 385, 3, "--->");
				textLine(1054, 1180, 385, 3, "<---");
				textLine(850, 1180, 520, 3, "Click de doi lua chon!");
				textLine(850, 1180, 555, 3, "Nhan Enter de xac nhan!");
				if(gioitinh == "NAM"){
					textBox(850, 920, 600, 635, 15, 3, "NAM");
					textBox(970, 1040, 600, 635, 7, 3, "NU");
				} else {
					textBox(850, 920, 600, 635, 7, 3, "NAM");
					textBox(970, 1040, 600, 635, 15, 3, "NU");
				}
				bool choosingSex = true;
				bool isMale = true;
				while(choosingSex){
					delay(1);
					if (ismouseclick(WM_LBUTTONDOWN)){
						int xx, yy;
						getmouseclick(WM_LBUTTONDOWN, xx, yy);
						if (xx >= 950 && xx <= 1025 && yy >= 385 && yy <= 420){
							if (isMale){
								isMale = false;
								gioitinh = "NU";
								textBox(950, 1025, 385, 420, YELLOW, 3, "NU");
							} else {
								isMale = true;
								gioitinh = "NAM";
								textBox(950, 1025, 385, 420, LIGHTGREEN, 3, "NAM");
							}
							
						}
					}
					if(kbhit()){
						char key = getch();
						if (key == 13){
							if(isMale){
								gioitinh = "NAM";
								// Chon gioi tinh nam
							} else{
								gioitinh = "NU";
								//Chon gioi tinh nu	
								
							}
							blankBox(865, 930, 385, 420);
							blankBox(1054, 1180, 385, 420);
							choosingSex = false;
							eOptionButton(0);
						} else if (key == 0){
							char key2 = getch();
							if (key2 == 75){
								if(!isMale){
									isMale = true;
									gioitinh = "NAM";
									textBox(850, 920, 600, 635, 15, 3, "NAM");
									textBox(970, 1040, 600, 635, 7, 3, "NU");
									textBox(950, 1025, 385, 420, LIGHTGREEN, 3, " NAM");
								}	
							} else if (key2 == 77){
								if(isMale){
									isMale = false;
									gioitinh = "NU";
									textBox(850, 920, 600, 635, 7, 3, "NAM");
									textBox(970, 1040, 600, 635, 15, 3, "NU");
									textBox(950, 1025, 385, 420, YELLOW, 3, " NU");
								}
							}
						}
					}
				}
				blankBox(810, 1180, 490, 650);	
				textLine(850, 1180, 510, 3, "Them nhan vien?");
				textBox(850, 890, 550, 585, 15, 3, "CO");
				textBox(920, 1000, 550, 585, 7, 3, "KHONG");
				bool isYES = true;
				bool choosing = true;
				while(choosing){
					delay(1);
					if(kbhit()){
						char key = getch();
						if (key == 13){
							if(isYES){
								choosing = false;
								if(e.cnt <= 500){
									e.addEmployee(ma, ho, ten, gioitinh);
									e.writeCurrentCode(ma);
									e.writeEmployee();
									for (int i = 0; i < 15; ++i){
										if(i + (curPage - 1) * 15 < e.cnt){
											temp[i] = e.emp[i + (curPage - 1) * 15];	
										} else {
											Employee *n = new Employee;
											n->codeEmp = "";
											n->lastName = "";
											n->firstName = "";
											n->sex = "";
											temp[i] = n;
										}
									}
									for (int i = 0; i <= 14; ++i){
										textBox(1, 80, 100 + i * 35, 135 + i * 35, 15, 3, toCString(temp[i]->codeEmp));
										textBox(81, 380, 100 + i * 35, 135 + i * 35,  15, 3, toCString(temp[i]->lastName));
										textBox(381, 680, 100 + i * 35, 135 + i * 35,  15, 3, toCString(temp[i]->firstName));
										textBox(681, 750, 100 + i * 35, 135 + i * 35,  15, 3, toCString(temp[i]->sex));
									}
									
									textBox(810, 1180, 225, 260, 15, 3, toCString(ho));
									textBox(810, 1180, 305, 340, 15, 3, toCString(ten));
									textBox(950, 1025, 385, 420, 15, 3, toCString(gioitinh));
									blankBox(810, 1180, 490, 650);
									textLine(850, 1180, 510, 3, "Da them!");
								} else{
									blankBox(810, 1180, 490, 650);
									textLine(850, 1180, 510, 3, "Toi da 500 nhan vien!");	
								}
								
								
									
								eOptionButton(0);
							} else{
								choosing = false;
								
								textBox(810, 1180, 145, 180, 15, 3, toCString(current->codeEmp));
								textBox(810, 1180, 225, 260, 15, 3, toCString(current->lastName));
								textBox(810, 1180, 305, 340, 15, 3, toCString(current->firstName));
								textBox(950, 1025, 385, 420, 15, 3, toCString(current->sex));
								
								blankBox(810, 1180, 490, 650);	
								eOptionButton(0);
							}
						} else if (key == 0){
							char key2 = getch();
							if (key2 == 75){
								if(!isYES){
									isYES = true;
									textBox(850, 890, 550, 585, 15, 3, "CO");
									textBox(920, 1000, 550, 585, 7, 3, "KHONG");
								}	
							} else if (key2 == 77){
								if(isYES){
									isYES = false;
									textBox(850, 890, 550, 585, 7, 3, "CO");
									textBox(920, 1000, 550, 585, 15, 3, "KHONG");
								}
							}
						}
					}
					if (ismouseclick(WM_LBUTTONDOWN)){
						int xx, yy;
						getmouseclick(WM_LBUTTONDOWN, xx, yy);
						if (xx >= 850 && xx <= 890 && yy >= 550 && yy <= 585){
							choosing = false;
							
							if(e.cnt <= 500){
								e.addEmployee(ma, ho, ten, gioitinh);
								e.writeCurrentCode(ma);
								e.writeEmployee();
								textBox(810, 1180, 225, 260, 15, 3, toCString(ho));
								textBox(810, 1180, 305, 340, 15, 3, toCString(ten));
								textBox(950, 1025, 385, 420, 15, 3, toCString(gioitinh));
							} else{
								textLine(850, 1180, 510, 3, "Toi da 500 nhan vien!");	
							}
							
							blankBox(810, 1180, 490, 650);
							textLine(850, 1180, 600, 3, "Da them!");	
							eOptionButton(0);
						} else if (xx >= 930 && xx <= 1000 && yy >= 550 && yy <= 585){
							choosing = false;
							
							textBox(810, 1180, 145, 180, 15, 3, toCString(current->codeEmp));
							textBox(810, 1180, 225, 260, 15, 3, toCString(current->lastName));
							textBox(810, 1180, 305, 340, 15, 3, toCString(current->firstName));
							textBox(950, 1025, 385, 420, 15, 3, toCString(current->sex));
							
							blankBox(810, 1180, 490, 650);	
							eOptionButton(0);
						}
					}
				}	
			}else if (x >= 120 && x <= 290 && y >= 635 && y <= 670){
				if(curPage != 1){
					--curPage;
					blankBox(810, 1180, 490, 650);
					blankBox(320, 500, 635, 670);
					string page = "Trang: "+ intToString(curPage);
					textLine(320, 490, 635, 3, toCString(page));
					
					for (int i = 0; i < 15; ++i){
						if(i + (curPage - 1) * 15 < e.cnt){
							temp[i] = e.emp[i + (curPage - 1) * 15];	
						} else {
							Employee *n = new Employee;
							n->codeEmp = "";
							n->lastName = "";
							n->firstName = "";
							n->sex = "";
							temp[i] = n;
						}
					}
					for (int i = 0; i <= 14; ++i){
						textBox(1, 80, 100 + i * 35, 135 + i * 35, 15, 3, toCString(temp[i]->codeEmp));
						textBox(81, 380, 100 + i * 35, 135 + i * 35,  15, 3, toCString(temp[i]->lastName));
						textBox(381, 680, 100 + i * 35, 135 + i * 35,  15, 3, toCString(temp[i]->firstName));
						textBox(681, 750, 100 + i * 35, 135 + i * 35,  15, 3, toCString(temp[i]->sex));
					}
					curItem = 0;
					current = temp[curItem];
					textBox(810, 1180, 145, 180, 15, 3, toCString(current->codeEmp));
					textBox(810, 1180, 225, 260, 15, 3, toCString(current->lastName));
					textBox(810, 1180, 305, 340, 15, 3, toCString(current->firstName));
					textBox(950, 1025, 385, 420, 15, 3, toCString(current->sex));
					
				}
			} else if(x >= 510 && x <= 650 && y >= 635 && y <= 670){
				if(curPage != (e.cnt/15) + 1){
					++curPage;
					blankBox(810, 1180, 490, 650);
					string page = "Trang: "+ intToString(curPage);
					blankBox(320, 500, 635, 670);
					textLine(320, 490, 635, 3, toCString(page));
					
					for (int i = 0; i < 15; ++i){
						if(i + (curPage - 1) * 15 < e.cnt){
							temp[i] = e.emp[i + (curPage - 1) * 15];	
						} else {
							Employee *n = new Employee;
							n->codeEmp = "";
							n->lastName = "";
							n->firstName = "";
							n->sex = "";
							temp[i] = n;
						}
					}
					for (int i = 0; i <= 14; ++i){
						textBox(1, 80, 100 + i * 35, 135 + i * 35, 15, 3, toCString(temp[i]->codeEmp));
						textBox(81, 380, 100 + i * 35, 135 + i * 35,  15, 3, toCString(temp[i]->lastName));
						textBox(381, 680, 100 + i * 35, 135 + i * 35,  15, 3, toCString(temp[i]->firstName));
						textBox(681, 750, 100 + i * 35, 135 + i * 35,  15, 3, toCString(temp[i]->sex));
					}
					curItem = 0;
					current = temp[curItem];
					textBox(810, 1180, 145, 180, 15, 3, toCString(current->codeEmp));
					textBox(810, 1180, 225, 260, 15, 3, toCString(current->lastName));
					textBox(810, 1180, 305, 340, 15, 3, toCString(current->firstName));
					textBox(950, 1025, 385, 420, 15, 3, toCString(current->sex));
					
				}
			}else if(x >= 1 && x <= 750 && y >= 100 && y <= 625){
				int yy = y - 100;
				blankBox(810, 1180, 490, 650);
				curItem = yy / 35;
				if(curItem + (curPage - 1) * 15 < e.cnt){
					current = e.emp[curItem + (curPage - 1) * 15];
					textBox(810, 1180, 145, 180, 15, 3, toCString(current->codeEmp));
					textBox(810, 1180, 225, 260, 15, 3, toCString(current->lastName));
					textBox(810, 1180, 305, 340, 15, 3, toCString(current->firstName));
					textBox(950, 1025, 385, 420, 15, 3, toCString(current->sex));
				}
					
			}
		}
	}
}

struct MaterialinBill{
//	materialNode *material;
	string code;
	string quan;
	string price;
	string vat;
	MaterialinBill(){
	};
	MaterialinBill(string code, string quan, string price, string vat){
	//	this->material = material;
		this->code = code;
		this->quan = quan;
		this->price = price;
		this->vat = vat;
	}
};

void bTab(mManager &m, eManager &e, bManager &b){
	billAgain:
		
	box(1, 1200, 41, 700, 15);
	box(1, 800, 200, 585, 15);
	blankBox(810, 1200, 385, 650);
	b.resetBill();
	int curPage = 1;
	string page = "Trang: "+ intToString(curPage);
	textLine(320, 490, 635, 3, toCString(page));
	textBox(120, 290, 635, 670, 7, 3, "Trang truoc");
	textBox(510, 650, 635, 670, 7, 3, "Trang sau");
	
	textBox(1, 200, 200, 235, 15, 3, "Ma vat tu");
	textBox(200, 400, 200, 235, 15, 3, "So luong");
	textBox(400, 600, 200, 235, 15, 3, "Don gia");
	textBox(600, 750, 200, 235, 15, 3, "VAT(%)");
	textBox(750, 800, 200, 235, LIGHTRED, 3, "Xoa");
	for(int i = 0; i < 10; ++i){
		textBox(1, 200, 235 + i * 35, 270 + i * 35, 15, 3, "");
		textBox(200, 400, 235 + i * 35, 270 + i * 35, 15, 3, "");
		textBox(400, 600, 235 + i * 35, 270 + i * 35, 15, 3, "");
		textBox(600, 750, 235 + i * 35, 270 + i * 35, 15, 3, "");
		textBox(750, 800, 235 + i * 35, 270 + i * 35, LIGHTRED, 3, "");	
	}
	//MaterialinBill*temp = new MaterialinBill[21];
//	BillDetail*temp = new BillDetail[21];
	int n = 0;
	float total = 0;
	textLine(500, 700, 55, 3, "LAP HOA DON");
	textLine(10, 200, 95, 3, "Loai hoa don:");
	textBox(210, 280, 90, 125,LIGHTRED, 3, "Nhap");
	textLine(290, 360, 95, 3, "Ngay:");
	textBox(370, 430, 90, 125, 15, 3, "");
	textLine(440, 530, 95, 3, "Thang:");
	textBox(540, 600, 90, 125, 15, 3, "");
	textLine(610, 670, 95, 3, "Nam:");
	textBox(680, 800, 90, 125, 15, 3, "");
	textLine(10, 100, 150, 3, "Ma NV:");
	textBox(110, 250, 145, 180, 15, 3, "");
	textLine(270, 600, 150, 3, "Ma hoa don:");
	textBox(430, 800, 145, 180, 15, 3, "");
	textLine(820, 1180, 95, 3,  "Ma vat tu: ");
	textBox(970, 1180, 90, 125, 15, 3, "");
	textLine(820, 1180, 150, 3, "So luong: ");
	textBox(970, 1180, 145, 180, 15, 3, "");
	textLine(820, 1180, 205, 3, "Don gia: ");
	textBox(970, 1180, 200, 235, 15, 3, "");
	textLine(820, 1180, 260, 3, "VAT(%): ");
	textBox(970, 1180, 255, 290, 15, 3, "");
	textBox(820, 990, 320, 355, 7, 3, "Them vat tu");
	textBox(1010, 1180, 320, 355, 7, 3, "Tao hoa don");
	
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
				eTab(m, e, b);
			} else if(x >= 1 && x <= 300 && y >= 1 && y <= 40){
				topBar(1);
				mTab(m, e, b);
			} else if(x >= 901 && x <= 1200 && y >= 1 && y <= 40){
				topBar(4);
				aTab(m, e, b);
			} else if (x >= 1010 && x <= 1180 && y >= 320 && y <= 355){
				blankBox(810, 1200, 385, 650);
				bool choosingType = true;
				bool isImport = true;
				char loai = 'N';
				textBox(850, 920, 550, 585, 15, 3, "NHAP");
				textBox(970, 1040, 550, 585, 7, 3, "XUAT");
				textLine(820, 1180, 400, 3, "Chon loai hoa don!");
				textLine(820, 1180, 435, 3, "Click de thay doi!");
				textLine(820, 1180, 470, 3, "Nhan Enter de xac nhan!");
				while(choosingType){
					delay(1);
					if (ismouseclick(WM_LBUTTONDOWN)){
						int xx, yy;
						getmouseclick(WM_LBUTTONDOWN, xx, yy);
						if (xx >= 210 && xx <= 280 && yy >=  90 && yy <= 125){
							if (isImport){
								isImport = false;
								loai = 'X';
								textBox(210, 280, 90, 125, LIGHTBLUE, 3, "Xuat");
								textBox(850, 920, 550, 585, 7, 3, "NHAP");
								textBox(970, 1040, 550, 585, 15, 3, "XUAT");
							} else {
								isImport = true;
								loai = 'N';
								textBox(210, 280, 90, 125,LIGHTRED, 3, "Nhap");
								textBox(850, 920, 550, 585, 15, 3, "NHAP");
								textBox(970, 1040, 550, 585, 7, 3, "XUAT");
							}
							
						}
					}
					if(kbhit()){
						char key = getch();
						if (key == 13){
							if(isImport){
								loai = 'N';
								// Chon hoa don nhap
							} else{
								loai = 'X';
								//Chon hoa don xuat
							}
							choosingType = false;
						} else if (key == 0){
							char key2 = getch();
							if (key2 == 75){
								if(!isImport){
									isImport = true;
									loai = 'N';
									textBox(850, 920, 550, 585, 15, 3, "NHAP");
									textBox(970, 1040, 550, 585, 7, 3, "XUAT");
									textBox(210, 280, 90, 125,LIGHTRED, 3, "Nhap");
								}	
							} else if (key2 == 77){
								if(isImport){
									isImport = false;
									loai = 'X';
									textBox(850, 920, 550, 585, 7, 3, "NHAP");
									textBox(970, 1040, 550, 585, 15, 3, "XUAT");
									textBox(210, 280, 90, 125, LIGHTBLUE, 3, "Xuat");
								}
							}
						}
					}
				}
				blankBox(810, 1200, 385, 650);
				textLine(820, 1180, 400, 3, "Ngay lap hoa don!");
				textLine(820, 1180, 435, 3, "Nhap ngay tu 1-31!");
				string ngay = "";
				dayLabel:
				editText(370, 430, 90, 125, true, 2, ngay);
				if(ngay.length() == 0){
					blankBox(810, 1200, 385, 650);
					textLine(820, 1180, 400, 3, "Khong duoc trong!");
					goto dayLabel;
				} else if(!isOnlyNumber(ngay)){
					blankBox(810, 1200, 385, 650);
					textLine(820, 1180, 400, 3, "Nhap dung dinh dang!");
					goto dayLabel;
				} else if(ngay.length() == 1){
					ngay = "0" + ngay;
					textBox(370, 430, 90, 125, 15, 3, toCString(ngay));
					
				} 
				if(!(ngay >= "01" && ngay <= "31")){
					blankBox(810, 1200, 385, 650);
					textLine(820, 1180, 400, 3, "Ngay lap hoa don!");
					textLine(820, 1180, 435, 3, "Nhap ngay tu 1-31!");
					goto dayLabel;
				}		
				blankBox(810, 1200, 385, 650);
				textLine(820, 1180, 400, 3, "Ngay lap hoa don!");
				textLine(820, 1180, 435, 3, "Nhap cac thang 1-12");
				if(ngay == "31"){
					blankBox(810, 1200, 385, 650);
					textLine(820, 1180, 400, 3, "Ngay lap hoa don!");
					textLine(820, 1180, 435, 3, "Nhap cac thang: 1, 3, 5");
					textLine(820, 1180, 470, 3, "7, 8, 10, 12");		
					
				} else if (ngay == "30"){
					blankBox(810, 1200, 385, 650);
					textLine(820, 1180, 400, 3, "Ngay lap hoa don!");
					textLine(820, 1180, 435, 3, "Nhap cac thang 1-12");
					textLine(820, 1180, 470, 3, "Khong nhap thang 2");
				}
				string thang = "";
				monthLabel:
				editText(540, 600, 90, 125, true, 2, thang);
				if(thang.length() == 0){
					blankBox(810, 1200, 385, 650);
					textLine(820, 1180, 400, 3, "Khong duoc trong!");
					goto monthLabel;
				} else if(!isOnlyNumber(thang)){
					blankBox(810, 1200, 385, 650);
					textLine(820, 1180, 400, 3, "Nhap dung dinh dang!");
					goto monthLabel;
				} else if(thang.length() == 1){
					thang = "0" + thang;
					textBox(540, 600, 90, 125, 15, 3, toCString(thang));
					
				} 
				if(!(thang >= "01" && thang <= "12")){
					blankBox(810, 1200, 385, 650);
					textLine(820, 1180, 400, 3, "Ngay lap hoa don!");
					textLine(820, 1180, 435, 3, "Nhap lai thang!");
					goto monthLabel;
				}
				if(ngay == "31" && (thang != "01"  && thang != "03" && thang != "05" && thang != "07" && thang != "08" && thang != "10" && thang != "12")){
					blankBox(810, 1200, 385, 650);
					textLine(820, 1180, 400, 3, "Nhap lai thang!");
					textLine(820, 1180, 435, 3, "Nhap cac thang: 1, 3, 5");
					textLine(820, 1180, 470, 3, "7, 8, 10, 12");
					goto monthLabel;	
				} else if (ngay == "30" && thang == "02"){
					blankBox(810, 1200, 385, 650);
					textLine(820, 1180, 400, 3, "Nhap lai thang!");
					textLine(820, 1180, 435, 3, "Nhap cac thang 1-12");
					textLine(820, 1180, 470, 3, "Khong nhap thang 2");
					goto monthLabel;
				}
				blankBox(810, 1200, 385, 650);
				textLine(820, 1180, 400, 3, "Ngay lap hoa don!");
				textLine(820, 1180, 435, 3, "Nhap nam!");
				if(ngay == "29" && thang == "02"){
					blankBox(810, 1200, 385, 650);
					textLine(820, 1180, 400, 3, "Ngay lap hoa don!");
					textLine(820, 1180, 435, 3, "Nhap nam nhuan!");
				}
				string nam = "";
				yearLabel:
				editText(680, 800, 90, 125, true, 4, nam);
				if(nam.length() == 0){
					blankBox(810, 1200, 385, 650);
					textLine(820, 1180, 400, 3, "Khong duoc trong!");
					goto yearLabel;
				}else if(nam.length() <= 3){
					blankBox(810, 1200, 385, 650);
					textLine(820, 1180, 400, 3, "Nhap nam tu 1900-9999!");
					goto yearLabel;
				} else if(nam < "1900" || nam > "9999"){
					blankBox(810, 1200, 385, 650);
					textLine(820, 1180, 400, 3, "Nhap nam tu 1900-9999!");
					goto yearLabel;
				}else if(!isOnlyNumber(nam)){
					blankBox(810, 1200, 385, 650);
					textLine(820, 1180, 400, 3, "Nhap dung dinh dang!");
					goto yearLabel;
				}
				nam = fillYear(nam);
				if(ngay == "29" && thang == "02" && (!isLeapYear(nam))){
					blankBox(810, 1200, 385, 650);
					textLine(820, 1180, 400, 3, "Ngay lap hoa don!");
					textLine(820, 1180, 435, 3, "Nhap nam nhuan!");
					goto yearLabel;
				}
				blankBox(810, 1200, 385, 650);
				textLine(820, 1180, 400, 3, "Nguoi lap hoa don!");
				textLine(820, 1180, 435, 3, "Nhap ma nhan vien!");
				string maNV = "";
				int indexNV = -1;
				codeELabel:
				editText(110, 250, 145, 180, false, 5, maNV);
				if(maNV.length() == 0){
					blankBox(810, 1200, 385, 650);
					textLine(820, 1180, 400, 3, "Khong duoc trong!");
					goto codeELabel;
				}
				indexNV = e.findEmployee(maNV);
				if(indexNV == -1){
					//tim ma nhan vien
					blankBox(810, 1200, 385, 650);
					textLine(820, 1180, 400, 3, "Khong tim thay maNV!");
					textLine(820, 1180, 435, 3, "Nhap lai ma nhan vien!");
					goto codeELabel;
				}
				blankBox(810, 1200, 385, 650);
				string maHD = nextGenB(b.getCurrentCode());
				textBox(430, 800, 145, 180, 15, 3, (char*)maHD.c_str());
				themvattu:
				blankBox(810, 1200, 385, 650);
				textLine(820, 1180, 400, 3, "Them vat tu!");
				textLine(820, 1180, 435, 3, "Nhap ma vat tu!");
				string maVT = "";
				codeMLabel:
				editText(970, 1180, 90, 125, false, 10, maVT);
				if(maVT.length() == 0){
					blankBox(810, 1200, 385, 650);
					textLine(820, 1180, 400, 3, "Khong duoc trong!");
					goto codeMLabel;
				}
				materialNode* node = m.findMaterialCode(maVT);
				if(node == NULL){
					blankBox(810, 1200, 385, 650);
					textLine(820, 1180, 400, 3, "Khong tim thay vat tu!");
					textLine(820, 1180, 435, 3, "Nhap lai ma vat tu!");
					goto codeMLabel;
				}
				if(b.isExist(maVT)){
					blankBox(810, 1200, 385, 650);
					textLine(820, 1180, 400, 3, "Trung ma vat tu!");
					textLine(820, 1180, 435, 3, "Nhap lai ma vat tu!");
					goto codeMLabel;	
				}
				blankBox(810, 1200, 385, 650);
				textLine(820, 1180, 400, 3, "Them vat tu!");
				textLine(820, 1180, 435, 3, "Nhap so luong!");
				string soluong = "";
				quanMLabel:
				editText(970, 1180, 145, 180, true, 10, soluong);
				if(soluong.length() == 0){
					blankBox(810, 1200, 385, 650);
					textLine(820, 1180, 400, 3, "Khong duoc trong!");
					goto quanMLabel;
				}
	
				if(loai == 'X'){
					
					float sl = toFloat(soluong);
					if(node->data.quantity < sl){
						blankBox(810, 1200, 385, 650);
						textLine(820, 1180, 400, 3, "Qua so luong ton!");
						textLine(820, 1180, 435, 3, "Xin nhap lai so luong!");
						string msg = "So luong ton: " + floatToString(node->data.quantity);
						textLine(820, 1180, 470, 3, (char*)msg.c_str());
						goto quanMLabel;
					}
				}
				blankBox(810, 1200, 385, 650);
				textLine(820, 1180, 400, 3, "Them vat tu!");
				textLine(820, 1180, 435, 3, "Nhap don gia!");
				string dongia = "";
				priceMLabel:
				editText(970, 1180, 200, 235, true, 10, dongia);
				if(dongia.length() == 0){
					blankBox(810, 1200, 385, 650);
					textLine(820, 1180, 400, 3, "Khong duoc trong!");
					goto priceMLabel;
				}
				
				blankBox(810, 1200, 385, 650);
				textLine(820, 1180, 400, 3, "Them vat tu!");
				textLine(820, 1180, 435, 3, "Nhap VAT(%)!");
				string VAT = "";
				vatMLabel:
				editText(970, 1180, 255, 290, true, 9, VAT);
				if(VAT.length() == 0){
					blankBox(810, 1200, 385, 650);
					textLine(820, 1180, 400, 3, "Khong duoc trong!");
					goto vatMLabel;
				}
				blankBox(810, 1200, 385, 650);
				textLine(820, 1180, 400, 3, "Click [Them vat tu]");
				textLine(820, 1180, 435, 3, "de tiep tuc them vat tu");
				textLine(820, 1180, 470, 3, "Nhan Enter de xac nhan!");
				textBox(920 , 1085, 510, 545, 15, 3, "Lap hoa don");
				
				if(n > 20){
					blankBox(810, 1200, 385, 650);
					textLine(820, 1180, 400, 3, "Toi da 20 vat tu");
				} else {
					
						
					b.addPayment(maVT, toFloat(soluong), toFloat(dongia), toFloat(VAT));
					//blankBox(810, 1200, 385, 650);
					string tmpTotal = "Tong don gia: " + floatToString(b.currentBill.total);
					blankBox(810, 1180, 630, 680);
					textLine(820, 1180, 650, 3, (char*)tmpTotal.c_str());
					//floatToString(temp[+ (curPage - 1) * 10].vat);
					for (int i = 0; i < 10; ++i){
						if(i + (curPage - 1) * 10 < b.currentBill.cnt){
							textBox(1, 200, 235 + i * 35, 270 + i * 35, 15, 3, (char*)b.currentBill.billDetail[i + (curPage - 1) * 10].code.c_str());
							textBox(200, 400, 235 + i * 35, 270 + i * 35, 15, 3, (char*)floatToString(b.currentBill.billDetail[i + (curPage - 1) * 10].quantity).c_str());
							textBox(400, 600, 235 + i * 35, 270 + i * 35, 15, 3, (char*)floatToString(b.currentBill.billDetail[i + (curPage - 1) * 10].price).c_str());
							textBox(600, 750, 235 + i * 35, 270 + i * 35, 15, 3, (char*)floatToString(b.currentBill.billDetail[i + (curPage - 1) * 10].vat).c_str());
							textBox(750, 800, 235 + i * 35, 270 + i * 35, LIGHTRED, 3, " X ");	
						} else {
							textBox(1, 200, 235 + i * 35, 270 + i * 35, 15, 3, "");
							textBox(200, 400, 235 + i * 35, 270 + i * 35, 15, 3, "");
							textBox(400, 600, 235 + i * 35, 270 + i * 35, 15, 3, "");
							textBox(600, 750, 235 + i * 35, 270 + i * 35, 15, 3, "");
							textBox(750, 800, 235 + i * 35, 270 + i * 35, LIGHTRED, 3, "");
						}
						
					}
				}
				
				bool choosing = true;
				while(choosing){
					delay(1);
					if (ismouseclick(WM_LBUTTONDOWN)){
						int xx, yy;
						getmouseclick(WM_LBUTTONDOWN, xx, yy);
						if (xx >= 820 && xx <= 990 && yy >= 320 && yy <= 355){
							//move to them vat tu
							textBox(970, 1180, 90, 125, 15, 3, "");
							textBox(970, 1180, 145, 180, 15, 3, "");
							textBox(970, 1180, 200, 235, 15, 3, "");
							textBox(970, 1180, 255, 290, 15, 3, "");
							if(n >= 20){
								blankBox(810, 1200, 385, 650);
								textLine(820, 1180, 400, 3, "Toi da 20 vat tu");
							} else {
								goto themvattu;
							}
							
						}else if (xx >= 120 && xx <= 290 && yy >= 635 && yy <= 670){
							if(curPage == 2){
								--curPage;
								blankBox(320, 500, 635, 670);
								string page = "Trang: "+ intToString(curPage);
								textLine(320, 490, 635, 3, toCString(page));
								
								for (int i = 0; i < 10; ++i){
									if(i < n){
										textBox(1, 200, 235 + i * 35, 270 + i * 35, 15, 3, (char*)b.currentBill.billDetail[i].code.c_str());
										textBox(200, 400, 235 + i * 35, 270 + i * 35, 15, 3, (char*)floatToString(b.currentBill.billDetail[i].quantity).c_str());
										textBox(400, 600, 235 + i * 35, 270 + i * 35, 15, 3, (char*)floatToString(b.currentBill.billDetail[i].price).c_str());
										textBox(600, 750, 235 + i * 35, 270 + i * 35, 15, 3, (char*)floatToString(b.currentBill.billDetail[i].vat).c_str());
										textBox(750, 800, 235 + i * 35, 270 + i * 35, LIGHTRED, 3, " X ");	
									} else {
										textBox(1, 200, 235 + i * 35, 270 + i * 35, 15, 3, "");
										textBox(200, 400, 235 + i * 35, 270 + i * 35, 15, 3, "");
										textBox(400, 600, 235 + i * 35, 270 + i * 35, 15, 3, "");
										textBox(600, 750, 235 + i * 35, 270 + i * 35, 15, 3, "");
										textBox(750, 800, 235 + i * 35, 270 + i * 35, LIGHTRED, 3, "");
									}
								}
							}
						}else if(xx >= 510 && xx <= 650 && yy >= 635 && yy <= 670){
							if(curPage != b.currentBill.cnt / 10 + 1){
								++curPage;
								blankBox(810, 1180, 490, 650);
								string page = "Trang: "+ intToString(curPage);
								blankBox(320, 500, 635, 670);
								textLine(320, 490, 635, 3, toCString(page));
								
								for (int i = 0; i < 10; ++i){
									if(i + (curPage - 1) * 10 < b.currentBill.cnt){
										textBox(1, 200, 235 + i * 35, 270 + i * 35, 15, 3, (char*)b.currentBill.billDetail[i + (curPage - 1) * 10].code.c_str());
										textBox(200, 400, 235 + i * 35, 270 + i * 35, 15, 3, (char*)floatToString(b.currentBill.billDetail[i + (curPage - 1) * 10].quantity).c_str());
										textBox(400, 600, 235 + i * 35, 270 + i * 35, 15, 3, (char*)floatToString(b.currentBill.billDetail[i + (curPage - 1) * 10].price).c_str());
										textBox(600, 750, 235 + i * 35, 270 + i * 35, 15, 3, (char*)floatToString(b.currentBill.billDetail[i + (curPage - 1) * 10].vat).c_str());
										textBox(750, 800, 235 + i * 35, 270 + i * 35, LIGHTRED, 3, " X ");
									} else {
										textBox(1, 200, 235 + i * 35, 270 + i * 35, 15, 3, "");
										textBox(200, 400, 235 + i * 35, 270 + i * 35, 15, 3, "");
										textBox(400, 600, 235 + i * 35, 270 + i * 35, 15, 3, "");
										textBox(600, 750, 235 + i * 35, 270 + i * 35, 15, 3, "");
										textBox(750, 800, 235 + i * 35, 270 + i * 35, LIGHTRED, 3, "");
									}
								}
								
								
							}
						} else if(xx >= 750 && xx <= 800 && yy >= 235 && yy <= 585){
							int ty = yy - 235;
							ty = ty / 35;
							if(ty + (curPage - 1) * 10 < b.currentBill.cnt){
								blankBox(810, 1200, 385, 650);
								textLine(820, 1180, 470, 3, "Xoa vat tu!");
								textBox(850, 920, 550, 585, 15, 3, "Co");
								textBox(970, 1060, 550, 585, 7, 3, "Khong");
								bool isYes = true;
								bool deleting = true;
								while(deleting){
									delay(1);
									if(kbhit()){
										char key = getch();
										if (key == 13){
											if(isYes){
												b.deletePayment(ty + (curPage - 1) * 10);
												//total -= b.currentBill.billDetail[ty + (curPage - 1) * 10].total;
												string tmpTotal = "Tong don gia: " + floatToString(b.currentBill.total);
												blankBox(810, 1180, 630, 680);
												textLine(820, 1180, 650, 3, (char*)tmpTotal.c_str());
												
						
												for (int i = 0; i < 10; ++i){
													if(i + (curPage - 1) * 10 < b.currentBill.cnt){
														textBox(1, 200, 235 + i * 35, 270 + i * 35, 15, 3, (char*)b.currentBill.billDetail[i + (curPage - 1) * 10].code.c_str());
														textBox(200, 400, 235 + i * 35, 270 + i * 35, 15, 3, (char*)floatToString(b.currentBill.billDetail[i + (curPage - 1) * 10].quantity).c_str());
														textBox(400, 600, 235 + i * 35, 270 + i * 35, 15, 3, (char*)floatToString(b.currentBill.billDetail[i + (curPage - 1) * 10].price).c_str());
														textBox(600, 750, 235 + i * 35, 270 + i * 35, 15, 3, (char*)floatToString(b.currentBill.billDetail[i + (curPage - 1) * 10].vat).c_str());
														textBox(750, 800, 235 + i * 35, 270 + i * 35, LIGHTRED, 3, " X ");	
													} else {
														textBox(1, 200, 235 + i * 35, 270 + i * 35, 15, 3, "");
														textBox(200, 400, 235 + i * 35, 270 + i * 35, 15, 3, "");
														textBox(400, 600, 235 + i * 35, 270 + i * 35, 15, 3, "");
														textBox(600, 750, 235 + i * 35, 270 + i * 35, 15, 3, "");
														textBox(750, 800, 235 + i * 35, 270 + i * 35, LIGHTRED, 3, "");
													}
												}
															
												blankBox(810, 1200, 385, 650);
												textLine(820, 1180, 400, 3, "Click [Them vat tu]");
												textLine(820, 1180, 435, 3, "de tiep tuc them vat tu");
												textLine(820, 1180, 470, 3, "Nhan Enter de xac nhan!");
												textBox(920 , 1085, 510, 545, 15, 3, "Lap hoa don");
											} else{
												
												blankBox(810, 1200, 385, 650);
												textLine(820, 1180, 400, 3, "Click [Them vat tu]");
												textLine(820, 1180, 435, 3, "de tiep tuc them vat tu");
												textLine(820, 1180, 470, 3, "Nhan Enter de xac nhan!");
												textBox(920 , 1085, 510, 545, 15, 3, "Lap hoa don");
											}
											deleting = false;
										} else if (key == 0){
											char key2 = getch();
											if (key2 == 75){
												if(!isYes){
													isYes = true;
													
													textBox(850, 920, 550, 585, 15, 3, "Co");
													textBox(970, 1060, 550, 585, 7, 3, "Khong");
												}	
											} else if (key2 == 77){
												if(isYes){
													isYes = false;
													textBox(850, 920, 550, 585, 7, 3, "Co");
													textBox(970, 1060, 550, 585, 15, 3, "Khong");
												}
											}
										}
									}
								}
									
							}
						}
					}
					if(kbhit()){
						char key = getch();
						if (key == 13){
							if(b.currentBill.cnt == 0){
								blankBox(810, 1200, 385, 650);
								textLine(820, 1180, 400, 3, "Nhap it nhat 1 vat tu!");
								textBox(970, 1180, 90, 125, 15, 3, "");
								textBox(970, 1180, 145, 180, 15, 3, "");
								textBox(970, 1180, 200, 235, 15, 3, "");
								textBox(970, 1180, 255, 290, 15, 3, "");	
								goto themvattu;
							}
							choosing = false;							
							for (int i = 0; i < b.currentBill.cnt; ++i){
								
								if(loai == 'N'){
									m.incQuantity(b.currentBill.billDetail[i].code, b.currentBill.billDetail[i].quantity);
									m.writeMaterial();
								} else {
									m.decQuantity(b.currentBill.billDetail[i].code, b.currentBill.billDetail[i].quantity);
									m.writeMaterial();
								}
							}
							
							
							int arr[100];
							
							int i = e.findEmployee(maNV);
							if (i != -1){
								insertBill(e.emp[i]->billList, b.currentBill);// in ra file tam thoi bi loi
							}
							b.currentBill.billType = loai;
							b.currentBill.time = Time((int)toInt(ngay), (int)toInt(thang), (int)toInt(nam));
							b.currentBill.code = maHD;
							b.currentBill.empCode = maNV;
							int index = e.findEmployee(maNV);
							if(index != -1){
								//
							}
							b.addBill();
							
							//b.writeBill(); luu dât xuong file - dang bi loi!
							
							b.resetBill();
							b.writeCurrentCode(maHD);
							blankBox(810, 1200, 385, 650);
							textLine(820, 1180, 400, 3, "Da lap hoa don!");
							goto billAgain;
							//bTab(m, e, b);
							// Luu data	
						} 
					}
				}
			}
		}
	}
}
void aTab(mManager &m, eManager &e, bManager &b){
	box(1, 1200, 41, 700, 15);
	box(1, 800, 200, 585, 15);
	textLine(500, 700, 80, 3, "THONG KE");
	int curPage = 1;
	string page = "Trang: "+ intToString(curPage);
	textLine(320, 490, 635, 3, toCString(page));
	textBox(120, 290, 635, 670, 7, 3, "Trang truoc");
	textBox(510, 650, 635, 670, 7, 3, "Trang sau");
	
	textBox(970, 1120, 120, 155, 7, 3, "In vat tu");
	textBox(970, 1170, 185, 220, 7, 3, "In nhan vien");
	textBox(970, 1140, 250, 285, 7, 3, "In hoa don");
	textBox(970, 1170, 315, 350, 7, 3, "Loc hoa don");
	textBox(970, 1140, 380, 415, 7, 3, "Loc vat tu");
	
	
	
//	Vat tu
//	textBox(1, 160, 200, 235, 15, 3, "Ma vat tu");
//	textBox(161, 460, 200, 235, 15, 3, "Ten vat tu");
//	textBox(461, 620, 200, 235, 15, 3, "Don vi");
//	textBox(621, 800, 200, 235, 15, 3, "So luong");

//  Nhan vien
//	textBox(1, 120, 200, 235, 15, 3, "Ma NV");
//	textBox(121, 370, 200, 235, 15, 3, "Ho");
//	textBox(371, 620, 200, 235, 15, 3, "Ten");
//	textBox(621, 800, 200, 235, 15, 3, "Gioi tinh");

//	for (int i = 1; i <= 10; ++i){
//		textBox(1, 160, 200 + i * 35, 235 + i * 35, 15, 3, "Ma vat tu");
//		textBox(161, 460, 200 + i * 35, 235 + i * 35, 15, 3, "Ten vat tu");
//		textBox(461, 620, 200 + i * 35, 235 + i * 35, 15, 3, "Don vi");
//		textBox(621, 800, 200 + i * 35, 235 + i * 35, 15, 3, "So luong");
//	}
	
	
	
	
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
				eTabLabel:
				topBar(2);
				eTab(m, e, b);
			} else if(x >= 601 && x <= 900 && y >= 1 && y <= 40){
				bTabLabel:
				topBar(3);
				bTab(m, e, b);
			} else if(x >= 1 && x <= 300 && y >= 1 && y <= 40){
				mTabLabel:
				topBar(1);
				mTab(m, e, b);
			} else if (x >= 970 && x<= 1120 && y >=  120 && y <= 155){
				mListLabel:
				m.sort();
				
				blankBox(820, 1180, 440, 680);
				box(1, 800, 200, 585, 15);
				blankBox(5, 950, 120, 190);
				textLine(300, 600, 150, 3, "Danh sach vat tu");
				textBox(1, 160, 200, 235, 15, 3, "Ma vat tu");
				textBox(161, 460, 200, 235, 15, 3, "Ten vat tu");
				textBox(461, 620, 200, 235, 15, 3, "Don vi");
				textBox(621, 800, 200, 235, 15, 3, "So luong");
				
				materialNode** temp = new materialNode* [10];
				int curPage = 1;
				for (int i = 0; i < 10; ++i){
					if(i + (curPage - 1) * 10 < m.cnt){
						temp[i] = m.parr[i + (curPage - 1) * 10];	
					} else {
						materialNode* n = new materialNode;
						n->data.codeMaterial = "";
						n->data.nameMaterial = "";
						n->data.quantity = 0;
						n->data.unitMaterial = "";
						temp[i] = n;
					}
				}
				for (int i = 0; i < 10; ++i){
					textBox(1, 160, 235 + i * 35, 270 + i * 35, 15, 3, (char*)temp[i]->data.codeMaterial.c_str());
					textBox(161, 460, 235 + i * 35, 270 + i * 35, 15, 3, (char*)temp[i]->data.nameMaterial.c_str());
					textBox(461, 620, 235 + i * 35, 270 + i * 35, 15, 3, (char*)temp[i]->data.unitMaterial.c_str());
					textBox(621, 800, 235 + i * 35, 270 + i * 35, 15, 3, (char*)floatToString(temp[i]->data.quantity).c_str());
				}
				while(1){
					delay(1);
					if(kbhit()){
						char key = getch();
						//if(key == 0) return;
					}
					int xx, yy;
					if (ismouseclick(WM_LBUTTONDOWN)){
						getmouseclick(WM_LBUTTONDOWN, xx, yy);
						if(xx >= 301 && xx <= 600 && yy >= 1 && yy <= 40){
							goto eTabLabel;
							
						} else if(xx >= 601 && xx <= 900 && yy >= 1 && yy <= 40){
							goto bTabLabel;
							
						} else if(xx >= 1 && xx <= 300 && yy >= 1 && yy <= 40){
							goto mTabLabel;
							
						} else if (xx >= 120 && xx <= 290 && yy >= 635 && yy <= 670){
							if(curPage != 1){
								--curPage;
								blankBox(320, 500, 635, 670);
								string page = "Trang: "+ intToString(curPage);
								textLine(320, 490, 635, 3, toCString(page));
					
								for (int i = 0; i < 10; ++i){
									if(i + (curPage - 1) * 10 < m.cnt){
										temp[i] = m.parr[i + (curPage - 1) * 10];	
									} else {
										materialNode* n = new materialNode;
										n->data.codeMaterial = "";
										n->data.nameMaterial = "";
										n->data.quantity = 0;
										n->data.unitMaterial = "";
										temp[i] = n;
									}
								}
								for (int i = 0; i < 10; ++i){
									textBox(1, 160, 235 + i * 35, 270 + i * 35, 15, 3, (char*)temp[i]->data.codeMaterial.c_str());
									textBox(161, 460, 235 + i * 35, 270 + i * 35, 15, 3, (char*)temp[i]->data.nameMaterial.c_str());
									textBox(461, 620, 235 + i * 35, 270 + i * 35, 15, 3, (char*)temp[i]->data.unitMaterial.c_str());
									textBox(621, 800, 235 + i * 35, 270 + i * 35, 15, 3, (char*)floatToString(temp[i]->data.quantity).c_str());
								}
								
							}		
						} else if(xx >= 510 && xx <= 650 && yy >= 635 && yy <= 670){
							if(curPage != (m.cnt/10) + 1){
								++curPage;
								blankBox(320, 500, 635, 670);
								string page = "Trang: "+ intToString(curPage);
								textLine(320, 490, 635, 3, toCString(page));
					
								for (int i = 0; i < 10; ++i){
									if(i + (curPage - 1) * 10 < m.cnt){
										temp[i] = m.parr[i + (curPage - 1) * 10];	
									} else {
										materialNode* n = new materialNode;
										n->data.codeMaterial = "";
										n->data.nameMaterial = "";
										n->data.quantity = 0;
										n->data.unitMaterial = "";
										temp[i] = n;
									}
								}
								
								for (int i = 0; i < 10; ++i){
									textBox(1, 160, 235 + i * 35, 270 + i * 35, 15, 3, (char*)temp[i]->data.codeMaterial.c_str());
									textBox(161, 460, 235 + i * 35, 270 + i * 35, 15, 3, (char*)temp[i]->data.nameMaterial.c_str());
									textBox(461, 620, 235 + i * 35, 270 + i * 35, 15, 3, (char*)temp[i]->data.unitMaterial.c_str());
									textBox(621, 800, 235 + i * 35, 270 + i * 35, 15, 3, (char*)floatToString(temp[i]->data.quantity).c_str());
								}
							}
						} else if(xx >= 970 && xx <= 1170 && yy >= 185 && yy <= 220){
							goto eListLabel;
						} else if(xx >= 970 && xx <= 1140 && yy >= 250 && yy <= 285){
							goto bLabel;
						} else if(xx >= 970 && xx <= 1170 && yy >= 315 && yy <= 350){
							goto timeLabel;
						} else if(xx >= 970 && xx <= 1140 && yy >= 380 && yy <= 415){
							goto topLabel;
						}
					}
				}
			} else if(x >= 970 && x <= 1170 && y >= 185 && y <= 220){
				eListLabel:
				e.sort();
				
				blankBox(820, 1180, 440, 680);
				box(1, 800, 200, 585, 15);
				blankBox(5, 950, 120, 190);
				textLine(300, 600, 150, 3, "Danh sach nhan vien");
				textBox(1, 120, 200, 235, 15, 3, "Ma NV");
				textBox(121, 370, 200, 235, 15, 3, "Ho");
				textBox(371, 620, 200, 235, 15, 3, "Ten");
				textBox(621, 800, 200, 235, 15, 3, "Gioi tinh");
				
				int curPage = 1;
				Employee** temp = new Employee*[10];
	
				for (int i = 0; i < 10; ++i){
					if(i + (curPage - 1) * 10 < e.cnt){
						temp[i] = e.emp[i + (curPage - 1) * 10];	
					} else {
						Employee *n = new Employee;
						n->codeEmp = "";
						n->lastName = "";
						n->firstName = "";
						n->sex = "";
						temp[i] = n;
					}
				}	
				for (int i = 0; i < 10; ++i){
					textBox(1, 120, 235 + i * 35, 270 + i * 35, 15, 3, (char*)temp[i]->codeEmp.c_str());
					textBox(121, 370, 235 + i * 35, 270 + i * 35, 15, 3, (char*)temp[i]->lastName.c_str());
					textBox(371, 620, 235 + i * 35, 270 + i * 35, 15, 3, (char*)temp[i]->firstName.c_str());
					textBox(621, 800, 235 + i * 35, 270 + i * 35, 15, 3, (char*)temp[i]->sex.c_str());
				}
				string page = "Trang: "+ intToString(curPage);
				textLine(320, 490, 635, 3, toCString(page));
				textBox(120, 290, 635, 670, 7, 3, "Trang truoc");
				textBox(510, 650, 635, 670, 7, 3, "Trang sau");
				
				while(1){
					delay(1);
					if(kbhit()){
						char key = getch();
						//if(key == 0) return;
					}
					int xx, yy;
					if (ismouseclick(WM_LBUTTONDOWN)){
						getmouseclick(WM_LBUTTONDOWN, xx, yy);
						if(xx >= 301 && xx <= 600 && yy >= 1 && yy <= 40){
							goto eTabLabel;
							
						} else if(xx >= 601 && xx <= 900 && yy >= 1 && yy <= 40){
							goto bTabLabel;
							
						} else if(xx >= 1 && xx <= 300 && yy >= 1 && yy <= 40){
							goto mTabLabel;
							
						} else if (xx >= 120 && xx <= 290 && yy >= 635 && yy <= 670){
							if(curPage != 1){
								--curPage;
								blankBox(320, 500, 635, 670);
								string page = "Trang: "+ intToString(curPage);
								textLine(320, 490, 635, 3, toCString(page));
					
								for (int i = 0; i < 10; ++i){
									if(i + (curPage - 1) * 10 < e.cnt){
										temp[i] = e.emp[i + (curPage - 1) * 10];	
									} else {
										Employee *n = new Employee;
										n->codeEmp = "";
										n->lastName = "";
										n->firstName = "";
										n->sex = "";
										temp[i] = n;
									}
								}	
								for (int i = 0; i < 10; ++i){
									textBox(1, 120, 235 + i * 35, 270 + i * 35, 15, 3, (char*)temp[i]->codeEmp.c_str());
									textBox(121, 370, 235 + i * 35, 270 + i * 35, 15, 3, (char*)temp[i]->lastName.c_str());
									textBox(371, 620, 235 + i * 35, 270 + i * 35, 15, 3, (char*)temp[i]->firstName.c_str());
									textBox(621, 800, 235 + i * 35, 270 + i * 35, 15, 3, (char*)temp[i]->sex.c_str());
								}	
							}		
						} else if(xx >= 510 && xx <= 650 && yy >= 635 && yy <= 670){
							if(curPage != (e.cnt/10) + 1){
								++curPage;
								string page = "Trang: "+ intToString(curPage);
								blankBox(320, 500, 635, 670);
								textLine(320, 490, 635, 3, toCString(page));
					
								for (int i = 0; i < 10; ++i){
									if(i + (curPage - 1) * 10 < e.cnt){
										temp[i] = e.emp[i + (curPage - 1) * 10];	
									} else {
										Employee *n = new Employee;
										n->codeEmp = "";
										n->lastName = "";
										n->firstName = "";
										n->sex = "";
										temp[i] = n;
									}
								}
								
								for (int i = 0; i < 10; ++i){
									textBox(1, 120, 235 + i * 35, 270 + i * 35, 15, 3, (char*)temp[i]->codeEmp.c_str());
									textBox(121, 370, 235 + i * 35, 270 + i * 35, 15, 3, (char*)temp[i]->lastName.c_str());
									textBox(371, 620, 235 + i * 35, 270 + i * 35, 15, 3, (char*)temp[i]->firstName.c_str());
									textBox(621, 800, 235 + i * 35, 270 + i * 35, 15, 3, (char*)temp[i]->sex.c_str());
								}
							}
						} else if (xx >= 970 && xx <= 1120 && yy >=  120 && yy <= 155){
							goto mListLabel;
						} else if(xx >= 970 && xx <= 1140 && yy >= 250 && yy <= 285){
							goto bLabel;
						} else if(xx >= 970 && xx <= 1170 && yy >= 315 && yy <= 350){
							goto timeLabel;
						} else if(xx >= 970 && xx <= 1140 && yy >= 380 && yy <= 415){
							goto topLabel;
						}
					}
				}			
			} else if(x >= 970 && x <= 1140 && y >= 250 && y <= 285){
				bLabel:
				
				string maHD = "";
				codeLabel:
				blankBox(5, 950, 120, 190);
				blankBox(820, 1180, 440, 680);
				box(1, 800, 200, 585, 15);
				textLine(850, 1180, 460, 3, "Nhap ma hoa don");
				editText(820, 1180, 635, 670, false, 20, maHD);
				
				if(maHD.length() == 0){
					blankBox(5, 950, 120, 190);
					blankBox(820, 1180, 440, 680);
					textLine(850, 1180, 460, 3, "Khong duoc trong!");
					goto codeLabel;
				}
				
				int index = b.searchBill(maHD);
				
				
					
				if(index == -1){
					blankBox(5, 950, 120, 190);
					blankBox(810, 1180, 440, 680);
					textLine(820, 1180, 460, 3, "Khong tim thay ma HD!");
				} else {
				//	Bill bill = b.parr[index];
					
					
					string type = "LoaiHD: "; 
					if(b.parr[index].billType == 'N'){
						type += "N";
					} else{
						type += "X";
					}
					textLine(5, 150, 165, 3, (char*)type.c_str());
					string day = "Ngay lap: " + intToString((long long)b.parr[index].time.date) + "/" + intToString((long long)b.parr[index].time.month) + "/" + intToString((long long)b.parr[index].time.year);
					textLine(160, 460, 165, 3, (char*)day.c_str());
					string codeEmp = "MaNV: " + b.parr[index].empCode;
					textLine(470, 640, 165, 3, (char*)codeEmp.c_str());
					string money = "$: " + floatToString(b.parr[index].total);
					textLine(650, 950, 165, 3, (char*)money.c_str());
					
					textBox(1, 150, 200, 235, 15, 3, "Ten vat tu");
					textBox(150, 300, 200, 235, 15, 3, "So luong");
					textBox(300, 450, 200, 235, 15, 3, "Don gia");
					textBox(450, 600, 200, 235, 15, 3, "VAT(%)");
					textBox(600, 800, 200, 235, 15, 3, "Thanh tien");
					
					
					int curPage = 1;
					BillDetail *temp = new BillDetail[10];
					
					for (int i = 0; i < 10; ++i){
						if(i + (curPage - 1) * 10 < b.parr[index].cnt){
							temp[i] = b.parr[index].billDetail[i + (curPage - 1) * 10];	
						} 
					}
					
					for (int i = 0; i < 10; ++i){
						if(i + (curPage - 1) * 10  < b.parr[index].cnt){
							//0m.findMaterialCode(temp[i].code);
							
							textBox(1, 150, 235 + i * 35, 270 + i * 35, 15, 3, (char*)m.findMaterialCode(temp[i].code)->data.nameMaterial.c_str());
							textBox(150, 300, 235 + i * 35, 270 + i * 35, 15, 3, (char*)floatToString(temp[i].quantity).c_str());
							textBox(300, 450, 235 + i * 35, 270 + i * 35, 15, 3, (char*)floatToString(temp[i].price).c_str());
							textBox(450, 600, 235 + i * 35, 270 + i * 35, 15, 3, (char*)floatToString(temp[i].vat).c_str());	
							textBox(600, 800, 235 + i * 35, 270 + i * 35, 15, 3, (char*)floatToString(temp[i].total).c_str());
						}else {
							textBox(1, 150, 235 + i * 35, 270 + i * 35, 15, 3, "");
							textBox(150, 300, 235 + i * 35, 270 + i * 35, 15, 3, "");
							textBox(300, 450, 235 + i * 35, 270 + i * 35, 15, 3, "");
							textBox(450, 600, 235 + i * 35, 270 + i * 35, 15, 3, "");
							textBox(600, 800, 235 + i * 35, 270 + i * 35, 15, 3, "");
						}
						
					}
					
					while(1){
						delay(1);
						if(kbhit()){
							char key = getch();
							//if(key == 0) return;
						}
						int xx, yy;
						if (ismouseclick(WM_LBUTTONDOWN)){
							getmouseclick(WM_LBUTTONDOWN, xx, yy);
							if(xx >= 301 && xx <= 600 && yy >= 1 && yy <= 40){
								goto eTabLabel;
							
							} else if(xx >= 601 && xx <= 900 && yy >= 1 && yy <= 40){
								goto bTabLabel;
							
							} else if(xx >= 1 && xx <= 300 && yy >= 1 && yy <= 40){
								goto mTabLabel;
							
							} else if (xx >= 120 && xx <= 290 && yy >= 635 && yy <= 670){
								if(curPage != 1){
									--curPage;
									blankBox(320, 500, 635, 670);
									string page = "Trang: "+ intToString(curPage);
									textLine(320, 490, 635, 3, toCString(page));
					
									for (int i = 0; i < 10; ++i){
										if(i + (curPage - 1) * 10 < b.parr[index].cnt){
											temp[i] = b.parr[index].billDetail[i + (curPage - 1) * 10];	
										} 
									}
										
									for (int i = 0; i < 10; ++i){
										if(i + (curPage - 1) * 10  < b.parr[index].cnt){
											textBox(1, 150, 235 + i * 35, 270 + i * 35, 15, 3, (char*)temp[i].code.c_str());
											textBox(150, 300, 235 + i * 35, 270 + i * 35, 15, 3, (char*)floatToString(temp[i].quantity).c_str());
											textBox(300, 450, 235 + i * 35, 270 + i * 35, 15, 3, (char*)floatToString(temp[i].price).c_str());
											textBox(450, 600, 235 + i * 35, 270 + i * 35, 15, 3, (char*)floatToString(temp[i].vat).c_str());	
											textBox(600, 800, 235 + i * 35, 270 + i * 35, 15, 3, (char*)floatToString(temp[i].total).c_str());
										}else {
											textBox(1, 150, 235 + i * 35, 270 + i * 35, 15, 3, "");
											textBox(150, 300, 235 + i * 35, 270 + i * 35, 15, 3, "");
											textBox(300, 450, 235 + i * 35, 270 + i * 35, 15, 3, "");
											textBox(450, 600, 235 + i * 35, 270 + i * 35, 15, 3, "");
											textBox(600, 800, 235 + i * 35, 270 + i * 35, 15, 3, "");
										}
										
									}	
								}		
							} else if(xx >= 510 && xx <= 650 && yy >= 635 && yy <= 670){
								if(curPage != (b.parr[index].cnt/10) + 1){
									++curPage;
									string page = "Trang: "+ intToString(curPage);
									blankBox(320, 500, 635, 670);
									textLine(320, 490, 635, 3, toCString(page));
					
									for (int i = 0; i < 10; ++i){
										if(i + (curPage - 1) * 10 < b.parr[index].cnt){
											temp[i] = b.parr[index].billDetail[i + (curPage - 1) * 10];	
										} 
									}
										
									for (int i = 0; i < 10; ++i){
										if(i + (curPage - 1) * 10  < b.parr[index].cnt){
											textBox(1, 150, 235 + i * 35, 270 + i * 35, 15, 3, (char*)temp[i].code.c_str());
											textBox(150, 300, 235 + i * 35, 270 + i * 35, 15, 3, (char*)floatToString(temp[i].quantity).c_str());
											textBox(300, 450, 235 + i * 35, 270 + i * 35, 15, 3, (char*)floatToString(temp[i].price).c_str());
											textBox(450, 600, 235 + i * 35, 270 + i * 35, 15, 3, (char*)floatToString(temp[i].vat).c_str());	
											textBox(600, 800, 235 + i * 35, 270 + i * 35, 15, 3, (char*)floatToString(temp[i].total).c_str());
										}else {
											textBox(1, 150, 235 + i * 35, 270 + i * 35, 15, 3, "");
											textBox(150, 300, 235 + i * 35, 270 + i * 35, 15, 3, "");
											textBox(300, 450, 235 + i * 35, 270 + i * 35, 15, 3, "");
											textBox(450, 600, 235 + i * 35, 270 + i * 35, 15, 3, "");
											textBox(600, 800, 235 + i * 35, 270 + i * 35, 15, 3, "");
										}
										
									}
								}
							} else if (xx >= 970 && xx <= 1120 && yy >=  120 && yy <= 155){
								goto mListLabel;
							} else if(xx >= 970 && xx <= 1170 && yy >= 185 && yy <= 220){
								goto eListLabel;
							} else if(xx >= 970 && xx <= 1170 && yy >= 315 && yy <= 350){
								goto timeLabel;
							} else if(xx >= 970 && xx <= 1140 && yy >= 380 && yy <= 415){
								goto topLabel;
							}
						}
					}		
				}
			} else if(x >= 970 && x <= 1170 && y >= 315 && y <= 350){
				timeLabel:
				blankBox(5, 950, 120, 190);
				box(1, 800, 200, 585, 15);
				blankBox(820, 1180, 440, 680);
				textLine(850, 1180, 450, 3, "Nhap ngay bat dau!");
				textLine(850, 1180, 550, 3, "Nhap ngay tu 1-31!");
				textLine(850, 1180, 485, 3, "Ngay: ");
				string ngay = "";
				ngayLabel:
				editText(950, 1050, 485, 520, true, 2, ngay);
				if(ngay.length() == 0){
					blankBox(5, 950, 120, 190);
					blankBox(820, 1180, 440, 680);
					textLine(850, 1180, 450, 3, "Nhap ngay bat dau!");
					textLine(850, 1180, 550, 3, "Khong duoc trong!");
					goto ngayLabel;
				} else if(!isOnlyNumber(ngay)){
					blankBox(5, 950, 120, 190);
					blankBox(850, 1180, 440, 680);
					textLine(850, 1180, 450, 3, "Nhap ngay bat dau!");
					textLine(820, 1180, 550, 3, "Nhap dung dinh dang!");
					goto ngayLabel;
				} else if(ngay.length() == 1){
					ngay = "0" + ngay;
				} 
				if(!(ngay >= "01" && ngay <= "31")){
					blankBox(5, 950, 120, 190);
					blankBox(820, 1180, 440, 680);
					textLine(850, 1180, 450, 3, "Nhap ngay bat dau!");
					textLine(820, 1180, 550, 3, "Nhap ngay tu 1-31!");
					goto ngayLabel;
				}
						
				blankBox(5, 950, 120, 190);
				blankBox(820, 1180, 440, 680);
				textLine(850, 1180, 450, 3, "Nhap ngay bat dau!");
				textLine(850, 1180, 550, 3, "Nhap cac thang 1-12");
				if(ngay == "31"){
					blankBox(5, 950, 120, 190);
					blankBox(820, 1180, 440, 680);
					textLine(850, 1180, 450, 3, "Nhap ngay bat dau!");
					textLine(850, 1180, 550, 3, "Nhap cac thang: 1, 3, 5");
					textLine(850, 1180, 585, 3, "7, 8, 10, 12");		
					
				} else if (ngay == "30"){
					blankBox(5, 950, 120, 190);
					blankBox(820, 1180, 440, 680);
					textLine(850, 1180, 450, 3, "Nhap ngay bat dau!");
					textLine(820, 1180, 550, 3, "Nhap cac thang 1-12");
					textLine(820, 1180, 585, 3, "Khong nhap thang 2");
				}
				
				textLine(850, 1180, 485, 3, "Thang: ");
				string thang = "";
				thangLabel:
				editText(950, 1050, 485, 520, true, 2, thang);
				if(thang.length() == 0){
					blankBox(5, 950, 120, 190);
					blankBox(820, 1180, 440, 680);
					textLine(850, 1180, 450, 3, "Nhap ngay bat dau!");
					textLine(850, 1180, 550, 3, "Khong duoc trong!");
					goto thangLabel;
				} else if(!isOnlyNumber(thang)){
					blankBox(5, 950, 120, 190);
					blankBox(820, 1180, 440, 680);
					textLine(850, 1180, 450, 3, "Nhap ngay bat dau!");
					textLine(850, 1180, 550, 3, "Nhap dung dinh dang!");
					goto thangLabel;
				} else if(thang.length() == 1){
					thang = "0" + thang;
				} 
				if(!(thang >= "01" && thang <= "12")){
					blankBox(5, 950, 120, 190);
					blankBox(820, 1180, 440, 680);
					textLine(850, 1180, 450, 3, "Nhap ngay bat dau!");
					textLine(850, 1180, 550, 3, "Nhap lai thang!");
					goto thangLabel;
				}
				if(ngay == "31" && (thang != "01"  && thang != "03" && thang != "05" && thang != "07" && thang != "08" && thang != "10" && thang != "12")){
					blankBox(5, 950, 120, 190);
					blankBox(820, 1180, 440, 680);
					textLine(850, 1180, 550, 3, "Nhap lai thang!");
					textLine(820, 1180, 585, 3, "Nhap cac thang: 1, 3, 5");
					textLine(820, 1180, 620, 3, "7, 8, 10, 12");
					goto thangLabel;	
				} else if (ngay == "30" && thang == "02"){
					blankBox(5, 950, 120, 190);
					blankBox(820, 1180, 440, 680);
					textLine(850, 1180, 550, 3, "Nhap lai thang!");
					textLine(820, 1180, 585, 3, "Nhap cac thang 1-12");
					textLine(820, 1180, 620, 3, "Khong nhap thang 2!");
					goto thangLabel;
				}
				blankBox(5, 950, 120, 190);
				blankBox(820, 1180, 440, 680);
				textLine(850, 1180, 450, 3, "Nhap ngay bat dau!");
				textLine(850, 1180, 550, 3, "Nhap nam!");
				if(ngay == "29" && thang == "02"){
					blankBox(5, 950, 120, 190);
					blankBox(820, 1180, 440, 680);
					textLine(850, 1180, 450, 3, "Nhap ngay bat dau!");
					textLine(850, 1180, 550, 3, "Nhap nam nhuan!");
				}
				textLine(850, 1180, 485, 3, "Nam: ");
				string nam = "";
				namLabel:
				editText(950, 1100, 485, 520, true, 4, nam);
				
				if(nam.length() == 0){
					blankBox(5, 950, 120, 190);
					blankBox(820, 1180, 440, 680);
					textLine(850, 1180, 450, 3, "Nhap ngay bat dau!");
					textLine(850, 1180, 550, 3, "Khong duoc trong");
					goto namLabel;
				}else if(nam.length() <= 3){
					blankBox(5, 950, 120, 190);
					blankBox(820, 1180, 440, 680);
					textLine(850, 1180, 450, 3, "Nhap ngay bat dau!");
					textLine(820, 1180, 550, 3, "Nhap nam tu 1900-9999!");
					goto namLabel;
				} else if(nam < "1900" || nam > "9999"){
					blankBox(5, 950, 120, 190);
					blankBox(820, 1180, 440, 680);
					textLine(850, 1180, 450, 3, "Nhap ngay bat dau!");
					textLine(820, 1180, 550, 3, "Nhap nam tu 1900-9999!");
					goto namLabel;
				}else if(!isOnlyNumber(nam)){
					blankBox(5, 950, 120, 190);
					blankBox(820, 1180, 440, 680);
					textLine(850, 1180, 450, 3, "Nhap ngay bat dau!");
					textLine(820, 1180, 550, 3, "Nhap dung dinh dang!");
					goto namLabel;
				}
				
				if(ngay == "29" && thang == "02" && (!isLeapYear(nam))){
					blankBox(5, 950, 120, 190);
					blankBox(820, 1180, 440, 680);
					textLine(850, 1180, 450, 3, "Nhap ngay bat dau!");
					textLine(820, 1180, 550, 3, "Nhap nam nhuan!");
					goto namLabel;
				}
				//nam bat dau
				
				blankBox(5, 950, 120, 190);
				blankBox(820, 1180, 440, 680);
				textLine(850, 1180, 450, 3, "Nhap ngay ket thuc!");
				textLine(850, 1180, 550, 3, "Nhap ngay tu 1-31!");
				textLine(850, 1180, 485, 3, "Ngay: ");
				string ngay1 = "";
				ngay1Label:
				editText(950, 1050, 485, 520, true, 2, ngay1);
				if(ngay1.length() == 0){
					blankBox(5, 950, 120, 190);
					blankBox(820, 1180, 440, 680);
					textLine(850, 1180, 450, 3, "Nhap ngay ket thuc!");
					textLine(850, 1180, 550, 3, "Khong duoc trong!");
					goto ngay1Label;
				} else if(!isOnlyNumber(ngay1)){
					blankBox(5, 950, 120, 190);
					blankBox(850, 1180, 440, 680);
					textLine(850, 1180, 450, 3, "Nhap ngay ket thuc!");
					textLine(820, 1180, 550, 3, "Nhap dung dinh dang!");
					goto ngay1Label;
				} else if(ngay1.length() == 1){
					ngay1 = "0" + ngay1;
				} 
				if(!(ngay1 >= "01" && ngay1 <= "31")){
					blankBox(5, 950, 120, 190);
					blankBox(820, 1180, 440, 680);
					textLine(850, 1180, 450, 3, "Nhap ngay ket thuc!");
					textLine(820, 1180, 550, 3, "Nhap ngay tu 1-31!");
					goto ngay1Label;
				}
						
				blankBox(5, 950, 120, 190);
				blankBox(820, 1180, 440, 680);
				textLine(850, 1180, 450, 3, "Nhap ngay ket thuc!");
				textLine(850, 1180, 550, 3, "Nhap cac thang 1-12");
				if(ngay1 == "31"){
					blankBox(5, 950, 120, 190);
					blankBox(820, 1180, 440, 680);
					textLine(850, 1180, 450, 3, "Nhap ngay ket thuc!");
					textLine(850, 1180, 550, 3, "Nhap cac thang: 1, 3, 5");
					textLine(850, 1180, 585, 3, "7, 8, 10, 12");		
					
				} else if (ngay1 == "30"){
					blankBox(5, 950, 120, 190);
					blankBox(820, 1180, 440, 680);
					textLine(850, 1180, 450, 3, "Nhap ngay ket thuc!");
					textLine(820, 1180, 550, 3, "Nhap cac thang 1-12");
					textLine(820, 1180, 585, 3, "Khong nhap thang 2");
				}
				
				textLine(850, 1180, 485, 3, "Thang: ");
				string thang1 = "";
				thang1Label:
				editText(950, 1050, 485, 520, true, 2, thang1);
				if(thang.length() == 0){
					blankBox(5, 950, 120, 190);
					blankBox(820, 1180, 440, 680);
					textLine(850, 1180, 450, 3, "Nhap ngay ket thuc!");
					textLine(850, 1180, 550, 3, "Khong duoc trong!");
					goto thang1Label;
				} else if(!isOnlyNumber(thang1)){
					blankBox(5, 950, 120, 190);
					blankBox(820, 1180, 440, 680);
					textLine(850, 1180, 450, 3, "Nhap ngay ket thuc!");
					textLine(850, 1180, 550, 3, "Nhap dung dinh dang!");
					goto thang1Label;
				} else if(thang1.length() == 1){
					thang1 = "0" + thang;
				} 
				if(!(thang1 >= "01" && thang1 <= "12")){
					blankBox(5, 950, 120, 190);
					blankBox(820, 1180, 440, 680);
					textLine(850, 1180, 450, 3, "Nhap ngay ket thuc!");
					textLine(850, 1180, 550, 3, "Nhap lai thang!");
					goto thang1Label;
				}
				if(ngay1 == "31" && (thang1 != "01"  && thang1 != "03" && thang1 != "05" && thang1 != "07" && thang1 != "08" && thang1 != "10" && thang1 != "12")){
					blankBox(5, 950, 120, 190);
					blankBox(820, 1180, 440, 680);
					textLine(850, 1180, 550, 3, "Nhap lai thang!");
					textLine(820, 1180, 585, 3, "Nhap cac thang: 1, 3, 5");
					textLine(820, 1180, 620, 3, "7, 8, 10, 12");
					goto thang1Label;	
				} else if (ngay1 == "30" && thang1 == "02"){
					blankBox(5, 950, 120, 190);
					blankBox(820, 1180, 440, 680);
					textLine(850, 1180, 550, 3, "Nhap lai thang!");
					textLine(820, 1180, 585, 3, "Nhap cac thang 1-12");
					textLine(820, 1180, 620, 3, "Khong nhap thang 2!");
					goto thang1Label;
				}
				blankBox(5, 950, 120, 190);
				blankBox(820, 1180, 440, 680);
				textLine(850, 1180, 450, 3, "Nhap ngay ket thuc!");
				textLine(850, 1180, 550, 3, "Nhap nam!");
				if(ngay1 == "29" && thang1 == "02"){
					blankBox(5, 950, 120, 190);
					blankBox(820, 1180, 440, 680);
					textLine(850, 1180, 450, 3, "Nhap ngay ket thuc!");
					textLine(850, 1180, 550, 3, "Nhap nam nhuan!");
				}
				textLine(850, 1180, 485, 3, "Nam: ");
				string nam1 = "";
				nam1Label:
				editText(950, 1100, 485, 520, true, 4, nam1);
				
				if(nam1.length() == 0){
					blankBox(5, 950, 120, 190);
					blankBox(820, 1180, 440, 680);
					textLine(850, 1180, 450, 3, "Nhap ngay ket thuc!");
					textLine(850, 1180, 550, 3, "Khong duoc trong");
					goto nam1Label;
				}else if(nam1.length() <= 3){
					blankBox(5, 950, 120, 190);
					blankBox(820, 1180, 440, 680);
					textLine(850, 1180, 450, 3, "Nhap ngay ket thuc!");
					textLine(820, 1180, 550, 3, "Nhap nam tu 1900-9999!");
					goto nam1Label;
				} else if(nam1 < "1900" || nam1 > "9999"){
					blankBox(5, 950, 120, 190);
					blankBox(820, 1180, 440, 680);
					textLine(850, 1180, 450, 3, "Nhap ngay ket thuc!");
					textLine(820, 1180, 550, 3, "Nhap nam tu 1900-9999!");
					goto nam1Label;
				}else if(!isOnlyNumber(nam1)){
					blankBox(5, 950, 120, 190);
					blankBox(820, 1180, 440, 680);
					textLine(850, 1180, 450, 3, "Nhap ngay ket thuc!");
					textLine(820, 1180, 550, 3, "Nhap dung dinh dang!");
					goto nam1Label;
				}
				
				if(ngay1 == "29" && thang1 == "02" && (!isLeapYear(nam1))){
					blankBox(5, 950, 120, 190);
					blankBox(820, 1180, 440, 680);
					textLine(850, 1180, 450, 3, "Nhap ngay bat dau!");
					textLine(820, 1180, 550, 3, "Nhap nam nhuan!");
					goto nam1Label;
				}
				
				Time from = Time((int)toInt(ngay), (int)toInt(thang), (int)toInt(nam));
				Time to = Time((int)toInt(ngay1), (int)toInt(thang1), (int)toInt(nam1));
				if(CompareTime(from, to) > 0){
					goto timeLabel;
				} else {
					b.getBillInTime(from, to);
					blankBox(5, 950, 120, 190);
					textLine(100, 800, 130, 3, "Bang liet ke hoa don trong khoang thoi gian");
					string timeText = "tu ngay " + ngay + "/" + thang + "/" + nam + "  den ngay " + ngay1 + "/" + thang1 + "/" + nam1;
					textLine(100, 800, 165, 3, (char*)timeText.c_str());
					
					
					
					textBox(1, 220, 200, 235, 15, 3, "ma HD");
					textBox(220, 340, 200, 235, 15, 3, "ddmmyyyy");
					textBox(340, 400, 200, 235, 15, 3, "Loai");
					textBox(400, 650, 200, 235, 15, 3, "Ten nhan vien ten");
					textBox(650, 800, 200, 235, 15, 3, "thanh tien");
					
					int curPage = 1;
					
					string page = "Trang: "+ intToString(curPage);
					blankBox(320, 500, 635, 670);
					textLine(320, 490, 635, 3, toCString(page));
					
					Bill temp[10];
					
					for (int i = 0; i < 10; ++i){
						if(i + (curPage - 1) * 10 < b.indexBillInTime){
							temp[i] = b.billInTime[i + (curPage - 1) * 10];	
						} 
					}
					
					for (int i = 0; i < 10; ++i){
						if(i + (curPage - 1) * 10  < b.indexBillInTime){
							textBox(1, 220, 235 + i * 35, 270 + i * 35, 15, 3, (char*)temp[i].code.c_str());
							string day = intToString(temp[i].time.date);
							if(day.length() == 1){
								day = "0" + day;
							}
							string month = intToString(temp[i].time.month);
							if(month.length() == 1){
								month = "0" + month;
							}
							string year = intToString(temp[i].time.year);
							year = fillYear(year);
							string dayText = day + month + year;
							textBox(220, 340, 235 + i * 35, 270 + i * 35, 15, 3, (char*)dayText.c_str());
							string type = "N";
							if(temp[i].billType == 'X'){
								type = "X";
							}
							textBox(340, 400, 235 + i * 35, 270 + i * 35, 15, 3, (char*)type.c_str());
							int index = e.findEmployee(temp[i].empCode);
							string name = temp[i].empCode + "(X)";
							if(index != -1){
								name = e.emp[index]->lastName + " " + e.emp[index]->firstName;
							}
							textBox(400, 650, 235 + i * 35, 270 + i * 35, 15, 3, (char*)name.c_str());
							textBox(650, 800, 235 + i * 35, 270 + i * 35, 15, 3, (char*)floatToString(temp[i].total).c_str());
						}else {
							textBox(1, 220, 235 + i * 35, 270 + i * 35, 15, 3, "");
							textBox(220, 340, 235 + i * 35, 270 + i * 35, 15, 3, "");
							textBox(340, 400, 235 + i * 35, 270 + i * 35, 15, 3, "");
							textBox(400, 650, 235 + i * 35, 270 + i * 35, 15, 3, "");
							textBox(650, 800, 235 + i * 35, 270 + i * 35, 15, 3, "");
						}
						
					}
					
					while(1){
						delay(1);
						if(kbhit()){
							char key = getch();
							//if(key == 0) return;
						}
						int xx, yy;
						if (ismouseclick(WM_LBUTTONDOWN)){
							getmouseclick(WM_LBUTTONDOWN, xx, yy);
							if(xx >= 301 && xx <= 600 && yy >= 1 && yy <= 40){
								goto eTabLabel;
							
							} else if(xx >= 601 && xx <= 900 && yy >= 1 && yy <= 40){
								goto bTabLabel;
							
							} else if(xx >= 1 && xx <= 300 && yy >= 1 && yy <= 40){
								goto mTabLabel;
							
							} else if (xx >= 120 && xx <= 290 && yy >= 635 && yy <= 670){
								if(curPage != 1){
									--curPage;
									blankBox(320, 500, 635, 670);
									string page = "Trang: "+ intToString(curPage);
									textLine(320, 490, 635, 3, toCString(page));
					
									for (int i = 0; i < 10; ++i){
										if(i + (curPage - 1) * 10 < b.indexBillInTime){
											temp[i] = b.billInTime[i + (curPage - 1) * 10];	
										} 
									}
							
									for (int i = 0; i < 10; ++i){
										if(i + (curPage - 1) * 10  < b.indexBillInTime){
											textBox(1, 220, 235 + i * 35, 270 + i * 35, 15, 3, (char*)temp[i].code.c_str());
											string day = intToString(temp[i].time.date);
											if(day.length() == 1){
												day = "0" + day;
											}
											string month = intToString(temp[i].time.month);
											if(month.length() == 1){
												month = "0" + month;
											}
											string year = intToString(temp[i].time.year);
											year = fillYear(year);
											string dayText = day + month + year;
											textBox(220, 340, 235 + i * 35, 270 + i * 35, 15, 3, (char*)dayText.c_str());
											string type = "N";
											if(temp[i].billType == 'X'){
												type = "X";
											}
											textBox(340, 400, 235 + i * 35, 270 + i * 35, 15, 3, (char*)type.c_str());
											int index = e.findEmployee(temp[i].empCode);
											string name = temp[i].empCode + "(X)";
											if(index != -1){
												name = e.emp[index]->lastName + " " + e.emp[index]->firstName;
											}
											textBox(400, 650, 235 + i * 35, 270 + i * 35, 15, 3, (char*)name.c_str());
											textBox(650, 800, 235 + i * 35, 270 + i * 35, 15, 3, (char*)floatToString(temp[i].total).c_str());
										}else {
											textBox(1, 220, 235 + i * 35, 270 + i * 35, 15, 3, "");
											textBox(220, 340, 235 + i * 35, 270 + i * 35, 15, 3, "");
											textBox(340, 400, 235 + i * 35, 270 + i * 35, 15, 3, "");
											textBox(400, 650, 235 + i * 35, 270 + i * 35, 15, 3, "");
											textBox(650, 800, 235 + i * 35, 270 + i * 35, 15, 3, "");
										}
						
									}
										
								}		
							} else if(xx >= 510 && xx <= 650 && yy >= 635 && yy <= 670){
								if(curPage != (b.indexBillInTime/10) + 1){
									++curPage;
									string page = "Trang: "+ intToString(curPage);
									blankBox(320, 500, 635, 670);
									textLine(320, 490, 635, 3, toCString(page));
					
									for (int i = 0; i < 10; ++i){
										if(i + (curPage - 1) * 10 < b.indexBillInTime){
											temp[i] = b.billInTime[i + (curPage - 1) * 10];	
										} 
									}
							
									for (int i = 0; i < 10; ++i){
										if(i + (curPage - 1) * 10  < b.indexBillInTime){
											textBox(1, 220, 235 + i * 35, 270 + i * 35, 15, 3, (char*)temp[i].code.c_str());
											string day = intToString(temp[i].time.date);
											if(day.length() == 1){
												day = "0" + day;
											}
											string month = intToString(temp[i].time.month);
											if(month.length() == 1){
												month = "0" + month;
											}
											string year = intToString(temp[i].time.year);
											year = fillYear(year);
											string dayText = day + month + year;
											textBox(220, 340, 235 + i * 35, 270 + i * 35, 15, 3, (char*)dayText.c_str());
											string type = "N";
											if(temp[i].billType == 'X'){
												type = "X";
											}
											textBox(340, 400, 235 + i * 35, 270 + i * 35, 15, 3, (char*)type.c_str());
											int index = e.findEmployee(temp[i].empCode);
											string name = temp[i].empCode + "(X)";
											if(index != -1){
												name = e.emp[index]->lastName + " " + e.emp[index]->firstName;
											}
											textBox(400, 650, 235 + i * 35, 270 + i * 35, 15, 3, (char*)name.c_str());
											textBox(650, 800, 235 + i * 35, 270 + i * 35, 15, 3, (char*)floatToString(temp[i].total).c_str());
										}else {
											textBox(1, 220, 235 + i * 35, 270 + i * 35, 15, 3, "");
											textBox(220, 340, 235 + i * 35, 270 + i * 35, 15, 3, "");
											textBox(340, 400, 235 + i * 35, 270 + i * 35, 15, 3, "");
											textBox(400, 650, 235 + i * 35, 270 + i * 35, 15, 3, "");
											textBox(650, 800, 235 + i * 35, 270 + i * 35, 15, 3, "");
										}
						
									}
								}
							} else if (xx >= 970 && xx <= 1120 && yy >=  120 && yy <= 155){
								goto mListLabel;
							} else if(xx >= 970 && xx <= 1170 && yy >= 185 && yy <= 220){
								goto eListLabel;
							} else if(xx >= 970 && xx <= 1140 && yy >= 250 && yy <= 285){
								goto bLabel;
							} else if(xx >= 970 && xx <= 1140 && yy >= 380 && yy <= 415){
								goto topLabel;
							}
						}
					}
				}
			} else if(x >= 970 && x <= 1140 && y >= 380 && y <= 415){
				topLabel:
				
				blankBox(5, 950, 120, 190);
				box(1, 800, 200, 585, 15);
				blankBox(820, 1180, 440, 680);
				textLine(850, 1180, 450, 3, "Nhap ngay bat dau!");
				textLine(850, 1180, 550, 3, "Nhap ngay tu 1-31!");
				textLine(850, 1180, 485, 3, "Ngay: ");
				string ngay = "";
				ngay2Label:
				editText(950, 1050, 485, 520, true, 2, ngay);
				if(ngay.length() == 0){
					blankBox(5, 950, 120, 190);
					blankBox(820, 1180, 440, 680);
					textLine(850, 1180, 450, 3, "Nhap ngay bat dau!");
					textLine(850, 1180, 550, 3, "Khong duoc trong!");
					goto ngay2Label;
				} else if(!isOnlyNumber(ngay)){
					blankBox(5, 950, 120, 190);
					blankBox(850, 1180, 440, 680);
					textLine(850, 1180, 450, 3, "Nhap ngay bat dau!");
					textLine(820, 1180, 550, 3, "Nhap dung dinh dang!");
					goto ngay2Label;
				} else if(ngay.length() == 1){
					ngay = "0" + ngay;
				} 
				if(!(ngay >= "01" && ngay <= "31")){
					blankBox(5, 950, 120, 190);
					blankBox(820, 1180, 440, 680);
					textLine(850, 1180, 450, 3, "Nhap ngay bat dau!");
					textLine(820, 1180, 550, 3, "Nhap ngay tu 1-31!");
					goto ngay2Label;
				}
						
				blankBox(5, 950, 120, 190);
				blankBox(820, 1180, 440, 680);
				textLine(850, 1180, 450, 3, "Nhap ngay bat dau!");
				textLine(850, 1180, 550, 3, "Nhap cac thang 1-12");
				if(ngay == "31"){
					blankBox(5, 950, 120, 190);
					blankBox(820, 1180, 440, 680);
					textLine(850, 1180, 450, 3, "Nhap ngay bat dau!");
					textLine(850, 1180, 550, 3, "Nhap cac thang: 1, 3, 5");
					textLine(850, 1180, 585, 3, "7, 8, 10, 12");		
					
				} else if (ngay == "30"){
					blankBox(5, 950, 120, 190);
					blankBox(820, 1180, 440, 680);
					textLine(850, 1180, 450, 3, "Nhap ngay bat dau!");
					textLine(820, 1180, 550, 3, "Nhap cac thang 1-12");
					textLine(820, 1180, 585, 3, "Khong nhap thang 2");
				}
				
				textLine(850, 1180, 485, 3, "Thang: ");
				string thang = "";
				thang2Label:
				editText(950, 1050, 485, 520, true, 2, thang);
				if(thang.length() == 0){
					blankBox(5, 950, 120, 190);
					blankBox(820, 1180, 440, 680);
					textLine(850, 1180, 450, 3, "Nhap ngay bat dau!");
					textLine(850, 1180, 550, 3, "Khong duoc trong!");
					goto thang2Label;
				} else if(!isOnlyNumber(thang)){
					blankBox(5, 950, 120, 190);
					blankBox(820, 1180, 440, 680);
					textLine(850, 1180, 450, 3, "Nhap ngay bat dau!");
					textLine(850, 1180, 550, 3, "Nhap dung dinh dang!");
					goto thang2Label;
				} else if(thang.length() == 1){
					thang = "0" + thang;
				} 
				if(!(thang >= "01" && thang <= "12")){
					blankBox(5, 950, 120, 190);
					blankBox(820, 1180, 440, 680);
					textLine(850, 1180, 450, 3, "Nhap ngay bat dau!");
					textLine(850, 1180, 550, 3, "Nhap lai thang!");
					goto thang2Label;
				}
				if(ngay == "31" && (thang != "01"  && thang != "03" && thang != "05" && thang != "07" && thang != "08" && thang != "10" && thang != "12")){
					blankBox(5, 950, 120, 190);
					blankBox(820, 1180, 440, 680);
					textLine(850, 1180, 550, 3, "Nhap lai thang!");
					textLine(820, 1180, 585, 3, "Nhap cac thang: 1, 3, 5");
					textLine(820, 1180, 620, 3, "7, 8, 10, 12");
					goto thang2Label;	
				} else if (ngay == "30" && thang == "02"){
					blankBox(5, 950, 120, 190);
					blankBox(820, 1180, 440, 680);
					textLine(850, 1180, 550, 3, "Nhap lai thang!");
					textLine(820, 1180, 585, 3, "Nhap cac thang 1-12");
					textLine(820, 1180, 620, 3, "Khong nhap thang 2!");
					goto thang2Label;
				}
				blankBox(5, 950, 120, 190);
				blankBox(820, 1180, 440, 680);
				textLine(850, 1180, 450, 3, "Nhap ngay bat dau!");
				textLine(850, 1180, 550, 3, "Nhap nam!");
				if(ngay == "29" && thang == "02"){
					blankBox(5, 950, 120, 190);
					blankBox(820, 1180, 440, 680);
					textLine(850, 1180, 450, 3, "Nhap ngay bat dau!");
					textLine(850, 1180, 550, 3, "Nhap nam nhuan!");
				}
				textLine(850, 1180, 485, 3, "Nam: ");
				string nam = "";
				nam2Label:
				editText(950, 1100, 485, 520, true, 4, nam);
				
				if(nam.length() == 0){
					blankBox(5, 950, 120, 190);
					blankBox(820, 1180, 440, 680);
					textLine(850, 1180, 450, 3, "Nhap ngay bat dau!");
					textLine(850, 1180, 550, 3, "Khong duoc trong");
					goto nam2Label;
				}else if(nam.length() <= 3){
					blankBox(5, 950, 120, 190);
					blankBox(820, 1180, 440, 680);
					textLine(850, 1180, 450, 3, "Nhap ngay bat dau!");
					textLine(820, 1180, 550, 3, "Nhap nam tu 1900-9999!");
					goto nam2Label;
				} else if(nam < "1900" || nam > "9999"){
					blankBox(5, 950, 120, 190);
					blankBox(820, 1180, 440, 680);
					textLine(850, 1180, 450, 3, "Nhap ngay bat dau!");
					textLine(820, 1180, 550, 3, "Nhap nam tu 1900-9999!");
					goto nam2Label;
				}else if(!isOnlyNumber(nam)){
					blankBox(5, 950, 120, 190);
					blankBox(820, 1180, 440, 680);
					textLine(850, 1180, 450, 3, "Nhap ngay bat dau!");
					textLine(820, 1180, 550, 3, "Nhap dung dinh dang!");
					goto nam2Label;
				}
				
				if(ngay == "29" && thang == "02" && (!isLeapYear(nam))){
					blankBox(5, 950, 120, 190);
					blankBox(820, 1180, 440, 680);
					textLine(850, 1180, 450, 3, "Nhap ngay bat dau!");
					textLine(820, 1180, 550, 3, "Nhap nam nhuan!");
					goto nam2Label;
				}
				//nam bat dau
				
				blankBox(5, 950, 120, 190);
				blankBox(820, 1180, 440, 680);
				textLine(850, 1180, 450, 3, "Nhap ngay ket thuc!");
				textLine(850, 1180, 550, 3, "Nhap ngay tu 1-31!");
				textLine(850, 1180, 485, 3, "Ngay: ");
				string ngay1 = "";
				ngay3Label:
				editText(950, 1050, 485, 520, true, 2, ngay1);
				if(ngay1.length() == 0){
					blankBox(5, 950, 120, 190);
					blankBox(820, 1180, 440, 680);
					textLine(850, 1180, 450, 3, "Nhap ngay ket thuc!");
					textLine(850, 1180, 550, 3, "Khong duoc trong!");
					goto ngay3Label;
				} else if(!isOnlyNumber(ngay1)){
					blankBox(5, 950, 120, 190);
					blankBox(850, 1180, 440, 680);
					textLine(850, 1180, 450, 3, "Nhap ngay ket thuc!");
					textLine(820, 1180, 550, 3, "Nhap dung dinh dang!");
					goto ngay3Label;
				} else if(ngay1.length() == 1){
					ngay1 = "0" + ngay1;
				} 
				if(!(ngay1 >= "01" && ngay1 <= "31")){
					blankBox(5, 950, 120, 190);
					blankBox(820, 1180, 440, 680);
					textLine(850, 1180, 450, 3, "Nhap ngay ket thuc!");
					textLine(820, 1180, 550, 3, "Nhap ngay tu 1-31!");
					goto ngay3Label;
				}
						
				blankBox(5, 950, 120, 190);
				blankBox(820, 1180, 440, 680);
				textLine(850, 1180, 450, 3, "Nhap ngay ket thuc!");
				textLine(850, 1180, 550, 3, "Nhap cac thang 1-12");
				if(ngay1 == "31"){
					blankBox(5, 950, 120, 190);
					blankBox(820, 1180, 440, 680);
					textLine(850, 1180, 450, 3, "Nhap ngay ket thuc!");
					textLine(850, 1180, 550, 3, "Nhap cac thang: 1, 3, 5");
					textLine(850, 1180, 585, 3, "7, 8, 10, 12");		
					
				} else if (ngay1 == "30"){
					blankBox(5, 950, 120, 190);
					blankBox(820, 1180, 440, 680);
					textLine(850, 1180, 450, 3, "Nhap ngay ket thuc!");
					textLine(820, 1180, 550, 3, "Nhap cac thang 1-12");
					textLine(820, 1180, 585, 3, "Khong nhap thang 2");
				}
				
				textLine(850, 1180, 485, 3, "Thang: ");
				string thang1 = "";
				thang3Label:
				editText(950, 1050, 485, 520, true, 2, thang1);
				if(thang.length() == 0){
					blankBox(5, 950, 120, 190);
					blankBox(820, 1180, 440, 680);
					textLine(850, 1180, 450, 3, "Nhap ngay ket thuc!");
					textLine(850, 1180, 550, 3, "Khong duoc trong!");
					goto thang3Label;
				} else if(!isOnlyNumber(thang1)){
					blankBox(5, 950, 120, 190);
					blankBox(820, 1180, 440, 680);
					textLine(850, 1180, 450, 3, "Nhap ngay ket thuc!");
					textLine(850, 1180, 550, 3, "Nhap dung dinh dang!");
					goto thang3Label;
				} else if(thang1.length() == 1){
					thang1 = "0" + thang;
				} 
				if(!(thang1 >= "01" && thang1 <= "12")){
					blankBox(5, 950, 120, 190);
					blankBox(820, 1180, 440, 680);
					textLine(850, 1180, 450, 3, "Nhap ngay ket thuc!");
					textLine(850, 1180, 550, 3, "Nhap lai thang!");
					goto thang3Label;
				}
				if(ngay1 == "31" && (thang1 != "01"  && thang1 != "03" && thang1 != "05" && thang1 != "07" && thang1 != "08" && thang1 != "10" && thang1 != "12")){
					blankBox(5, 950, 120, 190);
					blankBox(820, 1180, 440, 680);
					textLine(850, 1180, 550, 3, "Nhap lai thang!");
					textLine(820, 1180, 585, 3, "Nhap cac thang: 1, 3, 5");
					textLine(820, 1180, 620, 3, "7, 8, 10, 12");
					goto thang3Label;	
				} else if (ngay1 == "30" && thang1 == "02"){
					blankBox(5, 950, 120, 190);
					blankBox(820, 1180, 440, 680);
					textLine(850, 1180, 550, 3, "Nhap lai thang!");
					textLine(820, 1180, 585, 3, "Nhap cac thang 1-12");
					textLine(820, 1180, 620, 3, "Khong nhap thang 2!");
					goto thang3Label;
				}
				blankBox(5, 950, 120, 190);
				blankBox(820, 1180, 440, 680);
				textLine(850, 1180, 450, 3, "Nhap ngay ket thuc!");
				textLine(850, 1180, 550, 3, "Nhap nam!");
				if(ngay1 == "29" && thang1 == "02"){
					blankBox(5, 950, 120, 190);
					blankBox(820, 1180, 440, 680);
					textLine(850, 1180, 450, 3, "Nhap ngay ket thuc!");
					textLine(850, 1180, 550, 3, "Nhap nam nhuan!");
				}
				textLine(850, 1180, 485, 3, "Nam: ");
				string nam1 = "";
				nam3Label:
				editText(950, 1100, 485, 520, true, 4, nam1);
				
				if(nam1.length() == 0){
					blankBox(5, 950, 120, 190);
					blankBox(820, 1180, 440, 680);
					textLine(850, 1180, 450, 3, "Nhap ngay ket thuc!");
					textLine(850, 1180, 550, 3, "Khong duoc trong");
					goto nam3Label;
				}else if(nam1.length() <= 3){
					blankBox(5, 950, 120, 190);
					blankBox(820, 1180, 440, 680);
					textLine(850, 1180, 450, 3, "Nhap ngay ket thuc!");
					textLine(820, 1180, 550, 3, "Nhap nam tu 1900-9999!");
					goto nam3Label;
				} else if(nam1 < "1900" || nam1 > "9999"){
					blankBox(5, 950, 120, 190);
					blankBox(820, 1180, 440, 680);
					textLine(850, 1180, 450, 3, "Nhap ngay ket thuc!");
					textLine(820, 1180, 550, 3, "Nhap nam tu 1900-9999!");
					goto nam3Label;
				}else if(!isOnlyNumber(nam1)){
					blankBox(5, 950, 120, 190);
					blankBox(820, 1180, 440, 680);
					textLine(850, 1180, 450, 3, "Nhap ngay ket thuc!");
					textLine(820, 1180, 550, 3, "Nhap dung dinh dang!");
					goto nam3Label;
				}
				
				if(ngay1 == "29" && thang1 == "02" && (!isLeapYear(nam1))){
					blankBox(5, 950, 120, 190);
					blankBox(820, 1180, 440, 680);
					textLine(850, 1180, 450, 3, "Nhap ngay bat dau!");
					textLine(820, 1180, 550, 3, "Nhap nam nhuan!");
					goto nam3Label;
				}
				
				Time from = Time((int)toInt(ngay), (int)toInt(thang), (int)toInt(nam));
				Time to = Time((int)toInt(ngay1), (int)toInt(thang1), (int)toInt(nam1));
				if(CompareTime(from, to) > 0){
					goto topLabel;
				} else {
					
					b.getBillInTime(from, to);
					blankBox(5, 950, 120, 190);
					textLine(100, 800, 130, 3, "Bang liet ke 10 vat tu cao nhat trong khoang thoi gian");
					string timeText = "tu ngay " + ngay + "/" + thang + "/" + nam + "  den ngay " + ngay1 + "/" + thang1 + "/" + nam1;
					textLine(100, 800, 165, 3, (char*)timeText.c_str());
					
					b.cntArr = 0;
					khoitao(b.t);
					
					for (int i = 0; i < b.indexBillInTime; ++i){
						if(b.billInTime[i].billType == 'X'){
							for(int j = 0; j < b.billInTime[i].cnt; ++j){
								materialNode *add = m.findMaterialCode(b.billInTime[i].billDetail[j].code);
								if(add == NULL){
									themNODE(b.t, b.billInTime[i].billDetail[j].code, b.billInTime[i].billDetail[j].total, NULL);
								
								} 
								themNODE(b.t, b.billInTime[i].billDetail[j].code, b.billInTime[i].billDetail[j].total, &add->data);
							}	
						}
						
					}
					
					textBox(1, 200, 200, 235, 15, 3, "ma vat tu");
					textBox(200, 500, 200, 235, 15, 3, "ten vat tu");
					textBox(500, 800, 200, 235, 15, 3, "thanh tien");
					
					int curPage = 1;
					
					string page = "Trang: "+ intToString(curPage);
					blankBox(320, 500, 635, 670);
					textLine(320, 490, 635, 3, toCString(page));
					
					Node** temp = new Node*[10];
					
					quickSortTotal(b.arr, 0, b.cntArr - 1, cmpT);
					
					for (int i = 0; i < 10; ++i){
						if(i + (curPage - 1) * 10 < b.cntArr){
							temp[i] = b.arr[i + (curPage - 1) * 10];	
						} 
					}
					
					for (int i = 0; i < 10; ++i){
						if(i + (curPage - 1) * 10  < b.cntArr){
							
							textBox(1, 200, 235 + i * 35, 270 + i * 35, 15, 3, (char*)temp[i]->code.c_str());
							textBox(200, 500, 235 + i * 35, 270 + i * 35, 15, 3, (char*)temp[i]->data->nameMaterial.c_str());
							textBox(500, 800, 235 + i * 35, 270 + i * 35, 15, 3, (char*)floatToString(temp[i]->total).c_str());
							
							
						}else {
							textBox(1, 200, 235 + i * 35, 270 + i * 35, 15, 3, "");
							textBox(200, 500, 235 + i * 35, 270 + i * 35, 15, 3, "");
							textBox(500, 800, 200, 235, 15, 3, "");
						}
						
					}
					while(1){
						delay(1);
						if(kbhit()){
							char key = getch();
							//if(key == 0) return;
						}
						int xx, yy;
						if (ismouseclick(WM_LBUTTONDOWN)){
							getmouseclick(WM_LBUTTONDOWN, xx, yy);
							if(xx >= 301 && xx <= 600 && yy >= 1 && yy <= 40){
								goto eTabLabel;
							
							} else if(xx >= 601 && xx <= 900 && yy >= 1 && yy <= 40){
								goto bTabLabel;
							
							} else if(xx >= 1 && xx <= 300 && yy >= 1 && yy <= 40){
								goto mTabLabel;
							
							} else if (xx >= 970 && xx <= 1120 && yy >=  120 && yy <= 155){
								goto mListLabel;
							} else if(xx >= 970 && xx <= 1170 && yy >= 185 && yy <= 220){
								goto eListLabel;
							} else if(xx >= 970 && xx <= 1140 && yy >= 250 && yy <= 285){
								goto bLabel;
							} else if(xx >= 970 && xx <= 1170 && yy >= 315 && yy <= 350){
								goto timeLabel;
							}
						}
					}
				}
				
				
				
				
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
	topBar(1);
	mManager m = mManager();
	eManager e = eManager();
	bManager b = bManager();
	mTab(m, e, b);
	
}
int main(int argc, char *argv[]){
	init();  
	while(!kbhit()) delay(1);   
    return 0;
}
