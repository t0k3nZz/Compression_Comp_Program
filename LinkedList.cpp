/*################### Compression / Decompression Program Header ###################
# Version 3.0 : <Compress3.0> Programmer : <Daniel Salazar>
# Due Date : 04 05, 2015 Event: Data Compression Competition
# Last Modified : 04 01 15, 02:00 
####################################################################################*/
#include"LinkedList.h"
// MAX is n+1 to account for '\0'
const int MIN = 4, MAX = 8;

/*###################### Function Header ########################
# Function Name : Decompress
# Last Modified : 03 30 15, 22:00
################################################################
# Functional Description :
# Decompress a textfile using a Dictionary
################################################################
# Algorithmic Description in Pseudocode :
# - Get length of file
# - Allocate memory
# - Read as a block
# - Process data block getting numbers
# -  Get number
# -  Move begining of num to next num
# -  Access binary file and get data
# -  Write decoded data to textfile
# - End processing data
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
// Constructor
LINKEDLIST::LINKEDLIST(void)
{
	head = NULL; 
	for (int i = 0; i < 26; ++i, check[i] = NULL);
	link = NULL;
}
// Destructor
LINKEDLIST::~LINKEDLIST(void)
{
	NODE *p = head, *q;
	// delete LINKEDLIST
	while (p != NULL)
	{
		q = p;
		p = p->next;
		delete q->ptr;
		delete q;
	}
}
// Insert a NODE in alphabetical order
void LINKEDLIST::Insert(DATA *data)
{
	// Variables
	NODE *d = new NODE;
	d->ptr = data;

	// Convert first letter into an index
	int i = int(data->dataParcel[0]) - 97;

	// Set direct access
	// direct access is empty
	if (check[i] == NULL)
	{
		check[i] = d;
	}
	// New node replaces old node
	else if (check[i] != NULL && strcmp(check[i]->ptr->dataParcel, d->ptr->dataParcel) > 0)
	{
		check[i] = d;
	}
	// Inset new node d
	// Insert at the begining of a list
	if (link == NULL)
	{
		d->next = NULL;
		d->last = NULL;
		head = d;
		return;
	}
	// Insert at the middle of a list 
	if (link->next != NULL)
	{
		d->next = link->next;
		d->last = link;
		link->next->last = d;
		link->next = d;
		return;
	}
	// Insert at end of list
	d->next = NULL;
	d->last = link;
	link->next = d;
	return;
}
// Gets a pointer to the predecessor of the word that is
// greater than or equal to dataParcel's word
void LINKEDLIST::GetPtr(char *dataParcel, int length)
{
	// List is empty
	if (IsEmpty())
	{
		link = NULL;
		return;
	}
	// Convert letter into an index
	int i = int(dataParcel[0]) - 97;

	// Check for partial access
	if (check[i] == NULL)
	{
		// Check for a predecessor
		while (i > 0 && check[i] == NULL) i--;	
		// Everything before it is empty
		if (i == 0 && check[0] == NULL)
		{
			link = NULL;
			return;
		}
			
	}
	// Either partial access or direct access
	NODE *p = check[i];

	// Temp buffer for word
	char buffer[MAX];
	memset(buffer, '\0', MAX);
	memcpy(buffer, dataParcel, length);

	// Check first node >= new node
	if (strcmp(p->ptr->dataParcel, buffer) >= 0)
	{
		// Either predecessor or head
		link = (p->last != NULL) ? p->last : NULL;
		return;
	}
	// Direct/Partial access is end of the list
	// Node is lass than new node
	if (p->next == NULL)
	{
		link = p;
		return;
	}
	// Scan rest of list
	while (p->next != NULL && strcmp(p->next->ptr->dataParcel, buffer) < 0) p = p->next;
	// Found link
	link = p;
	return;
}
// if duplicate, return duplicate node's number
unsigned long long LINKEDLIST::GetNumber(char *dataParcel, int length)
{
	// Not a duplicate if list empty
	if (IsEmpty())
		return 0;
	// Temp buffer for word
	char buffer[MAX];
	memset(buffer, '\0', MAX);
	memcpy(buffer, dataParcel, length);
	// Link from begining of list
	if (link == NULL)
	{
		link = head;
		// Duplicate word
		if (strcmp(link->ptr->dataParcel, buffer) == 0)
			return link->ptr->number;
		// Unique word
		else
			return 0;
	}
	// End of list, no duplicate
	if (link->next == NULL)
		return 0;
	// Next word is a duplicate
	if (strcmp(link->next->ptr->dataParcel, buffer) == 0)
		return link->next->ptr->number;
	// Next word is not a duplicate
	return 0;
}
