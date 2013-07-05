/*
	this file contains all the general purpose functions which
	are needed all over the kernel and do not have a fixed location.
*/

#ifndef _SYSTEM_CPP
#define _SYSTEM_CPP

__inline__ void outportb (unsigned short port, unsigned char data);
/*
	i dont know why, when i seperate these declarations and implementations
	in seperate header and cpp files and include just the header file i get
	a linker error i guess it is because this function is a inline function
	and moreover it is primarly written in C rather C++.
*/
__inline__ void outportb (unsigned short port, unsigned char data) 
{
	__asm__ __volatile__ ("outb %1, %0"
	:
	: "dN" (port),
	"a" (data));
}

#endif
