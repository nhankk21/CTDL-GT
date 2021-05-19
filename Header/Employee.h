#include <string>
#include <string.h>

class Employee{
	public:
	string codeEmp;
	string lastName;
	string firstName;
	string middleName;
	bool sex;// 0: male, 1: female
	Bill *toBill;
	
	Employee(string codeEmp, string lastName, string middleName, string firstName, bool sex) {
		// Tao 1 employee moi
		this->codeEmp = codeEmp;
		this->lastName = lastName;
		this->middleName = middleName;
		this->firstName = firstName;
		this->sex = sex;
		toBill = NULL;
	}
	void update(string lastName, string middleName, string firstName, bool sex) {
		this->lastName = lastName;
		this->middleName = middleName;
		this->firstName = firstName;
		this->sex = sex;
	}	
};

class listEmployee{
	int n = 0;
	Employee *employee[500];
	void insert(Employee emp){
		employee[n] = emp;
		++n;
	}
	void searchByFirstName(string firstName){
		for (int i = 0; i < n; ++i){
			if (firstName == employee[i].firstName){
				//
			}
		}
	}
	void searchByLastName(string lastName){
		for (int i = 0; i < n; ++i){
			if (lastName == employee[i].lastName){
				//
			}
		}
	}
};
