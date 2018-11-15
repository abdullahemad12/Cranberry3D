#include <iostream>
#include <assert.h>
#include "linkedlist.h"


using namespace std;

Node::Node(void* Object)
{
	this->Object = Object;
	this->next = NULL;
}

Linkedlist::Linkedlist(void)
{
	this->length = 0;
	this->head = NULL;
}

void Linkedlist::add(void* object)
{
	Node* newNode = new Node(object);
	Node* cur = this->head;
	if(cur == NULL)
	{
		this->head = newNode;
		
	}
	else{
		while(cur->next != NULL)
		{
			cur = cur->next;		
		}
		cur->next = newNode;
	}
	this->length++;
}

void Linkedlist::add_to_front(void* Object)
{
	Node* newNode = new Node(Object);
	if(this->head == NULL)
	{
		this->head = newNode;
	}
	else
	{
		newNode->next = this->head;
		this->head = newNode;
	}
	this->length++;
}



void* Linkedlist::delete_at(int index)
{
	Node* cur = this->head;
	Node* prev = NULL;
	while(index != 0 && cur != NULL)
	{
		prev = cur;
		cur = cur->next;
		index--;
	}
	void* ret;
	if(cur == NULL)
	{
		ret = NULL;
	}
	else if(prev == NULL)
	{
		this->head = cur->next;
		ret = cur->Object;
		cur->next = NULL;
		delete cur;
		this->length--;
	}
	else
	{
		prev->next = cur->next;
		ret = cur->Object;
		cur->next = NULL;
		delete cur;
		this->length--;
	}
	return ret;
}


void* Linkedlist::delete_object(void* object)
{
	Node* cur = this->head;
	Node* prev = NULL;
	while(cur->Object != object && cur != NULL)
	{
		prev = cur;
		cur = cur->next;
	}
	
	void* ret;
	if(cur == NULL)
	{
		ret = NULL;
	}
	else if(prev == NULL)
	{
		this->head = cur->next;
		ret = cur->Object;
		cur->next = NULL;
		delete cur;
		this->length--;
	}
	else
	{
		prev->next = cur->next;
		ret = cur->Object;
		cur->next = NULL;
		delete cur;
		this->length--;
	}
	return ret;
}

Linkedlist::~Linkedlist(void)
{
	this->destroy();
}

void Linkedlist::destroy(void)
{
	Node* cur = this->head;
	while(cur != NULL)
	{
		Node* node = cur;
		cur = cur->next;
		delete node;
	}
}

bool Linkedlist::contains(void* object)
{
	
	Node* cur = this->head;
	while(cur != NULL && cur->Object != object)
	{
		cur = cur->next;
	}
	return cur != NULL;
}

Node* Linkedlist::getHead(void)
{
	return this->head;
}


void* Linkedlist::getAt(int i)
{
	if(i < 0)
	{
		return NULL;
	}

	Node* cur = this->head;
	
	while(cur != NULL && i > 0)
	{
		cur = cur->next;
		i--;
	}

	return cur;
}


int Linkedlist::getLength(void)
{

	return this->length;
}

Array* Linkedlist::toArray(size_t object_size)
{
	Array* arr = new Array(this->length, object_size);
	Node* cur = this->head;
	while(cur != NULL)
	{
		arr->addObject(cur->Object);
		cur = cur->next;
	}
	return arr;
}




Array::Array(unsigned int length, size_t object_size)
{
	this->object_size = object_size;
	this->length = length; 
	this->array = (void*) malloc(object_size * length);
	this->cursor = 0;
}

void* Array::getArray(void)
{
	return this->array;
}

unsigned int Array::getLength(void)
{
	return this->length;
}


void Array::addObject(void* object)
{
	int object_size = this->object_size;
	unsigned char* arr = (unsigned char*) this->array;	
	unsigned char* Bobject = (unsigned char*) object;
	unsigned int ptr = 0;
	while(object_size > 0)
	{
		arr[this->cursor++] = Bobject[ptr++];
		object_size--;
	}
}


int main(void)
{

	Linkedlist* ll = new Linkedlist();

	for(int i = 0; i < 1000; i++)
	{
		int* x = new int();
		*x = i;
		ll->add((void*)x);
	}

	while(ll->getLength() > 0)
	{
		delete (int*)ll->delete_at(0);
	}
	delete ll->getHead();	
	delete ll;
}