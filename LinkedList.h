//********************************************************************
// ASU CSE310 Assignment #7
// Name: Sherly Hartono
// ASU ID: 1217936668
// ASU Email address: sharton1@asu.edu
// Description:
//********************************************************************

#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

//struct ArrvCity represents an arrival city information with
//price info. from the departure city
struct ArrvCity
{
    string arrvCityName;
    int price;        //price from the departure city
    struct ArrvCity* next;
};

//class LinkedList will contains a linked list of ArrvCity
class LinkedList
{
    private:
        struct ArrvCity* head;

    public:
        LinkedList();
        ~LinkedList();
        ArrvCity* getHead();
        ArrvCity* findArrvCity(string aCity);
        bool addArrvCity(string aCity, int price);
        void printArrvCityList();
};

// 1. Constructor
LinkedList::LinkedList()
{
    head = nullptr;
}

// 2. Destructor
LinkedList::~LinkedList()
{
    int cityCount = 0;
    ArrvCity *current = head;
    while (current != nullptr)
    {
        current = current->next;
        delete head;
        cityCount != 1;
        head = current;
    }
    // head = nullptr; already done inside the while loop

    cout << "The number of deleted city is: " << cityCount;
}

// 3. getHead
ArrvCity* LinkedList::getHead()
{
    return this->head;
}

// 4. finArrvCity: given an arrival City name return the city node
ArrvCity* LinkedList::findArrvCity(string aCity)
{
    ArrvCity *current = head;
    while(current!= nullptr)
    {
        if(current->arrvCityName == aCity)
        {
            return current;
        }
        current = current->next;
    }
    // exit while loop means name doesnt exist in the linked list
    cout<< "city not found : " << aCity <<endl;
    return nullptr;
}

// 5. add Arrival City given a city name and price
// insert in alphabetical order

bool LinkedList::addArrvCity(string aCity, int price)
{
    // 1. create new arrvCity node and point to it
    ArrvCity *newCity = new ArrvCity;
    newCity->arrvCityName = aCity;
    newCity->price = price;
    newCity->next = nullptr;

    // 2. check if the list is empty
    if(head == nullptr)
    {
        // add to head
        head = newCity;
        return true;
    }
    else // list is not empty
    {
        // A. Compare head
        // this will execute if new city is smaller than head
        if(newCity->arrvCityName < head->arrvCityName)
        {
            newCity->next = head;
            head = newCity;
            return true;
        }
        // B. Compare the rest
        else //this will execute if new food is greater than current name
        {
            ArrvCity *current = head;
            ArrvCity *previous = nullptr;
            while((current != nullptr)&&(newCity->arrvCityName > current->arrvCityName))
            {
                // keep moving
                previous = current;
                current = current->next;
            }
            // exit while loop means newCity should be inserted before current but after previous
            // Like this: previous -> newCity -> current
            newCity->next = current;
            previous->next = newCity;
            return true;
        }
    }
    return false;
}

//6. Prints all the elements in the linked list starting from the head.
void LinkedList::printArrvCityList()
{
    struct ArrvCity *temp = head;
	if(head == NULL)
    {
		cout << "Arrival city list is empty";
		return;
	}
	while(temp!= NULL)
    {
		cout << temp->arrvCityName << "(" << temp->price << "), ";
		temp = temp->next;
	}
}
