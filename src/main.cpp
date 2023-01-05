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
typedef std::chrono::high_resolution_clock myclock;
myclock::time_point beginning = myclock::now();
static default_random_engine gen = default_random_engine();
int main(int argc, char *argv[])
{
	cmp companies[cmps * 100];
	init::initialize(companies, &gen);
	cout << "AvgSalary, AvgPM" << endl;
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
		double AvgPriceMultiplier = 0;
		for (int a = 0; a < cmps; a++)
		{
			AvgPriceMultiplier += companies[a].price_multiplier;
			companies[a].wealth += 1000;
			for (int b = 0; b < emps_per_cmp; b++)
			{
				average_Salary += companies[a].emps[b].last_salary;
				companies[a].emps[b].wealth += 1000;
			}
		}
		average_Salary /= (cmps*emps_per_cmp);
		AvgPriceMultiplier /= cmps;
		cout << average_Salary << "," << AvgPriceMultiplier << endl;
	}
}