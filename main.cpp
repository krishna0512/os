#include "drivers/monitor.h"

int main () {

	video *v;
	v->init();
	v->setColor(COLOR_BLUE, COLOR_RED);
	v->clear();
	int n=23;
	v->write(n);
	v->write('\n');
	v->write("This is Krishna Tulsyan");
	v->write('\'');
	v->write((float)23.003202);
	v->write('\n');
	v->write(25);
	v->write('\n');
	char* s="is a good boy\n";
	v->write(s);
	float nn=23.003202;
	v->write(nn);			//not working properly.
	v->write('\n');
	v->write(23.003202);

	return 0;
}

