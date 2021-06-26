#include <iostream>
#include <string>
#include <string.h>
#include <cstring>

using namespace std;
string firstCode = "MVT0000001";
char* toCString(string s){
	char *c_string;
	c_string = new char[s.length()];
	for (int i = 0; i < s.length(); ++i){
    	c_string[i] = s[i];
	}
	c_string[s.length()] = '\0';
	return c_string;
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
string nextGenM(string s){
	if(s == "MVT2000001"){
		return s;
	}
	for (int i = s.length() - 1; i >= 3; --i){
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
	if(s == "MNV501"){
		return s;
	}
	for (int i = s.length() - 1; i >= 3; --i){
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
	string s1 = "";
	string s2 = "";
	for (int i = 0; i < 7; ++i){
		s2 += s[i];
	}
	for (int i = 7; i < s.length(); ++i){
		s1 += s[i];
	}
	if(s1 == "9999999999999"){
		return s;
	}
	for (int i = s1.length() - 1; i >= 7; --i){
		if (s1[i] + 1 <= '9'){
			s1[i] += 1;
			break;
		} else{
			s1[i] = '0';
		}
	}
	return s2 + s1;
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
string onlyNumber(string s){
	string res = "";
	for (int i = 0; i < s.length(); ++i){
		if(s[i] >= '0' && s[i] <= '9'){
			res += s[i];
		}
	}
	return res;
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
	bool isNegative = false;
	if(num == 0){
		return 0;
	} else{
		if (num < 0){
			isNegative = true;
			num *= -1.0;
		}
	}
	long long INT = (long long)num;
	string intS = intToString(INT);
	float FLOAT = (float)num - (float)INT;
//	return FLOAT;
	string floatS = "";
	if(FLOAT != 0) floatS += '.';
	while(FLOAT != 0.0){
		FLOAT = FLOAT * 10.0;
		long long INT = (long long)FLOAT;
		double F = (float)INT;
		floatS += ('0' + INT);
		FLOAT = FLOAT - F;
	}
	return intS + floatS;
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
int main(){
	double f = 1123.9999;
	cout << nextGenB("MNV201-1111111111111");
	return 0;	
}
