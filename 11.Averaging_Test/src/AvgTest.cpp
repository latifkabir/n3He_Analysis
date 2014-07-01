//This script can plot the data for specified channel in specified region.
//Latiful Kabir
// Date:05/20/2014


#include<iostream>
#include"ReadBinary.h"
#include<cmath>
#include<fstream>
#include<TCanvas.h>
#include<TGraph.h>
#include<TRint.h>
#include<TAxis.h>

using namespace std;

void AvgTest(int ch=0,int init=0){

  ReadBinary fa("/media/siplu/USB20FD/n3He_DAQ/avg_test/Interpolation/bigrawfile_1_1");
  //1.Getting the data in arrays

  const int filesize=102760448 ;//In Byte
  const int entries=(int)(8*filesize)/(32*64);
  const int start=init;

 //2.Plotting the Sync pulse and pre-amp pick pick-up signal

   TCanvas *c1 = new TCanvas("c1","Plot for the channel");

   TGraph *gr1 = new TGraph();
   for(int i=1;i<240;i++)
   {
       gr1->SetPoint(i-1,0.25*i,fa.GetValue(ch,i));
   }   
   gr1->Draw("AP");
   gr1->SetTitle("Plot for the channel");
   gr1->GetXaxis()->SetTitle("Entry$");
   gr1->GetYaxis()->SetTitle("ADC Count");
   gr1->SetMarkerStyle(7);
//3.Plot for mergerd data

  ReadBinary fa2("/media/siplu/USB20FD/n3He_DAQ/avg_test/Interpolation/bigrawfile_4_4");

  // TCanvas *c2 = new TCanvas("c2","Plot for the channel");
   TGraph *gr2 = new TGraph();
   double ave;
   double x[4];
   for(int i=0;i<60;i++)
   {
       x[0]=(double)fa.GetValue(ch,4*i+1);
       x[1]=(double)fa.GetValue(ch,4*i+2);
       x[2]=(double)fa.GetValue(ch,4*i+3);
       x[3]=(double)fa.GetValue(ch,4*i+4);

       // ave=fa.GetValue(ch,4*i+1)+fa.GetValue(ch,4*i+2)+fa.GetValue(ch,4*i+3)+fa.GetValue(ch,4*i+4);
       ave=(x[0]+x[1]+x[2]+x[3]);
       ave=0.25*ave;
       gr2->SetPoint(i,i+1,ave);
       // cout<<x[0]<<"   "<<x[1]<<"   "<<x[2]<<"   "<<x[3]<<"   "<<ave<<endl;
   }   
   gr2->Draw("psame");
   gr2->SetTitle("Plot for the channel");
   gr2->GetXaxis()->SetTitle("Entry$");
   gr2->GetYaxis()->SetTitle("ADC Count");
   gr2->SetMarkerStyle(20);
   gr2->SetMarkerColor(2);

   TGraph *gr3 = new TGraph();
   for(int i=1;i<61;i++)
   {
       gr3->SetPoint(i-1,i+0.4,fa2.GetValue(ch,i));
   }   
   gr3->Draw("psame");
   gr3->SetMarkerStyle(20);
   gr3->SetMarkerColor(4);

   

 
}

int main(int argc, char** argv)
{

    if(ifstream("/media/siplu/USB20FD/n3He_DAQ/avg_test/Interpolation/bigrawfile_1_1")) 
    {
	int channel=0,start=0;
 
	gApplication = new TRint("AvgTest", &argc,argv,0,0,kTRUE);
	AvgTest(channel,start);
	gApplication->Run();
    }
    else
    {
	cout<<"No data file... exiting... !!!!"<<endl;
    }    
}
