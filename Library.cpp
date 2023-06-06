#include<iostream>
#include<fstream>
#include<string>
#include<vector>

struct book
{
	int year;
	std::string title;
};

void GetInput(std::vector<std::vector<book>>& library, int& nrShelves, int& nrBooks, std::ifstream& inputFile, std::ofstream& outputFile)
{
	if (!inputFile.is_open())
	{
		outputFile << "There is not a file with this name!";
		inputFile.close();
		outputFile.close();
		exit(EXIT_SUCCESS);
	}

	inputFile >> nrShelves >> nrBooks;

	if (nrShelves != nrBooks || nrShelves <= 0 || nrBooks <= 0)
	{
		outputFile << "The chosen size is not valid!";
		inputFile.close();
		outputFile.close();
		exit(EXIT_SUCCESS);
	}

	book myBook;
	for (int shelf = 0; shelf < nrShelves; shelf++)
	{
		std::vector<book> raftIntreg;
		for (int bookIndex = 0; bookIndex < nrBooks; bookIndex++)
		{
			inputFile >> myBook.year >> myBook.title;

			raftIntreg.push_back(myBook);
		}
		library.push_back(raftIntreg);
	}
}

int VerifyShelfOrder(const std::vector<book>& shelf, int left, int right, int option, bool sorted)
{
	if (option == 0)
	{
		if (left <= right)
		{
			int middle = (left + right) / 2;

			if ((middle == 0 && shelf[middle].year > shelf[middle + 1].year) || (middle == shelf.size() - 1 && shelf[middle - 1].year > shelf[middle].year) || (middle != 0 && shelf[middle - 1].year > shelf[middle].year) || (middle != shelf.size() - 1 && shelf[middle].year > shelf[middle + 1].year))
				sorted = false;

			VerifyShelfOrder(shelf, left, middle - 1, option, sorted);
			VerifyShelfOrder(shelf, middle + 1, right, option, sorted);
		}

		if (sorted)
			return 1;
		return 0;
	}

	if (option == 1)
	{
		if (left <= right)
		{
			int middle = (left + right) / 2;

			if ((middle == 0 && shelf[middle].title > shelf[middle + 1].title) || (middle == shelf.size() - 1 && shelf[middle - 1].title > shelf[middle].title) || (middle != 0 && shelf[middle - 1].title > shelf[middle].title) || (middle != shelf.size() - 1 && shelf[middle].title > shelf[middle + 1].title))
				sorted = false;

			VerifyShelfOrder(shelf, left, middle - 1, option, sorted);
			VerifyShelfOrder(shelf, middle + 1, right, option, sorted);
		}

		if (sorted)
			return 1;
		return 0;
	}
}

int Search(const std::vector<std::vector<book>>& library, int left, int right, bool option, int& sum)
{
	if (left <= right)
	{
		int middle = (left + right) / 2;

		sum += VerifyShelfOrder(library[middle], left, library.size() - 1, option, true);
		
		Search(library, left, middle - 1, option, sum);
		Search(library, middle + 1, right, option, sum);
	}

	return sum;
}

void PrintResults(const std::vector<std::vector<book>>& library, const int& nrShelves, const int& nrBooks, std::ifstream& inputFile, std::ofstream& outputFile)
{
	outputFile << "The number of shelves that are already ordered by: " << std::endl;

	int sum = 0;

	outputFile << "a) The year of publication is " << Search(library, 0, nrShelves - 1, 0, sum) << "!" << std::endl;

	sum = 0;
	outputFile << "b) The title of the books is " << Search(library, 0, nrShelves - 1, 1, sum) << "!";

	inputFile.close();
	outputFile.close();
}

int main()
{
	std::ifstream inputFile("Library.in");
	std::ofstream outputFile("Library.out");
	std::vector<std::vector<book>> library;
	int nrShelves, nrBooks;

	GetInput(library, nrShelves, nrBooks, inputFile, outputFile);
	PrintResults(library, nrShelves, nrBooks, inputFile, outputFile);

	return 0;
}