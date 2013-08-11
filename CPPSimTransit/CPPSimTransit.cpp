// CPPSimTransit.cpp : Defines the entry point for the console application.
//
#include <stdio.h>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <list>
#include <unordered_map>
#include <tuple>
#include <queue>
#include <algorithm>

using namespace std;
typedef int sid;

struct Station {
	string name;
	sid id;
};
struct Traveler {
	string name;
	sid start;
	sid end;
};
// Stream to Travelers
std::istream& operator>> (std::istream& is, vector<Traveler>& l)
{
	while(is.good()) {
		Traveler d;
		getline(is, d.name, ',');
		is >> d.start; is.get();
		is >> d.end; 
		getline(is, string(), '\n'); // force next line
		l.push_back(d);
	}
	return is;
}

struct Driver {
	Driver():trips(0){}
	string name;
	sid start;
	sid trips;
};

struct Vehicle {
	Vehicle(Driver Driver, sid StopID, int Capacity, vector<Station> GoingTo, bool reversePath=false):driver(Driver),capacity(Capacity), goingTo(GoingTo), sindex(0) {
		if(reversePath) reverse(goingTo.begin(), goingTo.end());
	}
	vector<Station> goingTo;
	Driver driver;
	int sindex;
	int capacity;
	int travelers;

	sid currentStationID() {
		return goingTo[sindex].id;
	}
	void step() {
		sindex++;
		if(sindex >= goingTo.size()-1) {
			//cout << driver.name << " reversing" << endl;
			reverse(goingTo.begin(), goingTo.end());
			sindex = 0;
			driver.trips++;
		}
	}
};

struct Route {
	string name;
	vector<Station> stations;
	sid& startID() { return stations[0].id; }
	sid& endID() { return stations[stations.size()-1].id; }
};
// Stream to Drivers
std::istream& operator>> (std::istream& is, unordered_map<sid, list<Driver>>& l)
{
	while(is.good()) {
		Driver d;
		getline(is, d.name, ',');
		is >> d.start; is.get();
		is >> d.trips; 
		if(d.name.length() > 0) l[d.start].push_back(d);
		getline(is, string(), '\n'); // force next line
	}
	return is;
}


struct SimData {
	vector<Route> routes;
	vector<Traveler> travelers;

	unordered_map<sid, list<Driver>> drivers; // Station to int
	unordered_map<sid, Station> stations;

	vector<Vehicle> vehicles; 
};

// Parse stream into a Route and containing Stations
std::istream& operator>> (std::istream& is, Route& r)
{
    getline(is, r.name, ',');
	if(is.peek()==' ') is.get();
	getline(is, string(), '\n');
	while(is.good()) {
		Station s;
		getline(is, s.name, ',');
		if(is.peek()==' ') is.get();
		is >> s.id;
		getline(is, string(), '\n');
		if(s.name.length() > 0) r.stations.push_back(s);
	}

    return is;
}

template <typename T>
T parse(const string& file, T& t) {
	ifstream infile("data/"+file+".csv");

	infile >> t;
	infile.close();
	return t;
}

// Open CSV file and create a Route while hashing the Stations
Route parseRoute(const string& file, unordered_map<int, Station>& hash) {
	Route route;
	parse(file, route);
	for(auto& s : route.stations) {
		if(hash.count(s.id)==0) hash[s.id] = s; //TODO: do not create duplicate Stations
	}
	return route;
}

void parse(SimData& data) {
	string files[] = {"47VanNess", "49Mission", "8xBayshore", "KIngleside", "LTaraval", "NJudah", "TThird"};
	for(auto &f : files) data.routes.push_back( parseRoute(f, data.stations) );

	parse("drivers", data.drivers );
	parse("passengers", data.travelers );
}

template <typename T>
T pop_back(list<T>& list) {
	T b = list.back();
	list.pop_back();
	return b;
}

Driver getDriver(SimData& data, const sid& id) {
	return pop_back( data.drivers[id] );
}

void setup(SimData& data) {
	// Put two Vehicles with drivers on every Route
	for(auto& r : data.routes) {
		Driver d1 = getDriver(data, r.startID());
		Driver d2 = getDriver(data, r.endID());
		Vehicle v1 ( d1, r.startID(), 10, r.stations );
		Vehicle v2 ( d2, r.endID(), 10, r.stations, true );
		
		data.vehicles.push_back( v1 );
		data.vehicles.push_back( v2 );
	}
}

void step(SimData& data) {
	for(auto& v : data.vehicles) {
		//cout << v.driver.name << " from: " << v.currentStationID();
		v.step();
		if(v.driver.trips==3) {
			cout << v.driver.name << " is down, ";
			v.driver = getDriver(data, v.currentStationID());
			cout << v.driver.name << " is a new driver" << endl;
		}
		//cout << " To: " << v.currentStationID() << endl;
	}
	for(auto& p: data.travelers) {
		
	}
}

int main(int argc, char argv[])
{
	SimData data;
	parse(data);
	
	cout << "Hash Test: " << data.stations[13163].name << endl;

	cout << "Stations: " << data.stations.size() << endl;
	cout << "Drivers: " << data.drivers.size() << endl;
	cout << "Passengers: " << data.travelers.size() << endl;

	setup(data);
	cout << "Setup completed." << endl;

	for(int i = 0; i < 39*4; i++) step(data);
	cout << "steps completed" << endl;

	int i;
	cin >> i;
	return 0;
}

int something() {
	return 0;
}





