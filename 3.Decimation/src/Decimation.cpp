#include<iostream>
#include<cstdio>
#include<string>
#include <sys/stat.h>
#include"Decimation.h"

using namespace std;

Decimation::Decimation(const char* filename)
{
     myfile=filename;
     ptr_myfile=fopen(filename,"rb");
     after.open("data/after.data");

}

Decimation::~Decimation()
{
    fclose(ptr_myfile);
     after.close();
}

size_t Decimation::GetFileSize()
{
    const string fname = string(myfile);
    struct stat st;
    if(stat(fname.c_str(), &st) != 0) {
        return 0;
    }
    return st.st_size;   
}

double Decimation::Decimate(int n,int point)
{

    struct rec
    {
	int my_data[64];
    };

 
    struct rec my_record;
    double value[64]={0};
    int x[64][n];

    if (!ptr_myfile)
    {
	cout<<"Unable to open file!"<<endl;
	return 1;
    }
    
    for(int counter=point;counter<(point+n);counter++)
    {
	fseek(ptr_myfile,sizeof(struct rec)*counter,SEEK_SET);
	fread(&my_record,sizeof(struct rec),1,ptr_myfile);
	//printf("%d   %d\n",counter,my_record.my_data[0]);
	for(int k=0;k<64;k++)
	{
	    x[k][counter-point]=my_record.my_data[k];
	}
    }
    for(int i=0;i<n;i++)
    {
	for(int k=0;k<64;k++)
	{
	    value[k]=value[k]+x[k][i];
	}
    }

    after<<point/n<<"    ";
    for(int k=0;k<64;k++)
    {
	after<<value[k]/n<<"    ";
    }
    after<<"\n";
    return (value[0]/n);
}


  
