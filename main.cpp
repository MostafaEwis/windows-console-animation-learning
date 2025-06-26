#include <iostream> 
#include <conio.h>
#include <windows.h> 
#include <typeinfo>

using namespace std;


int main(int argc, char** argv){
	int max = 10000;
	int iterations = 10;
	int step = max / iterations;
	short int x = 0;
	short int y = 0;
	char in = '8';
	bool exit = false;
	while(!exit){
		HANDLE ewis = GetStdHandle(STD_OUTPUT_HANDLE);
		//SetConsoleCursorPosition(ewis, {10, 10});
		//for(int j = 0; j < i / step; j++){
		//	cout << '-';
		//}
		//for(int j = 0; j < iterations - i / step; j++){
		//	cout << '.';
		//}
		//cout <<' ' << i / step << '/' << iterations << endl; 
		in = getch();	
		if(in == 'j'){
			y++;
		}else if(in == 'k'){
			if(y > 0) y--;
		}else if(in == 'h'){
			if(x > 0) x--;
		}else if(in == 'l'){
			x++;
		}else if(in == 'c'){
			exit = true;
		}
		SetConsoleCursorPosition(ewis, {x, y});
		//cout << i <<  endl;
	}
	return 0;
}
