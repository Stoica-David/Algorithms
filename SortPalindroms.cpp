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
		outputFile << "The chosen size is not valid!";
		inputFile.close();
		outputFile.close();
		exit(EXIT_SUCCESS);
	}

	vector = new int[size];

}

void ReadVector(int*& vector, const int& size, std::ifstream& inputFile, std::ofstream& outputFile)
{
	for (int index = 0; index < size; index++)
	{
		if (inputFile.eof())
		{
			outputFile << "There are not enough elements in the vector!";
			inputFile.close();
			outputFile.close();
			exit(EXIT_SUCCESS);
		}

		inputFile >> vector[index];
	}

}

bool Palindrome(int& number)
{
	int numberCopy = number, reverse = 0;
	if (number < 10)
		return true;

	while (numberCopy)
	{
		reverse = reverse * 10 + numberCopy % 10;
		numberCopy /= 10;
	}

	if (number == reverse)
		return true;
	return false;
}

int Pivot(int*& vector,int& start, int& end)
{
	int counter = 0;
	for (int index = end; index >= start; index--)
	{
		if (Palindrome(vector[index]))
			return index;
	}
}

void Swap(int& element1, int& element2)
{
	if(Palindrome(element1) && Palindrome(element2))
	{
		int tmp = element1;
		element1 = element2;
		element2 = tmp;
	}
}

int Partition(int*& vector, const int& size, int& start, int& end, int callNumber)
{
	callNumber++;
	int position = Pivot(vector, start, end);
	int pivot = vector[position];
	std::cout << pivot << std::endl;
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

void QuickSort(int*& vector, const int& size, int start, int final)
{
	//O(n log n)
	if (start < final)
	{
		int partition = Partition(vector, size, start, final, 0);
		QuickSort(vector, size, start, partition - 1);
		QuickSort(vector, size, partition + 1, final);
	}
}

void PrintVector(int*& vector, const int& size, std::ifstream& inputFile, std::ofstream& outputFile)
{
	for (int index = 0; index < size; index++)
	{
		outputFile << vector[index]  << " ";
	}

	delete[] vector;
}

int main()
{
	std::ifstream InputFile("SortPalindroms.in");
	std::ofstream outputFile("SortPalindroms.out");
	int* vector;	int size;

	Allocate(vector, size, InputFile, outputFile);
	ReadVector(vector, size, InputFile, outputFile);
	QuickSort(vector, size, 0, size - 1);
	PrintVector(vector, size, InputFile, outputFile);

	return 0;
}