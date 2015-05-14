/*################### Compression / Decompression Program Header ###################
# Version 3.0 : <Compress3.0> Programmer : <Daniel Salazar>
# Due Date : 04 05, 2015 Event: Data Compression Competition
# Last Modified : 04 01 15, 02:00 
####################################################################################*/
#include"Base93.h"
const int BinaryBondary = 5;
/*###################### Function Header ########################
# Function Name : CompressNumber
# Last Modified : 04 04 15, 11:00
################################################################
# Functional Description :
# Convert Base 10 to Base 93
################################################################
# Algorithmic Description in Pseudocode :
# - if num > 93
# -  convert each part into base 93
# - return result of conversion
#####################################################################
# Parameters passed into the function:
# unsigned long long
# - num: decimal number to be converted
#
# Parameters passed out of the function:
# string
# - a string object representing the base 93 conversion
###################################################################################
# Variable Description :
# string
# - result: temp variable
# int
# - length: the base
# - index: holds a count for the multiples of 93 (exponent)
# - power: base
# - div: dividend
################################################################################*/
std::string BASE93::CompressNumber(unsigned long long num)
{
	std::string result = "";
	int length = dictionary.length(), index = 0;
	int power = 0, div = 0;
	while (num >= pow(length, index)) ++index;
	--index;
	while (index >= 0)
	{
		power = (int)pow(length, index);
		div = num / power;
		result += dictionary[div];
		num -= power * div;
		--index;
	}
	return result;
}
/*###################### Function Header ########################
# Function Name : DecompressNumber
# Last Modified : 04 04 15, 11:00
################################################################
# Functional Description :
# Convert Base 93 to Base 10
################################################################
# Algorithmic Description in Pseudocode :
# - reverse the string
# - Move down the string
# -  convert each element into a digit
# -  add digit to result
# - return result
#####################################################################
# Parameters passed into the function:
# string
# - a string object representing the base 93 conversion
#
# Parameters passed out of the function:
# unsigned long long
# - num: decimal number that was converted
###################################################################################
# Variable Description :
# unsigned long long
# - result: number that was converted
# int
# - length: the base
# - index: holds a count for the multiples of 93 (exponent)
# - power: base
# - ind: index
################################################################################*/
unsigned long long BASE93::DecompressNumber(std::string code)
{
	unsigned long long  result = 0;
	int length = dictionary.length(), index = 0;
	int power = 0, ind = 0;
	std::reverse(code.begin(), code.end());
	for (int i = 0; i < code.length(); ++i)
	{
		power = (int)pow(length, index);
		ind = GetIndex(code[i]);
		result += power * ind;
		++index;
	}
	return result;
}
// Finds c in the dictionary and returns the index
int BASE93::GetIndex(char c)
{
	for (unsigned int i = 0; i < dictionary.length(); ++i)
	{
		if (dictionary[i] == c)
		{
			return i;
		}
	}
	return -1;
}
//#######################Compress Word#############################

// Convert a word into binary then convert into BASE 93
std::string BASE93::CompressWord(char *buffer, int length)
{
	return BinTo93(WordToBin(buffer, length), length);
}

// Goes through each letter and appends the appropriate binary string
// of length 5 ranging from (00001 : 'a') to (11010 : 'z')
std::string BASE93::WordToBin(char *buffer, int length)
{
	std::string result = "";
	int i = 0;
	while (i < length)
		result += binRef.substr((int(buffer[i++] - 97) * BinaryBondary), BinaryBondary);
	return result;
}

// If there are 4, 5, or 6, letters convert whole binary string
// If there are 7 letters, convert the first 6, then convert the 7th
// It provides n-1 letters
std::string BASE93::BinTo93(std::string result, int length)
{
	int i = 0, j = (length * BinaryBondary);
	// convert all of binary strings 4, 5, and 6
	if (length < 7)
		return CompressNumber(BinToDec(result.substr(i, j)));
	// special case 7
	std::string temp = "";
	// convert binary strings 4-6
	j = 30;
	temp += CompressNumber(BinToDec(result.substr(i, j)));
	if (temp.size() == 4) temp += "*";
	// convert 7th binary string
	i = 30;
	j = 35;
	return (temp + CompressNumber(BinToDec(result.substr(i, j))));
}

// Reverses the string, checks for any '1's,  adding the BASE 10
// equivalent to the result
unsigned long long BASE93::BinToDec(std::string binary)
{
	std::string temp = "";
	for (int i = binary.size()-1; i >= 0; --i)
		temp += (binary.c_str()[i] == '1') ? '1' : '0';
	unsigned long long result = 0;
	unsigned int i = 0;
	while (i < temp.size())
	{
		if (temp.c_str()[i] == '1')
			result += pow(2, i);
		++i;
	}
	return result;
}


//####################### Decompress Word #############################

// Converts BASE 93 into binary then convert into a word
std::string BASE93::DecompressWord(std::string word)
{
	return BinToWord(BASE93ToBin(word));
}

// Converts BASE 93 into decimal then converts into binary
std::string BASE93::BASE93ToBin(std::string word)
{
	if (word.size() < 6)
		return DecToBin(DecompressNumber(word));
	std::string result = "";
	std::string temp = "";
	// Special case short BASE93
	if (word.c_str()[4] == '*')
	{
		temp += word.c_str()[5];
		// Convert first 4 BASE93 characters
		result += DecToBin(DecompressNumber(word.substr(0, 4)));
		// convert 5th character
		result += DecToBin(DecompressNumber(temp));
		return (result);		
	}
	// Convert first 5 BASE93 characters
	result = DecToBin(DecompressNumber(word.substr(0, 5)));
	// Convert 6th character
	temp += word.c_str()[5];
	result += DecToBin(DecompressNumber(temp));
	return result;
}

// Convert from Decimal to Binary and pad to make size a multipe of 5
std::string BASE93::DecToBin(unsigned long long num)
{
	std::string result = "";
	int base = 2, index = 0;
	int power = 0, div = 0;
	while (num >= pow(base, index)) ++index;
	--index;
	while (index >= 0)
	{
		power = (int)pow(base, index);
		div = num / power;
		result += ((div % 2 == 0) ? "0" : "1");
		num -= power * div;
		--index;
	}
	// Pad with zeroes
	if ((result.size() % 5) != 0)
	{
		int pad = 5 - (result.size() % 5);
		for (int i = 0; i < pad; ++i) result.insert(0,"0");

	}
	return result;
}
// Convert binary into a word
std::string BASE93::BinToWord(std::string binary)
{
	std::string result = "";
	int i = 0, j = 6;
	while (i < binary.size())
	{
		result += char(BinToDec(binary.substr(i, BinaryBondary)) + 96);
		i += 5;
	}
	return result;
}
