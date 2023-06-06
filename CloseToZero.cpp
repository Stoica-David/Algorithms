#include<iostream>
#include<fstream>
#include<cmath>

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

void Swap(int& element1, int& element2)
{
	int tmp = element1;
	element1 = element2;
	element2 = tmp;
}

int Partition(int*& vector, int& start, int& end)
{
	int pivot = vector[end];
	int index = start;
	for (int counter = start; counter <= end; counter++)
	{
		if (vector[counter] <= pivot)
		{
			Swap(vector[index], vector[counter]);
			index++;
		}
	}
	return index - 1;
}

void QuickSort(int*& vector, int start, int end)
{
	//O(n log n)
	if (start < end)
	{
		int partition = Partition(vector, start, end);
		QuickSort(vector, start, partition - 1);
		QuickSort(vector, partition + 1, end);
	}
}

int NrPositiveElements(int*& vector, const int& size)
{
	//O(n)
	int counter = 0;
	for (int index = 0; index < size; index++)
	{
		if (vector[index] > 0)
			counter++;
	}

	return counter;
}

int NrNegativeElements(int*& vector, const int& size)
{
	//O(n)
	int counter = 0;
	for (int index = 0; index < size; index++)
	{
		if (vector[index] < 0)
			counter++;
	}

	return counter;
}

void NoNegatives(int*& vector, const int& size, int& minimum1, int& minimum2)
{
	//O(n)
	minimum1 = vector[0];
	minimum2 = vector[1];
	for (int index = 2; index < size; index++)
	{
		if (vector[index] < minimum2)
			minimum2 = vector[index];
		if (vector[index] < minimum2 && vector[index] < minimum1)
		{
			minimum2 = minimum1;
			minimum1 = vector[index];
		}
	}
}

void NoPositives(int*& vector, const int& size, int& maximum1, int& maximum2)
{
	//O(n)
	maximum1 = vector[0];
	maximum2 = vector[1];
	for (int index = 2; index < size; index++)
	{
		if (vector[index] <= maximum2 && vector[index] > maximum1)
			maximum1 = vector[index];
		if (vector[index] > maximum2 && vector[index] > maximum1)
		{
			maximum1 = maximum2;
			maximum2 = vector[index];
		}
	}
}

void FindElements(int*& vector, const int& size, std::ifstream& inputFile, std::ofstream& outputFile)
{
	//O(n log n)
	int element1 = vector[0], element2 = vector[1], left = 0, right = size - 1, sum, minimum = vector[0] + vector[1];

	if (NrNegativeElements(vector, size) == 0)
		NoNegatives(vector, size, element2, element1);
	else if (NrPositiveElements(vector, size) == 0)
		NoPositives(vector, size, element2, element1);
	else
	{
		QuickSort(vector, 0, size - 1);

		while (left < right)
		{
			sum = vector[left] + vector[right];

			if (abs(sum) < abs(minimum) || sum == 0)
			{
				element1 = vector[left];
				element2 = vector[right];
				minimum = sum;
			}

			if (sum > 0)
				right--;

			if (sum < 0)
				left++;
		}
	}

	outputFile << "The elements of which sum is the closest to zero are " << element1 << " and " << element2 << ", with their sum being " << element1 + element2 << std::endl;

	delete[] vector;

	inputFile.close();
	outputFile.close();
}

int main()
{
	std::ifstream inputFile("CloseToZero.in");
	std::ofstream outputFile("CloseToZero.out");
	int* vector, size;

	ReadVector(vector, size, inputFile, outputFile);
	FindElements(vector, size, inputFile, outputFile);

	return 0;
}