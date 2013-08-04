// CPPSimTransit.cpp : Defines the entry point for the console application.
//

//#include "stdafx.h"
#include <stdio.h>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <list>
#include <unordered_map>

using namespace std;
/*
template <class T>
struct DNode {
	T* next;
	T* prev;
};

template <class T>
struct DList {
	T* head;
	void add(T* node) {
		head = node;
	}
	void remove(T* node) {
	}
};
*/
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

Route parseRoute(string file, unordered_map<int, Station>* cache) {
	ifstream infile("data/"+file);
	if(infile.good()==false) exit(1);
	stringstream buffer;
	
	bool firstl=true;
	Route route;
	Station s;
	
	while( infile.good()  ) {
		char c = infile.get();
		if(c=='\n') {
			if(firstl) firstl=false;
			else {
				buffer >> s.id;
				if( (*cache).find(s.id) != (*cache).end() ) s=(*cache)[s.id];
				else (*cache)[s.id] = s;
				route.stations.push_back(s);
				s = Station();
			}
			buffer = stringstream();
		}
		else if(c==',') {
			if(firstl) route.name = buffer.str();
			else s.name = buffer.str();
			
			buffer = stringstream();
		}
		else buffer << c;
	}
	infile.close();
	return route;
}

int main(int argc, char argv[])
{
	SimData data;
	data.routes.push_back( parseRoute("47VanNess.csv", &data.stations) );
	data.routes.push_back( parseRoute("49Mission.csv", &data.stations) );
	
	cout << "at: " << data.stations[13163].name << endl;
	/*
	auto r = data.routes.front();
	for(auto s : r.stations) {
		cout << s.name << "++" << s.id << endl;
	}
	*/

	int i;
	cin >> i;
	return 0;
}





