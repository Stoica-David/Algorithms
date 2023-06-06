#include<iostream>
#include<fstream>

void ReadVector(int*& vector, int& size, std::ifstream& inputFile, std::ofstream& outputFile)
{
 //O(n)
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

	for (int index = 0; index < size; index++)
	{
		if (inputFile.eof())
		{
			outputFile << "There are not enough elements in the vector! ";
			inputFile.close();
			outputFile.close();
			exit(EXIT_SUCCESS);

		}
		inputFile >> vector[index];
	}
}

int BinarySearch(int*& vector, int element, int left, int right)
{
  //O(log n)
	int middle;
	if (left <= right)
	{
		middle = (left + right) / 2;

		if (vector[middle] == element)
			return middle + 1;

		if (vector[middle] < element)
			return BinarySearch(vector, element, middle + 1, right);

		return BinarySearch(vector, element, left, middle - 1);
	}

	return left;
}

void InsertionSort(int*& vector, const int& size)
{
  //O(n log n)
	int current, currentPosition, index2;
	for (int index = 1; index < size; index++)
	{
		index2 = index - 1;
		current = vector[index];
		
		currentPosition = BinarySearch(vector, current, 0, index2);

		while (index2 >= currentPosition)
		{
			vector[index2 + 1] = vector[index2];
			index2--;
		}
		vector[index2 + 1] = current;
	}
}

void PrintVector(int*& vector, const int& size, std::ifstream& inputFile, std::ofstream& outputFile)
{
  //O(n log n)
	InsertionSort(vector, size);
	outputFile << "Sorted vector: ";
	for (int index = 0; index < size; index++)
	{
		outputFile << vector[index] << " ";
	}

	delete[] vector;

	inputFile.close();
	outputFile.close();
}

int main()
{
	std::ifstream inputFile("EfficientInsertionSort.in");
	std::ofstream ouputFile("EfficientInertionSort.out");
	int* vector, size;

	ReadVector(vector, size, inputFile, ouputFile);
	PrintVector(vector, size, inputFile, ouputFile);

	return 0;
}