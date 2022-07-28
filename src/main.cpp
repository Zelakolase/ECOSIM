#include <iostream>
#include <string>
#include "conf.h"
#include "offer.h"
#include "cmp.h"
#include "operation.h"
#include "init.h"
#include <chrono>
using namespace std;
offer o;
cmp companies[cmps];
  typedef std::chrono::high_resolution_clock myclock;
  myclock::time_point beginning = myclock::now();
static default_random_engine gen = default_random_engine();
int main(int argc, char *argv[])
{
	init::initialize(companies, &gen);
	cout <<"inflation over time" << endl;
	for (int i = 0; i < iterations; i++)
	{
		for (int i = 0; i < cmps; i++)
		{
			operation::work(&companies[i], &o);
			gen.seed((myclock::now() - beginning).count());
		}
		for (int i = 0; i < cmps; i++)
		{
			operation::demand(&companies[i], &o, &gen);
			gen.seed((myclock::now() - beginning).count());
		}
		for (int i = 0; i < cmps; i++)
		{
			operation::revenue(&companies[i], &o, 0.0, &gen);
			gen.seed((myclock::now() - beginning).count());
		}
		o.clear();
		double average_Salary = 0;
		for(int a = 0;a < cmps; a++) {
			// if (companies[a].price_multiplier > 1.5) companies[a].price_multiplier -= 0.4;
			average_Salary += companies[i].salary;
		}
		average_Salary /= cmps;
		cout << average_Salary << endl;
	}
}