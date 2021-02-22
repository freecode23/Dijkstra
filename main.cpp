//********************************************************************
// ASU CSE310 Assignment #7
// Name: Sherly Hartono
// ASU ID: 1217936668
// ASU Email address: sharton1@asu.edu
// Description:
//********************************************************************

#include "Graph.h"

using namespace std;

void getDepCityInfo(string oneLine, string &depCityName, LinkedList *arrvCityList);
void getArrvCityInfo(string oneArrvCityInfo, string &arrvCityName, int &price);

int main()
{
   int count; //a variable for number of nodes
   string oneLine, sourceCityName;
   cout << "Enter num of cities: ";
   cin >> count;
   cin.ignore(20, '\n');

   // 1. Create an Array of Departure city that will store them
   City *cityArray = new City[count];

   // 2. For each line of input of Departure City, we want to set its name and its Linked List of Arrival City
   for (int i = 0; i < count; i++)
   {
      // Initialize:
      // a) LinkedList of arrival cities
      cityArray[i].arrvCityList = new LinkedList();

      // b) each Departure city's node's d value to be very large 20000 (to mimic infinity)
      cityArray[i].d = 20000;
      cityArray[i].pi = nullptr;

      cout << "\nEnter one City info.: " << endl;
      getline(cin, oneLine);

      // 3. call getDepCityInfo() to set departure city's linked list and name
      // from oneLine
      getDepCityInfo(oneLine, cityArray[i].cityName, cityArray[i].arrvCityList);
   }

   // 4. Get Source city
   cout << "Enter source city name: ";
   getline(cin, sourceCityName);

   //5. create a MinHeap, capacity is big enough - twice of the node's number
   MinHeap *cityHeap = new MinHeap(count * 2);

   //Insert each City object from cityArray one by one inside the cityHeap
   // 6. For each of the departure city object in the cityArray, insert into cityHeap
   for (int i = 0; i < count; i++)
   {
      cityHeap->insert(cityArray[i]);
   }

   // create a Graph object by using its constructor
   Graph *graph = new Graph(count, cityHeap);

   //print the graph adjacency list before running Dijkstra algorithm
   cout << "\n\nPrint the graph before Dijkstra algorithm" << endl;
   graph->printGraph();

   //Do depth first search on the graph
   graph->dijkstra(sourceCityName);

   //print the Dijkstra shortest path result
   cout << "\nPrint the Dijkstra algorithm running result" << endl;

   cout << "\nSource City: " << sourceCityName;
   graph->printDijkstraPath(sourceCityName);
}

//**************************************************************
//This function from one line, get all departure city's name and
//all its arrival city's info.
void getDepCityInfo(string oneLine, string &depCityName, LinkedList *arrvCityList)
{
   //A. Get departure city name
   string delimiter = ",";

   int pos = oneLine.find(delimiter);          // get position of delimiter
   string token = oneLine.substr(0, pos);      // get the string before delimiter
   depCityName = token;                        // set depCityName
   cout << "oneLine: " << oneLine << endl;
   cout << "token: " << token << endl;
   oneLine.erase(0, pos + delimiter.length()); // erase Departure city name

   // B. Get all arrival cities inside Linked List
   // 1.intialize variable for arrival city
   string oneArrvCityInfo;
   string arrvCityName;
   int price;

   pos = oneLine.find(delimiter);              // get position of delimiter
   token = oneLine.substr(0, pos);             // get the string before delimiter
   oneArrvCityInfo = token;                    // set first Arrival city info
   oneLine.erase(0, pos + delimiter.length()); // erase the first Arrival city from the line

   // 2. while loop: while arrivalCityInfo is not an empty string keep doing getArrvCityInfo
   while (token != "")
   {

      // 3. get info
      getArrvCityInfo(oneArrvCityInfo, arrvCityName, price);

      // 4. add to linkedlist
      arrvCityList->addArrvCity(arrvCityName, price);

      // 5. get next one
      pos = oneLine.find(delimiter);
      token = oneLine.substr(0, pos);
      oneArrvCityInfo = token;
      oneLine.erase(0, pos + delimiter.length());
   }
}

//****************************************************************************
//This function from a string such as 'Atlanta(1100)', get one arrival city's
//name and air ticket price
void getArrvCityInfo(string oneArrvCityInfo, string &arrvCityName, int &price)
{
   string delimiter1 = "(", delimiter2 = ")";
   int pos = oneArrvCityInfo.find(delimiter1);
   string token = oneArrvCityInfo.substr(0, pos);
   arrvCityName = token;

   oneArrvCityInfo.erase(0, pos + delimiter1.length());

   pos = oneArrvCityInfo.find(delimiter2);
   token = oneArrvCityInfo.substr(0, pos);
   price = stoi(token);
   oneArrvCityInfo.erase(0, pos + delimiter2.length());
}
