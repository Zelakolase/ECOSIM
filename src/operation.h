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
                in->raw_materials = in->raw_materials - (unitsToProduce * luxury_dependency);
            }
        }
        double price = in->previous_price * in->price_multiplier;
        in->previous_units_produced = unitsToProduce;
        in->previous_price = price;
        o->add(in->product, price, unitsToProduce, in->id);
    }
    /*
    demand products
    */
    static void demand(cmp *in, offer *o)
    {
        if(in->previous_units_produced * luxury_dependency <= in->raw_materials && in->product == luxury_product_name) {
            pair<double, int> raw_materials_purchase = operation::buy(o,"food",in->wealth);
            in->wealth = in->wealth - raw_materials_purchase.first;
            in->raw_materials = in->raw_materials + raw_materials_purchase.second;
        }
        // TODO: Emp Demand
    }
    /*
    collect revenue, salary update, price_multiplier update
    */
    static void revenue(cmp *in, offer *o)
    {
        // TODO: Revenue calc
    }
    /*
    ts : to spend
    utp : units to purchase
    function: find suitable offer and buy 'utp' units with 'ts' money
    out: pair. first: spent money, second: bought units
    */
    static pair<double, int> buy(offer *o, string product, int utp, double ts)
    {
        // TODO: Algorithm
    }
    /*
    ts: to spend
    function: find optimal offer and spend 'ts' on it
    out: pair. first: spent money, second: bought units
    */
    static pair<double, int> buy(offer *o, string product, double ts)
    {
        // TODO: Algorithm
    }
};

#endif