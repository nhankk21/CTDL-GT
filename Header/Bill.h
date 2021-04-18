#include <string>
#include <string.h>

class Bill{
	char billNumber[21];	
	string dateBill;
	bool typeBill; //0: N, 1: X
	DetailBill *toDetailBill;
};

class listBill{
	Bill data;
	listBill *next;
};

class DetailBill{
	char codeMaterial[11];
	int quantity;
	double price;
	double vat;
};

DetailBill listDetailBill[20];


