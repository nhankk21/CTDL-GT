#include <string>
#include <string.h>

class Employee{
	private:
		string codeEmp;
		string lastName;
		string firstName;
		string middleName;
		bool sex;// 0: male, 1: female
		Bill *toBill;	
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
