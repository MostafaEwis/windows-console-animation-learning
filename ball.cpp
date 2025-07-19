#include <iostream> 
#include <conio.h>
#include <windows.h> 
#include <chrono>
#include <thread>
#include <typeinfo>
#include <cmath>

#define G_R 0.6180339887f
#define PTP 141.2119980822f / 72.f
#define CODE '.'
#define FS 12

using namespace std;

void drawCircle(SHORT x,SHORT y, int radius){
	short int cx, cy = 0;
	HANDLE circleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	system("cls");
	for(int d = radius; d > 0; d--){
		float halfChordLen = sqrt(pow(radius, 2) - pow(d, 2));
		//the line height in my terminal is 1.3 that's why I'm using it instead of 1
		halfChordLen *= 1.2 / G_R;
		cy = d + y;
		cx = x - halfChordLen;
		SetConsoleCursorPosition(circleHandle, {cx, cy});
		for(int i = 0; i < halfChordLen; i++){
			cout << CODE;
		}

		cx = x;
		SetConsoleCursorPosition(circleHandle, {cx, cy});
		for(int i = 0; i < halfChordLen; i++){
			cout << CODE;
		}
	}
	for(int d = -radius; d <= 0; d++){
		float halfChordLen = sqrt(pow(radius, 2) - pow(d, 2));
		halfChordLen *= 1.2 / G_R;
		cy = d + y;
		cx = x - halfChordLen;
		SetConsoleCursorPosition(circleHandle, {cx, cy});
		for(int i = 0; i < halfChordLen; i++){
			cout << CODE;
		}

		cx = x;
		SetConsoleCursorPosition(circleHandle, {cx, cy});
		for(int i = 0; i < halfChordLen; i++){
			cout << CODE;
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
void magicBall(float x, float y, int radius, bool opt = true){
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
	float oldX = x;
	float oldY = y;
	bool redraw = false;
	while(true){
		GetWindowRect(hwnd, &wr);
		currRight = wr.right;
		currTop = wr.top;
		dx += currRight - prevRight;
		dy += currTop - prevTop;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {0, 0});
		cout << dx << ", " << dy << endl;
		cout << x << ", " << y << endl;
		cout << wr.right << ", " << wr.top << endl;
		cout << (float)dy / (PTP * FS) << ", " << (float)dx / (PTP * FS * G_R) << endl;
		if(abs(dx) > (PTP * FS * G_R)){
			x -= dx / (PTP * FS * G_R);
			dx = 0;
			redraw = true;
		}
		if(abs(dy) > (PTP * FS)){
			y -= dy / (PTP * FS);
			dy = 0;
			redraw = true;
		}
		if(redraw || !opt){
			drawCircle(x, y, radius);
			redraw = false;
		}

		prevRight = currRight;
		prevTop = currTop;
	}
}

int main(int argc, char** argv){
	//to hide the cursor
	cout << "\e[?25l";
	magicBall(40, 20, 5);
	return 0;
}
