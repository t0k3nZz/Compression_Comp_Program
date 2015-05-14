/*################### Compression / Decompression Program Header ###################
# Version 3.0 : <Compress3.0> Programmer : <Daniel Salazar>
# Due Date : 04 05, 2015 Event: Data Compression Competition
# Last Modified : 04 01 15, 02:00 
####################################################################################*/
#include<cmath>
#include<string>

class BASE93
{
private:
	const std::string binRef = "0000100010000110010000101001100011101000010010101001011011000110101110011111000010001100101001110100101011011010111110001100111010";
	const std::string dictionary = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ !?\"'`^#$%@&+=/:;|\\_<>[]{}()~";
	// Compress number helper
	int GetIndex(char);
	// Compress word helpers
	std::string WordToBin(char*, int);
	std::string BinTo93(std::string, int);
	unsigned long long BinToDec(std::string);
	// Decompress word helpers
	std::string BASE93ToBin(std::string);
	std::string BinToWord(std::string);
	std::string DecToBin(unsigned long long);

	
public:
	std::string CompressWord(char*, int);
	std::string DecompressWord(std::string);
	std::string CompressNumber(unsigned long long);
	unsigned long long DecompressNumber(std::string);
};
