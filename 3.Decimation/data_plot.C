void data_plot()
{      //1.Inporting the data in to two arrays x and y
        ifstream data;
	double x[35000],y[35000],z[35000];
	int index=0;
	
	data.open("data/after.data");

	while(!data.eof())
	{	
	    data >>x[index]>>y[index]>>z[index];
		index++;
	}
	cout<<"Total number of Entries "<<(index-1)<<endl;
	
	for(int i=0; i<(index-1);i++)
	{ 	
	    cout<<x[i]<<"  "<<y[i]<<"  "<<z[i]<<endl;
	}
	//2.Making graph of x and y	
	gr= new TGraph(index-1,x,y);
	gr->GetXaxis()->SetTitle(" X ");
	gr->GetYaxis()->SetTitle("Y=x^2");	
	gr->SetTitle("A simple graph from data");
	gr->Draw("AP");
}

