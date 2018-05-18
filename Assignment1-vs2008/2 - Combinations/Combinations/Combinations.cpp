/*
 * File: Combinations.cpp
 * ----------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Combinations problem.
 * [TODO: rewrite the documentation]
 */

#include <iostream>
#include <string>
#include "console.h"
using namespace std;

/* Prototypes */
int C(int n, int k);

int main() {

    return 0;
}

//we calculate C with recursion.
int C(int n, int k)
{
	if(k==0 || n==k)return 1;
	return C(n-1, k-1)+C(n-1, k);
}