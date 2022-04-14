#include <string>
#include <string.h>
#include "Bill.h"
// Khai bao tiep cau truc Employee trong ham main

class Employee{
	public:
	string codeEmp;
	string lastName;
	string firstName;
	string sex;
	BillNode *billList;
	
	Employee() {}
	~Employee() {
		for (BillNode *k = billList; k != NULL; k = k->next)
			delete k;
	}
	
	void operator = (const Employee &emp) {
		this->codeEmp = emp.codeEmp;
		this->lastName = emp.lastName;
		this->firstName = emp.firstName;
		this->sex = emp.sex;
		*billList = *(emp.billList);
	}
	
	Employee(string codeEmp, string lastName, string firstName, string sex) {
		// Tao 1 employee moi
		this->codeEmp = codeEmp;
		this->lastName = lastName;
		this->firstName = firstName;
		this->sex = sex;
		billList = NULL;
	}
	void edit(string lastName, string firstName, string sex) {
		this->lastName = lastName;
		this->firstName = firstName;
		this->sex = sex;
	}	
};

bool cmpE(Employee* a, Employee* b){
	if(a->firstName < b->firstName){
		return true;
	} else if(a->firstName > b->firstName){
		return false;
	} else {
		if(a->lastName < b->lastName) {
			return true;
		} else return false;
	}
}

void quickSortEmployee(Employee* emp[], int l , int r, bool(*compare)(Employee*, Employee*)) {	
	if (l <= r) {
		Employee* key = emp[(l+r)/2];
		int i = l;
		int j = r;
		while (i <= j) {
			while (compare(emp[i], key))
				i++;
			while (compare(key, emp[j]))
				j--;
 
			if (i <= j) {
				swap(emp[i], emp[j]);
				i++;
				j--;
			}
		}
		if (l < j)
			quickSortEmployee(emp, l, j, cmpE);
		if (r > i)
			quickSortEmployee(emp, i, r, cmpE);
	}
}
