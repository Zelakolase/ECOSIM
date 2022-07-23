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
    static void demand(cmp *in, offer *o, default_random_engine *gen)
    {
        if(in->previous_units_produced * luxury_dependency <= in->raw_materials && in->product == luxury_product_name) {
            pair<double, int> raw_materials_purchase = operation::buy(o,"food",in->wealth);
            in->wealth = in->wealth - raw_materials_purchase.first;
            in->raw_materials = in->raw_materials + raw_materials_purchase.second;
        }
        for(int i = 0;i < emps_per_cmp;i++) {
            double energy = 0;
            uniform_real_distribution<double> food_rand(origin_food_need, bound_food_need);
            pair<double, int> food_purchase = operation::buy(o, "food",food_rand((*gen)), in->emps[i].wealth);
            in->emps[i].wealth = in->emps[i].wealth - food_purchase.first;
            energy = energy + (food_purchase.second * food_energy_multiplier);
            if(food_purchase.first >= in->emps[i].last_salary) {
                // Nothing goes to rest
            }else {
                double rm = in->emps[i].last_salary - food_purchase.first;
                pair<double, int> luxury_purchase = operation::buy(o, luxury_product_name, (1 - in->emps[i].y) * rm);
                in->emps[i].wealth = in->emps[i].wealth - luxury_purchase.first;
                rm = rm - luxury_purchase.first;
                energy = energy + (luxury_purchase.second * luxury_energy_multiplier);
                in->emps[i].wealth = in->emps[i].wealth + rm;
            }
            in->emps[i].energy = in->emps[i].energy + energy;
            double FcpLastSalary = food_purchase.first / in->emps[i].last_salary;
            if(FcpLastSalary > fear_sensitivity_bound) {
                // Y factor increase
                in->emps[i].y = in->emps[i].y + (in->emps[i].y * (FcpLastSalary * in->emps[i].fear)); 
            }
            if(FcpLastSalary <= fear_sensitivity_origin) {
                // Y factor decrease
                in->emps[i].y = in->emps[i].y - (in->emps[i].y * (FcpLastSalary * in->emps[i].fear)); 
            }
            in->emps[i].last_salary = 0;
        }
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