#include<iostream>
#include<vector>

void ReadVector(std::vector<int>& vector, long int number)
{
	vector.clear();
	int size = 1;
	while (number)
	{
		vector.push_back(number % 10);
		number /= 10;
		size++;
	}
}

int Reverse(int number) {
	int reverse = 0;
	while (number) {
		reverse = reverse * 10 + number % 10;
		number = number / 10;
	}
	return reverse;
}

int NrDigits(int number)
{
	int nrDigits = 0;
	while (number)
	{
		number /= 10;
		nrDigits++;
	}
	return nrDigits;
}

void Multiply(std::vector<int>& vector, int number) 
{
	int transport = 0, digit, product;
	for (int index = vector.size() - 1; index >= 0; index--)
	{
		 product = (number * vector[index]) + transport;
		if (product > 9)
		{
			vector[index] = product % 10;
			transport = (product / 10) % 10;
		}
		else
		{
			vector[index] = product;
			transport = 0;
		}
 	}
	if (product > 9)
		vector.insert(vector.begin(), 1);
}

void PrintVector(std::vector<int> vector)
{
	for (int index = 0; index < vector.size(); index++)
	{
		std::cout << vector[index];
	}
	std::cout << std::endl;
}

int main()
{
	long int n; int size, multiplier;	std::vector<int> vector;
	std::cout << "Give a number: "; std::cin >> n;
	srand(time(NULL));
	multiplier = rand() % 9 + 1;
	ReadVector(vector, Reverse(n));
	Multiply(vector, multiplier);
	std::cout << n << " * " << multiplier << " = ";
	PrintVector(vector);
	return 0;
}