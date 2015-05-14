//Bryan Wieger
#include <iostream>
#include <fstream>
#include <string>
using namespace std;


int main()
{
	//Variables for file opening
	ifstream file1,file2;
	string f1,f2;
	
	//Get names of files
	cout<<"Enter File1 name: ";
	cin>>f1;
	cout<<"Enter File2 name: ";
	cin>>f2;
	
	//change file names
	f1+=".txt";
	f2+=".txt";
	
	//open files
	file1.open(f1.c_str());
	file2.open(f2.c_str());
	
	//Parameters for comparision
	string in1,in2;
	unsigned long long counter =1;
	bool same=true;
	while(!file1.eof()){ //comparison loop
		file1>>in1;
		file2>>in2;
		if(in1!=in2) {
			cout<<"There is a diff at line "<<counter;
			cout<<"\nFile1 had: "<<in1;
			cout<<"\nFile2 had: "<<in2;
			same=false;
			break;
		}
		counter++;
	}
	if(same) cout<<"\nFiles are the same\n";
	
		
	cin.get(); //Pause for user to review info
	cin.get(); 
	//close files
	cout<<"\n\nEnd Program";
	file1.close();
	file2.close();
}

