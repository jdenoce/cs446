#include "config_data.h"
#include <iostream>
using namespace std;
#include <fstream>

int main(void)
{
char* config_file = new char[20];
string temp, temp2, file_path;
float ftemp;
int* xtable = new int[8];
int xversion = 0, itemp;

cout<<"====================="<<endl<<"Welcome to OS simulator"<<endl<<"by: Jordan DeNoce"<<endl<<"====================="<<endl;
cout<<"Please enter configuration file: ";
cin>>config_file;

//open file-------file needs to be from a command line argument
fstream fin;
fin.open(config_file);

//check for correct input
getline(fin, temp);
if(temp!="Start Simulator Configuration File")
{
 cout<<"Invalid configuration file (1st line)"<<endl;
 return 0;
}
fin>>temp;
if(temp!="Version/Phase:")
{
  cout<<"Invalid configuration file (second line)"<<endl;
  return 0;
}
fin>>ftemp;
if(ftemp < 1.0 || ftemp > 4.0)
{
  cout<<"Invalid Verson/Phase"<<endl;
  return 0;
} 
xversion = ftemp;
getline(fin, temp);
fin>>temp;
fin>>temp2;
if(temp != "File" && temp2 != "Path:")
{
  cout<<"Invalid configuration file (third line)"<<endl;
  return 0;
}
fin>>temp;
file_path = temp;//takes in the file path stored in file_path

fin>>itemp;
getline(fin, temp);
cout<<itemp<<temp<<endl;


fin.close();



return 0;
}
