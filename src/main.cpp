#include <iostream>
#include <string>
#include "conf.h"
#include "offer.h"
#include "cmp.h"
using namespace std;
offer o;
cmp companies[cmps];
int main(int argc, char *argv[])
{
	// this function has multiple roles. Initialization, and economy iteration
	o.add("test", 1,2,3);
	cout << o.get_ids(map<string,string>{pair<string, string> {"product","test"}}).at(0) << endl;
	o.print();
}

void init() {
	for(int i = 0;i < cmps; i++) {
		cmp temp;
		temp.id = i;
		temp.wealth = init_wealth;
		temp.salary = init_salary;
		temp.raw_materials = init_raw_materials;
		temp.previous_price = init_price;
		temp.price_multiplier = init_price_multiplier;
		temp.pmi = false;
		temp.greed_multiplier = 0; // <-- should be rand double value between conf.origin_greed_multiplier and conf.bound_greed_multiplier
		temp.product = ""; // <- should be a rand such that 'food' will be assigned by a chance of conf.food_cmp_percent
		for(int p = 0;p < emps_per_cmp;p++) {
			temp.emps[p].energy = init_energy;
			temp.emps[p].id = p;
			temp.emps[p].last_salary = init_salary;
			temp.emps[p].wealth = init_wealth;
			temp.emps[p].y = 0; // <-- rand double value between conf.origin_y and conf.bound_y
			temp.emps[p].fear = 0; // <-- rand double value between conf.origin_fear and conf.bound_fear
		}
		companies[i] = temp;
		delete(&temp);
	}
}