#include "monitor.h"


video::video(void)
{
	vid=(unsigned short*) 0xb8000;
	cursor_x=cursor_y=0;
	back_color=COLOR_BLACK;		//initial values of the color
	fore_color=COLOR_WHITE;
}

video::~video(void)
{
	vid=0x00;
	cursor_x=cursor_y=0;
}

void video::init (void) {
	vid=(unsigned short*) 0xb8000;
	cursor_x=cursor_y=0;
	back_color=COLOR_BLACK;		//initial values of the color
	fore_color=COLOR_WHITE;
}

void video::clear (void)
{
	for (int i=0;i<80*25;i++)
	{
		//returns a blank with desired background.
		vid[i]=attribute(' ',back_color,fore_color);
	}
	cursor_x=cursor_y=0;
	updateCursor();		//sets the cursor position to 0,0
}

void video::putc (char c)
{
	int pos=cursor_x+(cursor_y*80);

	//handler for various special characters.
	switch(c)
	{
		case '\n':
			cursor_x=0;
			cursor_y++;
			break;
		default:
			vid[pos]=attribute(c,back_color,fore_color);
			//we need to increase the cursor as scroll doesnt do that.
			cursor_x++;
			break;
	}
	//this will handle the scrolling of the screen.
	scroll();
}

void video::putc (char c, int x, int y)
{
	vid[x+(y*80)]=attribute(c,back_color,fore_color);

	//please notice that this function doesnot call the scroll function hence doesnt affect cursor position.
	//i designed it this way bcoz if it will affect the cursor position then it will be a mess tracking it.
}

void video::write (char* s)
{
	int i=0;
	while (s[i])
	{
		putc(s[i++]);
	}
}

void video::write (int n)
{
	//first we have to check for zero at the end of number.
	int b=n;
	//counting the number of zeros.
	int c=0;
	while (b%10==0)
	{
		c++;
		b/=10;
	}
	int a=0;
	char* temp="0123456789";
	//reversing the number and extracting each of its digit.
	while (n>0)
	{
		int x=n%10;
		a=(a*10)+x;
		n/=10;
	}
	//reversed number stored in a
	while (a>0)
	{
		putc(temp[a%10]);
		a/=10;
	}
	//printing out the zeros.
	while (c!=0)
	{
		putc('0');
		c--;
	}
}

void video::write(char c) {
	putc(c);
}

void video::write (float nn) {
/*
 * There is a bug in this code function that if the call is made like
 * write((foat)23.003202);
 * it gives the output as 23.0032024563
 * while the double function below works perfectly fine...
 */
	float decimal=nn-(int)nn;
	write((int)nn);
	if (decimal == 0) return;

	putc('.');
	decimal*=10;
	// first print out all the zeros after decimal point.
	while (!(int)decimal) {
		write('0');
		decimal*=10;
	}
	while ((float)((float)decimal-(float)((int)decimal)) >0.0005) decimal*=10;
	write((int)decimal);
}

void video::write (double nn) {
	double decimal=nn-(int)nn;
	write((int)nn);
	if (decimal == 0) return;

	putc('.');
	decimal*=10;
	// first print out all the zeros after decimal point.
	while (!(int)decimal) {
		write('0');
		decimal*=10;
	}
	while ((double)((double)decimal-(double)((int)decimal)) >0.0005) decimal*=10;
	write((int)decimal);
}

void video::setCursorPosition (int xx,int yy) 
{
	cursor_x=xx;
	cursor_y=yy;
	short position=(short)((yy*80) + xx);
	// cursor LOW port to vga INDEX register
	outportb(0x3D4, 0x0F);
	outportb(0x3D5, (char)(position&0xFF));
	// cursor HIGH port to vga INDEX register
	outportb(0x3D4, 0x0E);
	outportb(0x3D5, (char)((position>>8)&0xFF));
}

void video::setColor(char b, char f)
{
	back_color=b;
	fore_color=f;
}

unsigned short video::attribute (char c, char b, char f)
{
	char attributeByte = (b << 4) | (f & 0x0F);
	return (short)(c | (attributeByte << 8));
}

void video::updateCursor (void)
{
	setCursorPosition(cursor_x,cursor_y);
}

void video::scroll (void)
{
	if (cursor_x>=80)
	{
		//we have reached end of the line now move
		//to the next line.
		cursor_y++;
		cursor_x=0;
	}
	if (cursor_y>=25)
	{
		//we have reached the end of the page
		//move all the chunk of data up by one line.
		for (int i=0*80;i<24*80;i++)
			vid[i]=vid[i+80];
		for (int i=24*80;i<25*80;i++)
			vid[i]=attribute(' ',back_color,fore_color);
		cursor_y=24;
	}
	updateCursor();
}






