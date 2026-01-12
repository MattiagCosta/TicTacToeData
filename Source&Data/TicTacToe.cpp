#include "TicTacToe.hpp"

using namespace std;

namespace TicTacToe{
	static bool HandleError(string error, bool throwError){
		if(throwError){
			throw error;
		}
		return false;
	}

	bool CheckDepth(int depth, bool strict, bool throwError){
		string error = "Invalid depth";
		if(strict && (depth < 1 || depth > 9)){
			return HandleError(error, throwError);
		}
		else if(depth < 0 || depth > 10){
			return HandleError(error, throwError);
		}
		return true;
	}

	bool CheckBoard(string board, bool throwError){
		string error = "Invalid board";
		if(board.length() != 9){
			return HandleError(error, throwError);
		}
		int firstPlayerCount = 0;
		int secondPlayerCount = 0;
		for(char status : board){
			if(status == firstPlayerStatus){
				firstPlayerCount;
			}
			else if(status == secondPlayerStatus){
				secondPlayerCount;
			}
		}
		if(secondPlayerCount > firstPlayerCount || firstPlayerCount - secondPlayerCount > 1){
			return HandleError(error, throwError);
		}
		return true;
	}

	bool CheckNumericMove(char move, bool throwError){
		string error = "Invalid move";
		if(move < '0' || move > '8'){
			return HandleError(error, throwError);
		}
		return true;
	}

	bool CheckNumericSequence(string numericSequence, bool throwError){
		string error = "Invalid numeric sequence";
		if(numericSequence.length() > 9){
			return HandleError(error, throwError);
		}
		vector<bool> cellsTaken;
		cellsTaken.resize(9);
		for(char move : numericSequence){
			if(move < '0' || move > '8'){
				if(throwError){
					throw error;
				}
				return false;
			}
			if(cellsTaken[move - '0']){
				if(throwError){
					throw error;
				}
				return false;
			}
			cellsTaken[move - '0'] = true;
		}
		return true;
	}

	bool CheckAfter(string after, bool throwError){
		string error = "Invalid after";
		if(after.length() != 9){
			return HandleError(error, throwError);
		}
		for(int i = 0; i < 9; i++){
			if(after[i] < '0' || after[i] > '8'){
				if(throwError){
					throw error;
				}
				return false;
			}
		}
		return true;
	}

	bool CheckPointOfView(string pointOfView, bool throwError){
		string error = "Invalid point of view";
		if(pointOfView.length() != 9){
			if(throwError){
					throw error;
				}
				return false;
		}
		return true;
	}

	bool CheckUniversalSequence(string universalSequence, bool throwError){
		string error = "Invalid universalSequence";
		for(int i = 1; i < universalSequence.length(); i++){
			if(universalSequence[i] == movesPartition && universalSequence[i - 1] == movesPartition){
				if(throwError){
					throw error;
				}
				return false;
			}
		}
		return true;
	}

	string ChangeBoard(string board, string after){
		string changedBoard;
		for(int i = 0; i < 9; i++){
			changedBoard += board[after[i] - '0'];
		}
		return changedBoard;
	}

	string TransformBoard(string board, string transformation){
		string transformedBoard;
		if(transformation == rotation){
			transformedBoard = ChangeBoard(board, "258147036");
		}
		else if(transformation == reflection){
			transformedBoard = ChangeBoard(board, "678345012");
		}
		return transformedBoard;
	}

	bool AreSimilarBoards(string boardA, string boardB){
		for(int i = 0; i < 4; i++){
			if(boardA == boardB){
				return true;
			}
			boardB = TransformBoard(boardB, string(reflection));
			if(boardA == boardB){
				return true;
			}
			boardB = TransformBoard(boardB, string(reflection));
			boardB = TransformBoard(boardB, string(rotation));
		}
		return false;
	}

	int CountMovesMade(string board){
		int count = 0;
		for(char status : board){
			if(status != emptyStatus){
				count++;
			}
		}
		return count;
	}

	char GetBoardNextStatus(string board){
		if(CountMovesMade(board) % 2 == 0){
			return firstPlayerStatus;
		}
		return secondPlayerStatus;
	}

	bool IsCompleteBoard(string board){
		if(CountMovesMade(board) == 9){
			return true;
		}
		if(
		(board[0] == board[1] && board[1] == board[2] && board[0] != emptyStatus)
		|| (board[0] == board[3] && board[3] == board[6] && board[0] != emptyStatus)
		|| (board[2] == board[5] && board[5] == board[8] && board[8] != emptyStatus)
		|| (board[6] == board[7] && board[7] == board[8] && board[8] != emptyStatus)
		|| (board[3] == board[4] && board[4] == board[5] && board[4] != emptyStatus)
		|| (board[1] == board[4] && board[4] == board[7] && board[4] != emptyStatus)
		|| (board[0] == board[4] && board[4] == board[8] && board[4] != emptyStatus)
		|| (board[2] == board[4] && board[4] == board[6] && board[4] != emptyStatus)
		){
			return true;
		}
		return false;
	}

