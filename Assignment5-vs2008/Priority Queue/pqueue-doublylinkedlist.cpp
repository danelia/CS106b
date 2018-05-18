/*************************************************************
 * File: pqueue-doublylinkedlist.cpp
 *
 * Implementation file for the DoublyLinkedListPriorityQueue
 * class.
 */
 
#include "pqueue-doublylinkedlist.h"
#include "error.h"

DoublyLinkedListPriorityQueue::DoublyLinkedListPriorityQueue() {
	//first thing we need to do is to make first addres null cause there are no elements in list
	head = NULL;
}

DoublyLinkedListPriorityQueue::~DoublyLinkedListPriorityQueue() {
	//deleting all our garbage
	while(true)
	{
		if(head==NULL)break;
		cellT* newCell = head->next;
		delete head;
		head=newCell;
	}
}

int DoublyLinkedListPriorityQueue::size() {
	//we get size with for loop through all addresses
	int result = 0;
	for(cellT* cell = head; cell != NULL; cell = cell->next)
		result++;

	return result;
}

bool DoublyLinkedListPriorityQueue::isEmpty() {
	//if head is null it means there is nothing in list
	return head==NULL;
}

void DoublyLinkedListPriorityQueue::enqueue(string value) {
	//we just make and than add new struct in list with value
	cellT* newCell = new cellT;
	newCell->value = value;
	newCell->next = head;
	newCell->prev = NULL;
	
	//if we already had head we need that's prev to be new cell
	if(head != NULL)
		head->prev = newCell;

	head = newCell;
}

string DoublyLinkedListPriorityQueue::peek() {
	//error if queue is empty
	if(isEmpty())
		error("Nothing ro peek");
	
	//we go through every value and peek one that is min
	string result = head->value;
	
	cellT* cell = head;
	for(; cell != NULL; cell = cell->next)
		if(cell->value <= result)
			result = cell->value;

	return result;
}

string DoublyLinkedListPriorityQueue::dequeueMin() {
	//we peek and save result to return it
	string result = peek();
	//we go throug queue and find this result to delete it
	cellT* removeThis = head;
	for(cellT* cell = head; cell != NULL; cell = cell->next)
		if(cell->value == result)
		{
			removeThis = cell;
			break;
		}
	//if it's head
	if(removeThis->prev == NULL)
	{
		head = removeThis->next;
		if(removeThis->next!=NULL)
			removeThis->next->prev=NULL;
	//if its tail
	}else if(removeThis->next == NULL)
	{
		removeThis->prev->next = NULL;
	//if its somewhere in middle
	}else
	{
		removeThis->prev->next = removeThis->next;
		removeThis->next->prev = removeThis->prev;
	}
	
	//finally we delete it
	removeThis->next = NULL;
	removeThis->prev = NULL;
	delete removeThis;

	return result;
}

