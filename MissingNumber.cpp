#include<iostream>
#include<fstream>
#include<vector>

void ReadVector(std::vector<int>& vector, std::ifstream& inputFile, std::ofstream& outputFile)
{
	if (!inputFile.is_open())
	{
		outputFile << "There is not a file with this name! ";
		inputFile.close();
		outputFile.close();
		exit(EXIT_SUCCESS);
	}

	int size;
	inputFile >> size;
	size--;

	if (size <= 0)
	{
		outputFile << "The chosen size is not valid!";
		inputFile.close();
		outputFile.close();
		exit(EXIT_SUCCESS);
	}

	int element;
	for (int index = 0; index < size; index++)
	{
		if (inputFile.eof())
		{
			outputFile << "There are not enough elements in the vector!";
			inputFile.close();
			outputFile.close();
			exit(EXIT_SUCCESS);
		}

		inputFile >> element;
		vector.push_back(element);

		if (element < 0 || (index != 0 && vector[index] == vector[index - 1]) || element > size)
		{
			outputFile << "The elements are not valid!";
			inputFile.close();
			outputFile.close();
			exit(EXIT_SUCCESS);
		}
	}
}

int NrLowerElements(const std::vector<int>& vector, int element)
{
	int number = 0;
	for (int index = 0; index < vector.size(); index++)
		if (vector[index] < element)
			number++;

	return number;
}

int SearchMissingNumber(const std::vector<int>& vector, int left, int right)
{
	if(left <= right)
	{
		
		int middle = (right + left) / 2;

		int nrLess = NrLowerElements(vector, middle);
		
		int nrLessPrevious = NrLowerElements(vector, middle - 1);

		if (nrLess < middle && nrLessPrevious == middle - 1)
		{
				return middle - 1;
		}
		if (nrLess < middle)
		{
			return SearchMissingNumber(vector, left, middle - 1);
		}
		else
		{
			return SearchMissingNumber(vector, middle + 1, right);
		}
	}

	return left;
}

void PrintMissingNumber(const std::vector<int>& vector, std::ifstream& inputFile, std::ofstream& outputFile)
{
	outputFile << "The missing number is " << SearchMissingNumber(vector, 0, vector.size() - 1) << "!";

	inputFile.close();
	outputFile.close();
}

int main()
{
	std::ifstream inputFile("MissingNumber.in");
	std::ofstream outputFile("MissingNumber.out");
	std::vector<int> vector;

	ReadVector(vector, inputFile, outputFile);
	PrintMissingNumber(vector, inputFile, outputFile);

	return 0;
}