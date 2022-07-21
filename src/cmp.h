#ifndef CMP_H
#define CMP_H
#include <string>
#include "conf.h"
#include "emp.h"
struct cmp {
    int id;
    double wealth;
    double price_multiplier;
    double salary;
    int raw_materials;
    int previous_units_produced;
    string product;
    double previous_price;
    double greed_multiplier;
    bool pmi;
    emp emps[emps_per_cmp];
};
#endif