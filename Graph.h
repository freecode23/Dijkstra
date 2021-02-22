//********************************************************************
// ASU CSE310 Assignment #7
// Name: Sherly Hartono
// ASU ID: 1217936668
// ASU Email address: sharton1@asu.edu
// Description: This is the header file that defines a directed graph
//********************************************************************

#include "MinHeap.h"

using namespace std;

class Graph
{
private:
   int numOfNode;     //number of nodes in the graph
   MinHeap *cityHeap; //a min-heap of departure City objects

public:
   Graph(int numOfNode, MinHeap *cityHeap);
   void destructor();
   void printGraph();
   void initialize_single_source(string sourceCityName);
   void relax(City u, City v);
   int findOneCity(string aCityName);
   void dijkstra(string sourceCityName);
   void printDijkstraPath(string sourceCityName);

   //  extra method
   int weight(City u, City v);
   void printParentSequence(City first_city, string sourceCityName);
};

//*******************************************************************
//1. Constructor
Graph::Graph(int numOfNode, MinHeap *cityHeap)
{
   this->numOfNode = numOfNode;
   this->cityHeap = cityHeap;
}

//*******************************************************************
//2. Destructor Graph::~Graph()
void Graph::destructor()
{
   delete[] cityHeap;
   cityHeap = nullptr;
   numOfNode = 0;
}

//*******************************************************************
// 3. Print Graph
void Graph::printGraph()
{
   cout << "\nHeap size = " << cityHeap->getSize() << endl;
   //  print title
   cout << left;
   cout << setw(15) << "\nCity Name"
        << setw(12) << "d Value"
        << setw(15) << "PI"
        << "Arrival City List" << endl;

   // print content
   for (int i = 0; i < numOfNode; i++)
   {
      cout << left;
      cout << setw(15) << cityHeap->getCityArray()[i].cityName
           << setw(12) << cityHeap->getCityArray()[i].d;
      string parent;
      if (cityHeap->getCityArray()[i].pi == 0)
      {
         parent = "No Parent";
      }
      else
      {
         parent = cityHeap->getCityArray()[i].pi->cityName;
      }

      cout << setw(15) << parent;
      cityHeap->getCityArray()[i].arrvCityList->printArrvCityList();
      cout << endl;
   }
}

//*******************************************************************
// 4. Initialize single source
void Graph::initialize_single_source(string sourceCityName)
{
   // get the index of the source City
   int index = findOneCity(sourceCityName);

   // change its d value to 0
   cityHeap->getCityArray()[index].d = 0;
}

//*******************************************************************
// 5. Find one city return its index
int Graph::findOneCity(string aCityName)
{
   for (int i = 0; i < numOfNode; i++)
   {
      if (cityHeap->getCityArray()[i].cityName == aCityName)
      {
         return i;
      }
   }
   return -1;
}
//*******************************************************************
// 5. Weighted(u,v)
int Graph::weight(City u, City v)
{
   // find city u in the array get its index
   // int indexofU = findOneCity(u.cityName);

   // get the price from u to this vArrival
   return u.arrvCityList->findArrvCity(v.cityName)->price;
}

//*******************************************************************
// 6. Relax
void Graph::relax(City u, City v)
{
   // TEST PRINT
   // cout << "\n==== RELAX: " << endl;
   // cout << "Deaprture's U city name:  " << u.cityName << endl;
   // cout << "Arrival's V city name  :  " << v.cityName << endl;
   // END TEST
   int indexofU = findOneCity(u.cityName);
   int indexofV = findOneCity(v.cityName);

   City *vptr = &cityHeap->getCityArray()[cityHeap->isFound(v.cityName)];
   // if direct price from Source to v is bigger than indirect price (Source to u + u to v)
   int w = weight(u, v);
   if ((vptr->d) > (u.d + w))
   {
      // make direct price as indirect (alter in the original array)
      vptr->d = cityHeap->getCityArray()[indexofU].d + w; //  v.d = u.d + w;
      vptr->pi = &cityHeap->getCityArray()[indexofU];     //v.pi = u
      cout << "vptr  name  : " << vptr->cityName << endl;
      cout << "vptr.pi : " << vptr->pi->cityName << endl;
   }
}