	static void GetBoardsAtKnownDepthBacktrack(int depth, int info, vector<string>& boards, string referenceBoard){
		if(CountMovesMade(referenceBoard) >= depth){
			if(info & ONGOING_ONLY && IsCompleteBoard(referenceBoard)){
				return;
			}
			if(info & COMPLETE_ONLY && !IsCompleteBoard(referenceBoard)){
				return;
			}
			if(info & EXCLUDE_SIMILAR){
				for(string existingBoard : boards){
					if(AreSimilarBoards(referenceBoard, existingBoard)){
						return;
					}
				}
			}
			boards.push_back(referenceBoard);
			return;
		}
		if(info & STANDARD_ONLY && IsCompleteBoard(referenceBoard)){
			return;
		}
		for(int i = 0; i < 9; i++){
			if(referenceBoard[i] == emptyStatus){
				referenceBoard[i] = GetBoardNextStatus(referenceBoard);
				GetBoardsAtKnownDepthBacktrack(depth, info, boards, referenceBoard);
				referenceBoard[i] = emptyStatus;
			}
		}
	}

	vector<string> GetBoardsAtKnownDepth(int depth, int info){
		vector<string> boards;
		string emptyBoard;
		for(int i = 0; i < 9; i++){
			emptyBoard += emptyStatus;
		}
		GetBoardsAtKnownDepthBacktrack(depth, info, boards, emptyBoard);
		return boards;
	}

	string ChangeNumericSequence(string numericSequence, string after){
		string changedNumericSequence;
		for(char move : numericSequence){
			changedNumericSequence += after[move - '0'];
		}
		return changedNumericSequence;
	}

	string TransformNumericSequence(string numericSequence, string transformation){
		string transformedNumericSequence;
		if(transformation == rotation){
			transformedNumericSequence = ChangeNumericSequence(numericSequence, "258147036");
		}
		else if(transformation == reflection){
			transformedNumericSequence = ChangeNumericSequence(numericSequence, "678345012");
		}
		return transformedNumericSequence;
	}

	bool AreSimilarNumericSequences(string numericSequenceA, string numericSequenceB){
		for(int i = 0; i < 4; i++){
			if(numericSequenceA == numericSequenceB){
				return true;
			}
			numericSequenceB = TransformNumericSequence(numericSequenceB, string(reflection));
			if(numericSequenceA == numericSequenceB){
				return true;
			}
			numericSequenceB = TransformNumericSequence(numericSequenceB, string(reflection));
			numericSequenceB = TransformNumericSequence(numericSequenceB, string(rotation));
		}
		return false;
	}

	string GetBoardFromNumericSequence(string numericSequence){
		string board;
		for(int i = 0; i < 9; i++){
			board += emptyStatus;
		}
		for(int i = 0; i < numericSequence.length(); i++){
			board[numericSequence[i] - '0'] = GetBoardNextStatus(board);
		}
		return board;
	}

	bool IsCompleteNumericSequence(string numericSequence){
		return IsCompleteBoard(GetBoardFromNumericSequence(numericSequence));
	}

	static void GetNumericSequencesAtKnownDepthBacktrack(int depth, int info, std::vector<std::string>& numericSequences, std::string referenceNumericSequence){
		if(referenceNumericSequence.length() >= depth){
			if(info & ONGOING_ONLY && IsCompleteNumericSequence(referenceNumericSequence)){
				return;
			}
			if(info & COMPLETE_ONLY && !IsCompleteNumericSequence(referenceNumericSequence)){
				return;
			}
			numericSequences.push_back(referenceNumericSequence);
			return;
		}
		if(info & STANDARD_ONLY && IsCompleteNumericSequence(referenceNumericSequence)){
			return;
		}
		vector<string> nextNumericSequences;
		for(int i = 0; i < 9; i++){
			if(referenceNumericSequence.find('0' + i) == string::npos){
				nextNumericSequences.push_back(referenceNumericSequence + (char)('0' + i));
			}
		}
		for(int i = 0; i < nextNumericSequences.size(); i++){
			if(info & EXCLUDE_SIMILAR){
				bool isUnique = true;
				for(int j = i + 1; j < nextNumericSequences.size(); j++){
					if(AreSimilarNumericSequences(nextNumericSequences[i], nextNumericSequences[j])){
						isUnique = false;
						break;
					}
				}
				if(isUnique){
					GetNumericSequencesAtKnownDepthBacktrack(depth, info, numericSequences, nextNumericSequences[i]);
				}
			}
			else{
				GetNumericSequencesAtKnownDepthBacktrack(depth, info, numericSequences, nextNumericSequences[i]);
			}
		}
	}

