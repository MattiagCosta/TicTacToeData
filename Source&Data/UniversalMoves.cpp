#include <stdexcept>
#include <iostream>
#include "TicTacToe.hpp"

using namespace std;
using namespace TicTacToe;

int main(){
	try{
		for(int i = 1; i < 10; i++){
			filesystem::path filePath = string("Data/UniversalMoves/UniversalMovesDeep") + (char)('0' + i) + string(".txt");
			WriteDataOnFile(filePath, GetUniversalMovesAtKnownDepth(i));
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
