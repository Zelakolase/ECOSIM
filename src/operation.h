#ifndef OPERATION_H
#define OPERATION_H
#include "cmp.h"
#include "emp.h"
#include "offer.h"
#include <iostream>
#include <random>
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
        if (in->previous_units_produced * luxury_dependency <= in->raw_materials && in->product == luxury_product_name)
        {
            pair<double, int> raw_materials_purchase = operation::buy(o, "food", in->wealth);
            in->wealth = in->wealth - raw_materials_purchase.first;
            in->raw_materials = in->raw_materials + raw_materials_purchase.second;
        }
        for (int i = 0; i < emps_per_cmp; i++)
        {
            double energy = 0;
            uniform_real_distribution<double> food_rand(origin_food_need, bound_food_need);
            pair<double, int> food_purchase = operation::buy(o, "food", food_rand((*gen)), in->emps[i].wealth, true);
            in->emps[i].wealth = in->emps[i].wealth - food_purchase.first;
            energy = energy + (food_purchase.second * food_energy_multiplier);
            if (food_purchase.first >= in->emps[i].last_salary)
            {
                // Nothing goes to rest
            }
            else
            {
                double rm = in->emps[i].last_salary - food_purchase.first;
                pair<double, int> luxury_purchase = operation::buy(o, luxury_product_name, (1 - in->emps[i].y) * rm);
                in->emps[i].wealth = in->emps[i].wealth - luxury_purchase.first;
                rm = rm - luxury_purchase.first;
                energy = energy + (luxury_purchase.second * luxury_energy_multiplier);
                in->emps[i].wealth = in->emps[i].wealth + rm;
            }
            in->emps[i].energy = in->emps[i].energy + energy;
            double FcpLastSalary = food_purchase.first / in->emps[i].last_salary;
            if (FcpLastSalary > fear_sensitivity_bound)
            {
                // Y factor increase
                in->emps[i].y = in->emps[i].y + (in->emps[i].y * (FcpLastSalary * in->emps[i].fear));
            }
            if (FcpLastSalary <= fear_sensitivity_origin)
            {
                // Y factor decrease
                in->emps[i].y = in->emps[i].y - (in->emps[i].y * (FcpLastSalary * in->emps[i].fear));
            }
            in->emps[i].last_salary = 0;
        }
    }
    /*
    collect revenue, salary update, price_multiplier update
    */
    static void revenue(cmp *in, offer *o, double taxrate, default_random_engine *gen)
    {
        row cmp_offer = o->get(in->id);
        bool RPD = cmp_offer.units > 0;
        bool QIN = cmp_offer.units == -1;
        bool INS = false;
        if(QIN) cmp_offer.units = 0;
        double revenue = cmp_offer.price * (in->previous_units_produced * cmp_offer.units);
        revenue = revenue - (revenue * taxrate);
        if(revenue <= emps_per_cmp * in->salary) {
            in->wealth = in->wealth + revenue;
            revenue = in->wealth;
            INS = true;
        }
        revenue = revenue - (emps_per_cmp * in->salary);
        for(int i = 0;i < emps_per_cmp;i++) {
            in->emps[i].last_salary = in->salary;
            in->emps[i].wealth = in->emps[i].wealth + in->salary;
        }
        if(INS) in->wealth = revenue;
        else if(revenue > 0) in->wealth = in->wealth + revenue;
        uniform_real_distribution<double> pm(0.07+in->greed_multiplier, 0.25+in->greed_multiplier);
        uniform_real_distribution<double> pm2(0.07, 0.25-in->greed_multiplier);
        if(in->pmi) in->price_multiplier = in->price_multiplier + (in->price_multiplier * pm(*gen));
        if(QIN) in->price_multiplier = in->price_multiplier + (in->price_multiplier * pm(*gen));
        else if(RPD) in->price_multiplier = in->price_multiplier + (in->price_multiplier * pm2(*gen));
        else {
            uniform_real_distribution<double> roulette(0.0,1.0);
            if(roulette(*gen) < 0.2+in->greed_multiplier) {
                uniform_real_distribution<double> pm3(0.1,0.25+ in->greed_multiplier);
                in->price_multiplier = in->price_multiplier + (in->price_multiplier * pm3(*gen));
            }
        }
        uniform_real_distribution<double> sm(0.05, 0.2+ in->greed_multiplier);
        if(INS) in->salary = in->salary - (in->salary * sm(*gen));
        else {
            uniform_real_distribution<double> roulette(0.0,1.0);
            if(roulette(*gen) < 0.5+ in->greed_multiplier + 0.25) {
                in->salary = in->salary - (in->salary * (sm(*gen)-0.05));
            }else if(roulette(*gen) < 0.5 + (0.25 - in->greed_multiplier)) {
                uniform_real_distribution<double> sm2(0.05, 0.2);
                in->salary = in->salary + (sm2(*gen) * in->salary);
            }
        }
    }
    /*
    ts : to spend
    utp : units to purchase
    function: find suitable offer and buy 'utp' units with 'ts' money
    out: pair. first: spent money, second: bought units
    */
    static pair<double, int> buy(offer *o, string product, int utp, double ts, bool rec)
    {
        pair<double, int> out;
        if (o->get_highest_units() == 0)
        {
            for (int i = 0; i < cmps; i++)
            {
                o->modify_units(i, -1);
            }
            out.first = 0;
            out.second = 0;
        }
        else
        {
            int optimal_index = 0;
            int optimal_units = 0;
            for (int i = 0; i < cmps; i++)
            {
                int MPU = ts / o->get(i).price; // Max Purchaseable Units
                MPU = MPU > o->get(i).units ? o->get(i).units : MPU;
                if (MPU > optimal_units)
                {
                    optimal_index = i;
                    optimal_units = MPU;
                }
            }
            if (optimal_units == 0)
            {
                out = buy(o, product, ts);
            }
            else if (optimal_units >= utp)
            {
                o->modify_units(optimal_index, o->get(optimal_index).units - utp);
                out.first = utp * o->get(optimal_index).price;
                out.second = utp;
            }
            else if (optimal_units < utp)
            {
                int unitspurchased = 0;
                double spent = 0;
                if (rec)
                {
                    for (int i = 0; i < cmps; i++)
                    {
                        if (utp != 0 && ts != 0)
                        {
                            pair<double, int> temp = buy(o, product, utp, ts, false);
                            if(temp.second != 0 && temp.first != 0) {
                            utp = utp - temp.second;
                            ts = ts - temp.first;
                            unitspurchased = unitspurchased + temp.second;
                            spent = spent + temp.first;
                            }else {
                                break;
                            }
                        }
                        else
                        {
                            break;
                        }
                    }
                    out.first = spent;
                    out.second = unitspurchased;
                }
                else
                {
                    out = buy(o, product, ts);
                }
            }
        }
        return out;
    }
    /*
    ts: to spend
    function: find optimal offer and spend 'ts' on it
    out: pair. first: spent money, second: bought units
    */
    static pair<double, int> buy(offer *o, string product, double ts)
    {
        pair<double, int> out;
        if (o->get_highest_units() == 0)
        {
            for (int i = 0; i < cmps; i++)
            {
                o->modify_units(i, -1);
            }
            out.first = 0;
            out.second = 0;
        }
        else
        {
            int highest_index = 0;
            int max_purchaseable_units = 0;
            for (int i = 0; i < cmps; i++)
            {
                row temp_row = o->get(i);
                if (temp_row.units > 0)
                {
                    int temp = ts / temp_row.price;
                    int purchaseable_units = temp > temp_row.units ? temp_row.units : temp;
                    if (purchaseable_units > max_purchaseable_units)
                    {
                        max_purchaseable_units = purchaseable_units;
                        highest_index = i;
                    }
                }
            }
            out.second = max_purchaseable_units;
            row final_row = o->get(highest_index);
            out.first = max_purchaseable_units * final_row.price;
            o->modify_units(highest_index, final_row.units - max_purchaseable_units);
        }
        return out;
    }
};
#endif