#ifndef INIT_H
#define INIT_H
#include "conf.h"
#include "cmp.h"
#include <random>
class init
{
private:
public:
	static void initialize(cmp *companies, default_random_engine *gen)
	{
		uniform_real_distribution<double> greed_rand(origin_greed_multiplier, bound_greed_multiplier);
		uniform_real_distribution<double> food_rand(0.0, 1.0);
		uniform_real_distribution<double> y_rand(origin_y, bound_y);
		uniform_real_distribution<double> fear_rand(origin_fear, bound_fear);
		for (int i = 0; i < cmps; i++)
		{
			cmp temp;
			temp.id = i;
			temp.wealth = init_wealth;
			temp.salary = init_salary;
			temp.raw_materials = init_raw_materials;
			temp.previous_price = init_price;
			temp.price_multiplier = init_price_multiplier;
			temp.pmi = false;
			temp.greed_multiplier = greed_rand((*gen));										  // <-- should be rand double value between conf.origin_greed_multiplier and conf.bound_greed_multiplier
			temp.product = food_rand((*gen)) < food_cmp_percent ? "food" : luxury_product_name; // <- should be a rand such that 'food' will be assigned by a chance of conf.food_cmp_percent
			for (int p = 0; p < emps_per_cmp; p++)
			{
				temp.emps[p].energy = init_energy;
				temp.emps[p].id = p;
				temp.emps[p].last_salary = init_salary;
				temp.emps[p].wealth = init_wealth;
				temp.emps[p].y = y_rand((*gen));		 // <-- rand double value between conf.origin_y and conf.bound_y
				temp.emps[p].fear = fear_rand((*gen)); // <-- rand double value between conf.origin_fear and conf.bound_fear
			}
			companies[i] = temp;
		}
	}
};

#endif