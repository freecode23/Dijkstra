//********************************************************************
// Assignment: ASU CSE310 HW#7
// Name: Sherly Hartono
// ASU ID: 1217936668
// ASU Email address: sharton1@asu.edu
//********************************************************
#include "LinkedList.h"

using namespace std;

//represent each node of the graph which is a departure City
struct City
{
	string cityName;
	int d;
	struct City *pi;
	LinkedList *arrvCityList;
};

//class Heap represents a Min-heap that contains City objects. Underline data structure is
//a one dimensional array of City objects.
class MinHeap
{
private:
	struct City *cityArray; //an array of City
	int capacity, size;

public:

	MinHeap(int capacity);
	~MinHeap();

	City *getCityArray();
	int getSize();
	int getCapacity();
	int isFound(string cityName);
	bool decreaseKey(int index, City oneCitywithNewD);
	bool insert(City oneCity);
	void heapify(int index);
	City getHeapMin();
	void extractHeapMin();
	int leftChild(int parentIndex);
	int rightChild(int parentIndex);
	int parent(int childIndex);
	void printHeap();

	//**this is the only newly added function, see textbook pp.157
	void build_min_heap();
};

//1. Constructor to dynamically allocate memory for a heap with the specified capacity
MinHeap::MinHeap(int capacity)
{
	// create array of city objects on heap. the size is "capacity"
	this->capacity = capacity;
	cityArray = new City[capacity];

	// size of heap represents the actual number of city objects stored inside the heap
	size = 0;
}

//2. Destructor
//Before termination, the destructor is called to free the associated memory occupied by the heap.
//and prints the number of nodes deleted by it.
MinHeap::~MinHeap()
{
	cout << "\nThe number of deleted city items is: " << size << endl;
	size = 0;
	delete[] cityArray;
}

// 3 Accessor for city array
City *MinHeap::getCityArray()
{
	return cityArray;
}

// 4 get heap size
int MinHeap::getSize()
{
	return size;
}

//5 get heap capacity
int MinHeap::getCapacity()
{
	return capacity;
}

//6 Decrease Key
bool MinHeap::decreaseKey(int index, City oneCitywithNewD)
{
	if (oneCitywithNewD.d > cityArray[index].d)
	{
		cout << "Decrease key error: new key is larger than current key" << endl;
		return false;
	}

	// 1) Place new City object at the last index
	cityArray[index] = oneCitywithNewD;

	// 2) while we are not yet at root node, and parent node still has smaller key than child's key
	while (index > 0 && cityArray[parent(index)].d > cityArray[index].d)
	{
		// 3) swap parent and child
		City temp = cityArray[parent(index)];

		cityArray[parent(index)] = cityArray[index];
		cityArray[index] = temp;

		// 4) i moves up to parent's
		index = parent(index);
		// cout << "move up to parent index is: " << parent(index) << endl;
	}
	return true;
}

//7 Find key's index
int MinHeap::isFound(string cityName)
{
	for (int i = 0; i < size; i++)
	{
		if (cityArray[i].cityName == cityName)
		{
			return i;
		}
	}
	return -1;
}

//8 Insert City
bool MinHeap::insert(City oneCity)
{
	// 2) Check city if already exists
	if (isFound(oneCity.cityName) != -1)
	{
		cout << "\nDuplicated city item. Not added\n";
		return false;
	}
	// 4) put newFood inside the new array
	// a) add new node to the tree
	size += 1;

	// b) create super large dummy node
	City dummyCity;
	dummyCity.d = 20000;

	// c) place it as the last node
	cityArray[size - 1] = dummyCity;

	// d) call decrease key
	// will place new City at CityArray[size]
	decreaseKey(size - 1, oneCity);

	return true;
}

//9 Heapify
// let the node at index to float down in min heap. so that subtree rooted at index obeys min heap property
void MinHeap::heapify(int index)
{
	// cout << "\nHeapify process: index: " << index << endl;
	// 1. get left and right child of index
	int left_child_idx = leftChild(index);
	int right_child_idx = rightChild(index);
	int smallest_idx;

	// 2. compare node at index with its left child
	// if left child its not the last node and left child is smaller than parent, make left child as smallest
	bool left_empty = cityArray[left_child_idx].cityName == "";

	if ((left_child_idx <= size - 1) && (cityArray[left_child_idx].d < cityArray[index].d))
	{
		// cout << "left child is smaller than parent" << endl;
		// cout << "left child index is " << left_child_idx << endl;
		smallest_idx = left_child_idx;
	}
	else
	{
		// cout << "left child is NOT smaller than parent" << endl;
		// cout << "left child is " << left_child_idx << endl;
		smallest_idx = index;
	}

	bool right_empty = cityArray[right_child_idx].cityName == "";
	//3. compare right child
	if ((right_child_idx <= size - 1) && (cityArray[right_child_idx].d < cityArray[smallest_idx].d) && (right_empty != 1))
	{

		smallest_idx = right_child_idx;
	}
	//4. if smallest is not the parent, then swap the order of struct
	if (smallest_idx != index)
	{
		City temp = cityArray[index];
		cityArray[index] = cityArray[smallest_idx];
		cityArray[smallest_idx] = temp;
		heapify(smallest_idx);
	}
}

//10 Accessor for the root of the heap
City MinHeap::getHeapMin()
{
	return cityArray[0];
}

//11
// extract the root of the heap. Replace the root by the
// last node than call heapify to float down this "last" node
void MinHeap::extractHeapMin()
{
	// printHeap();
	// 1. check if there is only one node ( cannot remove it)
	if (size < 1)
	{
		cout << "heap underflow" << endl;
	}
	// 2. swap min to last node and remove it
	City min = this->cityArray[0];
	cityArray[0] = this->cityArray[size - 1];

	// 3. float down this small key node that is now at the root position
	heapify(0);

	// 4. remove this node from the heap
	size--;
}

// 12 leftChild
// Returns left child's index inside the 1D array
int MinHeap::leftChild(int parentIndex)
{
	return 2 * parentIndex + 1;
}

// 13 righChild()
// Returns right child's index inside the 1D array
int MinHeap::rightChild(int parentIndex)
{
	return 2 * parentIndex + 2;
}

//14 Parent()
// Return parents index given a node's index
int MinHeap::parent(int childIndex)
{
	return (childIndex - 1) / 2;
}
// 15) Build min heap
void MinHeap::build_min_heap()
{
	for (int i = (size / 2) - 1; i >= 0; i--)
	{
		// cout << "i value: " << i << endl;
		heapify(i);
	}
}

void MinHeap::printHeap()
{
	if (cityArray == NULL || size == 0)
		cout << "\nEmpty heap, no elements" << endl;
	else
	{
		cout << "\nHeap size = " << getSize() << "\n"
			 << endl;

		for (int i = 0; i < this->getSize(); i++)
		{
			cout << left;
			cout << setw(8) << "index: " << i;
			cout << setw(8) << ", Destination City: " << this->cityArray[i].cityName;
			cout << setw(8) << this->cityArray[i].d << endl;
			cityArray[i].arrvCityList->printArrvCityList();
			cout << "\n"<< endl;
		}
	}
}
