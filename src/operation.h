#ifndef OPERATION_H
#define OPERATION_H
#include "cmp.h"
#include "emp.h"
#include "offer.h"
#include <iostream>
class operation
{
private:
    /* data */
public:
    // work and put offer to market
    static void work(cmp *in, offer *o)
    {
        int unitsToProduce = 0;
        for (int i = 0; i < emps_per_cmp; i++)
        {
            unitsToProduce = unitsToProduce + in->emps->energy;
        }
        if (in->product == luxury_product_name)
        {
            int tempUTP = (in->raw_materials / luxury_dependency);
            unitsToProduce = unitsToProduce > tempUTP ? tempUTP : unitsToProduce;
            if (unitsToProduce < luxury_dependency)
            {
                unitsToProduce = 0;
            }
            else
            {
                in->raw_materials = unitsToProduce * luxury_dependency;
            }
        }
        double price = in->previous_price * in->price_multiplier;
        in->previous_units_produced = unitsToProduce;
        in->previous_price = price;
        o->add(in->product, price, unitsToProduce, in->id);
    }
};

#endif