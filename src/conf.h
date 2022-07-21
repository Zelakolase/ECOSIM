#ifndef CONF_H
#define CONF_H
/*
Basic initalization values for the model
*/
#include <string>
using namespace std;
const int cmps = 100; // num of cmps
const int emps_per_cmp = 100; // num of employees per cmp
const double init_wealth = 100; // starting wealth for cmps, emps
const double init_price = 1; // starting price for all products
const string luxury_product_name = "jewelry"; // luxury product name
const double init_energy = 10; // starting energy level for emps
const int iterations = 100; // num of model iterations
const int luxury_dependency = 2; // number of food units required for each luxury unit
const int init_raw_materials = 10; // starting raw materials for all cmps
const double food_energy_multiplier = 1.4; // obvious function
const double luxury_energy_multiplier = 0.4; // ~
const double food_cmp_percent = 0.8; // percentage of food cmps to total cmps
#endif