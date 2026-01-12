#include <stdexcept>
#include <iostream>
#include "TicTacToe.hpp"

using namespace std;
using namespace TicTacToe;

int main(){
	try{
		for(int i = 1; i < 5; i++){
			filesystem::path filePath = string("Data/UniversalSequences/LowDepth/UniversalSequencesDeep") + (char)('0' + i) + string(".txt");
			WriteDataOnFile(filePath, GetUniversalSequencesAtKnownDepth(i, EXCLUDE_SIMILAR, EXCLUDE_SIMILAR));
		}
		for(int i = 5; i < 10; i++){
			filesystem::path filePath = string("Data/UniversalSequences/HighDepth/All/UniversalSequencesDeep") + (char)('0' + i) + string(".txt");
			WriteDataOnFile(filePath, GetUniversalSequencesAtKnownDepth(i, EXCLUDE_SIMILAR, EXCLUDE_SIMILAR));
		}
		for(int i = 5; i < 9; i++){
			filesystem::path filePath = string("Data/UniversalSequences/HighDepth/StandardOngoing/UniversalSequencesDeep") + (char)('0' + i) + string(".txt");
			WriteDataOnFile(filePath, GetUniversalSequencesAtKnownDepth(i, EXCLUDE_SIMILAR | STANDARD_ONLY | ONGOING_ONLY, EXCLUDE_SIMILAR));
		}
		for(int i = 5; i < 10; i++){
			filesystem::path filePath = string("Data/UniversalSequences/HighDepth/StandardComplete/UniversalSequencesDeep") + (char)('0' + i) + string(".txt");
			WriteDataOnFile(filePath, GetUniversalSequencesAtKnownDepth(i, EXCLUDE_SIMILAR | STANDARD_ONLY | COMPLETE_ONLY, EXCLUDE_SIMILAR));
		}
	}
	catch(const exception& e){
		cerr << e.what();
	}
	catch(const string& e){
		cerr << e;
	}
	catch(...){
		cerr << "An unknown error occoured\n";
	}

	return 0;
}
