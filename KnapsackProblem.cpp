#include<iostream>
#include<fstream>
#include<vector>
#include<iomanip>

struct object
{
	float weight, value, profit;
};

void ReadVector(std::vector<object>& objects, int& knapsackWeight, std::ifstream& inputFile, std::ofstream& outputFile)
{
	if (!inputFile.is_open())
	{
		outputFile << "There is not a file with this name!";
		inputFile.close();
		outputFile.close();
		exit(EXIT_SUCCESS);
	}

	int size;
	inputFile >> size;

	if (size <= 0)
	{
		outputFile << "The chosen size is not valid!";
		inputFile.close();
		outputFile.close();
		exit(EXIT_SUCCESS);
	}

	object current;
	for (int index = 0; index < size; index++)
	{
		if (inputFile.eof())
		{
			outputFile << "There are not enough elements in the vector!";
			inputFile.close();
			outputFile.close();
			exit(EXIT_SUCCESS);
		}

		inputFile >> current.value >> current.weight;

		objects.push_back(current);
	}

	inputFile >> knapsackWeight;

	if (knapsackWeight <= 0)
	{
		outputFile << "The chosen weight is not valid!";
		inputFile.close();
		outputFile.close();
		exit(EXIT_SUCCESS);
	}

	inputFile.close();
}

bool Comparator(object& object1, object& object2)
{
	object1.profit = (object1.value / object1.weight);

	object2.profit = (object2.value / object2.weight);

	return object1.profit >= object2.profit;
}

void swap(object& object1, object& object2)
{
	object tmp = object1;
	object1 = object2;
	object2 = tmp;
}

int Partition(std::vector<object>& objects, int left, int right)
{
	object pivot = objects[right];
	int index = left;
	for (int counter = left; counter <= right; counter++)
	{
		if (Comparator(objects[counter], pivot))
		{
			swap(objects[counter], objects[index]);
			index++;
		}
	}

	return index - 1;
}

void QuickSort(std::vector<object>& objects, int left, int right)
{
	if (left < right)
	{
		int partition = Partition(objects, left, right);

		QuickSort(objects, left, partition - 1);
		QuickSort(objects, partition + 1, right);
	}
}

void MaxProfit(std::vector<object>& objects, int& knapsackWeight, std::ofstream& outputFile)
{
	QuickSort(objects, 0, objects.size() - 1);

	float maxProfit = 0; int index = 0;

	while (knapsackWeight && index < objects.size())
	{
		if (objects[index].weight <= knapsackWeight)
		{
			maxProfit += objects[index].value;

			knapsackWeight -= objects[index].weight;
		}
		else
		{
			maxProfit += (knapsackWeight / objects[index].weight) * objects[index].value;

			knapsackWeight = 0;
		}

		index++;
	}

	outputFile << "The max profit is " << std::setprecision(4) << maxProfit << " lei!";

	outputFile.close();
}

int main()
{
	std::ifstream inputFile("KnapsackProblem.in");
	std::ofstream outputFile("KnapsackProblem.out");
	std::vector<object> objects;	int knapsackWeight;

	ReadVector(objects, knapsackWeight, inputFile, outputFile);
	MaxProfit(objects, knapsackWeight, outputFile);

	return 0;
}