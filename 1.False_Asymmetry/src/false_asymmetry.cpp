//This script can calculate asymmetry. This is the  version 6.0.
//Latiful Kabir
//version:5.0 , Date:05/05/2014


#include<iostream>
#include"ReadBinary.h"
#include<cmath>
#include<fstream>

using namespace std;

void false_asymmetry(int ch,double *ind_asym,int &m)
{
  ReadBinary fa("/home/daq/DATA/ACQ2006/ufw_data/Known_asym_ch-1&33/bigrawfile");
// const long long entries0=4*68800000;
  long long file_size=96468992;                        //In byte
  long long entries0=(long)(file_size*8/(32*64));  
  //const long long n=entries0; 
  
  
 
   //3.Calculating the Asymmetry
   int k=0;int q=0; int r=0; //int o=0;
   const int width=600; 
   const int pulse_no=entries0/width;
   //double p1[10000]={};
   double p1[pulse_no];
   const int cut_off=9.5e7;
   const double factor=4.7e-9*1/(20*width);  //This factor is to convert ADC value to volt/entry

   
 while((k+width+200)<entries0 && r<(entries0-1))
 {
   
    for(long j=k;j<entries0;j++)
    {
	
	//if(j%100==0){cout<<"Printing for verification:"<<j<<"	"<<fa.GetValue(ch,j)<<endl;}

	if(abs(fa.GetValue(0,j))>cut_off)
      {
	
	{  p1[q]=0;
           for (int i=j;i<j+width;i++)
           {
	       p1[q]=p1[q]+fa.GetValue(ch,(i+400));
	   }
        }
       
        k=j+width;
	q=q+1;
       	break;
      }
      r++;
    }
 }
  	 
 
    
   if(q!=0)
   {  
 
     double A=0; double A_0=0; int e=0;
     if(q%2==0)
     {
       for(int i=0;i<(q-2)/2;i++)
       {
	 A_0=(p1[2*i]-p1[2*i+1])*factor;
	 A=A+A_0;
	 ind_asym[i]=A_0;
	 e++;
       }
     }
     else
     {
       for(int i=0;i<=(int)(q-2)/2;i++)
       {
	 A_0=(p1[2*i]-p1[2*i+1])*factor;
	 A=A+A_0;
	 ind_asym[i]=A_0;
	 e++;
       }
      
     }
     //why (q-2): There are three things- i) q starts from zero,so no. of 
     // entry (q+1); ii)p1[q] has default value 0, as last increment of q     //does not fill the array iii)We want to skip the last p1 value.

 

     //4.Printing the The Asymmetry calculation outcome
     cout<<"*******************************************************"<<endl;
     cout<<"           THIS IS FOR CHANNEL-"<<(ch+1)<<"         "<<endl;
     cout<<"****************************************************"<<endl;
     cout<<"*       The Number of Pulses Considered:"<<2*e<<endl;
     cout<<"*       The Number of Entries Considered:"<<2*e*width<<endl;
     cout<<"*       Asymmetry:"<<A/e<<endl;
     cout<<"****************************************************"<<endl;
    
     m=e;
   }
   //7.Exiting if the cut_off is incorrect
   else
   {

     cout<<"*********************************************"<<endl;
     cout<<"Check Your cut_off value or No data file...Exiting!!!"<<endl;
     cout<<"***********************************************"<<endl;
   }


}


int main()
{
   char file[200];   

   int ch_list[33]={1,2,3,4,5,6,7,8,9,10,20,21,22,23,24,32,33,34,35,36,37,38,39,40,41,42,43,52,53,54,55,56,57};

    for(int i=1;i<33;i++)
    {
	ofstream asymmetry;
	sprintf(file,"asym_file_ch-%d",ch_list[i]);
	asymmetry.open(file);

	const int size=200000;
        double ind_asym[size]={0};
	int m=0;

	false_asymmetry(ch_list[i],ind_asym,m);
    	if(size<m)
	{
	    cout<<"Increase size of the array!!"<<endl;
	}
	else
	{
	   for(int j=0;j<m;j++)
	   {
	       asymmetry<<j<<"  "<<ind_asym[j]<<endl;
	   }
	}
	asymmetry.close();
    }

   
   
    return(0);
}
