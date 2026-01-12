#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <filesystem>
#include <fstream>

#define EXCLUDE_SIMILAR 1
#define STANDARD_ONLY 2
#define COMPLETE_ONLY 4
#define ONGOING_ONLY 8

namespace TicTacToe{
	inline constexpr char emptyStatus = '0';
	inline constexpr char firstPlayerStatus = '1';
	inline constexpr char secondPlayerStatus = '2';
	inline constexpr char positionId = 'P';
	inline constexpr char movesPartition = '-';
	inline constexpr std::string_view rotation = "counterclockwise90rotation";
	inline constexpr std::string_view reflection = "0reflection";
	inline constexpr std::string_view initialPointOfView = "CBCBABCBC";
	inline constexpr std::string_view centerPointOfView = "EDEDPDEDE";
	inline constexpr std::string_view middlePointOfView = "HPHIGIJFJ";
	inline constexpr std::string_view cornerPointOfView = "PMNMKONOL";

	bool CheckDepth(int depth, bool strict, bool throwError);
	bool CheckBoard(std::string board, bool throwError);
	bool CheckNumericMove(char move, bool throwError);
	bool CheckNumericSequence(std::string numericSequence, bool throwError);
	bool CheckAfter(std::string after, bool throwError);
	bool CheckPointOfView(std::string pointOfView, bool throwError);
	bool CheckUniversalSequence(std::string universalSequence, bool throwError);

	std::string ChangeBoard(std::string board, std::string after);
	std::string TransformBoard(std::string board, std::string transformation);
	bool AreSimilarBoards(std::string boardA, std::string boardB);
	int CountMovesMade(std::string board);
	char GetBoardNextStatus(std::string board);
	bool IsCompleteBoard(std::string board);
	std::vector<std::string> GetBoardsAtKnownDepth(int depth, int info);

	std::string ChangeNumericSequence(std::string numericSequence, std::string after);
	std::string TransformNumericSequence(std::string numericSequence, std::string transformation);
	bool AreSimilarNumericSequences(std::string numericSequenceA, std::string numericSequenceB);
	std::string GetBoardFromNumericSequence(std::string numericSequence);
	bool IsCompleteNumericSequence(std::string numericSequence);
	std::vector<std::string> GetNumericSequencesAtKnownDepth(int depth, int info);

	std::string RotatePointOfView(std::string pointOfView);
	std::string MatchPointOfView(std::string pointOfView, int desiredCellNumericId);

	std::unordered_map<char, int> GetUniversalMoveLiteralIds(std::string universalMove);
	bool AreSimilarUniversalMoves(std::string universalMoveA, std::string universalMoveB);
	std::vector<std::string> GetUniversalMovesFromPointsOfViews(std::vector<std::string> pointOfViews);
	std::vector<std::string> GetUniversalMovesAtKnownDepth(int depth);

	std::string ConvertNumericSequencIntoUniversalSequence(std::string sequence);
	std::vector<std::string> GetUniversalSequenceMoves(std::string universalSequence);
	bool AreSimilarUniversalSequences(std::string universalSequenceA, std::string universalSequenceB);
	std::vector<std::string> GetUniversalSequencesAtKnownDepth(int depth, int numericSequencesInfo, int universalSequencesInfo);

	void WriteDataOnFile(std::filesystem::path path, std::vector<std::string> data);
}