	vector<string> GetNumericSequencesAtKnownDepth(int depth, int info){
		vector<string> numericSequences;
		GetNumericSequencesAtKnownDepthBacktrack(depth, info, numericSequences, "");
		return numericSequences;
	}

	string RotatePointOfView(string pointOfView){
		string rotatedPointOfView = "";
		rotatedPointOfView += pointOfView[2];
		rotatedPointOfView += pointOfView[5];
		rotatedPointOfView += pointOfView[8];
		rotatedPointOfView += pointOfView[1];
		rotatedPointOfView += pointOfView[4];
		rotatedPointOfView += pointOfView[7];
		rotatedPointOfView += pointOfView[0];
		rotatedPointOfView += pointOfView[3];
		rotatedPointOfView += pointOfView[6];
		return rotatedPointOfView;
	}

	string MatchPointOfView(string pointOfView, int desiredCellNumericId){
		for(int i = 0; i < 4; i++){
			if(pointOfView[desiredCellNumericId] == positionId){
				break;
			}
			pointOfView = RotatePointOfView(pointOfView);
		}
		return pointOfView;
	}

	unordered_map<char, int> GetUniversalMoveLiteralIds(string universalMove){
		unordered_map<char, int> universalMoveLiteralIds;
		for(char literalId : universalMove){
			universalMoveLiteralIds[literalId]++;
		}
		return universalMoveLiteralIds;
	}

	bool AreSimilarUniversalMoves(string universalMoveA, string universalMoveB){
		if(universalMoveA.length() != universalMoveB.length()){
			return false;
		}
		unordered_map<char, int> universalMoveALiteralIds = GetUniversalMoveLiteralIds(universalMoveA);
		unordered_map<char, int> universalMoveBLiteralIds = GetUniversalMoveLiteralIds(universalMoveB);
		for(auto [literalId, count] : universalMoveALiteralIds){
			if(universalMoveBLiteralIds[literalId] != count){
				return false;
			}
		}
		return true;
	}

	static void JoinMovesInOneSet(vector<string>& existingSet, vector<string> setToJoin, bool check){
		if(check){
			for(string universalMoveB : setToJoin){
				for(string universalMoveA : existingSet){
					if(AreSimilarUniversalMoves(universalMoveA, universalMoveB)){
						universalMoveB = "";
						break;
					}
				}
				if(universalMoveB != ""){
					existingSet.push_back(universalMoveB);
				}
			}
		}
		else{
			for(string universalMove : setToJoin){
				existingSet.push_back(universalMove);
			}
		}
	}

	vector<string> GetUniversalMovesFromPointsOfViews(vector<string> pointOfViews){
		vector<string> universalMoves;
		vector<int> takenCellsNumbericIds;
		for(string pointOfView : pointOfViews){
			int takenCellNumericId = find(pointOfView.begin(), pointOfView.end(), positionId) - pointOfView.begin();
			if(takenCellNumericId < 9){
				takenCellsNumbericIds.push_back(takenCellNumericId);
			}
		}
		for(int numericId = 0; numericId < 9; numericId++){
			if(find(takenCellsNumbericIds.begin(), takenCellsNumbericIds.end(), numericId) != takenCellsNumbericIds.end()){
				continue;
			}
			string move = "";
			for(string pointOfView : pointOfViews){
				move += pointOfView[numericId];
			}
			JoinMovesInOneSet(universalMoves, {move}, true);
		}
		return universalMoves;
	}

	static void GetUniversalMovesAtKnownDepthBacktrack(int depth, std::vector<std::string>& universalMoves, std::vector<std::string>& everyPossiblePointOfView, std::vector<std::string> referencePointOfViews){
		if(referencePointOfViews.size() >= depth){
			JoinMovesInOneSet(universalMoves, GetUniversalMovesFromPointsOfViews(referencePointOfViews), true);
		}
		else{
			for(string possiblePointOfView : everyPossiblePointOfView){
				if(find(referencePointOfViews.begin(), referencePointOfViews.end(), possiblePointOfView) != referencePointOfViews.end()){
					continue;
				}
				vector<string> nextPointOfViews = referencePointOfViews;
				nextPointOfViews.push_back(possiblePointOfView);
				GetUniversalMovesAtKnownDepthBacktrack(depth, universalMoves, everyPossiblePointOfView, nextPointOfViews);
			}
		}
	}

