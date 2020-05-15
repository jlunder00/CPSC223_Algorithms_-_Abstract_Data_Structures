
//----------------------------------------------------------------------
// Author: Jason Lunder
// Assignment: 1
// Implementation of a class representing a basic stock share,
// a derived class of a security.
//----------------------------------------------------------------------

#include "stock.h"


Stock::Stock(std::string the_symbol) : Security(the_symbol)
{}

//getters and setters for the various aspects of a stock
void Stock::set_purchase_price(double the_purchase_price)
{
  purchase_price = the_purchase_price;
}

double Stock::get_purchase_price() const
{
  return purchase_price;
}

//Calculates the profit in selling a stock
double Stock::sell_value() const
{
  return (get_share_value()-purchase_price)*get_holdings();
}

