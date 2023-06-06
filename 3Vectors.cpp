#include<iostream>
#include<fstream>

void Allocate(int**& matrix, int& size, int& p, std::ifstream& inputFile, std::ofstream& outputFile)
{
	if (!inputFile.is_open())
	{
		std::cout << "There is no file with the given name! " << std::endl;
		inputFile.close();
		outputFile.close();
		exit(EXIT_SUCCESS);
	}

	inputFile >> size >> p;

	if (size <= 0)
	{
		outputFile << "The value of n is not valid! " << std::endl;
		inputFile.close();
		outputFile.close();
		exit(EXIT_SUCCESS);
	}

	if (p > (size * size) / 2)
	{
		outputFile << "The value of p is not valid! " << std::endl;
		inputFile.close();
		outputFile.close();
		exit(EXIT_SUCCESS);
	}

	matrix = new int* [size];
	
	//O(n)
	for (int linie = 0; linie < size; linie++)
	{
		matrix[linie] = new int[size];
	}

}

void ReadVectors(int*& Va, int*& La, int*& Ca, const int& p, std::ifstream& inputFile, std::ofstream& outputFile)
{
	Va = new int[p];
	//O(n)
	for (int index = 0; index < p; index++)
	{
		if (inputFile.eof())
		{
			outputFile << "There are not enough elements in the file! " << std::endl;
			inputFile.close();
			outputFile.close();
			exit(EXIT_SUCCESS);
		}
		inputFile >> Va[index];
	}

	La = new int[p];
	//O(n)
	for (int index = 0; index < p; index++)
	{
		if (inputFile.eof())
		{
			outputFile << "There are not enough elements in the file! " << std::endl;
			inputFile.close();
			outputFile.close();
			exit(EXIT_SUCCESS);
		}
		inputFile >> La[index];
	}

	Ca = new int[p];
	//O(n)
	for (int index = 0; index < p; index++)
	{
		if (inputFile.eof())
		{
			outputFile << "There are not enough elements in the file! " << std::endl;
			inputFile.close();
			outputFile.close();
			exit(EXIT_SUCCESS);
		}
		inputFile >> Ca[index];
	}
}

void InitializeMatrix(int**& matrix, const int& size)
{
	//O(n^2)
	for (int line = 0; line < size; line++)
	{
		for (int column = 0; column < size; column++)
		{
			matrix[line][column] = 0;
		}
	}
}

void ConstructMatrix(int**& matrix, const int& size, const int& p, int*& Va, int*& La, int*& Ca)
{
	InitializeMatrix(matrix, size);
	
	//O(n)
	for (int index = 0; index < p; index++)
	{
		matrix[La[index]][Ca[index]] = Va[index];
	}
}

void PrintMatrix(int**& matrix, const int& size, std::ifstream& inputFile, std::ofstream& outputFile)
{
	outputFile << "a) " << std::endl;
	
	//O(n^2)
	for (int line = 0; line < size; line++)
	{
		for (int column = 0; column < size; column++)
		{
			outputFile << matrix[line][column] << " ";
		}
		outputFile << std::endl;
	}
}

void ConstructVectors(int*& Va, int*& La, int*& Ca, int*& Vb, int*& Lb, int*& Cb, int*& Vc, int*& Lc, int*& Cc, const int& p, const int& size, std::ofstream& outputFile)
{		
	outputFile << "b) " << std::endl;

	
	Vc = new int[2 * p];
	
	//O(n)
	for (int index = 0; index < p; index++)
	{
		Vc[index] = Va[index];
	}

	for (int index = 0; index < p; index++)
	{
		Vc[index + p] = Vb[index];
	}

	Lc = new int[2 * p];
	for (int index = 0; index < p; index++)
	{
		Lc[index] = La[index];
	}

	for (int index = 0; index < p; index++)
	{
		Lc[index + p] = Lb[index];
	}

	Cc = new int[2 * p];
	for (int index = 0; index < p; index++)
	{
		Cc[index] = Ca[index];
	}

	for (int index = 0; index < p; index++)
	{
		Cc[index + p] = Cb[index];
	}

	int** sumMatrix;
	sumMatrix = new int* [size];
	for (int line = 0; line < size; line++)
	{
		sumMatrix[line] = new int[size];
	}

	//O(n^2)
	InitializeMatrix(sumMatrix, size);

	for (int index = 0; index < (p * 2); index++)
	{
		sumMatrix[Lc[index]][Cc[index]] += Vc[index];
	}

	for (int line = 0; line < size; line++)
	{
		for (int column = 0; column < size; column++)
		{
			outputFile << sumMatrix[line][column] << " ";
		}
		outputFile << std::endl;
	}

	outputFile.close();
}

void Deallocate(int**& matrix, const int& size, int*& Va, int*& La, int*& Ca)
{
	//O(n);
	for (int line = 0; line < size; line++)
	{
		delete[] matrix[line];
	}
	delete[] matrix;
	delete[] Va;
	delete[] La;
	delete[] Ca;

}

int main()
{
	int** matrix;	int* Va,* La,* Ca,* Vb,* Lb,* Cb, * Vc,* Lc,* Cc;
	int size, p;
	std::ifstream inputFile("3Vectors.in");
	std::ofstream outputFile("3Vectors.out");

	Allocate(matrix, size, p, inputFile, outputFile);
	ReadVectors(Va, La, Ca, p, inputFile, outputFile);
	ReadVectors(Vb, Lb, Cb, p, inputFile, outputFile);
	ConstructMatrix(matrix, size, p, Va, La, Ca);
	PrintMatrix(matrix, size, inputFile, outputFile);
	ConstructVectors(Va, La, Ca, Vb, Lb, Cb, Vc, Lc, Cc, p, size, outputFile);
	Deallocate(matrix, size, Va, La, Ca);

	return 0;
}
