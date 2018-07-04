#ifndef TICKET_H
#define TICKET_H

#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include<string.h>
#include <fstream>
#include <ctime>

const int N = 20;
bool A = false, B = true;
time_t t = time(0);
tm * pt = localtime(&t);
static int g_num = -1;
void mainmenu();
struct Time
{
	int hour;
	int minute;
};

#endif
