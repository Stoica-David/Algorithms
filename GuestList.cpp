#include<iostream>
#include<fstream>
#include<vector>
#include<algorithm>

struct person
{
	int personIndex, friendIndex;
};

bool ComparatorPersonIndex(person guest1, person guest2)
{
	return guest1.personIndex < guest2.personIndex;
}

void ReadList(std::vector<person>& guestList, std::ifstream& inputFile, std::ofstream& outputFile)
{
	if (!inputFile.is_open())
	{
		outputFile << "There is not a file with this name!\n";
		inputFile.close();
		outputFile.close();
		exit(EXIT_SUCCESS);
	}

	person guest;
	while (!inputFile.eof())
	{
		inputFile >> guest.personIndex >> guest.friendIndex;

		if (guest.personIndex < 0 || guest.friendIndex < 0)
		{
			outputFile << "There are non valid values on the list!\n";
			inputFile.close();
			outputFile.close();
			exit(EXIT_SUCCESS);
		}

		guestList.push_back(guest);

		guestList.push_back({ guest.friendIndex, guest.personIndex });
	}
}

void SortList(std::vector<person>& guestList)
{
	std::sort(guestList.begin(), guestList.end(), ComparatorPersonIndex);
}

int MaxList(const std::vector<person>& guestList)
{
	int maximum = guestList[0].personIndex;

	for (int index = 0; index < guestList.size(); index++)
	{
		if (guestList[index].personIndex > maximum)
			maximum = guestList[index].personIndex;
	}

	return maximum;
}

std::vector<person> NumberGuests(std::vector<person>& guestList)
{
	std::vector<person> partyGuests;

	SortList(guestList);

	int maximum = MaxList(guestList), nrAppearances = 0, valueIndex = 0;

	for (int value = 1; value <= maximum; value++)
	{
		nrAppearances = 0;

		for (int index = 0; index < guestList.size(); index++)
		{
			if (guestList[index].personIndex == value)
			{
				nrAppearances++;
				valueIndex = index;
			}
		}

		if (nrAppearances >= 5 && nrAppearances <= maximum - 5)
			partyGuests.push_back(guestList[valueIndex]);
	}

	return partyGuests;
}

void PrintGuests(std::vector<person>& guestList, std::ifstream& inputFile, std::ofstream& outputFile)
{
	std::vector<person> partyGuests;

	partyGuests = NumberGuests(guestList);

	for (int index = 0; index < partyGuests.size(); index++)
	{
		outputFile << "At the party " << partyGuests[index].personIndex << " will come!" << std::endl;
	}

	inputFile.close();
	outputFile.close();
}

int main()
{
	std::ifstream inputFile("GuestList.in");
	std::ofstream outputFile("GuestList.out");
	std::vector<person> guestList;

	ReadList(guestList, inputFile, outputFile);
	PrintGuests(guestList, inputFile, outputFile);

	return 0;
}