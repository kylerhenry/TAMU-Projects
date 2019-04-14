#include "temperaturedb.h"
#include <fstream>
using namespace std;

void TemperatureDatabase::loadData(const string& filename) {
	ifstream dataFile;
	dataFile.open(filename);
	if (dataFile.fail()) {
		cerr << "Could not open file: " << filename << endl;
		return;
	}
	LinkedList* list = new LinkedList();
	int location;
	int year;
	int month;
	double temper;
	while (!dataFile.eof()) {
		dataFile >> location >> year >> month >> temper;
		if (temper == -99.99) {
			cin.clear();
		}
		else if (temper <-50.0 || temper > 50.0) {
			cerr << "Invalid temperature in data file." << endl;
		}
		else {
			list->insert(location, year, month, temper);
		}
	}
	dataFile.close();
}

void TemperatureDatabase::performQuery(const string& filename) {
	// Implement this function
}
