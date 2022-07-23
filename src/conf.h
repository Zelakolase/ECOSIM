#ifndef CONF_H
#define CONF_H
/*
Basic initalization values for the model
*/
#include <string>
using namespace std;
const int cmps = 10; // num of cmps
const int emps_per_cmp = 100; // num of employees per cmp
const double init_wealth = 100; // starting wealth for cmps, emps
const double init_price = 1; // starting price for all products
const double init_price_multiplier = 1.1; // starting price multiplier for all cmps
const double origin_greed_multiplier = 0.0;
const double bound_greed_multiplier = 0.15;
const double origin_y = 0.0;
const double bound_y = 0.4;
const double origin_fear = 0.0;
const double bound_fear = 0.4;
const double init_salary = 100; // starting salary for all cmps
const string luxury_product_name = "jewelry"; // luxury product name
const double init_energy = 10; // starting energy level for emps
const int iterations = 1; // num of model iterations
const int luxury_dependency = 2; // number of food units required for each luxury unit
const int init_raw_materials = 10; // starting raw materials for all cmps
const double food_energy_multiplier = 1.4; // obvious function
const double luxury_energy_multiplier = 0.4; // ~
const double food_cmp_percent = 0.8; // percentage of food cmps to total cmps
const int origin_food_need = 5;
const int bound_food_need = 10;
const double fear_sensitivity_bound = 0.7; // Y factor increase if food consumption exceeds 'fear_sensitivity_bound' of the total salary
const double fear_sensitivity_origin = 0.3; // Y factor decrease if food consumption didn't exceed 'fear_sensitivity_origin' of the total salary
#endif