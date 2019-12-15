/** 
 * RBT insertion and comparison with unordered linked list written in c++.
 * Data Structure Assignment 4
 * Written by Ritish Karki. Student ID 00676516
 * **/

#include "RBT.cpp"
#include<iostream>
#include<vector>
#include<fstream>
#include<stdlib.h>
#include<time.h>
#include<string>


#include <random>
#include <chrono>

#include "UnorderedLinkedList.hpp"
using namespace std;

// function to generate the random numbers for the files
void generateWrite(unsigned int size){

	// create a random engine
	default_random_engine URNG { };

	seed_seq::result_type seeds[] { random_device {}(), seed_seq::result_type(chrono::system_clock::now().time_since_epoch().count()) };

	// create the seed sequence
	seed_seq sseq(begin(seeds), end(seeds));

	// seed the random engine
	URNG.seed(sseq);

	// create a distribution from 0 to size inclusive
	uniform_int_distribution<unsigned> DIST(0, size);

	// generating the random numbers according to the size parameter
	const unsigned num_rnd { size };

	// open the correct file for writing
	ofstream file(to_string(size)+ ".txt");

	// skip count
	const unsigned count { 10 };

	for (size_t loop = 0; loop < num_rnd; loop++) {
		// get a random number
		unsigned num { DIST(URNG) };

		//  write to file
		file << num << endl;
	}

   	file.close();
}

// function to write to the Red Black Tree
void writeToRBTree(int size, RBTree<int>& tree){
	ifstream inFile;
	int data;

	inFile.open(to_string(size) + ".txt");

	if (!inFile) {
        cout << "Unable to open file";
        exit(1); // terminate with error
    }
    
    while (inFile >> data) {
		tree.insert(data);
    }
    
    inFile.close();
}

// function to write to the Unordered Linked List
void writeToUnorderedLinkedList(int size, UnorderedLinkedList<int>& list){
	ifstream inFile;
	int data;

	inFile.open(to_string(size) + ".txt");

	if (!inFile) {
        cout << "Unable to open file";
        exit(1); // terminate with error
    }
    
    while (inFile >> data) {
		list.insert(data);
    }
    
    inFile.close();
}

// function to select the random line from the selected file and return it
int random_line(int size) {
   	vector<string> data;
	ifstream file(to_string(size)+ ".txt");
    string line;
	string randomLine;
    while (getline(file, line)) data.push_back(line);
	randomLine = data[rand() % data.size()];

	// convert the string data to int and return
	return stoi(randomLine);
}

int main() {
	// for generating the different random number set every time
	srand(time(NULL));
	int randomNumberFromFile;
	unsigned int sizes[5] ={100,1000,10000,100000,1000000};
	RBTree<int>* tree = new RBTree<int>;
	UnorderedLinkedList<int>* list = new UnorderedLinkedList<int>;

	// index for selecting a random file from among the generted text files and writing that file to red black tree
	int randomFileToWrite = rand() % 5;

	// generate files and sizes
	cout << endl << endl<< "Generating files and filling them with random numbers" << endl << endl;
	for (int i = 0; i < 5; i++){
		string treeName;
		generateWrite(sizes[i]);
		treeName = to_string(sizes[i]) + "Tree";
	}

	// read and insert the content of the selected random file to red black tree
	cout << "Inserting contents of selected random file to Red Black Tree" << endl;
	writeToRBTree(sizes[randomFileToWrite], *tree);
	cout << "Inserting contents of selected random file to Unsorted Linked List" << endl << endl;
	// read and insert the content of the selected random file to the unordered linked list
	writeToUnorderedLinkedList(sizes[randomFileToWrite], *list);

	// get a random line from the selcted random file 
	randomNumberFromFile = random_line(sizes[randomFileToWrite]);
	cout << "Random number from file which has " << sizes[randomFileToWrite] << " elements is : " << randomNumberFromFile << endl;

	// calculating and displaying the time to search the random number in red black tree
	auto start = chrono::system_clock::now();
	tree -> search(randomNumberFromFile);
	auto end = chrono::system_clock::now();

	chrono::duration<double> elapsed_seconds = end-start;
   	time_t end_time = chrono::system_clock::to_time_t(end);
 
   	cout << "Time to search " << randomNumberFromFile << " in RBT is : " << elapsed_seconds.count() << "s\n";

	// calculating and displaying the time to search the radnom number in linked list
	auto startList = chrono::system_clock::now();
	list -> search(randomNumberFromFile);
	auto endList = chrono::system_clock::now();

	chrono::duration<double> elapsed_seconds_list = endList-startList;
   	time_t end_time_list = chrono::system_clock::to_time_t(endList);
 
   	cout << "Time to search " << randomNumberFromFile << " in unordered linked list is : " << elapsed_seconds_list.count() << "s\n";
	
	// checking if the tree has the same number of black nodes along each simple path
	int blackHeight;
	blackHeight = tree -> checkBlackNodes();
	if(blackHeight == 0){
		cout << endl << "No of black nodes along the each path is not same" << endl;
	}else{
		cout << endl << "Tree has same number of black nodes in each path of the tree and it's black height is: " << blackHeight << endl;
	}

	// deleting the random numbers from the RBTree 
	cout << endl << "Deleting the random number " << randomNumberFromFile << " from the file." << endl;
	tree -> remove(randomNumberFromFile);

	delete tree;
	delete list;
	return 0;
}

