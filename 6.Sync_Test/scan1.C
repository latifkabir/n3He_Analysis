#include"/home/daq/KABIR/ANALYSIS/libn3He/TBranchBinary_cc.so"
void scan1(int p){
  

  //TH1F *histo = new TH1F("histo","T_{0}+pulse (expanded) NON-sync.",1100000,0,1100000);
  TH1F *histo = new TH1F("histo","T_{0}+pulse (expanded) Sync.",11000000,0,11000000);
  histo->GetXaxis()->SetTitle("time [(64kHz)^{-1}]");
                           
  TTree t("t","");
   char* fn[1]=
  {
    // "./bigrawfile_non_sync"
     "./bigrawfile_sync"
  };

  TBranchBinary b(&t, 1, fn,"d[64]/I");
  t.GetListOfBranches()->Add(&b);
  t.SetEntries();

  //1.Getting the data in arrays

    int *buffer = b.GetAddress();
    int entries = b.GetEntries();

    const int n=6e6;
    const int start=0;
    double x[n],y[n];
    for(int i = start;i < (start+n);i++){
      b.GetEntry(i);
      //if (i >500 && i <700) cout << i << "\t" << buffer[0] << endl;
      x[i-start]=i;
      y[i-start]=buffer[p]/(2.12e8);
      
      histo->SetBinContent(i,y[i-start]);
    }
 

    //2.Plotting the Sync pulse and pre-amp pick pick-up signal
    
    //TCanvas *c1 = new TCanvas("c1","False Asymmetry Measurement");
    
    //gr1 = new TGraph(n,x,y);
    //gr1->Draw("AP");
    
    //histo->GetXaxis()->SetRangeUser(0,5000);
    //histo->Draw();
    
    //gr1->GetXaxis()->SetTitle("Entry$");
    //gr1->GetYaxis()->SetTitle("ADC Count");
    
    
    const int Npls=10000;
    TF1 *func[Npls];
    char fname[200];
    
    int T0_bin[Npls]; //First T0 signal header
    
    int T0_count = 0;// counting T0 pulses
    
    for(int ibin = 1; ibin < 6000000; ibin++){
      if (histo->GetBinContent(ibin) < -5.0){
	
	//cout << "pulse #-" << T0_count << " i= "<< i << endl;
	
	T0_bin[T0_count] = ibin;
	
	sprintf(fname,"func_%d",T0_count);
	func[T0_count] = new TF1(fname,"pol1", T0_bin[T0_count]+5, T0_bin[T0_count]+8);
	//func[T0_count] = new TF1(fname,"pol1", T0_bin[T0_count]+3, T0_bin[T0_count]+6);
	
	T0_count++;
	
      }
    }
    
    
    //TH1F *deltaT_histo = new TH1F("dT_histo","T_{1} - T_{0} distribution", 100, 2.5, 4.5);
    TH1F *deltaT_histo = new TH1F("dT_histo","T_{1} - T_{0} distribution", 100, 0.5, 2.5);
    deltaT_histo->GetXaxis()->SetTitle("time [(64kHz)^{-1}]");   
    deltaT_histo->GetYaxis()->SetTitle("ADC counts [Volts]");   
    
    // delta vs pulse-N
    TH1F *deltaT_vs_pls_histo = new TH1F("dT_vs_pls_histo","#delta T distribution vs. pulse-#", 6000,0,6000);
    deltaT_vs_pls_histo->GetXaxis()->SetTitle("Pulse-#");
    deltaT_vs_pls_histo->GetYaxis()->SetTitle("DeltaT [(64kHz)^{-1}]");      
    
    // delta consecutive
    TH1F *deltaT_cons_histo = new TH1F("dT_cons_histo","#DeltaT_{i+1} - #DeltaT_{i} distribution", 100, -0.1, 0.1);
    deltaT_cons_histo->GetXaxis()->SetTitle("#DeltaT_{i+1} - #DeltaT_{i} [(64kHz)^{-1}]"); 
    deltaT_cons_histo->GetYaxis()->SetTitle("Entries"); 
    
    double T1[Npls];
    double T0[Npls];
    
    for(int i = 0; i < 6000; i++){
      
      
      T0[i]=(double )T0_bin[i];

      histo->Fit(func[i],"RQ");
      if (i%1000==0) cout << "i = " << i << endl;
      
      // Intercept at y=0
      T1[i] = -1.0*(func[i]->GetParameter(0)/func[i]->GetParameter(1));
      
      //cout << i << " delta_t =  " << T1[i] - T0[i] << " chi2 = " << func[i]->GetChisquare() << endl;
      
      deltaT_histo->Fill(T1[i] - T0[i]);
      deltaT_vs_pls_histo->SetBinContent(i+1, T1[i] - T0[i]);
      
      if (i>0) {
	//cout << i << " delta_t_i+1 =  " << T1[i] - T0[i] << "  delta_t_i = " << T1[i-1] - T0[i-1] << endl;
	deltaT_cons_histo->Fill( (T1[i] - T0[i]) - (T1[i-1] - T0[i-1]) );
	//deltaT_cons_histo->Fill( TMath::Abs(T1[i] - T0[i]) - (T1[i-1] - T0[i-1]) );
      }
    }
    
    //TCanvas *c2 = new TCanvas();
    //deltaT_histo->Draw();
    
    TH1F *histo_first = (TH1F *) histo->Clone("histo_first");
    histo_first->GetXaxis()->SetRangeUser(510,640);
    histo_first->GetXaxis()->SetRangeUser(160,290);
    histo_first->SetTitle("First T_{0}+pulse");
    
    
    cout << "print-1" << endl;
    
    TCanvas *c3 = new TCanvas();
    histo_first->Draw();
    
    cout << "print-2" << endl;
    
    //TH1F *histo_zoomed = (TH1F *) histo->Clone("histo_zoomed");
    //histo_zoomed->GetXaxis()->SetRangeUser(0,10000);
    //histo_zoomed->SetTitle("T_{0}+pulse zoomed in");
    
    cout << "print-3" << endl;
    
    //TCanvas *c4 = new TCanvas();
    //histo_zoomed->Draw();
    
    cout << "print-4" << endl;
    
    TCanvas *c5 = new TCanvas("c5","");
    deltaT_vs_pls_histo->Draw();

    TCanvas *c6 = new TCanvas("c6","");
    deltaT_cons_histo->Draw();
    
    
    //c1->Print("Allpulses_non_sync.png");
    //c2->Print("deltaT_non_sync.png");
    //c3->Print("Firstpulse_non_sync.png");
    //c4->Print("Zoomedpulses_non_sync.png");

    //c1->Print("Allpulses_sync.png");
    //c2->Print("deltaT_sync.png");
    //c3->Print("Firstpulse_sync.png");
    //c4->Print("Zoomedpulses_sync.png");
    //c5->Print("deltaT_vs_pulseN_sync.png");
    //c6->Print("deltaT_consecutive_sync.png");
   
}


