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

using namespace std;

struct Station {
	string name;
	int id;
};
struct Route {
	string name;
	vector<Station> stations;
};
struct Traveler {
	string name;
	int start;
};
struct Driver {
	string name;
	int start;
	int trips;
};
// Stream to Drivers
std::istream& operator>> (std::istream& is, list<Driver>& l)
{
	while(is.good()) {
		Driver d;
		getline(is, d.name, ',');
		is >> d.start; is.get();
		is >> d.trips; 
		getline(is, string(), '\n'); // force next line
		l.push_back(d);
	}
	return is;
}

struct SimData {
	vector<Route> routes;
	vector<Traveler> travelers;
	list<Driver> drivers;
	
	unordered_map<int, Station> stations;
};

// Parse stream into a Route and containing Stations
std::istream& operator>> (std::istream& is, Route& r)
{
    getline(is, r.name, ',');
	if(is.peek()==' ') is.get();
    string skip;
	getline(is, skip, '\n');
	while(is.good()) {
		Station s;
		getline(is, s.name, ',');
		if(is.peek()==' ') is.get();
		is >> s.id;
		r.stations.push_back(s);
	}

    return is;
}

template <typename T>
T parse(string& file, T& t) {
	ifstream infile("data/"+file+".csv");
	//T t;
	infile >> t;
	infile.close();
	return t;
}

// Open CSV file and create a Route while hashing the Stations
Route parseRoute(string& file, unordered_map<int, Station>& hash) {
	Route route;
	parse<Route>(file, route);
	for(auto& s : route.stations) hash[s.id] = s;
	return route;
}

void init(SimData& data) {
	string files[] = {"47VanNess", "49Mission", "8xBayshore", "KIngleside", "LTaraval", "NJudah", "TThird"};
	for(auto &f : files) data.routes.push_back( parseRoute(f, data.stations) );

	parse<list<Driver>>( string("drivers"), data.drivers );
}

int main(int argc, char argv[])
{
	SimData data;
	init(data);
	
	cout << "at: " << data.stations[13163].name << endl;

	cout << "Stations: " << data.stations.size();


	int i;
	cin >> i;
	return 0;
}

int something() {
	return 0;
}





