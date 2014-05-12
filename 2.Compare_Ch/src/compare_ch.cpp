//This script can plot the data for two channels to be compared.
//Latiful Kabir
// Date:05/05/2014


#include<iostream>
#include"ReadBinary.h"
#include<cmath>
#include<fstream>
#include<TCanvas.h>
#include<TGraph.h>
#include<TRint.h>
#include<TAxis.h>

using namespace std;

void compare_ch(){
   
  ReadBinary fa("data/000");
              
  //1.Getting the data in arrays

    const int n=1e4;
    const int start=0;
    double x[n],y[n],z[n];
    for(int i = start;i < (start+n);i++){
   
    x[i-start]=i;
    y[i-start]=fa.GetValue(0,i);
    z[i-start]=fa.GetValue(5,i);

  }
 

 //2.Plotting the Sync pulse and pre-amp pick pick-up signal

   TCanvas *c1 = new TCanvas("c1","False Asymmetry Measurement");
   c1->Divide(1,2);
   c1->cd(1);

   TGraph *gr1 = new TGraph(n,x,y);
   gr1->Draw("AP");
   gr1->SetTitle("Plot for channel-1");
   gr1->GetXaxis()->SetTitle("Entry$");
   gr1->GetYaxis()->SetTitle("ADC Count");

   c1->cd(2);
   TGraph *gr2 = new TGraph(n,x,z);
   gr2->Draw("AP");
   gr2->SetTitle("Plot for channel-5");
   gr2->GetXaxis()->SetTitle("Entry$");
   gr2->GetYaxis()->SetTitle("ADC Count");
 
}

int main(int argc, char** argv)
{
  gApplication = new TRint("compare_ch", &argc, argv);
  compare_ch();
  gApplication->Run();
}
