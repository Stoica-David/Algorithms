#include<iostream>
#include<fstream>
#include<vector>

void ReadN(int& n, std::ifstream& inputFile, std::ofstream& outputFile)
{
	if (!inputFile.is_open())
	{
		outputFile << "There is not a file with this name!";
		inputFile.close();
		outputFile.close();
		exit(EXIT_SUCCESS);
	}

	inputFile >> n;

	if (n <= 0)
	{
		outputFile << "The value of n is not valid!\n";
		inputFile.close();
		outputFile.close();
		exit(EXIT_SUCCESS);
	}
}

void Multiply(std::vector<std::vector<int>>& fibonacci, std::vector<std::vector<int>>& fibonacciMatrix)
{
	int element1 = fibonacci[0][0] * fibonacciMatrix[0][0] + fibonacci[0][1] * fibonacciMatrix[1][0];
	int element2 = fibonacci[0][0] * fibonacciMatrix[0][1] + fibonacci[0][1] * fibonacciMatrix[1][1];
	int element3 = fibonacci[1][0] * fibonacciMatrix[0][0] + fibonacci[1][1] * fibonacciMatrix[1][0];
	int element4 = fibonacci[1][0] * fibonacciMatrix[0][1] + fibonacci[1][1] * fibonacciMatrix[1][1];

	fibonacci[0][0] = element1;
	fibonacci[0][1] = element2;
	fibonacci[1][0] = element3;
	fibonacci[1][1] = element4;

}

void Power(std::vector<std::vector<int>>& fibonacci, std::vector<std::vector<int>> fibonacciMatrix, const int& n)
{
	if (n <= 1)
		return;

	Power(fibonacci, fibonacciMatrix, n / 2);
	Multiply(fibonacci, fibonacci);

	if (n % 2 == 1)
	{
		Multiply(fibonacci, fibonacciMatrix);
	}
}

int NthTerm(std::vector<std::vector<int>>& fibonacci, const std::vector<std::vector<int>>& fibonacciMatrix, int n)
{
	fibonacci = { {1,1},{1,0} };
	if (n == 0)
		return 0;
	else
		Power(fibonacci, fibonacciMatrix, n);

	return fibonacci[1][0];
}

void PrintNthTerm(const int& n, std::vector<std::vector<int>>& fibonacci, std::vector<std::vector<int>>& fibonacciMatrix, std::ifstream& inputFile, std::ofstream& outputFile)
{
	outputFile << "The " << n << "-th term of the Fibonacci sequence is " << NthTerm(fibonacci, fibonacciMatrix, n) << "!";

	inputFile.close();
	outputFile.close();
}

int main()
{
	std::ifstream inputFile("NthFibonacci.in");
	std::ofstream outputFile("NthFibonacci.out");
	std::vector<std::vector<int>> fibonacci, fibonacciMatrix = { {1,1} , {1,0} };
	int n;

	ReadN(n, inputFile, outputFile);
	PrintNthTerm(n, fibonacci, fibonacciMatrix, inputFile, outputFile);
	
	return 0;
}