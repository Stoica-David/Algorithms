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
	}

	vector = new int[size];
}

void ReadVector(int*& vector, const int& size, std::ifstream& inputFile, std::ofstream& outputFile)
{
	//O(n)
	for (int index = 0; index < size; index++)
	{
		if (inputFile.eof())
		{
			outputFile << "There are not enough elements in the vector! ";
			inputFile.close();
			outputFile.close();
		}
		inputFile >> vector[index];
	}
}

bool VerifyAscendingOrder(int*& vector, const int& size, int& counter, int& position)
{
	//O(n)
	int previous = vector[0];
	counter = 0;
	for (int index = 1; index < size; index++)
	{
		if (vector[index] < previous)
		{
			counter++;
			position = index;
		}
		previous = vector[index];
	}
	if(counter == 0)
		return true;
	return false;
}

void InsertElement(int*& vector, int*& newVector, const int& size, int element)
{
	//O(n)
	int position = size - 1;
	for (int index = 0; index < size; index++)
	{
		if (vector[index] > element)
		{
			position = index;
			break;
		}
	}

	newVector = new int[size + 1];

	for (int index = 0; index < position; index++)
	{
		newVector[index] = vector[index];
	}

	newVector[position] = element;

	for (int index = 0; index < size - position; index++)
	{
		newVector[index + position + 1] = vector[index + position];
	}
}

void EliminateElement(int*& vector, int*& newVector, const int& size, int position)
{
	//O(n)
	newVector = new int[size - 1];
	for (int index = 0; index < position; index++)
	{
		newVector[index] = vector[index];
	}

	for (int index = 0; index < size - 1 - position; index++)
	{
		newVector[index + position] = vector[index + position
			+ 1];
	}
}

void PrintVector(int*& vector, const int& size, std::ifstream& inputFile, std::ofstream& outputFile)
{
	//O(n)
	for (int index = 0; index < size; index++)
	{
		outputFile << vector[index] << " ";
	}

	inputFile.close();
	outputFile.close();
}

void Deallocate(int*& vector, const int& size)
{
	delete[] vector;
}

void IdentifyCase(int*& vector, int*& newVector, const int& size, std::ifstream& inputFile, std::ofstream& outputFile)
{
	int counter, position;
	bool orderedVector = VerifyAscendingOrder(vector, size, counter, position);
	if (orderedVector)
	{
		int element;
		inputFile >> element;
		InsertElement(vector, newVector, size, element);
		PrintVector(newVector, size + 1, inputFile, outputFile);
		Deallocate(newVector, size + 1);
	}
	else if (counter == 1)
	{
		EliminateElement(vector, newVector, size, position - 1);
		PrintVector(newVector, size - 1, inputFile, outputFile);
		Deallocate(newVector, size - 1);
	}
	else
	{
		outputFile << "There are more elements in the vector that mess up the ascending order! ";
	}

	inputFile.close();
	outputFile.close();
}

int main()
{
	std::ifstream inputFile("InsertEfficiently.in");
	std::ofstream outputFile("InsertEfficiently.out");
	int* vector,* newVector;	int size;

	Allocate(vector, size, inputFile, outputFile);
	ReadVector(vector, size, inputFile, outputFile);
	IdentifyCase(vector, newVector, size, inputFile, outputFile);
	Deallocate(vector, size);
	return 0;
}