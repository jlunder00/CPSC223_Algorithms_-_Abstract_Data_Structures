
//----------------------------------------------------------------------
// Author: Jason Lunder
// Assignment: 1
// Implementation for a basic class representing a general financial
// security. 
//----------------------------------------------------------------------

#include <string>
#include "security.h"


Security::Security(std::string the_symbol) : symbol(the_symbol)
{}

//Getters and setters for the various aspects of a security.
std::string Security::get_symbol() const
{
  return symbol;
}


void Security::set_share_value(double current_share_value)
{
  share_value = current_share_value;
}


double Security::get_share_value() const
{
  return share_value;
}


void Security::set_holdings(int number_of_holdings)
{
  holdings = number_of_holdings;
}


int Security::get_holdings() const
{
  return holdings;
}

//Calculates the current market worth of the security.
double Security::market_worth() const
{
  return get_share_value() * get_holdings();
}
