#include <string>
#include <string.h>

class Bill{
	string billNumber;	
	string dateBill;
	bool typeBill; //0: N, 1: X
	DetailBill *toDetailBill;
	Bill (string billNumber, string dateBill, bool typeBill) {
		this->billNumber = billNumber;
		this->dateBill = dateBill;
		this->typeBill = typeBill;
		toDetailBill = NULL;
	}
};

struct Time {
	int date, month, year;
	Time(){};
	Time(const int &date, const int &month, const int &year) {
		this->date = date;
		this->month = month;
		this->year = year;
	}
}

class billNode{
	Bill dataBill;
	BillNode *next;
};

class billDetail{
	string codeMaterial;
	int quantity;
	double price;
	double vat;
	double total;
	billDetail(){};
	billDetail(string codeMaterial, int quantity, double price, double vat) {
		this->codeMaterial = codeMaterial;
		this->quantity = quantity;
		this->price = price;
		this->vat = vat;
		total = ((quantity * price) * (100 + vat) / 100);
	}
	void operator = (const billDetail &b) {
		this->codeMaterial = b.codeMaterial;
		this->quantity = b.quantity;
		this->price = b.price;
		this->vat = b.vat;
		this->total = b.total;
	}
};

DetailBill listDetailBill[20];