	vector<string> GetUniversalMovesAtKnownDepth(int depth){
		vector<string> everyPossiblePointOfView = {
			string(centerPointOfView),
			string(middlePointOfView), MatchPointOfView(string(middlePointOfView), 1), MatchPointOfView(string(middlePointOfView), 3), MatchPointOfView(string(middlePointOfView), 5), MatchPointOfView(string(middlePointOfView), 7),
			string(cornerPointOfView), MatchPointOfView(string(cornerPointOfView), 0), MatchPointOfView(string(cornerPointOfView), 2), MatchPointOfView(string(cornerPointOfView), 6), MatchPointOfView(string(cornerPointOfView), 8)
		};
		vector<string> universalMoves;
		GetUniversalMovesAtKnownDepthBacktrack(depth, universalMoves, everyPossiblePointOfView, {std::string(initialPointOfView)});
		return universalMoves;
	}

	string ConvertNumericSequencIntoUniversalSequence(string numericSequence){
		string universalSequence = "";
		vector<string> casesToConsider = {string(initialPointOfView)};
		for(char move : numericSequence){
			int integerMove = move - '0';
			if(casesToConsider.size() > 1){
				universalSequence += movesPartition;
			}
			for(string similarMovesCase : casesToConsider){
				universalSequence += similarMovesCase[integerMove];
			}
			switch(move){
				case '4':
					casesToConsider.push_back(MatchPointOfView(string(centerPointOfView), integerMove));
					break;
				case '0':
				case '2':
				case '6':
				case '8':
					casesToConsider.push_back(MatchPointOfView(string(cornerPointOfView), integerMove));
					break;
				default:
					casesToConsider.push_back(MatchPointOfView(string(middlePointOfView), integerMove));
					break;
			}
		}
		return universalSequence;
	}

	vector<string> GetUniversalSequenceMoves(string universalSequence){
		size_t lastPartition = 0, nextPartition;
		vector<string> moves;
		while(lastPartition < universalSequence.length()){
			nextPartition = universalSequence.find(movesPartition, lastPartition);
			if(nextPartition == string::npos){
				nextPartition = universalSequence.length();
			}
			moves.push_back(universalSequence.substr(lastPartition, nextPartition - lastPartition));
			lastPartition = nextPartition + 1;
		}
		return moves;
	}

	bool AreSimilarUniversalSequences(string universalSequenceA, string universalSequenceB){
		if(universalSequenceA.length() != universalSequenceB.length()){
			return false;
		}
		size_t lastPartition = 0, nextPartition;
		string moveA, moveB;
		do{
			nextPartition = universalSequenceA.find(movesPartition, lastPartition);
			if(nextPartition == string::npos){
				nextPartition = universalSequenceA.length();
			}
			moveA = universalSequenceA.substr(lastPartition, nextPartition - lastPartition);
			if(moveA.length() > 0){
				moveB = universalSequenceB.substr(lastPartition, nextPartition - lastPartition);
				if(!AreSimilarUniversalMoves(moveA, moveB)){
					return false;
				}
			}
			lastPartition = nextPartition + 1;
		}while(lastPartition < universalSequenceA.length());
		return true;
	}

	vector<string> GetUniversalSequencesAtKnownDepth(int depth, int numericSequencesInfo, int universalSequencesInfo){
		vector<string> numericSequences = GetNumericSequencesAtKnownDepth(depth, numericSequencesInfo);
		vector<string> universalSequences;
		string universalSequence;
		bool unique;
		for(string numericSequence : numericSequences){
			universalSequence = ConvertNumericSequencIntoUniversalSequence(numericSequence);
			if(universalSequencesInfo & EXCLUDE_SIMILAR){
				unique = true;
				for(string uniqueUniversalSequence : universalSequences){
					if(AreSimilarUniversalSequences(universalSequence, uniqueUniversalSequence)){
						unique = false;
						break;
					}
				}
				if(unique){
					universalSequences.push_back(universalSequence);
				}
			}
			else{
				universalSequences.push_back(universalSequence);
			}
		}
		return universalSequences;
	}

	void WriteDataOnFile(filesystem::path path, vector<string> data){
		if(path.has_parent_path() && !filesystem::exists(path.parent_path())){
			filesystem::create_directories(path.parent_path());
		}
		ofstream outputFile(path, ios::trunc);
		for(string one : data){
			outputFile << one << "\n";
		}
		outputFile.close();
	}
}
