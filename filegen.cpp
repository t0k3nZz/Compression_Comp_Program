//Bryan Wieger
#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <fstream>
using namespace std;

typedef unsigned long long ll;

void filemaker(string [],ll, ll, ll,int,int,int); //used to make the file
string randStr(ll, ll); //out puts a random string from 4-7 characters in length
string getfilename(); //creates a string ending in .txt


int main()
{
	srand(time(NULL));
	string * repeat;
	while(true){
		cout<<"Number of lines: ";
		ll S,min,max;
		int denom, num,n;
		cin>>S;
		cout<<"\nMin Char per line: ";
		cin>>min;
		cout<<"\nMax Char per line: ";
		cin>>max;
		cout<<"\nEnter probability numerator for selection of repeating data: ";
		cin>>num;
		cout<<"\nEnter probability denominator for selection of repeating data: ";
		cin>>denom;
		cout<<"\nEnter number of keys: ";
		cin>>n;
		repeat=new string[n];
		for(int i=0; i<n; i++){
			repeat[i]=randStr(min,max);
		}
		filemaker(repeat,S,min,max,denom,num,n);
	}
	return 0;	
}

string getfilename(){
	string res="";
	cout<<"Filename: ";
	cin>>res;
	res+=".txt";
	return res;
}

void filemaker(string repeat[], ll S, ll min, ll max,int denom,int num,int n){
	ofstream out;
	out.open(getfilename().c_str());
	int c,d;
	for(ll i=0; i<S; i++){
		c=rand()%denom;
		c/=num; //1 out of twelve that randStr() will be called
		switch(c){
			case 0:
				d=rand()%n;
				out<<repeat[d]<<endl;
				break;
			case 1:
				out<<randStr(min,max)<<endl;
				break;
			default:;
		}
	}
	out << '*';
	out.close();	
}

string randStr(ll min, ll max){
	string res="";
	int l=rand()%(max-min+1)+min;
	while(res.length()<l) res+=((char)((rand()%26+(int)'a')));
	return res;
}

