#ifndef Included_NameModel_H
#define Included_NameModel_H

#include <string>
#include <string.h>

using namespace std;

struct Time{
	int date, month, year;
	Time(){};
	Time(int date, int month, int year) {
		this->date = date;
		this->month = month;
		this->year = year;
	}

	void operator = (Time t) {
		this->date = t.date;
		this->month = t.month;
		this->year = t.year;
	}
};

int CompareTime(Time a, Time b) {
	if (a.year != b.year) {
		if (a.year > b.year) return 1;
		else return -1;
	}
	else {
		if (a.month != b.month) {
			if (a.month > b.month) return 1;
			else return -1;
		}
		else {
			if (a.date != b.date) {
				if (a.date > b.date) return 1;
				else return -1;
			}
			else return 0;
		}
	}
}

class BillDetail{
	public:
	string code; // material code
	float quantity;
	float price;
	float vat;
	
	float total = 0; // Tong gia tri cua bill
	BillDetail(){};
	BillDetail(string code, float quantity, float price, float vat) {
		this->code = code;
		this->quantity = quantity;
		this->price = price;
		this->vat = vat;
		this->total = ((quantity * price) * (100.0 + vat) / 100.0);
	}
//	void operator = (BillDetail &b) {
//		this->code = b.code;
//		this->quantity = b.quantity;
//		this->price = b.price;
//		this->vat = b.vat;
//		this->total = b.total;
//	}
};

const int MAX_MATERIALS_PER_BILL = 20; // Toi da 20 vat tu tren 1 hoa don



struct Bill {
	string empCode; // Ma nv lap hoa don
	string code; // So hoa don
	Time time; // Ngay lap hoa don
	char billType; // Loai
	int cnt; 
	BillDetail* billDetail; // Con tro cthd
	public: int findBillDetail(string mavt) {
		for (int i = 0; i < cnt; i++) {
			if (billDetail[i].code == mavt) return i;
		}
		return -1;
	}
	
	float total;
	Bill() {
		cnt = 0;
		billDetail = new BillDetail[MAX_MATERIALS_PER_BILL];
		for(int i = 0; i < MAX_MATERIALS_PER_BILL; ++i){
			billDetail[i] = BillDetail();
		}
		total = 0;
	}
	
	Bill(string mahd, string manv, Time time, char loai) {
		empCode = mahd;
		code = manv;
		this->time = time;
		billType = loai;
	}
	
	~Bill() {
		delete billDetail;
	}
	
	public: void deleteBillDetail(int index) {
		
		this->total -= billDetail[index].total;
		for (int i = index; i < cnt - 1; i++) {
			billDetail[i] = billDetail[i+1];
		}
		--cnt;
	}
	
	public: void addBillDetail(string code, float quantity, float price, float vat) {
		billDetail[cnt] = BillDetail(code, quantity, price, vat);
		this->total += billDetail[cnt].total;
		cnt++;
	}
	
	public: void resetBill() {
		this->total = 0;
		this->cnt = 0;
	}
//	public: void operator = (Bill &b) {	
//		this->empCode = b.empCode;
//		this->code = b.code;
//		this->time = b.time;
//		this->billType = b.billType;
//		
//		this->cnt = b.cnt;
//		*billDetail = *(b.billDetail);
//	}
}; 


class BillNode {
	public:
	Bill dataBill;
	BillNode *next;
};

BillNode* insertBill(BillNode* &list, const Bill& bill) { 
	BillNode *tmp = new BillNode;
	tmp->next = NULL;
	tmp->dataBill.time = bill.time;
	tmp->dataBill.total = bill.total;
	tmp->dataBill.billType = bill.billType;
	tmp->dataBill.code = bill.code;
	
	// tmp->dataBill.billDetail = new BillDetail;
	*tmp->dataBill.billDetail = *(bill.billDetail);
	
	if (list == NULL) {
		list = tmp;
	}
	else {
		BillNode* p = list;
		while (p->next != NULL)
			p = p->next;
		p->next = tmp;
		
	}
	return list;
	
}

BillNode* findBill(BillNode* list, string billCode) {
	while (list != NULL && list->dataBill.code != billCode)
		list = list->next;
	return list; // Neu khong tim duoc thi list tra ve NULL	
}
#endif // Included_NameModel_H
