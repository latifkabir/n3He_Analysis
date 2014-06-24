#include<iostream>
#include"ReadBinary.h"
#include<cmath>
#include<fstream>
#include<TCanvas.h>
#include<TGraph.h>
#include<TRint.h>
#include<TAxis.h>
#include<TF1.h>
#include<TStyle.h>
#include<TH1F.h>
using namespace std;



void sync_fit()
{
    // gStyle->SetOptStat(111111);
    // gStyle->SetOptFit(1);

    ReadBinary fa("/media/siplu/USB20FD/DATA/sync_test/bigrawfile");


    const long filesize=211812352 ;//In Byte
    const long entries=(long)(8*filesize)/(32*64);
    const long start=0;
    const long ch=0;
    const long pulses=(long)((entries-start)/700);
    long counter=0;

    TCanvas *c1 = new TCanvas("c1","Plot for the channel");

    TGraph *gr1 = new TGraph((entries-start));
    for(long i=start;i<entries;i++)
    {
	gr1->SetPoint(i-start,i,fa.GetValue(ch,i));
    }   
    gr1->Draw("AP");
    gr1->SetTitle("Plot for the channel");
    gr1->GetXaxis()->SetTitle("Entry$");
    gr1->GetYaxis()->SetTitle("ADC Count");
    c1->Print("plot.png");

    TCanvas *c2=new TCanvas("Plot for Slopes");
    //TF1 *f1=new TF1("f1","[0]*x+[1]"); //For method-2
    
    TGraph *intpt=new TGraph(pulses);
    TGraph *slope=new TGraph(pulses);
    TH1F *h=new TH1F("h","Histogram for intercept",500,0.7,0.8);

    for (long i=start;i<entries;i++)
    {
    	if((fa.GetValue(ch,i)<-1e9))
    	{
	    //f1->SetRange(i+2,i+6);  //Method-2  
	    //TF1 *f1=new TF1("f1","[0]*x+[1]",i+2,i+6);//Method-1 for fit range
	    TF1 *f1=new TF1("f1","[0]*x+[1]");
    	    gr1->Fit("f1","Q","",i+2,i+6);//Method-3
    	    //gr1->Fit("f1","RQ");//For Method-1
    	    slope->SetPoint(counter,i,f1->GetParameter(0));
    	    intpt->SetPoint(counter,i,((-f1->GetParameter(1)/f1->GetParameter(0))-i));
	    h->Fill(((-f1->GetParameter(1)/f1->GetParameter(0))-i));
	    counter=counter+1;
    	    // cout<<"First fit parameter:"<<f1->GetParameter(0)<<endl;
    	    // cout<<"Second fit parameter:"<<f1->GetParameter(1)<<endl;
	    delete f1;
    	}
    }
    //slope->Print();
    slope->Draw("AP");
    slope->SetTitle("Plot for slopes");
    slope->SetMarkerStyle(7);
    c2->Print("slope.png");

    TCanvas *c3=new TCanvas("Plot for Intercepts");
    intpt->Draw("AP");
    intpt->SetTitle("Plot for intercepts");
    intpt->SetMarkerStyle(7);
    c3->Print("intercept.png");
    TCanvas *c4=new TCanvas("Histogram for Intercepts");
    h->Draw();
    c4->Print("Histogram.png");
   
}


int main(int argc, char** argv)
{
    if(ifstream("/media/siplu/USB20FD/DATA/sync_test/bigrawfile")) 
    {
	gApplication = new TRint("sync", &argc,argv,0,0,kTRUE);
	sync_fit();
	gApplication->Run();
    }
    else
    {
	cout<<"No data file... exiting... !!!!"<<endl;
    }    
    
}


/*

Fit("f1","R"); here option "R" will enable fit only in the range for which f1 is defined.
Option "Q" is Quiet mode, no printing for fitting.

*/
