#include <stdexcept>
#include <iostream>
#include "TicTacToe.hpp"

using namespace std;
using namespace TicTacToe;

int main(){
	try{
		for(int i = 1; i < 5; i++){
			filesystem::path filePath = string("Data/NumericSequences/LowDepth/NumericSequencesDeep") + (char)('0' + i) + string(".txt");
			WriteDataOnFile(filePath, GetNumericSequencesAtKnownDepth(i, EXCLUDE_SIMILAR));
		}
		for(int i = 5; i < 10; i++){
			filesystem::path filePath = string("Data/NumericSequences/HighDepth/All/NumericSequencesDeep") + (char)('0' + i) + string(".txt");
			WriteDataOnFile(filePath, GetNumericSequencesAtKnownDepth(i, EXCLUDE_SIMILAR));
		}
		for(int i = 5; i < 9; i++){
			filesystem::path filePath = string("Data/NumericSequences/HighDepth/StandardOngoing/NumericSequencesDeep") + (char)('0' + i) + string(".txt");
			WriteDataOnFile(filePath, GetNumericSequencesAtKnownDepth(i, EXCLUDE_SIMILAR | STANDARD_ONLY | ONGOING_ONLY));
		}
		for(int i = 5; i < 10; i++){
			filesystem::path filePath = string("Data/NumericSequences/HighDepth/StandardComplete/NumericSequencesDeep") + (char)('0' + i) + string(".txt");
			WriteDataOnFile(filePath, GetNumericSequencesAtKnownDepth(i, EXCLUDE_SIMILAR | STANDARD_ONLY | COMPLETE_ONLY));
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
