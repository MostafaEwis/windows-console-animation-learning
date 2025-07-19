#include <iostream> 
#include <conio.h>
#include <windows.h> 
#include <chrono>
#include <thread>
#include <typeinfo>
#include <cmath>

#define G_R 0.6180339887
using namespace std;

void drawBall(SHORT x,SHORT y, int radius){
	short int cx, cy = 0;
	HANDLE circleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	system("cls");
	float M_PI2 = 2 * M_PI;
	float step = 0.01;
		for(float rad = step; rad < M_PI2; rad += step){
			cx = (short int)((cos(rad) * radius + x));
			cy = (short int)((sin(rad) * radius + y) * G_R);
			SetConsoleCursorPosition(circleHandle, {cx, cy});
			cout << '.';
		}

	SetConsoleCursorPosition(circleHandle, {0, 0});

}
void drawCircle(SHORT x,SHORT y, int radius){
	short int cx, cy = 0;
	HANDLE circleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	system("cls");
	for(int d = radius; d >= 0; d--){
		float halfChordLen = sqrt(pow(radius, 2) - pow(d, 2));
		halfChordLen *= 1.3 / G_R;
		cy = d + 10;
		cx = x - halfChordLen;
		SetConsoleCursorPosition(circleHandle, {cx, cy});
		for(int i = 0; i < halfChordLen; i++){
			cout << '.';
		}

		cx = x;
		SetConsoleCursorPosition(circleHandle, {cx, cy});
		for(int i = 0; i < halfChordLen; i++){
			cout << '.';
		}
	}
	for(int d = -radius; d < 0; d++){
		float halfChordLen = sqrt(pow(radius, 2) - pow(d, 2));
		halfChordLen *= 1.3 / G_R;
		cy = d + 10;
		cx = x - halfChordLen;
		SetConsoleCursorPosition(circleHandle, {cx, cy});
		for(int i = 0; i < halfChordLen; i++){
			cout << '.';
		}

		cx = x;
		SetConsoleCursorPosition(circleHandle, {cx, cy});
		for(int i = 0; i < halfChordLen; i++){
			cout << '.';
		}
	}
}
HWND GetConsoleHwnd(){
       #define MY_BUFSIZE 1024 // Buffer size for console window titles.
       HWND hwndFound;         // This is what is returned to the caller.
       char pszNewWindowTitle[MY_BUFSIZE]; // Contains fabricated
                                           // WindowTitle.
       char pszOldWindowTitle[MY_BUFSIZE]; // Contains original
                                           // WindowTitle.

       // Fetch current window title.

       GetConsoleTitle(pszOldWindowTitle, MY_BUFSIZE);

       // Format a "unique" NewWindowTitle.

       wsprintf(pszNewWindowTitle,"%d/%d",
                   GetTickCount(),
                   GetCurrentProcessId());

       // Change current window title.

       SetConsoleTitle(pszNewWindowTitle);

       // Ensure window title has been updated.

       Sleep(40);

       // Look for NewWindowTitle.

       hwndFound=FindWindow(NULL, pszNewWindowTitle);

       // Restore original window title.

       SetConsoleTitle(pszOldWindowTitle);

       return(hwndFound);
   }
void magicBall(SHORT x, SHORT y, int radius){
	RECT wr;
	HWND hwnd = GetConsoleHwnd();
	GetWindowRect(hwnd, &wr);
	float dx = 0;
	float dy = 0;
	drawCircle(x, y, radius);
	bool exit = false;
	char exitChar = ' ';
	LONG currRight = wr.right;
	LONG prevRight = wr.right;
	LONG currTop = wr.top;
	LONG prevTop = wr.top;
	while(true){
		//dy and dx should be floats and should only take effect when the increment is more than the bounds
		//dy % 12 is the bound and dx % (G_R * 12) is the other bound after that it should be reset
		GetWindowRect(hwnd, &wr);
		currRight = wr.right;
		currTop = wr.top;
		dx += currRight - prevRight;
		dy += currTop - prevTop;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {0, 0});
		cout << dx << ", " << dy << endl;
		cout << x << ", " << y << endl;
		cout << wr.right << ", " << wr.top << endl;
		if(abs(dx) > 6 || abs(dy) > 6){
		cout << (float)dx / 80 << ", " << (float)dy / 100 << endl;
			x -= (float)dx / 6;
			y -= (float)dy/ 6;
			drawCircle(x, y, radius);
			if(abs(dx) > 6) dx = 0;
			if(abs(dy) > 6) dy = 0;
		}

		prevRight = currRight;
		prevTop = currTop;
	}
}

int main(int argc, char** argv){
	magicBall(50, 50 * G_R, 5);
	//drawCircle(50, 50, 10);
	return 0;
}