//*******************************************************************
// 7. Dijkstra
void Graph::dijkstra(string sourceCityName)
{
   initialize_single_source(sourceCityName);
   cityHeap->build_min_heap();

   // 1. initialization
   City S[numOfNode + 1]; // an array S that contains cities whose shortest path have been determined
   City u;                // destination city
   City vDeparture;       // v as departure city
   ArrvCity vArrival;     // v as arrival city
   ArrvCity *current;     // traverse pointer for the linked list

   /// 2. Create a deep copy of cityHeap
   MinHeap *Q = new MinHeap(cityHeap->getCapacity());
   for (int i = 0; i < cityHeap->getSize(); ++i)
   {
      Q->insert(cityHeap->getCityArray()[i]);
   }

   int count = 0;

   // 3. Traverse through each Departure City in Q

   while (Q->getSize() > 0)
   {
      Q->build_min_heap();

      // 4. set u
      u = Q->getHeapMin();

      // 5. Add u to array S
      S[count] = u;
      count++;
      // 6. traverse through the linked list of v's for the departure city u, then implement relax(u,v) to get shortest distance
      // that is to set V.d

      // -1 Set up a current pointer to the head of the linked list of u
      current = u.arrvCityList->getHead();

      // -2 Traversing
      while (current != nullptr)
      {
         //-3 Convert V as cityArrv object in LinkedList to V City object in the main array so we can modify its d value
         vArrival = *current;
         vDeparture = cityHeap->getCityArray()[findOneCity(vArrival.arrvCityName)]; // Q

         //-4 check if vDeparture exist in u's LinkedList if yes do relax, otherwise skip
         if (u.arrvCityList->findArrvCity(vDeparture.cityName) != nullptr) // Q
         {
            relax(u, vDeparture); // set v.d and v.pi on original array
         }

         // -5 update this V.d value in copy array Q so extractMin can be done properly only if d exist
         // change the d value
         if ((Q->isFound(vDeparture.cityName)) != -1)
         {
            Q->getCityArray()[Q->isFound(vDeparture.cityName)].d = cityHeap->getCityArray()[findOneCity(vDeparture.cityName)].d;
         }
         current = current->next;
      }
      Q->extractHeapMin();
   }
}

void Graph::printDijkstraPath(string sourceCityName)
{
   cout << left;
   cout << setw(15) << "\n\nArrival City"
        << setw(15) << "Lowest Price"
        << setw(15) << "Shortest path" << endl;

   // create a copy minheap Q
   MinHeap *Q = new MinHeap(cityHeap->getCapacity());
   for (int i = 0; i < cityHeap->getSize(); ++i)
   {
      Q->insert(cityHeap->getCityArray()[i]);
   }

   // set the first city to print
   City first_city = cityHeap->getCityArray()[0];

   // while cityHeap->getsize() != 0
   while (Q->getSize() != 0)
   {
      // 1. build min heap
      Q->build_min_heap();
      first_city = Q->getCityArray()[0];

      // 2. print out the first one
      cout << setw(15) << first_city.cityName
           << setw(15) << first_city.d;
      if (first_city.cityName != sourceCityName)
      {
         printParentSequence(first_city, sourceCityName); // 3. print parent sequence
      }
      cout << setw(15) << first_city.cityName << endl; // 4.print self
      Q->extractHeapMin();                             // remove this
   }
}

void Graph::printParentSequence(City first_city, string sourceCityName)
{
   string piNameArray[cityHeap->getSize()];
   int counter = 0;

   while (first_city.cityName != sourceCityName)
   {
      // save its parent to array  [youngest, mid, oldest(source city)]
      piNameArray[counter] = first_city.pi->cityName;
      // set current city to its parent
      first_city = *first_city.pi;

      counter++;
   }

   int size = cityHeap->getSize();
   // print oldest first , from the end of array
   // make sure name exist check for empty name
   for (int i = size - 1; i >= 0; i--)
   {
      if (piNameArray[i] != "")
      {
         cout << piNameArray[i]
              << "->";
      }
   }
}
