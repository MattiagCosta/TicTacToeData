#include <stdexcept>
#include <iostream>
#include "TicTacToe.hpp"

using namespace std;
using namespace TicTacToe;

int main(){
	try{
		for(int i = 0; i < 5; i++){
			filesystem::path filePath = string("Data/Boards/LowDepth/BoardsDeep") + (char)('0' + i) + string(".txt");
			WriteDataOnFile(filePath, GetBoardsAtKnownDepth(i, EXCLUDE_SIMILAR));
		}
		for(int i = 5; i < 10; i++){
			filesystem::path filePath = string("Data/Boards/HighDepth/All/BoardsDeep") + (char)('0' + i) + string(".txt");
			WriteDataOnFile(filePath, GetBoardsAtKnownDepth(i, EXCLUDE_SIMILAR));
		}
		for(int i = 5; i < 9; i++){
			filesystem::path filePath = string("Data/Boards/HighDepth/StandardOngoing/BoardsDeep") + (char)('0' + i) + string(".txt");
			WriteDataOnFile(filePath, GetBoardsAtKnownDepth(i, EXCLUDE_SIMILAR | STANDARD_ONLY | ONGOING_ONLY));
		}
		for(int i = 5; i < 10; i++){
			filesystem::path filePath = string("Data/Boards/HighDepth/StandardComplete/BoardsDeep") + (char)('0' + i) + string(".txt");
			WriteDataOnFile(filePath, GetBoardsAtKnownDepth(i, EXCLUDE_SIMILAR | STANDARD_ONLY | COMPLETE_ONLY));
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
