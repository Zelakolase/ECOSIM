#include <iostream>
#include <string>
#include "conf.h"
#include "offer.h"
#include <utility>
#include <map>
using namespace std;
int main(int argc, char *argv[])
{
	// this function has multiple roles. Initialization, and economy iteration
	offer o;
	o.add("test", 5, 5, 4);
	cout << o.get_ids(map<string, string> {pair<string, string> {"product", "test"}}).data() << endl;
}