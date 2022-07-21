#ifndef OFFER_H
#define OFFER_H
/*
offer object
*/
#include <string>
#include "conf.h"
using namespace std;
struct row
{ // every row
    string product;
    int units;
    double price;
    int id;
};
struct offers
{ // offers (multiple rows)
    row arr[cmps];
    int insert_pos = 0;
};
class offer
{
private:
    offers o;

public:
    /*Adds one row to the end of array*/
    void add(string product, double price, int units, int id)
    {
        o.arr[o.insert_pos] = row{
            product,
            units,
            price,
            id};
        o.insert_pos++;
    }
    /*clear all elements
    IMPORTANT NOTE: We don't have to clear all elements. we just zero the insert position so we can overwrite on it. this is a performance optimization over mem space.
    */
    void clear()
    {
        o.insert_pos = 0;
    }
    /*get an element by index*/
    row get(int i) {
        return o.arr[i];
    }
};
#endif