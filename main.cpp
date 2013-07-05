#include "drivers/monitor.h"
#include "utils/string.h"

int main () {

video v;

v.setColor(COLOR_BLUE, COLOR_RED);
v.clear();
string s="krishna";
v.write(s);
v.putc('\n');
v.write("cool text!");

return 0;
}

