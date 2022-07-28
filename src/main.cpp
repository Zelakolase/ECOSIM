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
			operation::demand(&companies[i], &o, &gen);
		}
		for (int i = 0; i < cmps; i++)
		{
			operation::revenue(&companies[i], &o, 0.0, &gen);
		}
		o.clear();
		double average_Salary = 0;
		for(int a = 0;a < cmps; a++) {
			for(int b = 0;b < emps_per_cmp;b++) average_Salary = average_Salary + companies[a].emps[b].last_salary;
		}
		average_Salary = average_Salary / (cmps * emps_per_cmp);
		cout << average_Salary << endl;
	}
}