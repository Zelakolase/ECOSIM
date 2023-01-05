#ifndef CONF_H
#define CONF_H
/*
Basic initalization values for the model
*/
#include <string>
using namespace std;
const int cmps = 100; // num of cmps
const double init_salary = 10; // starting salary for all cmps
const int emps_per_cmp = 10; // num of employees per cmp
const double init_wealth = (emps_per_cmp * init_salary) * 12; // starting wealth for cmps, emps
const double init_price_multiplier = 1; // starting price multiplier for all cmps
const double origin_greed_multiplier = 0.0;
const double bound_greed_multiplier = 0.01;
const double origin_y = 0.0;
const double bound_y = 0.2;
const double origin_fear = 0.0;
const double bound_fear = 0.3;
const string luxury_product_name = "jewelry"; // luxury product name
const double init_energy = 5; // starting energy level for emps
const int iterations = 500; // num of model iterations
const double init_price = 1; // starting price for all products
const int luxury_dependency = 2; // number of food units required for each luxury unit
const int init_raw_materials = (init_energy * emps_per_cmp) * 1.5; // starting raw materials for all cmps
const double food_energy_multiplier = 10; // obvious function
const double luxury_energy_multiplier = food_energy_multiplier * 2.75; // ~
const double food_cmp_percent = 0.65; // percentage of food cmps to total cmps
const int origin_food_need = 0.8;
const int bound_food_need = 5;
const double fear_sensitivity_bound = 0.7; // Y factor increase if food consumption exceeds 'fear_sensitivity_bound' of the total salary
const double fear_sensitivity_origin = 0.3; // Y factor decrease if food consumption didn't exceed 'fear_sensitivity_origin' of the total salary
#endif