/*************************************************************
 * File: pqueue-vector.cpp
 *
 * Implementation file for the VectorPriorityQueue
 * class.
 */
 
#include "pqueue-vector.h"
#include "error.h"

VectorPriorityQueue::VectorPriorityQueue() {
	// TODO: Fill this in!
}

VectorPriorityQueue::~VectorPriorityQueue() {
	// TODO: Fill this in!
}

int VectorPriorityQueue::size() {
	//size will be the size of our vector
	return elems.size();
}

bool VectorPriorityQueue::isEmpty() {
	//it's true if size is 0
	return size()==0;
}

void VectorPriorityQueue::enqueue(string value) {
	//we just add new value in our vector
	elems.add(value);
}

string VectorPriorityQueue::peek() {
	//error if queue is empty
	if(isEmpty())
		error("Nothing to peek.");
	
	//we find the minimum value throug all elements
	string result = elems[0];
	for(int i = 1; i < elems.size(); i++)
		if(elems[i] < result)
			result = elems[i];
	
	return result;
}

string VectorPriorityQueue::dequeueMin() {

	//we peek minimum element
	string result = peek();

	//and than search for it in vector
	int n = 0;
	for(int i = 0; i < elems.size(); i++)
		if(elems[i] == result)
			n = i;
	
	//than we remove it
	elems.remove(n);
	return result;
}

