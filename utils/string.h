#ifndef _STRING_H
#define _STRING_H


class string
{
	public:
		string (void);
		string (char* s);
		~string (void);
		char charAt(int n);

		int length;

	private:
		char* str;
};



#endif
