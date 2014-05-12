#include"/home/daq/KABIR/ANALYSIS/libn3He/TBranchBinary_cc.so"
void data_scan(int p){
  
                           
  TTree t("t","");
   char* fn[1]=
  {
       "/home/daq/DATA/ACQ2006/ufw_data/Known_asym_ch-1&33/bigrawfile"
  };
  TBranchBinary b(&t, 1, fn,"d[64]/I");
  t.GetListOfBranches()->Add(&b);
  t.SetEntries();

  //1.Getting the data in arrays

    int *buffer = b.GetAddress();
    int entries = b.GetEntries();

    const int n=1e5;
    const int start=0;
    double x[n],y[n],z[n];
    for(int i = start;i < (start+n);i++){
    b.GetEntry(i);
    // cout << i << "\t" << buffer[0] << endl;
    x[i-start]=i;
    y[i-start]=buffer[0];
    z[i-start]=buffer[p];

  }
 

 //2.Plotting the Sync pulse and pre-amp pick pick-up signal

   TCanvas *c1 = new TCanvas("c1","False Asymmetry Measurement");
   c1->Divide(1,2);
   c1->cd(1);

   gr1 = new TGraph(n,x,y);
   gr1->Draw("AP");
   gr1->GetXaxis()->SetTitle("Entry$");
   gr1->GetYaxis()->SetTitle("ADC Count");

   c1->cd(2);
   gr2 = new TGraph(n,x,z);
   gr2->Draw("AP");
   gr2->GetXaxis()->SetTitle("Entry$");
   gr2->GetYaxis()->SetTitle("ADC Count");
 
}

