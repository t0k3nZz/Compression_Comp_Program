/*################### Compression / Decompression Program Header ###################
# Version 3.0 : <Compress3.0> Programmer : <Daniel Salazar>
# Due Date : 04 05, 2015 Event: Data Compression Competition
# Last Modified : 04 01 15, 02:00 
####################################################################################*/
#include<iostream>
struct DATA
{
	// 4-7 character range + \0
	char dataParcel[8];
	// Assign a number to each unique value
	unsigned long long number;
};
struct NODE
{
	DATA *ptr;
	NODE *next;
	NODE *last;
};
class LINKEDLIST
{
private:
	NODE *check[26];
	NODE *head;
	NODE *link; // Hold next ptr
public:
	LINKEDLIST(void);
	~LINKEDLIST(void);
	void Insert(DATA*);
	bool IsEmpty(void) { return head == NULL; };
	unsigned long long GetNumber(char*, int);
	void GetPtr(char*, int);
};
