//This script can Decimate/Average the binary data.
//Latiful Kabir
// Date:16/05/2014


#include<iostream>
#include"ReadBinary.h"


using namespace std;

int main(void)
{
  ReadBinary fa("../data/000");
  int size=fa.GetFileSize();
  int entries=(int)8*size/(64*32);
  int n;
                
  cout<<"Enter number of entries to be decimated:"<<endl; 
  cin>>n;

    for(int i=0;i<(entries-n);i=i+n)
    {
	fa.Decimate(n,i);
    }
    cout<<"File size:"<<fa.GetFileSize()<<endl;   

    return(0);
}
