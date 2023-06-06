#include<iostream>
#include<fstream>

void Allocate(int*& vector, int& size, std::ifstream& inputFile, std::ofstream& outputFile)
{
	if (!inputFile.is_open())
	{
		outputFile << "There is not a file with this name! ";
		inputFile.close();
		outputFile.close();
		exit(EXIT_SUCCESS);
	}

	inputFile >> size;

	if (size <= 0)
	{
		outputFile << "The chosen size is not valid! ";
		inputFile.close();
		outputFile.close();
		exit(EXIT_SUCCESS);
	}

	vector = new int[size];

}

void ReadVector(int*& vector, const int& size, std::ifstream& inputFile, std::ofstream& outputFile)
{
	//O(n)
	inputFile >> vector[0];

	int previous = vector[0];	bool decreasing = true;

	for (int index = 1; index < size; index++)
	{
		if (inputFile.eof())
		{
			outputFile << "There are not enough elements in the vector! " << std::endl;
			inputFile.close();
			outputFile.close();
			exit(EXIT_SUCCESS);
		}

		inputFile >> vector[index];
		
		if (vector[index] > previous)
			decreasing = false;

		previous = vector[index];
	}

	if (!decreasing)
	{
		outputFile << "The given vector is not in a decreasing order! ";
		inputFile.close();
		outputFile.close();
		exit(EXIT_SUCCESS);
	}

}

int BinarySearch(int*& vector, int& element, int left, int right)
{
	//O(log n)
	int middle;
	if (left <= right)
	{
		middle = (left + right) / 2;

		if (vector[middle] == element)
			return middle;
		
		if (vector[middle] < element)
			return BinarySearch(vector, element, left, middle - 1);
		
		return BinarySearch(vector, element, middle + 1, right);

	}
	return -1;
}

void PrintPositions(int*& vector, int& size, std::ifstream& inputFile, std::ofstream& outputFile)
{
	//O(n)
	int number, m;
	std::cout << "m = ";
	std::cin >> m;

	if (size <= 0)
	{
		std::cout << "The chosen size is not valid! ";
		exit(EXIT_SUCCESS);
	}

	for (int index = 0; index < m; index++)
	{
		std::cin >> number;
		int position = BinarySearch(vector, number, 0, size - 1);
		if (position != -1)
			outputFile << "The element " << number << " is on the position number " << position << std::endl;
		else
			outputFile << "The element " << number << " is not in the vector!" << std::endl;
	}

	inputFile.close();
	outputFile.close();
}

void Deallocate(int*& vector)
{
	delete[] vector;
}

int main()
{
	std::ifstream inputFile("BinarySearch.in");
	std::ofstream outputFile("BinarySearch.out");
	int* vector;	int size;

	Allocate(vector, size, inputFile, outputFile);
	ReadVector(vector, size, inputFile, outputFile);
	PrintPositions(vector, size, inputFile, outputFile);
	Deallocate(vector);

	return 0;
}