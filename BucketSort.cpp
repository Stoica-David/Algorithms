#include<iostream>
#include<fstream>

void Allocate(float*& vector, int& size, std::ifstream& inputFile, std::ofstream& outputFile)
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

	vector = new float[size];

}

void ReadVector(float*& vector, const int& size, std::ifstream& inputFile, std::ofstream& outputFile)
{
	//O(n)
	bool valid = true;
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

		if (vector[index] > 1 || vector[index] < 0)
			valid = false;
	}

	if (!valid)
	{
		outputFile << "The elements are not valid! ";
		inputFile.close();
		outputFile.close();
		exit(EXIT_SUCCESS);
	}

}

int FreePos(float*& vector, const int& size)
{
	//O(n)
	for (int index = 0; index < size; index++)
	{
		if (vector[index] == 0)
			return index;
	}
	return -1;
}

void CreateBuckets(float*& vector, const int& size, float**& buckets)
{
	//O(n)
	buckets = new float* [size];
	for (int index = 0; index < size; index++)
	{
		buckets[index] = new float [size];
	}

	for (int index = 0; index < size; index++)
	{
		for (int index2 = 0; index2 < size; index2++)
		{
			buckets[index][index2] = 0;
		}
	}

}

void FillBuckets(float*& vector, const int& size, float**& buckets)
{
	//O(n ^ 2)
	for (int index = 0; index < size; index++)
	{
		int numarBucket = size * vector[index];
		int pozitieLibera = FreePos(buckets[numarBucket], size);
		buckets[numarBucket][pozitieLibera] = vector[index];
	}
}

void Swap(float& element1, float& element2)
{
	float tmp = element1;
	element1 = element2;
	element2 = tmp;
}

int Partition(float*& vector, int& start, int& end)
{
	//O(n)
	float pivot = vector[end];
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

void QuickSort(float*& vector, int start, int end)
{
	//O(n log n)
	if (start < end)
	{
		int partition = Partition(vector, start, end);
		QuickSort(vector, start, partition - 1);
		QuickSort(vector, partition + 1, end);
	}
}

void BucketSort(float**& buckets, const int& size)
{
	//O(n * n log n)
	for (int index = 0; index < size; index++)
	{
		QuickSort(buckets[index], 0, size - 1);
	}
}

void MergeBuckets(float**& buckets, const int& size, float*& sortedVector)
{
	//O(n ^ 2)
	sortedVector = new float[size];

	int position = 0;
	for (int index = 0; index < size; index++)
	{
		for (int index2 = 0; index2 < size; index2++)
		{
			if (buckets[index][index2] != 0)
			{
				sortedVector[position] = buckets[index][index2];
				position++;
			}
		}
	}
}

void PrintVector(float*& vector, const int& size, std::ifstream& inputFile, std::ofstream& outputFile)
{
	//O(n)
	for (int index = 0; index < size; index++)
	{
		outputFile << vector[index] << " ";
	}
}

void Deallocate(float*& vector)
{
	delete[] vector;
}

int main()
{
	float* vector, ** buckets;	int size;
	std::ifstream inputFile("BucketSort.in");
	std::ofstream outputFile("BucketSort.out");

	Allocate(vector, size, inputFile, outputFile);
	ReadVector(vector, size, inputFile, outputFile);
	CreateBuckets(vector, size, buckets);
	FillBuckets(vector, size, buckets);
	BucketSort(buckets, size);
	MergeBuckets(buckets, size, vector);
	PrintVector(vector, size, inputFile, outputFile);
	Deallocate(vector);

	return 0;
}