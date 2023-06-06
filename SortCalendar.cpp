#include <iostream>
#include <fstream>

struct data
{
    int day, month, year;
};

void Allocate(data*& datas, int& size)
{
    size = 100;

    datas = new data[size];
}

void ReadDataVector(char array[100], data*& datas, int& size, std::ifstream& inputFile, std::ofstream& outputFile)
{
    //O(n)
    if (!inputFile.is_open())
    {
        outputFile << "There is not a file with this name! ";
        inputFile.close();
        outputFile.close();
        exit(EXIT_SUCCESS);
    }

    int index = 0;
    while (!inputFile.eof())
    {
        bool valid = true;
        inputFile.getline(array, 100);
        if (strlen(array) == 10 && array[2] == '/' && array[5] == '/' && isdigit(array[0]) && isdigit(array[1]) && isdigit(array[3]) && isdigit(array[4]) && isdigit(array[6]) && isdigit(array[7]) && isdigit(array[8]) && isdigit(array[9]))
        {
            char dayArray[100];
            dayArray[0] = array[0];
            dayArray[1] = array[1];
            datas[index].day = atoi(dayArray);

            char monthArray[100];
            monthArray[0] = array[3];
            monthArray[1] = array[4];
            datas[index].month = atoi(monthArray);

            char yearArray[100];
            yearArray[0] = array[6];
            yearArray[1] = array[7];
            yearArray[2] = array[8];
            yearArray[3] = array[9];
            datas[index].year = atoi(yearArray);

            index++;
        }
    }

    size = index;

    if (index == 0)
    {
        outputFile << "There are no valid datas in the dataFile! ";
        inputFile.close();
        outputFile.close();
        exit(EXIT_SUCCESS);
    }

}

void Swap(data& element1, data& element2)
{
	data tmp = element1;
	element1 = element2;
	element2 = tmp;
}

void SwapDatas(data*& datas, int index1, int index2)
{
    if (datas[index1].year > datas[index2].year)
        Swap(datas[index1], datas[index2]);
    else if (datas[index1].year == datas[index2].year && datas[index1].month > datas[index2].month)
        Swap(datas[index1], datas[index2]);
    else if (datas[index1].year == datas[index2].year && datas[index1].month == datas[index2].month && datas[index1].day > datas[index2].day)
        Swap(datas[index1], datas[index2]);
}

int Partition(data*& datas, int& start, int& end, int dataType)
{
    int pivot, element;
    if(dataType == 2)
        pivot = datas[end].year;
    if (dataType == 1)
        pivot = datas[end].month;
    if (dataType == 0)
        pivot = datas[end].day;
    
    int index = start;
    
    for (int counter = start; counter <= end; counter++)
    {
        if (dataType == 2)
            element = datas[counter].year;
        if (dataType == 1)
            element = datas[counter].month;
        if (dataType == 0)
            element = datas[counter].day;

        if (element <= pivot)
        {
            SwapDatas(datas, index, counter);
            index++;
        }
	}
	return index - 1;
}

void QuickSort(data*& datas, int indexStart, int indexFinal, int tipData)
{
    //O(n log n)
	if (indexStart < indexFinal)
	{
		int partitie = Partition(datas, indexStart, indexFinal, tipData);
		QuickSort(datas, indexStart, partitie - 1, tipData);
		QuickSort(datas, partitie + 1, indexFinal, tipData);
	}
}

void PrintDataVector(data*& datas, const int& size, std::ifstream& inputFile, std::ofstream& outputFile)
{
    //O(n)
    for (int index = 0; index < size; index ++)
    {
        if(datas[index].month < 10)
            outputFile << datas[index].day << "/" << 0 << datas[index].month << "/" << datas[index].year << std::endl;
        else
            outputFile << datas[index].day << "/" << datas[index].month << "/" << datas[index].year << std::endl;
    }

    inputFile.close();
    outputFile.close();
}

void Deallocate(data*& datas)
{
    delete[] datas;
}

int main()
{
    std::ifstream inputFile("SortCalendar.in");
    std::ofstream outputFile("SortCalendar.out");
    data* vector;   int size; char array[100];

    Allocate(vector, size);
    ReadDataVector(array, vector, size, inputFile, outputFile);
    QuickSort(vector, 0, size - 1, 2);
    QuickSort(vector, 0, size - 1, 1);
    QuickSort(vector, 0, size - 1, 0);
    PrintDataVector(vector, size, inputFile, outputFile);
    Deallocate(vector);

    return 0;
}