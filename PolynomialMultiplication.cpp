#include<iostream>
#include<fstream>

void Validation(const int& polynomialDegree, std::ifstream& inputFile, std::ofstream& outputFile)
{
	if (polynomialDegree < 0)
	{
		outputFile << "The chosen degree is not valid!\n";
		inputFile.close();
		outputFile.close();
		exit(EXIT_SUCCESS);
	}
}

void Inputs(int*& Polynomial1, int*& Polynomial2, int& degree1, int& degree2, std::ifstream& inputFile, std::ofstream& outputFile)
{
	if (!inputFile.is_open())
	{
		outputFile << "There is not a file with this name!";
		inputFile.close();
		outputFile.close();
		exit(EXIT_SUCCESS);
	}

	inputFile >> degree1;
	Validation(degree1, inputFile, outputFile);
	Polynomial1 = new int[degree1];

	for (int index = 0; index < degree1; index++)
	{
		if (inputFile.eof())
		{
			outputFile << "There are not enough elements in the vector!";
			inputFile.close();
			outputFile.close();
			exit(EXIT_SUCCESS);
		}

		inputFile >> Polynomial1[index];
	}

	inputFile >> degree2;
	Validation(degree2, inputFile, outputFile);
	Polynomial2 = new int[degree2];


	for (int index = 0; index < degree2; index++)
	{
		if (inputFile.eof())
		{
			outputFile << "There are not enough elements in the vector!";
			inputFile.close();
			outputFile.close();
			exit(EXIT_SUCCESS);
		}

		inputFile >> Polynomial2[index];
	}

}

int EqualizeDegree(int*& Polynomial1, int*& Polynomial2, int& degree1, int& degree2)
{
	int maxDegree = std::max(degree1, degree2);

	if (maxDegree == degree1)
	{
		int* polynomial2Copy = Polynomial2;

		Polynomial2 = new int[degree1];

		for (int index = 0; index < degree2; index++)
		{
			Polynomial2[index] = polynomial2Copy[index];
		}

		for (int index = degree2; index < degree1; index++)
		{
			Polynomial2[index] = 0;
		}

		delete[] polynomial2Copy;

		return degree1;
	}
	else
	{
		int* polynomial1Copy = Polynomial1;

		Polynomial1 = new int[degree2];

		for (int index = 0; index < degree1; index++)
		{
			Polynomial1[index] = polynomial1Copy[index];
		}

		for (int index = degree1; index < degree2; index++)
		{
			Polynomial1[index] = 0;
		}

		delete[] polynomial1Copy;

		return degree2;
	}
}

int* SumPolynomials(int* Polynomial1, int* Polynomial2, int& degree)
{
	int maxDegree = 2 * degree;

	int* polynomialsSum = new int[maxDegree];

	for (int index = 0; index < maxDegree; index++)
	{
		polynomialsSum[index] = Polynomial1[index] + Polynomial2[index];
	}

	return polynomialsSum;
}

void PrintPolynomial(int*& Polynomial, const int& degree, std::ifstream& inputFile, std::ofstream& outputFile)
{
	for (int index = 0; index < degree - 1; index++)
	{
		if (Polynomial[index] != 0)
		{
			if (index == 0)
				outputFile << Polynomial[index] << " + ";
			else if (index != degree - 2)
				outputFile << Polynomial[index] << " * X^" << index << " + ";
			else
				outputFile << Polynomial[index] << " * X^" << index;
		}
	}

	if (Polynomial[degree - 1] != 0)
		outputFile << " + " << Polynomial[degree - 1] << " * X^" << degree - 1;

	outputFile << std::endl;

	delete[] Polynomial;
	inputFile.close();
	outputFile.close();
}

int* HalvesProduct(int* product1, int* product2, int* product3, int degree)
{
	int size = (degree * 2) - 2;

	int* halvesProduct = new int[size + 1];

	for (int index = 0; index <= size; index++)
	{
		halvesProduct[index] = product3[index] - product1[index] - product2[index];
	}

	return halvesProduct;
}

