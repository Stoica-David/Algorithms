#include<iostream>
#include<vector>

void ReadVector(std::vector<int>& vector, int size)
{
	vector.clear();
	int element;
	for (int index = 0; index < size; index++)
	{
		std::cin >> element;
		vector.push_back(element);
	}
	std::cout << std::endl;
}

void Merge(std::vector<int>& vector1, std::vector<int>& vector2, std::vector<int>& mergedVector)
{
	mergedVector.clear();
	int element, size1 = vector1.size(), size2 = vector2.size(), i = 0, j = 0;
	while (i < size1 && j < size2)
	{
		if (vector1[i] < vector2[j])
		{
			mergedVector.push_back(vector1[i]);
			i++;
		}
		else
		{
			mergedVector.push_back(vector2[j]);
			j++;
		}
	}
	while (i < size1)
	{
		mergedVector.push_back(vector1[i]);
		i++;
	}
	while (j < size2)
	{
		mergedVector.push_back(vector2[j]);
		j++;
	}
}

void PrintVector(std::vector<int> mergedVector)
{
	std::cout << "The two merged vectors: ";
	for (int index = 0; index < mergedVector.size(); index++)
	{
		std::cout << mergedVector[index] << " ";
	}
	std::cout << std::endl;
}

int main()
{
	std::vector<int> vector1, vector2, mergedVector;
	int m, n;
	std::cout << "n = ";
	std::cin >> n;
	std::cout << "Vector1 : ";
	ReadVector(vector1, n);
	std::cout << "m = ";
	std::cin >> m;
	std::cout << "Vector2 : ";
	ReadVector(vector2, m);
	Merge(vector1, vector2, mergedVector);
	PrintVector(mergedVector);
	return 0;
}