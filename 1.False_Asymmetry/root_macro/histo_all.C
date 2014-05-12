void histo_all()
{
	double fassym_ch[100];
	double fassym_err_ch[100];
	double s[100];

	char file[200]; 
	ofstream rms("rms_value");
	
	double n;

	int ch_list[33]={1,2,3,4,5,6,7,8,9,10,20,21,22,23,24,32,33,34,35,36,37,38,39,40,41,42,43,52,53,54,55,56,57};

    for(int i=1;i<33;i++)
    {
	ifstream datafile;
	sprintf(file,"asym_file_ch-%d",ch_list[i]);
	datafile.open(file);

	double x[200000],y[200000];
	
	int index=0;
	
	while(!datafile.eof())
	{
		datafile>>x[index]>>y[index];
		index++;
	}
	datafile.close();

	int N=(index-1);
	double ymax=y[0],ymin=y[0];
	for(int k=1;k<N;k++)
	{
		if(y[k]>ymax)
			ymax=y[k];
		if(y[k]<ymin)
			ymin=y[k];
	}
	
	TCanvas *c1= new TCanvas("c1",file);
	TH1F* h=new TH1F("h",file,200,ymax,ymin);
	
	for(int j=0;j<N;j++)
	{
		h->Fill(y[j]);
	}
	h->Draw();
	h->Draw();
	h->GetXaxis()->SetTitle("Asymmetry");
	h->GetYaxis()->SetTitle("Frequency");
	s[ch_list[i]]=h->GetRMS(1);
	fassym_ch[ch_list[i]]=h->GetMean(1);
	n=h->GetEntries();
	fassym_err_ch[ch_list[i]]=s[ch_list[i]]/sqrt(n);

	sprintf(file,"asym_file_ch-%d.pdf",ch_list[i]);
	c1->Print(file);

	rms<<ch_list[i]<<"	"<<fassym_ch[ch_list[i]]<<"	"<<s[ch_list[i]]/sqrt(n)<<"	"<<endl;
    }
	
    rms.close();


	

   double weight_i, fassym_i;
   double Ave_fasymm=0.0, Ave_fasymm_err=0.0, weight_sum=0.0;

   for(int k=1;k<33;k++)
   {
     	cout << "channel - " << ch_list[k] << "  assym +- err " << fassym_ch[ch_list[k]] << "  +-  " << fassym_err_ch[ch_list[k]] << endl;
     	weight_i = 1.0/pow(fassym_err_ch[ch_list[k]],2);
        fassym_i = (weight_i*fassym_ch[ch_list[k]]);
        weight_sum = weight_sum + weight_i;
        Ave_fasymm = Ave_fasymm + fassym_i;
   }
   Ave_fasymm_err = 1.0/sqrt(weight_sum);
   Ave_fasymm = Ave_fasymm / weight_sum;
   cout << " average  assym +- err " << Ave_fasymm << " +-  " << Ave_fasymm_err << endl;

}
