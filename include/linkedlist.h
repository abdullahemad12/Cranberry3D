#ifndef linkedlist_H
#define linkedlist_H
/**
  * this is a linkedlist class
  */

class Array{
	private:
		void* array;
		unsigned int length;
		unsigned int cursor;
		size_t object_size; /*assumed to be multiple of 8*/
	public: 
		Array(unsigned int length, size_t object_size);
		void* getArray(void);
		unsigned int getLength(void);
		void addObject(void* object);
};



class Node
{
	public:
	void* Object;
	Node* next;
	Node(void* object);
};


class Linkedlist 
{
	private:
	Node* head;
	int length;
	void destroy(void);
	public:
	Linkedlist(void);
	~Linkedlist(void);
	void add(void* Object);
	void add_to_front(void* Object);
	void* delete_at(int index);
	void* delete_object(void* object);
	bool contains(void* object);
	Node* getHead(void);
	void* getAt(int i);
	int getLength(void);
 	Array* toArray(size_t object_size);
};



#endif