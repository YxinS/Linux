#include<iostream>
int _IsDuan(){
struct Is{
	int a;
	char b;
}s;
s.a=1;
return s.b;
}

int main(){
	int num = _IsDuan();
	if(num == 1){
		std::cout << "xiaoduan" << std::endl;
	}
	else{
		std::cout << "daduan" << std::endl;
	}
	return 0;
}
