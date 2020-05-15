// ----------------------------------------------------------------------
// Author:Jason Lunder 
// Assignment: 2
// ----------------------------------------------------------------------

#include "decimal.h"

void addMatching(int_vec* tempZeros, int_vec* tempIntegers, int rhsLength, int lhsSize, int lhsDiff, 
		int_vec integerDigitsTemp, int_vec zerosDigitsTemp, int midLoopLength);
void addZerosRight(int_vec* tempZeros, int_vec* tempIntegers, int lastLoopLength, 
		int midLoopLength, int_vec integersDigitsTemp);
void addZerosLeft(int_vec*, int_vec*, int_vec, int);
std::string addHelper(int_vec*, int_vec*);
// default value is "0."
Decimal::Decimal() : point_loc(0)
{
  digits.push_back(0);
}


Decimal::Decimal(std::string val, int point_location)
  : point_loc(point_location)
{
  int n = int(val.size());
  // invalid cases: bad point location, empty string
  if (point_loc > n || n == 0) {
    // set to default value "0."
    point_loc = 0;
    digits.push_back(0);
    return;
  }
  // parse string
  for (int i = 0; i < n; ++i) {
    char c = val[i];
    if (std::isdigit(c))
      digits.push_back(c - '0');
    else {
      // invalid character found
      digits.clear();
      point_loc = 0;
      digits.push_back(0);
      return;
    }
  }
  reduce_zeros();
}


// TODO: Finish remaining Decimal functions ... 

// binary addition operator
Decimal Decimal::operator+(const Decimal& rhs) const{
	int lhsDiff;
	int_vec lhs_temp;
	int_vec rhs_temp;
	//these are temprorary int_vecs that will be built from digits and rhs.digits, with zeros
	//appended on either end so that they are the same length, such that calling the ith
	//element of these vectors returns the digit from the same place relative to the decimal point
	
	int_vec* tempZeros;
	int_vec* tempIntegers;
	int_vec* newTempZeros;
	int_vec* newTempIntegers;
	//these pointers allow me to create functions that do the actual manipulation with the pointers,
	//and simply assign the pointers to references of the temporary vectors above,
	//which results in less conditional checks.
	
	int_vec integersDigitsTemp;
	int_vec zerosDigitsTemp;
	//direct copies of digits and rhs.digits to be used with the int_vec pointers

	//determine which operand has less digits on the left side so that the pointer that
	//will have zeros appended onto the left side will be assigned to that temporary int_vec
	if((digits.size() - point_loc) < (rhs.digits.size() - rhs.point_loc))
	{
		tempZeros = &lhs_temp;
		zerosDigitsTemp = digits;
		tempIntegers = &rhs_temp;
		integersDigitsTemp = rhs.digits;
		lhsDiff = (rhs.digits.size() - rhs.point_loc) - (digits.size()-point_loc);
	}
	else if((digits.size() - point_loc) > (rhs.digits.size() - rhs.point_loc))
	{
		tempZeros = &rhs_temp;
		zerosDigitsTemp = rhs.digits;
		tempIntegers = &lhs_temp;
		integersDigitsTemp = digits;
		lhsDiff = (digits.size() - point_loc) - (rhs.digits.size()-rhs.point_loc);
	}
	else
	{
		//if both have the same amount of digits on the left side of the decimal, start the operation for
		//inputting the digits that overlap, allow functionality for the right hand side being
		//different in length, and for both having the same size and decimal point.
		tempZeros = &lhs_temp;
		tempIntegers = &rhs_temp;
		
		lhsDiff = 0;	

		int lhsSize = (digits.size()>rhs.digits.size()) ? digits.size() - point_loc : rhs.digits.size() - rhs.point_loc;
		int rhsLength = (point_loc > rhs.point_loc) ? point_loc : rhs.point_loc;
		int midLoopLength = (lhsSize-lhsDiff)+rhsLength;
		addMatching(tempZeros, tempIntegers, rhsLength, lhsSize, 0, rhs.digits, digits, midLoopLength);
		
		if(point_loc != rhs.point_loc)
		{
			newTempZeros =  (point_loc < rhs.point_loc) ? &rhs_temp : &lhs_temp;
			newTempIntegers = (point_loc > rhs.point_loc) ? &rhs_temp : &lhs_temp;
		}
		int lastLoopLength = (point_loc < rhs.point_loc) ? rhs.point_loc - point_loc : point_loc - rhs.point_loc;
		addZerosRight(newTempZeros, newTempIntegers, lastLoopLength, midLoopLength, integersDigitsTemp);
		
		int finalPointLoc = (point_loc < rhs.point_loc) ? rhs.point_loc : point_loc;
		
		std::string result = addHelper(tempZeros, tempIntegers);
		
		newTempZeros = nullptr;
		newTempIntegers = nullptr;
		tempIntegers = nullptr;
		tempZeros = nullptr;
		
		Decimal output(result, point_loc);
		
		return output;
	}

	addZerosLeft(tempZeros, tempIntegers, integersDigitsTemp, lhsDiff);
	
	int lhsSize = (digits.size()>rhs.digits.size()) ? digits.size() - point_loc : rhs.digits.size() - rhs.point_loc;
	int rhsLength = (point_loc > rhs.point_loc) ? point_loc : rhs.point_loc; //turing operator
	int midLoopLength = (lhsSize-lhsDiff)+rhsLength;
	addMatching(tempZeros, tempIntegers, rhsLength, lhsSize, lhsDiff, integersDigitsTemp, zerosDigitsTemp, midLoopLength);
	//the overlapping section
	
	if(rhs.point_loc != point_loc)
	{
		newTempZeros =  (point_loc < rhs.point_loc) ? &rhs_temp : &lhs_temp;
		newTempIntegers = (point_loc > rhs.point_loc) ? &rhs_temp : &lhs_temp;
	}
	int lastLoopLength = (point_loc < rhs.point_loc) ? rhs.point_loc - point_loc : point_loc - rhs.point_loc;
	addZerosRight(newTempZeros, newTempIntegers, lastLoopLength, midLoopLength, integersDigitsTemp);
	//format the right side of the decimal
	
	int finalPointLoc = (point_loc < rhs.point_loc) ? rhs.point_loc : point_loc;

	std::string result = addHelper(tempZeros, tempIntegers);

	tempZeros = nullptr;
	tempIntegers = nullptr;
	newTempZeros = nullptr;
	newTempIntegers = nullptr;
	Decimal output(result, finalPointLoc);
	return output;
}

