#ifndef OFFER_H
#define OFFER_H
/*
offer object
*/
#include <string>
#include <vector>
#include <map>
#include "conf.h"
using namespace std;
struct row
{ // every row
    string product = "";
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
    row get(int i)
    {
        return o.arr[i];
    }
    /*Gets index IDs of rows according to certain rules. iterates through all rows
    note: complexity is O(n) where 'n' is the number of rows/offers
    */
    vector<int> get_ids(map<string, string> in)
    {
        vector<int> ids;
        bool product_compare = in.find("product") != in.end();
        bool units_compare = in.find("units") != in.end();
        bool price_compare = in.find("price") != in.end();
        bool id_compare = in.find("id") != in.end();
        if (product_compare || units_compare || price_compare || id_compare)
        {
            for (int i = 0; i < cmps; i++)
            {
                if(product_compare) {
                    if(o.arr[i].product == in.at("product")) ids.push_back(i);
                }
                if(units_compare) {
                    if(o.arr[i].units == stoi(in.at("units"))) ids.push_back(i);
                }
                if(price_compare) {
                    if(o.arr[i].price == stoi(in.at("price"))) ids.push_back(i);
                }
                if(id_compare) {
                    if(o.arr[i].id == stoi(in.at("id"))) ids.push_back(i);
                }
            }
        }
        return ids;
    }
    /*prints out the offers*/
    void print() {
        printf("id, product, price, units\n");
        for(int i = 0;i < cmps;i++) {
            cout << o.arr[i].id;
            cout << "," << o.arr[i].product;
            cout << "," << o.arr[i].price;
            cout << "," << o.arr[i].units << endl;
        }
    }
};
#endif