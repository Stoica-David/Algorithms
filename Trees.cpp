#include<iostream>
#include<fstream>
#include<vector>

void Inputs(std::vector<std::vector<int>>& orchard, int& length, int& width, std::ifstream& inputFile, std::ofstream& outputFile)
{
	if (!inputFile.is_open())
	{
		outputFile << "There is not a file with this name!";
		inputFile.close();
		outputFile.close();
		exit(EXIT_SUCCESS);
	}

	inputFile >> length >> width;

	if (length <= 0 || width <= 0)
	{
		outputFile << "The chosen size is not valid!";
		inputFile.close();
		outputFile.close();
		exit(EXIT_SUCCESS);
	}

	int nrFruits;
	for (int line = 0; line < length; line++)
	{
		std::vector<int> row;
		for (int column = 0; column < width; column++)
		{
			inputFile >> nrFruits;
			row.push_back(nrFruits);

			if (nrFruits < 0)
			{
				outputFile << "The elements are not valid!";
				inputFile.close();
				outputFile.close();
				exit(EXIT_SUCCESS);
			}

		}
		orchard.push_back(row);
	}
}

bool IsPrime(int element)
{
	if (element == 2)
		return true;
	if (element <= 1)
		return false;
	for (int divisor = 2; divisor < element; divisor++)
	{
		if (element % divisor == 0)
			return false;
	}

	return true;
}

int SearchPrimeNumbers(const std::vector<int>& vector, int left, int right, int& sum)
{
	int middle;
	if (left <= right)
	{
		middle = (left + right) / 2;

		if (IsPrime(vector[middle]))
		{
			sum += vector[middle];
		}
		SearchPrimeNumbers(vector, left, middle - 1, sum);
		SearchPrimeNumbers(vector, middle + 1, right, sum);

	}
	return sum;
}

int FruitSum(const std::vector<std::vector<int>>& orchard, const int& width, int left, int right, int& sum)
{
	if (left <= right)
	{
		int middle = (left + right) / 2;

		int currentSum = 0;
		sum += SearchPrimeNumbers(orchard[middle], 0, width - 1, currentSum);

		FruitSum(orchard, width, left, middle - 1, sum);
		FruitSum(orchard, width, middle + 1, right, sum);
	}

	return sum;
}

void PrintSum(const std::vector<std::vector<int>>& orchard, const int& length, const int& width, std::ifstream& inputFile, std::ofstream& outputFile)
{
	int sum = 0;
	FruitSum(orchard, width, 0, length - 1, sum);
	outputFile << "The sum of the fruits for the trees that have a prime number of fruits is " << sum << "!";

	inputFile.close();
	outputFile.close();
}

int main()
{
	std::ifstream inputFile("Trees.in");
	std::ofstream outputFile("Trees.out");
	std::vector<std::vector<int>> orchard;	int length, width;

	Inputs(orchard, length, width, inputFile, outputFile);
	PrintSum(orchard, length, width, inputFile, outputFile);


	return 0;
}