int* Concatenation(int* product1, int* product2, int* product3, int degree)
{
	int size = 2 * degree + 2 * degree - 2;

	int* polynomialProduct;

	polynomialProduct = new int[size + 1];

	for (int index = 0; index <= size; index++)
	{
		polynomialProduct[index] = 0;
	}

	int index2 = 0;
	for (int index = 0; index <= (2 * degree - 2); index++)
	{
		polynomialProduct[index] = product1[index2];
		index2++;
	}

	index2 = 0;
	for (int index = degree; index <= (degree + 2 * degree - 2); index++)
	{
		polynomialProduct[index] = product3[index2] + polynomialProduct[index];
		index2++;
	}

	index2 = 0;
	for (int index = 2 * degree; index <= size; index++)
	{
		polynomialProduct[index] = product2[index2] + polynomialProduct[index];
		index2++;
	}

	return polynomialProduct;
}

int* PolynomialProduct(int* Polynomial1, int* Polynomial2, int degree)
{
	degree = (degree + 1) / 2;

	if (degree == 1)
	{
		int product1, product2, product3;

		product1 = (Polynomial1[0] * Polynomial2[0]);
		product2 = (Polynomial1[1] * Polynomial2[1]);
		product3 = (Polynomial1[0] + Polynomial1[1]) * (Polynomial2[0] + Polynomial2[1]);

		int* polynomialProduct = new int[3];

		polynomialProduct[0] = product1;
		polynomialProduct[1] = product3 - product1 - product2;
		polynomialProduct[2] = product2;

		return polynomialProduct;
	}
	else
	{
		int* firstHalfPolynomial1, * secondHalfPolynomial1, * firstHalfPolynomial2, * secondHalfPolynomial2;

		firstHalfPolynomial1 = new int[degree];
		secondHalfPolynomial1 = new int[degree];
		firstHalfPolynomial2 = new int[degree];
		secondHalfPolynomial2 = new int[degree];

		for (int index = 0; index < degree; index++)
		{
			firstHalfPolynomial1[index] = Polynomial1[index];
			secondHalfPolynomial1[index] = Polynomial1[index + (degree / 2) + 1];
			firstHalfPolynomial2[index] = Polynomial2[index];
			secondHalfPolynomial2[index] = Polynomial2[index + (degree / 2) + 1];
		}

		int* sumPolynomial1, * sumPolynomial2;

		sumPolynomial1 = new int[2 * degree];
		sumPolynomial2 = new int[2 * degree];

		sumPolynomial1 = SumPolynomials(firstHalfPolynomial1, secondHalfPolynomial1, degree);
		sumPolynomial2 = SumPolynomials(firstHalfPolynomial2, secondHalfPolynomial2, degree);

		int* product1, * product2, * product3Initial;

		product1 = new int[degree * 2 - 1];
		product2 = new int[degree * 2 - 1];
		product3Initial = new int[degree * 2 - 1];

		product1 = PolynomialProduct(firstHalfPolynomial1, firstHalfPolynomial2, degree);
		product2 = PolynomialProduct(secondHalfPolynomial1, secondHalfPolynomial2, degree);
		product3Initial = PolynomialProduct(sumPolynomial1, sumPolynomial2, degree);

		int* product3Final;

		product3Final = new int[degree * 2 - 1];

		product3Final = HalvesProduct(product1, product2, product3Initial, degree);

		int* polynomialProduct;

		polynomialProduct = new int[2 * degree];

		polynomialProduct = Concatenation(product1, product2, product3Final, degree);

		delete[] firstHalfPolynomial1, firstHalfPolynomial2, secondHalfPolynomial1, secondHalfPolynomial2, product1, product2, product3Initial, sumPolynomial1, sumPolynomial2, product3Final;

		return polynomialProduct;
	}
}


int main()
{
	std::ifstream inputFile("PolynomialMultiplication.in");
	std::ofstream outputFile("PolynomialMultiplication.out");
	int* Polynomial1, * Polynomial2, degree1, degree2;

	Inputs(Polynomial1, Polynomial2, degree1, degree2, inputFile, outputFile);
	EqualizeDegree(Polynomial1, Polynomial2, degree1, degree2);

	int* polynomialProduct = PolynomialProduct(Polynomial1, Polynomial2, degree1);

	PrintPolynomial(polynomialProduct, degree1 - 1 + degree2, inputFile, outputFile);


	return 0;
}