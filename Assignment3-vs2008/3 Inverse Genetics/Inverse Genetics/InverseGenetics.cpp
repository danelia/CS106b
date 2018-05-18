/*
 * File: InverseGenetics.cpp
 * --------------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Inverse Genetics problem
 * on Assignment #3.
 * [TODO: extend the documentation]
 */

#include <iostream>	
#include <string>
#include <fstream>
#include <simpio.h>
#include "set.h"
#include "map.h"
#include "console.h"
using namespace std;

/* Function: listAllRNAStrandsFor(string protein,
 *                                Map<char, Set<string> >& codons);
 * Usage: listAllRNAStrandsFor("PARTY", codons);
 * ==================================================================
 * Given a protein and a map from amino acid codes to the codons for
 * that code, lists all possible RNA strands that could generate
 * that protein
 */
void listAllRNAStrandsFor(string protein, Map<char, Set<string> >& codons);

/* Function: loadCodonMap();
 * Usage: Map<char, Lexicon> codonMap = loadCodonMap();
 * ==================================================================
 * Loads the codon mapping table from a file.
 */
Map<char, Set<string> > loadCodonMap();

//helping method to print RNA strands
void helper(string protein, Map<char, Set<string> >& codons, string soFar);


int main() {
    /* Load the codon map. */
    Map<char, Set<string> > codons = loadCodonMap();

	//test
	string protein = toUpperCase(getLine("Enter protein: "));
	foreach(char ch in protein)
		if(!codons.containsKey(ch))
			cout<<"No such RNA."<<endl;
	listAllRNAStrandsFor(protein, codons);
    return 0;
}

/* You do not need to change this function. */
Map<char, Set<string> > loadCodonMap() {
    ifstream input("codons.txt");
    Map<char, Set<string> > result;

    /* The current codon / protein combination. */
    string codon;
    char protein;

    /* Continuously pull data from the file until all data has been
     * read.
     */
    while (input >> codon >> protein) {
        result[protein] += codon;
    }

    return result;
}

void listAllRNAStrandsFor(string protein, Map<char, Set<string> >& codons)
{
	helper(protein, codons, "");
}

//helping method to print RNA strands
void helper(string protein, Map<char, Set<string> >& codons, string soFar) {
	//base case
    if (protein.length() == 0) cout << soFar << endl;

    foreach (string codonString in codons[protein[0]])
		helper(protein.substr(1), codons, soFar + codonString);

}