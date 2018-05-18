/*************************************************************
 * File: pqueue-linkedlist.cpp
 *
 * Implementation file for the LinkedListPriorityQueue
 * class.
 */
 
#include "pqueue-linkedlist.h"
#include "error.h"

LinkedListPriorityQueue::LinkedListPriorityQueue() {
	//first thing we need to do is to make first addres null cause there are no elements in list
	head = NULL;
}

LinkedListPriorityQueue::~LinkedListPriorityQueue() {
	//deleting all our garbage
	while(true)
	{
		if(head == NULL)break;
		cellT* next = head->next;
		delete head;
		head = next;
	}
}

int LinkedListPriorityQueue::size() {
	//we get size with for loop through all addresses
	int result = 0;
	for(cellT* cell = head; cell != NULL; cell = cell->next)
		result++;

	return result;
}

bool LinkedListPriorityQueue::isEmpty() {
	//if head is null it means there is nothing in list
	return head==NULL;
}

void LinkedListPriorityQueue::enqueue(string value) {
	cellT* newCell = new cellT;
	newCell->value = value;
	newCell->next = NULL;
	//when the list is empty
	if(head==NULL)
		head = newCell;
	else
	{
		for(cellT* cell = head; cell != NULL; cell = cell->next)
		{
			cellT* next = cell->next;
			//best option when we have to take our new cell at first place
			if(cell == head && value <= head->value)
			{
				newCell->next = head;
				head = newCell;
				break;
			}
			
			//when we went to the last struct in our list we just put our new cell there
			if(next == NULL)
			{
				cell->next = newCell;
				break;
			}
	
			//worst option, when we have to put it somewhere in middle
			if(newCell->value > cell->value && newCell->value <= next->value)
			{
				cell->next = newCell;
				newCell->next = next;
				break;
			}
		}
	}


}

string LinkedListPriorityQueue::peek() {
	//error if queue is empty
	if(isEmpty())
		error("Nothing to peek");
	
	//return the first value
	return head->value;
}

string LinkedListPriorityQueue::dequeueMin() {
	//we peek the value
	string result = peek();
	
	//than we delete it
	cellT* next = head->next;
	delete head;
	head = next;
	
	return result;
}

