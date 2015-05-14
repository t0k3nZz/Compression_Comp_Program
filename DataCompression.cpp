/*################### Compression / Decompression Program Header ###################
# Version 3.0 : <Compress3.0> Programmer : <Daniel Salazar>
# Due Date : 04 05, 2015 Event: Data Compression Competition
# Last Modified : 04 13 15, 01:00 
####################################################################################*/
#include <fstream> // ifstream && ofstream
#include <sstream> // ostringstream
#include<ctime> // clock
#include"LinkedList.h"
#include"Base93.h"

// MAX is n+1 to account for '\0'
const int MIN = 4, MAX = 8;

/*#################### Function Header ########################
# Function Name : Compress
# Last Modified : 04 04 15, 11:00
################################################################
# Functional Description :
# Compress a textfile
################################################################
# Algorithmic Description in Pseudocode :
# - Get length of file
# - Allocate memory
# - Read as a block
# - Process data block getting words
# -  Get word
# -  Get pointer to predecessor
# -  Get number
# -  If not a duplicate
# -   Create and set data
# -   Insert DATA
# -   Convert word to BASE93
# -   Write BASE93 to binary file
# -  End if
# -  Convert number to BASE93
# -  Write BASE93
# -  Move begining of word to next word
# - End processing data
# - Write code to compressed file
/*#################################################################################
# Parameters passed into the function:
# ifstream
# - fin: FileToCompress.txt
# ofstream
# - fout1: Database.txt
# - fout2: Compressed.txt
#
# Parameters passed out of the function:
# void
###################################################################################
# Variable Description : 
# string
# - code: holds compressed data
# - s: temp container for word
# bool
# - first: know when to start using seperators
# ULL
# - count: number of unique words
# - num: temp var to hold duplicate word's number or not
# char*
# - buffer: memory block for words
# int
# - length: length of buffer
# - size: length of word
# - i: word's begining
# - j: word's end
# - sz: size of word
# DATA*
# - data: object to hold word and count
# LINKEDLIST
# - list: linked list of data objects
# BASE93
# - convert: convert words and numbers to BASE93
###########################################################################*/
void Compress(std::ifstream &fin, std::ofstream &fout1, std::ofstream &fout2)
{
	// variables
	std::string code = "";
	std::string p = ".";
	unsigned long long count = 1;
	unsigned long long num = 0;
	LINKEDLIST list;
	BASE93 convert;
	std::cout << "Reading file..." << std::endl;
	// Get length of file
	fin.seekg(0, fin.end);
	int length = fin.tellg();
	fin.seekg(0, fin.beg);
	// Allocate memory
	char *buffer = new char[length];
	// Read as a block
	fin.read(buffer, length);
	fin.close();
	std::cout << "Processing data..." << std::endl;
	// Process data block getting words
	int i = 0, j = 0, size = 0;
	while (buffer[i] != '*' && j < length)
	{
		// Get word
		while (isalpha(buffer[j]))j++;
		size = j - i;
		// Get pointer to predecessor
		list.GetPtr(&buffer[i], size);
		// Get number (n>0 is duplicate)
		num = list.GetNumber(&buffer[i], size);
		// If not a duplicate
		if (num == 0)
		{
			// Create and set data
			DATA *words = new DATA;
			memset(words->dataParcel, '\0', MAX);
			memcpy(words->dataParcel, &buffer[i], size);
			words->number = count;
			// Insert DATA
			list.Insert(words);
			// Get a new number
			num = count++;
			// Get size
			int sz = 0;
			for (int i = 0; i < MAX; i++) if (isalpha(words->dataParcel[i])) ++sz;
			// Convert word to BASE93
			std::string s = convert.CompressWord(words->dataParcel, sz);
			// Print BASE93
			fout1.write(s.c_str(), s.length());
			fout1.seekp((num)* (MAX - 2));
		}
		// Convert number to BASE93
		code = convert.CompressNumber(num);
		// Print BASE93
		fout2.write(code.c_str(), sizeof(char)*code.size());
		// Print '.' to seperate numbers
		fout2.write(p.c_str(), sizeof(char)*p.size());
		// Move begining of word to next word
		i = ++j;
	}
	fout1.close();
	fout2.close();
	return;
}
/*###################### Function Header ########################
# Function Name : Decompress
# Last Modified : 04 04 15, 11:00
################################################################
# Functional Description :
# Decompress a textfile using a Dictionary
################################################################
# Algorithmic Description in Pseudocode :
# - Get length of file
# - Allocate memory
# - Read as a block
# - Close file
# - Process data block getting numbers
# -  Get number
# -  Access binary file and get data
# -  Decompress code and print
# -  Convert c-string to string object
# -  Convert BASE93 to word
# -  Write decoded data to textfile
# -  Print word
# -  Skip '.'
# -  Reset data
# - End processing data
# - Close files
#####################################################################
# Parameters passed into the function:
# fstream
# - fin1: Database.txt
# ifstream
# - fin2: Compressed.txt
# ofstream
# - fout2: DecompressedFile.txt
#
# Parameters passed out of the function:
# void
###################################################################################
# Variable Description :
# char*
# - buffer: memory block for words
# char
# - data[8]: temp var for words
# int
# - length: length of buffer
# - n: temp var for numbers
# - i: word's begining
# - j: word's end
################################################################################*/
void Decompress(std::fstream &fin1, std::ifstream &fin2, std::ofstream &fout)
{
	BASE93 convert;
	std::cout << "Reading file..." << std::endl;
	// Get length of file
	fin2.seekg(0, fin2.end);
	int length = fin2.tellg();
	fin2.seekg(0, fin2.beg);
	// Allocate memory
	char *buffer = new char[length];
	// Read as a block
	fin2.read(buffer, length);
	fin2.close();
	std::cout << "Processing data..." << std::endl;
	// Process data block getting numbers
	int j = 0, size = 0;
	char data[7] = { '\0' };
	std::string temp = "";
	while (j < length-1)
	{
		// Get number
		while (buffer[j] != '.' && (buffer[j] >= 32 && buffer[j] <= 126))
			temp += buffer[j++];
		// Access binary file and get data
                fin1.clear();
		fin1.seekg(((convert.DecompressNumber(temp)) - 1) * (MAX - 2));
		fin1.read((char *)&data, (MAX - 2));
		// Decompress code and print
		temp = "";
		// Convert c-string to string object
		for (int x = 0; x < 6 && int(data[x]) >= 32 && int(data[x]) <= 126; ++x)
			temp += data[x];
		// Convert BASE93 to word
		temp = convert.DecompressWord(temp);
		// Print word
		fout << temp << '\n';
		// Skip '.'
		++j;
		// Reset data
		memset(data, '\0', 7);
		temp = "";
	}
	fout << '*';
	fin1.close();
	fout.close();
	return;
}
/*###################################################################################
# Overall Program Functional Description :
# Compresses and Decompresses Text Data
###################################################################################*/
int main()
{
	clock_t t = clock();
	int choice;
	std::string file1, file2;

	std::cout << "\tCompress3.0 by Daniel Salazar" << std::endl;
	std::cout << "Choose an option\n" << std::endl;
	std::cout << "1.) Compress" << std::endl;
	std::cout << "2.) Decompress" << std::endl;
	std::cin >> choice;
	
	if (choice == 1)
	{
		std::cout << "\n**COMPRESSION**" << std::endl;

		std::cout << "Enter input filename: " << std::flush;
		std::cin >> file1;
		file1.append(".txt");
		std::cout << "\nEnter output filename: " << std::flush;
		std::cin >> file2;
		file2.append(".txt");

		std::ifstream in(file1.c_str());
		std::ofstream out1("Database.txt");
		out1.close();
		out1.open("Database.txt", std::ios::out || std::ios::binary || std::ios::trunc);
		std::ofstream out2(file2.c_str());
		if (!in)
		{
			std::cout << "Error opening input file!";
			return -1;
		}
		if (!out1)
		{
			std::cout << "Error opeing output file#1!";
			in.close();
			return -2;
		}
		if (!out2)
		{
			std::cout << "Error opeing output file #2!";
			in.close();
			out1.close();
			return -3;
		}
		Compress(in, out1, out2);
	}
	else if (choice == 2)
	{
		std::cout << "\n**DE-COMPRESSION**" << std::endl;
		std::cout << "Enter input filename: " << std::flush;
		std::cin >> file1;
		file1.append(".txt");
		std::cout << "\nEnter output filename: " << std::flush;
		std::cin >> file2;
		file2.append(".txt");
		std::fstream in1("Database.txt", std::ios::in || std::ios::binary || std::ios::trunc);
		std::ifstream in2(file1.c_str());
		std::ofstream out(file2.c_str());
		if (!in1)
		{
			std::cout << "Error opening input file!";
			return -1;
		}
		if (!in2)
		{
			std::cout << "Error opening input file!";
			in1.close();
			return -2;
		}
		if (!out)
		{
			std::cout << "Error opeing output file!";
			in1.close();
			in2.close();
			return -3;
		}
		Decompress(in1, in2, out);
	}
	else
	{
		std::cout << "Quiting!" << std::endl;
		return 0;
	}
	t = clock() - t;
	std::cout << "\n----------------------------" << std::endl;
	std::cout << "Process exited after " << ((float)t) / CLOCKS_PER_SEC << " seconds." << std::endl;
	std::cin.get();
	std::cin.get();
	return 0;
}

