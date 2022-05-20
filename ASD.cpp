// ASD.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <time.h>
#include <vector>
#include <string>
#include <ctime>



void randomizeNumbers() {
	std::ofstream outdata;

	srand(time(NULL));
	int iSecret = rand() % 100 + 1;

	outdata.open("numbers.txt");
	for (int i = 0; i < 300000; i++) {
		int iSecret = rand() % 100000 + 1;
		outdata << iSecret << ",";
	}
	outdata.close();
}

std::vector<int> retrieveArray(std::string path) {
	std::vector<int> ints;
	std::string number = "";
	std::ifstream file;

	file.open(path, std::ios::in);

	if (file.good()) {
		std::string line;
		file >> line;
		for (int i = 0; i < line.length(); i++) {
			if (line[i] != ',') {
				number += line[i];
			}
			else
			{
				ints.push_back(std::stoi(number));
				number = "";
			}
		}
	}
	else {
		std::cerr << "error";
		throw std::invalid_argument("Cos nie tak z tablica");
	}

	return ints;
}

void saveFinal(std::string filename, std::vector<int> sorted) {
	std::ofstream outdata;
	outdata.open(filename);

	for (int i = 0; i < sorted.size(); i++) {
		outdata << sorted[i] << ",";
	}
	outdata.close();
}

void heapify(std::vector<int>& numbs, int size, int i) {
	int biggest = i;
	int l = 2 * i + 1;
	int r = 2 * i + 2;
	if (l < size && numbs[l] > numbs[biggest])
	{
		biggest = l;
	}

	if (r < size && numbs[r] > numbs[biggest])
	{
		biggest = r;
	}

	if (biggest != i) {
		{
			std::swap(numbs[i], numbs[biggest]);
			heapify(numbs, size, biggest);
		}

	}
}

void heapSort(std::vector<int>& numbs, int size) {
	for (int i = size / 2 - 1; i >= 0; i--)
		heapify(numbs, size, i);

	for (int i = size - 1; i > 0; i--) {
		std::swap(numbs[0], numbs[i]);

		heapify(numbs, i, 0);
	}
}

int lomutoPartition(std::vector<int>& numbs, int low, int high) {
	int x = numbs[high];
	int i = low - 1;
	for (int j = low; j < high; j++) {
		if (x >= numbs[j]) {
			i++;
			std::swap(numbs[j], numbs[i]);
		}
	}
	std::swap(numbs[i + 1], numbs[high]);
	return i + 1;
}

void lomutoQS(std::vector<int>& numbs, int low, int high) {
	if (low < high) {
		int piv = lomutoPartition(numbs, low, high);
		lomutoQS(numbs, low, piv - 1);
		lomutoQS(numbs, piv + 1, high);
	}
}

void mergeSplitted(std::vector<int>& numbs, int low, int high) {

	int mid = (low + high) / 2;
	int k = low;
	int i = (high + low) / 2 + 1;

	std::vector<int> temparr;

	while (k <= mid && i <= high) {

		if (numbs[k] >= numbs[i]) {

			temparr.push_back(numbs[i]);
			i++;
		}
		else
		{

			temparr.push_back(numbs[k]);
			k++;
		}

	}
	while (k <= mid) {
		temparr.push_back(numbs[k]);
		k++;

	}
	while (i <= high) {
		temparr.push_back(numbs[i]);
		i++;

	}

	for (int z = 0; low <= high; low++, z++)
	{
		numbs[low] = temparr[z];
	}
}

void mergeSort(std::vector<int>& numbs, int low, int high) {
	if (low < high) {
		mergeSort(numbs, low, (low + high) / 2);
		mergeSort(numbs, (low + high) / 2 + 1, high);
		mergeSplitted(numbs, low, high);
	}
}
		
void improvedBubbleSort(std::vector<int>& numbs) {
	bool WasChange;
	for (int i = numbs.size() - 1; i > 0; i--) {
		WasChange = false;
		for (int j = 0; j < numbs.size() - 1; j++) {
			if (numbs[j] > numbs[j + 1]) {
				std::swap(numbs[j], numbs[j + 1]);
				WasChange = true;
			}
		}
		if (WasChange == false)
		{
			return;
		}
	}
}

int main()
{
	int choice;
	std::string path;
	
	std::cout << "1-Random Numbers\n2-Sorted Numbers\n3-Backward Sorted Numbers\nInput:";
	std::cin >> choice;
	switch (choice) {
	case 1:
		path = "numbers.txt";
		break;
	case 2:
		path = "SortedNumbers.txt";
		break;
	case 3:
		path = "ReverseSorted.txt";
		break;
	default:
		throw std::invalid_argument("Zly wybor");
		break;
	}
	std::vector<int> numbers = retrieveArray(path);

	std::cout << "1-Heapsort\n2-MergeSort\n3-Quicksort\n4-Bubblesort";
	std::cin >> choice;

	switch (choice) {
	case 1:
		clock_t begin = clock();
		heapSort(numbers, numbers.size());
		clock_t finish = clock();
		saveFinal("heapSort.txt", numbers);
		std::cout << "Time:" << double(finish - begin) / CLOCKS_PER_SEC;
		break;
	case 2:
		clock_t begin = clock();
		lomutoQS(numbers, 0, numbers.size() - 1);
		clock_t finish = clock();
		saveFinal("LomutoQuickSort.txt", numbers);
		std::cout << "Time:" << double(finish - begin) / CLOCKS_PER_SEC;
		break;
	case 3:
		clock_t begin = clock();
		mergeSort(numbers, 0, numbers.size() - 1);
		clock_t finish = clock();
		saveFinal("MergeSort.txt", numbers);
		std::cout << "Time:" << double(finish - begin) / CLOCKS_PER_SEC;
		break;
	case 4:
		clock_t begin = clock();
		improvedBubbleSort(numbers);
		clock_t finish = clock();
		saveFinal("ImprovedBubbleSort.txt", numbers);
		std::cout << "Time:" << double(finish - begin) / CLOCKS_PER_SEC;
		break;
	default:
		throw std::invalid_argument("Zly wybor");
		break;
	}


	return 0;
}
