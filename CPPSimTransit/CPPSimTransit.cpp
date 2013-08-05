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
};

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
// Open CSV file and create a Route while hashing the Stations
Route parseRoute(string& file, unordered_map<int, Station>& hash) {
	ifstream infile("data/"+file);

	Route route;
	infile >> route;
	for(auto& s : route.stations) hash[s.id] = s;

	infile.close();
	return route;
}

int main(int argc, char argv[])
{
	SimData data;
	string files[] = {"47VanNess", "49Mission", "8xBayshore", "KIngleside", "LTaraval", "NJudah", "TThird"};
	for(auto &f : files) data.routes.push_back( parseRoute(f+".csv", data.stations) );
	
	cout << "at: " << data.stations[13163].name << endl;

	cout << "Stations: " << data.stations.size();


	int i;
	cin >> i;
	return 0;
}

int something() {
	return 0;
}





