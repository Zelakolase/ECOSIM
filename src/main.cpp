#include <iostream>
#include <string>
#include "conf.h"
#include "offer.h"
#include "cmp.h"
#include "operation.h"
#include "init.h"
using namespace std;
offer o;
cmp companies[cmps];
int main(int argc, char *argv[])
{
	// this function has multiple roles. Initialization, and economy iteration
	init::initialize(companies);
	for(int i = 0;i < cmps;i++) {
		operation::work(&companies[i], &o);
	}
	o.print();
}