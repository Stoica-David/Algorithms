#include<iostream>
#include<vector>

void ReadMatrix(std::vector<std::vector<int>>& matrix, int& nrLines, int& nrColumns)
{
	std::cout << "Give the nr of lines and columns: ";
	std::cin >> nrLines >> nrColumns;

	if (nrLines <= 0 || nrLines > 100 || nrColumns <= 0 || nrColumns > 100)
	{
		std::cout << "The chosen size is not valid!" << std::endl;
		exit(EXIT_SUCCESS);
	}

	std::cout << "Give the elements of the matrix: " << std::endl;

	int element;    bool valid = true;
	for (int line = 0; line < nrLines; line++)
	{
		std::vector<int> lineVector;
		for (int column = 0; column < nrColumns; column++)
		{
			std::cout << "matrix[" << line << "][" << column << "] = ";
			std::cin >> element;
			lineVector.push_back(element);
			if (element < 0 || element > 1000)
				valid = false;
		}
		matrix.push_back(lineVector);
	}
	std::cout << std::endl;

	if (!valid)
	{
		std::cout << "The elements of the matrix are not in the [0, 1000] range!" << std::endl;
		exit(EXIT_SUCCESS);
	}

	std::cout << "Initial matrix: " << std::endl;
	for (int line = 0; line < nrLines; line++)
	{
		for (int column = 0; column < nrColumns; column++)
		{
			std::cout << matrix[line][column] << " ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}
 
void PrintMatrix(const std::vector<std::vector<int>>& matrix, const int& nrLines, const int& nrColumns)
{
	std::cout << "Elements: " << std::endl;

	for (int counter = 0; counter < nrLines; counter++)
	{
		if (counter % 2 == 1)
		{
			int column = 0, line = counter;
			while (line >= 0)
			{
				std::cout << matrix[line][column] << " ";
				column++;
				line--;
			}
		}
		
		if (counter % 2 == 0)
		{
			int column = counter, line = 0;
			while (column >= 0)
			{
				std::cout << matrix[line][column] << " ";
				line++;
				column--;
			}
		}
	}
	if (nrLines % 2 == 0)
	{
		for (int counter = 1; counter < nrLines; counter++)
		{
			if (counter % 2 == 0)
			{
				int column = counter, line = nrLines - 1;
				while (line >= counter)
				{
					std::cout << matrix[line][column] << " ";
					column++;
					line--;
				}
			}

			if (counter % 2 == 1)
			{
				int column = nrColumns - 1, line = counter;
				while (column >= counter)
				{
					std::cout << matrix[line][column] << " ";
					line++;
					column--;
				}
			}
		}
	}
	else
	{
		for (int counter = 1; counter < nrLines; counter++)
		{
			if (counter % 2 == 1)
			{
				int column = counter, line = nrLines - 1;
				while (line >= counter)
				{
					std::cout << matrix[line][column] << " ";
					column++;
					line--;
				}
			}

			if (counter % 2 == 0)
			{
				int column = nrColumns - 1, line = counter;
				while (column >= counter)
				{
					std::cout << matrix[line][column] << " ";
					line++;
					column--;
				}
			}
		}
	}
}

int main()
{
	std::vector<std::vector<int>> matrix;
	int nrLines, nrColumns;

	ReadMatrix(matrix, nrLines, nrColumns);
	PrintMatrix(matrix, nrLines, nrColumns);
	
	return 0;
}