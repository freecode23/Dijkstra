## Task Description ##

Implement the Dijkstra's shotest path algorithm to find the cheapest flight path from a source city to all other cities.
The example input is given as follows (not real air ticket prices, for testing purpose only)

5<br/>
Phoenix,Chicago(562),Atlanta(1156),<br/>
Atlanta,Duluth(150),Chicago(250),<br/>
Chicago,El Paso(279),Atlanta(350),<br/>
Duluth,El Paso(460),<br/>
El Paso,Phoenix(798),Duluth(670),<br/>
Phoenix<br/>

The number in the first line represents number of departure cities, i.e. it corresponds to the
number of vertices inside the directed graph.
For above example, there will be 5 different departture cities/vertices in the flight routes.
Followed by the city numbers are lines repersent departure and arrival city and air ticket price info.
For example:<br/>

Phoenix,Chicago(562),Atlanta(1156),<br/>

Above represents a departure city Phoenix and two arrival cities Chicago and Atlanta.
Number inside the parenthesis represents the airfair, i.e. from Phoenix to Chicago,
the air ticket price is $562 (for simplicy, just use integer), and from Phoenix to Atlanta, the air ticket price is $1156. Note: the ticket price info. represents the weight of the edge and for different direction between two cities, the ticket price might be different. For example, flight from Atlanta to Chicago, the airfair is $250, where the price from Chicago to Atlanta is $350.

For some cities, if there's no flight departuring from it, you will see the line as, for example:<br/>

Tucson,,<br/>

The last line of the input represents the source city, for above input example, it is Phoenix,
so you will need to apply Dijkstra's shortest path algorithm to compute the cheapest flight route from Phoenix to any other cities.

## 2. Class description ##<br/>
### LinkedList ###<br/>
Inside the LinkedList class, you have the following ArrCity structure defined. It represents the node of the LinkedList which is an arrival city with city's name and airfair price from a specific departure city.

````struct ArrCity
````{
    ````string arrCityName;
    ````int price;
    ````struct ArrCity* next;
````};


