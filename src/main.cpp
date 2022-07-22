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
static default_random_engine gen = default_random_engine();
int main(int argc, char *argv[])
{
	init::initialize(companies, &gen);
	for (int i = 0; i < iterations; i++)
	{
		for (int i = 0; i < cmps; i++)
		{
			operation::work(&companies[i], &o);
		}
		for (int i = 0; i < cmps; i++)
		{
			operation::demand(&companies[i], &o);
		}
		for (int i = 0; i < cmps; i++)
		{
			operation::revenue(&companies[i], &o);
		}
	}
}