//append zeros onto the right side of the decimal point 
void addZerosRight(int_vec* tempZeros, int_vec* tempIntegers, int lastLoopLength, int midLoopLength, int_vec integersDigitsTemp)
{
	for(int i = midLoopLength; i < lastLoopLength; i++)
	{
		tempZeros->push_back(0);
		tempIntegers->push_back(integersDigitsTemp[i]);
	}
}

//insert all the digits that match in place
void addMatching(int_vec* tempZeros, int_vec* tempIntegers, int rhsLength, int lhsSize, int lhsDiff, int_vec integersDigitsTemp, int_vec zerosDigitsTemp, int midLoopLength)
{	
	for(int i = 0; i < midLoopLength; i++)
	{
		tempZeros->push_back(zerosDigitsTemp[i]);
		tempIntegers->push_back(integersDigitsTemp[i+lhsDiff]);
	}
}

//append zeros to the left side for the int_vec that requires more zeros to match
void addZerosLeft(int_vec* tempZeros, int_vec* tempIntegers, int_vec integersDigitsTemp, int lhsDiff)
{
	for(int i = 0; i < lhsDiff; i++)
	{
		tempZeros->push_back(0);
		tempIntegers->push_back(integersDigitsTemp[i]);
	}
}

//perform the addition of the two reformatted int_vecs
std::string addHelper(int_vec* zeros, int_vec* integers)
{
	std::string result = "";
	int a = 0;
	int b = 0;
	int c = 0;
	int carry = 0;
	for(int i = 0; i < zeros->size(); i++)
	{
		a = zeros->at(zeros->size()-1-i);
		b = integers->at(zeros->size()-1-i);
		c = a + b + carry;
		result = (c >= 10) ? std::to_string(c-10)+result : std::to_string(c)+result;
		carry = (c >= 10) ? 1 : 0;
		b = 0;
		a = 0;
	}
	result = (carry == 1) ? std::to_string(carry)+result : result;
	zeros = nullptr;
	integers = nullptr;
	return result;
}
// prefix increment operator
Decimal& Decimal::operator++(){
	*this = *this + Decimal("1",0);
	return *this;
}

// postfix increment operator
Decimal Decimal::operator++(int){
	Decimal copy = *this;
	*this = *this + Decimal("1",0);
	return copy;
}

void Decimal::reduce_zeros(){
	while(digits.back() == 0 && point_loc > 0)
	{
		digits.pop_back();
		--point_loc;
	}
	while(digits[0] == 0 && digits.size() != point_loc)
		digits.erase(digits.begin());
}

bool Decimal::operator<(const Decimal& rhs) const {
	return rhs > *this;
}

bool Decimal::operator==(const Decimal& rhs) const {
	return !(*this < rhs) && !(rhs < *this); 
}

bool Decimal::operator>(const Decimal& rhs) const {
	if((digits.size() - point_loc) > (rhs.digits.size() - rhs.point_loc))
		return true;
	else if((digits.size() - point_loc) < (rhs.digits.size() - rhs.point_loc))
		return false;
	int size;
	if(point_loc <= rhs.point_loc)
		size = digits.size();
	else
		size = rhs.digits.size();
	for(int i = 0; i < size; i++)
	{
		if(digits[i] > rhs.digits[i])
			return true;
		else if(digits[i] < rhs.digits[i])
			return false;
	}
	return digits.size() > rhs.digits.size();
}

bool Decimal::operator<=(const Decimal& rhs) const {
	return (*this < rhs) || (*this == rhs);
}

bool Decimal::operator>=(const Decimal& rhs) const {
	return (*this > rhs) || (*this == rhs);
}

bool Decimal::operator!=(const Decimal& rhs) const {
	return !(*this == rhs);
}


std::ostream& operator<<(std::ostream& out, const Decimal& val){
	for(int i = 0; i < val.digits.size(); i++)
	{
		if(i == (val.digits.size() - val.point_loc))
			out<<".";
		out<<val.digits[i];
	}
	return out;
}
