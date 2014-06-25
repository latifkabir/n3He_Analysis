# include <cstdlib>
# include <iostream>
# include <iomanip>
# include <cmath>
#include<fstream>

//-----------------------------
#include<TCanvas.h>
#include<TGraph.h>
#include<TRint.h>
#include<TAxis.h>
#include<TF1.h>
#include<TStyle.h>
#include<TH1F.h>

//----------------------------
#include"ReadBinary.h"
# include "llsq.hpp"

using namespace std;

int main (int argc, char** argv);
void test01 ( );

int main (int argc, char** argv)

{
  // timestamp ( );
  // cout << "\n";
  // cout << "LLSQ_PRB\n";
  // cout << "  C++ version\n";
  // cout << "  Test the LLSQ library.\n";
    if(ifstream("/home/daq/DATA/ACQ2006/sync_test/bigrawfile_30m"))
    {
	// test01 ( );
	gApplication = new TRint("sync", &argc,argv,0,0,kTRUE);
	test01();
	gApplication->Run();
    }
  else
    {
	cout<<"No data file... exiting... !!!!"<<endl;
    }
//
//  Terminate.
//
  // cout << "\n";
  // cout << "LLSQ_PRB\n";
  // cout << "  Normal end of execution.\n";
  // cout << "\n";
  // timestamp ( );

  return 0;
}

//***************************************************************
void test01 ( )

{
//----------------------------------------------------
    ReadBinary fa("/home/daq/DATA/ACQ2006/sync_test/bigrawfile_30m");

    const long filesize=18387828736;//In Byte
    const long entries=(long)(8*filesize)/(32*64);
    const long start=0;
    const long ch=0;
    const long pulses=(long)((entries-start)/700);
    long counter=0;


//--------------------------------------------------

  double a;
  double b;
  double error;
  int i;
  int n = 5;
  double x[5];
  double y[5];
//----------------------------------------------------
  TGraph *intpt=new TGraph();
  TGraph *slope=new TGraph();
  TH1F *h=new TH1F("h","Histogram for intercept",500,0.76,0.766);

//----------------------------------------------------
    for (long j=start;j<entries;j++)
    {
    	if((fa.GetValue(ch,j)<-1e9))
    	{
	    x[0]=(double)(j+2);  
	    x[1]=(double)(j+3);  
	    x[2]=(double)(j+4);  
	    x[3]=(double)(j+5);  
	    x[4]=(double)(j+6);  

	    y[0]=(double)fa.GetValue(ch,j+2);
	    y[1]=(double)fa.GetValue(ch,j+3);
	    y[2]=(double)fa.GetValue(ch,j+4);
	    y[3]=(double)fa.GetValue(ch,j+5);
	    y[4]=(double)fa.GetValue(ch,j+6);

	    // cout<<x[0]<<"    "<<y[0]<<endl;

	    llsq ( n, x, y, a, b );

	    // cout << "\n";
	    // cout << "  Estimated relationship is y = " << a << " * x + " << b << "\n";
 


	    slope->SetPoint(counter,counter+1,a);
    	    intpt->SetPoint(counter,counter+1,((-b/a)-j));
	    h->Fill(((-b/a)-j));
	    counter=counter+1;

    	}
    }

    TCanvas *c2=new TCanvas("Plot for Slopes");
    //slope->Print();
    slope->Draw("AP");
    slope->SetTitle("Plot for slopes");
    //slope->SetMarkerStyle(20);
    c2->Print("slope.png");

    TCanvas *c3=new TCanvas("Plot for Intercepts");
    intpt->Draw("AP");
    intpt->SetTitle("Plot for intercepts");
    //intpt->SetMarkerStyle(20);
    c3->Print("intercept.png");
    TCanvas *c4=new TCanvas("Histogram for Intercepts");
    h->Draw();
    c4->Print("Histogram.png");
   





//------------------------------------------------------
  // cout << "\n";
  // cout << "TEST01\n";
  // cout << "  LLSQ can compute the formula for a line of the form\n";
  // cout << "    y = A * x + B\n";
  // cout << "  which minimizes the RMS error to a set of N data values.\n";

  // llsq ( n, x, y, a, b );

  // cout << "\n";
  // cout << "  Estimated relationship is y = " << a << " * x + " << b << "\n";
  // cout << "  Expected value is         y = 61.272 * x - 39.062\n";
  // cout << "\n";
  // cout << "     I      X       Y      B+A*X    |error|\n";
  // cout << "\n";
  // error = 0.0;
  // for ( i = 0; i < n; i++ )
  // {
  //   cout << "  " << setw(4) << i
  //        << "  " << setw(7) << x[i]
  //        << "  " << setw(7) << y[i]
  //        << "  " << setw(7) << b + a * x[i]
  //        << "  " << setw(7) << b + a * x[i] - y[i] << "\n";
  //   error = error + pow ( b + a * x[i] - y[i], 2 );
  // }
  // error = sqrt ( error / ( double ) n );
  // cout << "\n";
  // cout << "  RMS error =                      " << error << "\n";

  return;
}
