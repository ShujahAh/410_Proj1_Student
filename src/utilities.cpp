/***
 * KP Utils
 */
#include <numeric>
#include <math.h>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "utilities.h"
#include "stdlib.h"

using namespace std;

//********************** private to this compilation unit **********************
std::vector<process_stats> data;
//if myString does not contain a string rep of number returns o
//if int not large enough has undefined behaviour, very fragile
int stringToInt(const char *myString) {
	return atoi(myString);
}

int loadData(const char* filename, bool ignoreFirstRow) {

	ifstream file;

	file.open(filename);

	if (!file.is_open()){
		return COULD_NOT_OPEN_FILE;
	}
	string line;
	if (ignoreFirstRow){
		getline(file, line);
	}
	while (getline(file,line)){
		int count = 0;
		for (int i = 0; i < line.size(); i++){
			if (line.substr(i,i+1).compare(",")==0 && (i ==1 || i == 3 || i == 5)){
				count += 1;
			}
		}
		if (count == 3 && line.size() == 7){
			process_stats temp;
			temp.process_number = stoi(line.substr(0, 1));
			temp.start_time = stoi(line.substr(2, 3));
			temp.cpu_time = stoi(line.substr(4, 5));
			temp.io_time = stoi(line.substr(6, 7));
			data.push_back(temp);

		}
	}
	return SUCCESS;
}

bool proc(process_stats one, process_stats two){
	return one.process_number < two.process_number;
}

bool star(process_stats one, process_stats two){
	return one.start_time < two.start_time;
}

bool cpu(process_stats one, process_stats two){
	return one.cpu_time < two.cpu_time;
}

bool io(process_stats one, process_stats two){
	return one.io_time < two.io_time;
}

//will sort according to user preference
void sortData(SORT_ORDER mySortOrder) {
	switch(mySortOrder){
		case (CPU_TIME) :
			sort(data.begin(), data.end(), cpu);
			break;
		case (PROCESS_NUMBER) :
			sort(data.begin(), data.end(), proc);
			break;
		case (START_TIME) :
			sort(data.begin(), data.end(), star);
			break;
		case (IO_TIME) :
			sort(data.begin(), data.end(), io);
			break;
	}

}

process_stats getNext() {

	process_stats myFirst;

	myFirst = data.at(0);

	data.erase(data.begin());

	return myFirst;
}

//returns number of process_stats structs in the vector holding them
int getNumbRows(){
	return data.size();
}


