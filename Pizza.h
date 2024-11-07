//
// Created by progr on 9/3/2024.
//

#ifndef PIZZA_H
#define PIZZA_H

#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include<string>
using std::cout, std::endl, std::ifstream, std::string, std::vector, std::ostream;

class Pizza
{
private:
    int pizza_id, order_id, quantity, unit_price, total_price;
    string pizza_name, order_date, order_time, size, category;

public:
    //constructor for the pizza class
    Pizza(int pizza_id, int order_id, int quantity, int unit_price, int total_price,
          string pizza_name, string order_date, string order_time, string size, string category)
    {
        this -> pizza_id = pizza_id;
        this -> order_id = order_id;
        this -> quantity = quantity;
        this -> unit_price = unit_price;
        this -> total_price = total_price;
        this -> pizza_name = pizza_name;
        this -> order_date = order_date;
        this -> order_time = order_time;
        this -> size = size;
        this -> category = category;
    };

    Pizza() {
        this -> pizza_id = 0;
        this -> order_id = 0;
        this -> quantity = 0;
        this -> unit_price = 0;
        this -> total_price = 0;
        this -> pizza_name = "name";
        this -> order_date = "date";
        this -> order_time = "time";
        this -> size = "size";
        this -> category = "category";
    };

    //getters for class attributes
    int get_pizza_id()
    {
        return pizza_id;
    }

    int get_order_id()
    {
        return order_id;
    }

    int get_unit_price()
    {
        return unit_price;
    }

    int get_total_price()
    {
        return total_price;
    }

    string get_pizza_name()
    {
        return pizza_name;
    }

    string get_order_date()
    {
        return order_date;
    }

    string get_order_time()
    {
        return order_time;
    }

    string get_size()
    {
        return size;
    }

    string get_category()
    {
        return category;
    }

    //setters for class attributes
    void set_pizza_id(int pizza_id)
    {
        this -> pizza_id = pizza_id;
    }

    void set_order_id(int order_id)
    {
        this -> order_id = order_id;
    }

    void set_unit_price(int unit_price)
    {
        this -> unit_price = unit_price;
    }

    void set_total_price(int total_price)
    {
        this -> total_price = total_price;
    }

    void set_quantity(int quantity)
    {
        this -> quantity = quantity;
    }

    void set_pizza_name(string pizza_name)
    {
        this -> pizza_name = pizza_name;
    }

    void set_order_date(string order_date)
    {
        this -> order_date = order_date;
    }

    void set_order_time(string order_time)
    {
        this -> order_time = order_time;
    }

    void set_size(string size)
    {
        this -> size = size;
    }

    void set_category(string category)
    {
        this -> category = category;
    }

    bool operator>(const Pizza& p2) const
    {
        return this -> total_price > p2.total_price;
    }

    bool operator<(const Pizza& p2) const
    {
        return this -> total_price < p2.total_price;
    }

    bool operator>=(const Pizza& p2) const
    {
        return this -> total_price >= p2.total_price;
    }

    bool operator<=(const Pizza& p2) const
    {
        return this -> total_price <= p2.total_price;
    }

    bool operator==(const Pizza& p2) const
    {
        return this -> total_price == p2.total_price;
    }
};

//loads data from the pizza_sales.csv into the vector passed as an argument
bool loadData(vector<Pizza>& pizzas)
{
    ifstream dataFile;
    dataFile.open("../pizza_sales.csv");

    if(dataFile)
    {
        cout << "Data File Opened" << endl;

        string header;
        getline(dataFile, header);
        //cout << header << endl;

        double pizza_id, order_id, quantity, unit_price, total_price;
        string pizza_name, order_date, order_time, size, category;

        char comma;
        string skip;

        while(dataFile)
        {
            dataFile>>pizza_id;
            dataFile>>comma;
            //cout<<pizza_id<<endl;

            dataFile>>order_id;
            //cout<<order_id<<endl;
            dataFile>>comma;

            getline(dataFile, pizza_name, ',');
            //cout << pizza_name << endl;

            dataFile>>quantity;
            //cout << quantity << endl;
            dataFile>>comma;

            getline(dataFile, order_date, ',');
            //cout << order_date << endl;

            getline(dataFile, order_time, ',');
            //cout << order_time << endl;

            dataFile>>unit_price;
            //cout << unit_price << endl;
            dataFile>>comma;

            dataFile>>total_price;
            //cout << total_price << endl;
            dataFile>>comma;

            getline(dataFile, size, ',');
            //cout << size << endl;

            getline(dataFile, category, ',');
            //cout << category << endl;

            getline(dataFile, skip, '\n');

            Pizza p = Pizza(pizza_id, order_id, quantity, unit_price, total_price,
                            pizza_name,order_date,order_time,size,category);

            pizzas.push_back(p);
        }

        dataFile.close();
        return true;
    }

    else {
        cout << "File not found" << endl;
        return false;
    }
}

//finds the most common name_id
string mostCommonPizza(vector<Pizza> pizzas)
{

    cout << "Finding most common pizza" << endl;
    vector<string> pizza_names;
    bool noDuplicate = true;

    pizza_names.push_back(pizzas.at(0).get_pizza_name());

    //create a list of all unique pizza name_id
    for(Pizza p : pizzas)
    {
        for(string name : pizza_names)
        {
            if(name == p.get_pizza_name())
            {
                //cout << "Duplicate" << endl;
                noDuplicate = false;
                break;
            }
        }

        if(noDuplicate)
        {
            pizza_names.push_back(p.get_pizza_name());
        }

        noDuplicate = true;
    }

    //count the number of each unique name_id in the dataset
    vector<int> count(pizza_names.size(), 0);

    for(Pizza p : pizzas)
    {
        for(int i = 0; i < pizza_names.size(); i++)
        {
            if(pizza_names.at(i) == p.get_pizza_name())
            {
                count[i]++;
            }
        }
    }

    //calculate which unique name_id had the most occurances in the data
    int max = 0;
    int pos = 0;

    for(int i = 0; i < count.size(); i++)
    {
        if(max < count.at(i))
        {
            max = count.at(i);
            pos = i;
        }

        //cout << count.at(i) << endl;
    }

    cout<<max << " Occurrences"<<endl;
    return pizza_names.at(pos);
}

#endif //PIZZA_H
