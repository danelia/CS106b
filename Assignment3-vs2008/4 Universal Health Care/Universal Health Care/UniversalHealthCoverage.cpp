/*
 * File: UniversalHealthCoverage.cpp
 * ----------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the UniversalHealthCoverage problem
 * on Assignment #3.
 * [TODO: extend the documentation]
 */
#include <iostream>
#include <string>
#include "set.h"
#include "vector.h"
#include "console.h"
using namespace std;

/* Function: canOfferUniversalCoverage(Set<string>& cities,
 *                                     Vector< Set<string> >& locations,
 *                                     int numHospitals,
 *                                     Vector< Set<string> >& result);
 * Usage: if (canOfferUniversalCoverage(cities, locations, 4, result)
 * ==================================================================
 * Given a set of cities, a list of what cities various hospitals can
 * cover, and a number of hospitals, returns whether or not it's
 * possible to provide coverage to all cities with the given number of
 * hospitals.  If so, one specific way to do this is handed back in the
 * result parameter.
 */
bool canOfferUniversalCoverage(Set<string>& cities,
                               Vector< Set<string> >& locations,
                               int numHospitals,
                               Vector< Set<string> >& result);


int main() {
    //test
	Set<string> cities;
	cities += "A", "B", "C", "D", "E", "F";
	Set<string> first;
	Set<string> second;
	Set<string> third;
	Set<string> fourth;
	first += "A", "B", "C";
	second += "A", "C", "D";
	third += "B", "F";
	fourth+= "C", "E", "F";
	Vector<Set<string>> locations;
	locations.add(first);
	locations.add(second);
	locations.add(third);
	locations.add(fourth);
	Vector<Set<string>> result;
	string final = canOfferUniversalCoverage(cities, locations, 3, result) ? "Possible":"Imppossible";
	cout<<final<<endl;
	cout<<result<<endl;
    return 0;
}

bool canOfferUniversalCoverage(Set<string>& cities,
                               Vector< Set<string> >& locations,
                               int numHospitals,
                               Vector< Set<string> >& result)
{
	//if cities is empty than we want to see if number of hospital is more or equals zero,
	//because if its negative it means its impossible to build requiered numer of hospitals.
	//with our recursive function cities will never be empty, but what if user inputs nothing?
	if(cities.isEmpty()) return numHospitals>=0;
	//we create set of string and add it all cities that we have in result.
	Set<string> citiesCovered;
    foreach(Set<string> covered in result) citiesCovered += covered;
	//and if cities is subset of this set that it means we covered cities with hospitals.
    if(cities.isSubsetOf(citiesCovered)) return true;
	//if number of hospitals is 0 and no base cases work before this, it means that its impossible to
	//cover cities and we return false.
	if(numHospitals == 0)return false;
	//we go through every lovation in locations.
	foreach(Set<string> curLocation in locations)
	{
		if(result.size()==0)
		{
			//we add this location in result and call for recursive part, if it returns false, it means we don't need this
			//location and we remove it.
			result.add(curLocation);
			if(canOfferUniversalCoverage(cities, locations, numHospitals-1, result))return true;
			else result.remove(0);
		}else
		{
			//if result size is not 0, than we go through every set in result,
			//and compare it with our current location.
			foreach(Set<string> curResult in result)
				if(curLocation != curResult)
				{
					//if they aren't same we add it in result and call recursive part.
					//if it return false it means we don't need this location either and we remove it.
					result.add(curLocation);
					if(canOfferUniversalCoverage(cities, locations, numHospitals-1, result))return true;
					else result.remove(result.size()-1);
				}
		}
	}
	return false;
}