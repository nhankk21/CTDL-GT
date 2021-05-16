#include<iostream>
#include<string>
#include<sstream>
using namespace std;

/// Chuan hoa ten
void nameStandardized(string &name) {
	while (name[0] == ' ') name.erase(name.begin()); /// Xoa space dau
	while (name[name.size() - 1] == ' ') name.pop_back(); /// Xoa space cuoi
	
	for (int i = 0; i < name.size() - 1; ++i) { 
	if (name[i] >= 65 && name[i] <= 90) name[i] += 32; /// Viet thuong het
	else if (name[i] == ' ' && name[i + 1] == ' ') name.erase(name.begin() + i, 1);
	}
	if (name[0] >= 97 && name[0] <= 122) name[0] -= 32; // In hoa ky tu dau tien
	for (int i = 1; i < name.size(); ++i) {
		if (name[i] == ' ' && name[i + 1] >= 97 && name[i + 1] <= 122) name[i + 1] -= 32; /// Viet hoa sau space
	}	
}

void codeStandardized(string &code) {
	
}

int main() {
	
}
