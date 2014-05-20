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

void PlotCh(int ch,int init){
   
  ReadBinary fa("../2.Compare_Ch/data/000");
              
  //1.Getting the data in arrays

    const int n=1e4;
    const int start=init;
    double x[n],y[n],z[n];
    for(int i = start;i < (start+n);i++){
   
    x[i-start]=i;
    y[i-start]=fa.GetValue(ch,i);

  }
 

 //2.Plotting the Sync pulse and pre-amp pick pick-up signal

   TCanvas *c1 = new TCanvas("c1","Plot for the channel");

   TGraph *gr1 = new TGraph(n,x,y);
   gr1->Draw("AP");
   gr1->SetTitle("Plot for the channel");
   gr1->GetXaxis()->SetTitle("Entry$");
   gr1->GetYaxis()->SetTitle("ADC Count");
 
}

int main(int argc, char** argv)
{
    int channel,start;
    cout<<"Enter the channel number:"<<endl;
    cin>>channel;
    cout<<"Enter the entry number to start:"<<endl;
    cin>>start;
 
    gApplication = new TRint("PlotCh", &argc,argv,0,0,kTRUE);
    PlotCh(channel,start);
    gApplication->Run();
    
}
