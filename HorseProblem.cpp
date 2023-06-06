#include<iostream>
#include<fstream>
#include<vector>

void Input(int& nrLines, int& nrColumns, int& startLine, int& startColumn, std::ifstream& inputFile, std::ofstream& outputFile)
{
	if (!inputFile.is_open())
	{
		outputFile << "There is not a file with this name!";
		inputFile.close();
		outputFile.close();
		exit(EXIT_SUCCESS);
	}

	inputFile >> nrLines >> nrColumns;

	if (nrLines <= 0 || nrColumns <= 0)
	{
		outputFile << "The chosen size is not valid!";
		inputFile.close();
		outputFile.close();
		exit(EXIT_SUCCESS);
	}

	inputFile >> startLine >> startColumn;

	if (startLine < 0 || startLine >= nrLines || startColumn < 0 || startColumn >= nrColumns)
	{
		outputFile << "The start position is not on the table!\n";
		inputFile.close();
		outputFile.close();
		exit(EXIT_SUCCESS);
	}
}

void InitializeTable(std::vector<std::vector<int>>& table, const int& nrLines, const int& nrColumns)
{
	for (int line = 0; line < nrLines; line++)
	{
		std::vector<int> lineVector;
		for (int column = 0; column < nrColumns; column++)
		{
			lineVector.push_back(0);
		}

		table.push_back(lineVector);
	}

}

bool IsEmpty(std::vector<std::vector<int>>& table, const int& nrLines, const int& nrColumns)
{
	for (int line = 0; line < nrLines; line++)
	{
		for (int column = 0; column < nrColumns; column++)
		{
			if (table[line][column] != 0)
				return true;
		}
	}

	return false;
}

int NrMoves(std::vector<std::vector<int>>& table, const int& nrLines, const int& nrColumns, int line, int column)
{
	const std::vector<int> lineVector = { -1,1,2,2,1,-1,-2,-2 }, columnVector = { 2,2,1,-1,-2,-2,-1,1 };
	int nrMoves = 0, newLine = 0, newColumn = 0;
	for (int index = 0; index < 8; index++) 
	{
		newLine = line + lineVector[index];
		newColumn = column + columnVector[index];
		if (newLine >= 0 && newLine < nrLines && newColumn >= 0 && newColumn < nrColumns && table[newLine][newColumn] == 0)
			nrMoves++;
	}

	return nrMoves;
}

void Traversal(std::vector<std::vector<int>>& table, int currentLine, int currentColumn, int& nrMoves, const int& nrLines, const int& nrColumns)
{
	const std::vector<int> lineVector = { -1,1,2,2,1,-1,-2,-2 }, columnVector = { 2,2,1,-1,-2,-2,-1,1 };

	if (table[currentLine][currentColumn] == 0)
		table[currentLine][currentColumn] = nrMoves;

	bool found = false;	int nrPossibleMoves = 0, newLine = 0, newColumn = 0, minimum = 9; 

	for (int moveIndex = 0; moveIndex < 8; moveIndex++)
	{
		newLine = currentLine + lineVector[moveIndex];
		newColumn = currentColumn + columnVector[moveIndex];
		if (newLine >= 0 && newLine < nrLines && newColumn >= 0 && newColumn < nrColumns && table[newLine][newColumn] == 0)
		{
			nrPossibleMoves = NrMoves(table, nrLines, nrColumns, newLine, newColumn);

			if (nrPossibleMoves < minimum)
			{
				minimum = nrPossibleMoves;
				currentLine = newLine;
				currentColumn = newColumn;
				found = true;
			}
		}

		if (found)
		{
			nrMoves++;
			Traversal(table, currentLine, currentColumn, nrMoves, nrLines, nrColumns);
		}
	}

}

bool CanTraverse(std::vector<std::vector<int>>& table, const int& nrLines, const int& nrColumns)
{
	for (int line = 0; line < nrLines; line++)
	{
		for (int column = 0; column < nrColumns; column++)
		{
			if (table[line][column] == 0)
				return false;
		}
	}

	return true;
}

void PrintTraversal(std::vector<std::vector<int>>& table, const int& nrLines, const int& nrColumns, const int& start, const int& end, std::ofstream& outputFile)
{
	int nrMoves = 1;

	Traversal(table, start, end, nrMoves, nrLines, nrColumns);

	for (int line = 0; line < nrLines; line++)
	{
		for (int column = 0; column < nrColumns; column++)
		{
			outputFile << table[line][column] << " ";
		}
		outputFile << std::endl;
	}

	if (!CanTraverse(table, nrLines, nrColumns))
		outputFile << "The given table cannot be traversed by the horse!\n";

	outputFile.close();
}

int main()
{
	std::ifstream inputFile("HorseProblem.in");
	std::ofstream outputFile("HorseProblem.out");
	std::vector<std::vector<int>> table;	int nrLines, nrColumns, start, end;

	Input(nrLines, nrColumns, start, end, inputFile, outputFile);
	InitializeTable(table, nrLines, nrColumns);
	PrintTraversal(table, nrLines, nrColumns, start, end, outputFile);

	return 0;
}