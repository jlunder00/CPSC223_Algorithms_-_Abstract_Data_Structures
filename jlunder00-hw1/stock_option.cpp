//----------------------------------------------------------------------
// Author: Jason Lunder
// Assignment: 1
// Implementation of a stock option, which is a derived class of
// a stock. This adds a strike_price to the stock, and overrides
// stock's sell_value(). 
//----------------------------------------------------------------------
#include <string>
#include "stock_option.h"

StockOption::StockOption(std::string the_symbol) : Stock(the_symbol)
{}

void StockOption::set_strike_price(double the_strike_price)
{
  strike_price = the_strike_price;
}

double StockOption::get_strike_price() const
{
  return strike_price;
}

//This function is overridden from stock.cpp. In stock.h, it is declared as virtual
//so that this overriding can happen correctly, less static binding cause errors.
//This calculates the profit from taking the specified stock option.
double StockOption::sell_value() const
{
  return ((strike_price-get_purchase_price())*get_holdings())
	  -(get_share_value()*get_holdings());
}
