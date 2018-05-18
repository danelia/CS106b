/*************************************************************
 * File: pqueue-heap.cpp
 *
 * Implementation file for the HeapPriorityQueue
 * class.
 */
 
#include "pqueue-heap.h"
#include "error.h"

HeapPriorityQueue::HeapPriorityQueue() {
	//we create array with default size 10
	arr = new string[10];
	used = 0;
	all = 10;
}

HeapPriorityQueue::~HeapPriorityQueue() {
	//we delete our array
	delete[] arr;
}

int HeapPriorityQueue::size() {
	//size will be how many elements are in array
	return used;
}

bool HeapPriorityQueue::isEmpty() {
	//if size is 0 it means queue is empty
	return size()==0;
}

void HeapPriorityQueue::enqueue(string value) {
	//if there is no more space in array for new value we double its size
	if(used == all)
	{
		all *= 2;
		string *newArr = new string[all];
		for(int i = 0; i < size(); i++)
			newArr[i] = arr[i];
		delete[] arr;
		arr = newArr;
	}

	//than we add this value
	arr[used] = value;

	//and finally bubble it up to find its place
	bubbleUp(used);

	used++;
}

string HeapPriorityQueue::peek() {
	//if array is empty we throw error massege
	if(isEmpty())
		error("Nothing to peek.");
	//we return the first element in array
	return arr[0];
}

string HeapPriorityQueue::dequeueMin() {
	//we peek array and save it as string
	string result = peek();
	
	//we replace first element with last in array
	string tmp = arr[0];
	arr[0] = arr[used-1];
	arr[used-1] = tmp;

	used--;

	//and we bubble it down until we find place for that value
	bubbleDown(0);	
	
	return result;
}

void HeapPriorityQueue::bubbleUp(int pos)
{
	//base case
	if(arr[pos] >= arr[(pos-1)/2])return;
	//changing places
	string tmp = arr[pos];
	arr[pos] = arr[(pos-1)/2];
	arr[(pos-1)/2] = tmp;
	//calling recursive function
	bubbleUp((pos-1)/2);
}

void HeapPriorityQueue::bubbleDown(int pos)
{
	int first = pos*2 + 1;
	int second = pos*2 + 2;
	
	int childToPick;
	
	//we find with which child we should replace(the one with bigest value)
	if(first > size()-1)
		return;
	if(second > size()-1)
		childToPick = first;
	else
		childToPick = arr[first] < arr[second] ? first : second;

	//than we replace it if needed and call for recursive function
	if(arr[pos] > arr[childToPick])
	{
		string tmp = arr[pos];
		arr[pos] = arr[childToPick];
		arr[childToPick] = tmp;
		bubbleDown(childToPick);
	}
}