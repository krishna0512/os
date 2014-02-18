#ifndef _MONITOR_H
#define _MONITOR_H

#include "../utils/string.h"
#include "../system.cpp"


//these are the character values of colors.
#define COLOR_BLACK			0
#define COLOR_BLUE			1
#define COLOR_GREEN			2
#define COLOR_CYAN			3
#define COLOR_RED			4
#define COLOR_MAGNETA			5
#define COLOR_BROWN			6
#define COLOR_LIGHT_GRAY	 	7
#define COLOR_DARK_GRAY 		8
#define COLOR_LIGHT_BLUE	 	9
#define COLOR_LIGHT_GREEN 		10
#define COLOR_LIGHT_CYAN 		11
#define COLOR_LIGHT_RED 		12
#define COLOR_LIGHT_MAGNETA		13
#define COLOR_LIGHT_BROWN 		14
#define COLOR_WHITE			15

class video
{
	public:
		video (void);									//contructor to init
		~video (void);									//destructor to destroy
		void init(void);								//temporary func to be used till def of new.
		void clear (void);								//clears the screen
		void putc (char character, int x, int y);		//to print the char @ specific position.
		void write (char* string);						//prints a null terminated string.
		void write (int n);								//to print the decimal number.
		void write (char c);							//to print a character to screen.
		void write (float n);							//to print the floating number.
		void write (double n);
		void setCursorPosition (int xx, int yy);		//changes the postition of the cursor
		void setColor (char background, char foreground);

	private:
		int cursor_x,cursor_y;				//to store the postition of cursor.
		char fore_color, back_color;		//to store the background and foreground colors.
		unsigned short *vid;				//video memory for output
		unsigned short attribute (char character, char background, char foreground);
		void putc (char character);			//library function to prints a single character
		void updateCursor (void);			//this quickly sets the cursor position to cursorx, cursory.
		void scroll(void);					//this function does all the nessacary scrolling.
};

#endif		//monitor_h ends.
