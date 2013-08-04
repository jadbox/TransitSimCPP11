// CPPSimTransit.cpp : Defines the entry point for the console application.
//

//#include "stdafx.h"
#include <stdio.h>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

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
};

Route parseRoute(string file) {
	ifstream infile("data/"+file);
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
	data.routes.push_back( parseRoute("47VanNess.csv") );
	data.routes.push_back( parseRoute("49Mission.csv") );
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





