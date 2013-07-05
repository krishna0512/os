#ifndef _STRING_CPP
#define _STRING_CPP

#include "string.h"

string::string(void)
{
	str="";
	length=0;
}

string::~string (void)
{
	str="";
	length=0;
}

string::string (char* s)
{
	str=s;
	for (int i=0;s[i]!='\0';i++) length++;
}

char::string::charAt (int i)
{
	if (i>=0&&i<length)
	{
		return str[i];
	}
	else
	{
		return '\0';
	}
}


#endif
