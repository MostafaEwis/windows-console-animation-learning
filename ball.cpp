#include <iostream> 
#include <conio.h>
#include <windows.h> 
#include <chrono>
#include <thread>
#include <typeinfo>
#include <cmath>

//the ratio between the width and height of the character is the golden ratio
#define GR 0.6180339887f
//the ratio between pixel density and point density
#define PTP 141.2119980822f / 72.f
//the character to draw
#define CODE '.' 
//the font size of the character, this is how many pixels the character height is
#define FS 12
//line height
#define LH 1.2
//since I'm using a 125% scaling in my laptop a pixel is not a pixel, it's 1.25 pixels making PPI less by a factor of 1.25
#define SCALE 1.25


using namespace std;

void drawCircle(const SHORT &x,const SHORT &y, int radius, const int &maxX,const  int &maxY){
	HANDLE circleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	system("cls");
	for(int d = radius; d >= -radius ; d--){
		float halfChordLen = sqrt(pow(radius, 2) - pow(d, 2));
		//the circle height looks taller than width and that's is due to the asymtery in the pixels of the terminal, I can compensate by making lengthing the width
		//the line height in my terminal is 1.2 that's why I'm using it instead of 1
		halfChordLen *= LH / GR;
		if( y + d < 0 || y + d >= maxY){
			continue;
		}
		for(SHORT i = x - halfChordLen; i < x + halfChordLen; i++){
			if(i < 0 || i >= maxX){
				continue;
			}
			SetConsoleCursorPosition(circleHandle, {i, (SHORT)(y + d)});
			cout << CODE;
		}
	}
}
//this function is from Microsoft docs, I have not written it 
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
void magicBall(int x, int y, int radius, bool opt = true){
	//to hide the cursor
	cout << "\e[?25l";
	RECT wr;
	HWND hwnd = GetConsoleHwnd();
	CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
	GetWindowRect(hwnd, &wr);
	LONG currLeft = wr.left;
	LONG prevLeft = wr.left;
	LONG currTop = wr.top;
	LONG prevTop = wr.top;
	float dx = 0;
	float dy = 0;

	float errorX = 0;
	float errorY = 0;

	float boundX = PTP * FS * GR / SCALE / SCALE;
	float boundY = PTP * FS / SCALE / SCALE;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &consoleInfo);
	//intialize the circle in the middle
	int maxX = consoleInfo.dwSize.X;
	int maxY = consoleInfo.dwSize.Y;
	x = maxX / 2;
	y = maxY / 2;
	drawCircle(x, y, radius, 2 * x, 2 * y);
	bool redraw = false;
	//I wanted to use getch() and exit on getting c, but I need a live loop and don't know how to use the input buffer without waiting and inturpteing the program.
	while(true){
		GetWindowRect(hwnd, &wr);
		currLeft = wr.left;
		currTop = wr.top;
		GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &consoleInfo);
		maxX = consoleInfo.dwSize.X;
		maxY = consoleInfo.dwSize.Y;
		dx += currLeft - prevLeft;
		dy += currTop - prevTop;
		//update the x, y of the circle only of the changes accounts for one or more pixels of the terminal
		if(abs(dx) > boundX){
			float intPart = 0;
			errorX += modff(dx / boundX, &intPart);
			x -= intPart;
			dx = 0;
			redraw = true;
		}
		if(abs(dy) > boundY){
			float intPart = 0;
			errorY += modff(dy / boundY, &intPart);
			y -= intPart;
			dy = 0;
			redraw = true;
		}
		if(errorX >= 1){
			errorX--;
			x--;
			redraw = true;
		}else if(errorX <= -1){
			errorX++;
			x++;
			redraw = true;
		}
		//cooler but bad is to use the bool value of abs(errorY) >= 1 and subtract it from errorY and y
		if(errorY >= 1){
			errorY--;
			y--;
			redraw = true;
		}else if(errorY <= -1){
			errorY++;
			y++;
			redraw = true;
		}
		if(redraw || !opt){
			drawCircle(x, y, radius, maxX, maxY);
			redraw = false;
		}

		prevLeft = currLeft;
		prevTop = currTop;
	}
}

int main(int argc, char** argv){
	magicBall(60, 20, 5);
	return 0;
}
