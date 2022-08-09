

//BFI_batch_TChiWZ_all.root
//i
using namespace std;
vector<string> split (const string &s, char delim) {
    vector<string> result;
    stringstream ss (s);
    string item;

    while (getline (ss, item, delim)) {
        result.push_back (item);
    }

    return result;
}
TH1D* collectBG(TFile* f, std::string bname, std::string regiondir, std::string proc){
//name of processes
//ttbar ST ZDY DB Wjets TB QCD
	TH1D* bg = (TH1D*) f->Get(bname.c_str());
	//TH1D* bgelf0 =(TH1D*) f->Get( (bname+"_Fakes_elf0").c_str() );
	//TH1D* bgelf1 =(TH1D*) f->Get( (bname+"_Fakes_elf1").c_str() );
	//TH1D* bgmuf0 =(TH1D*) f->Get( (bname+"_Fakes_muf0").c_str() );
	//TH1D* bgmuf1 =(TH1D*) f->Get( (bname+"_Fakes_muf1").c_str() );

	//find all fake hists
	TDirectory* rdir = (TDirectory*) f->Get(regiondir.c_str());
	TList* lst = rdir->GetListOfKeys();
	std::set<const char*> keyset{};
	for(int i=0; i<lst->GetSize(); i++){
		keyset.insert(lst->At(i)->GetName());
	}
	/*for(auto const &i: keyset){
	 std::cout<<i<<std::endl;
	}
	*/
	std::set<const char*> subset{};
	for(auto const &i: keyset){
		bool Process=false;
		bool Fake=false;
		bool Variations=false;
		std::string hname(i);
		//std::cout<<"scanning for "<<proc<<" "<<hname<<" ";
                std::size_t found1 = hname.find(proc);
                std::size_t found2 = hname.find("Fakes");
                std::size_t found3 = hname.find("RISR");
                std::size_t found4 = hname.find("Mperp");
                std::size_t found5 = hname.find("BTAG");
                std::size_t found6 = hname.find("TRIG");
                if(found1!=std::string::npos) Process=true;
                if(found2!=std::string::npos) Fake=true;
                if(found3!=std::string::npos) Variations=true;
                if(found4!=std::string::npos) Variations=true;
                if(found5!=std::string::npos) Variations=true;
                if(found6!=std::string::npos) Variations=true;
                if(Process && Fake && !Variations){//std::cout<<" TRUE \n";
			subset.insert(i);  //erase is segfaulting?? this didnt happen in tests.. root version?  
		}
                else{
			//std::cout<<" FALSE \n";
                       // keyset.erase(i);//erase elements that dont trigger both bools
                }
	}//end keyset loop
/*	std::cout<<"POST REMOVAL\n";
        for(auto const &i: subset){
		std::cout<<i<<std::endl;
	}
	std::cout<<"end subset\n";
*/
	//loop keyset get all TH1D*
	std::vector<TH1D*> hists{};
	hists.push_back(bg);
	for(auto const &i: subset){
		//std::cout<<i<<std::endl;
		std::string key(i);
		hists.push_back( (TH1D*) f->Get( (regiondir+"/"+key).c_str() ) );
	}

	TH1D* h = NULL;
	/*if(bg != NULL) h = bg;
	if(h == NULL) return h;
        if(bgelf0 != NULL) h->Add(bgelf0);
	if(bgelf1 != NULL) h->Add(bgelf1);
	if(bgmuf0 != NULL) h->Add(bgmuf0);
	if(bgmuf1 != NULL) h->Add(bgmuf1);	
	*/
	//loop and find a non null hist
	//std::vector<TH1D*> hists = { bg, bgelf0, bgelf1, bgmuf0, bgmuf1 };
	int I=-1;
	for(int i=0; i<hists.size(); i++){
		if(hists.at(i) != NULL){
			I=i;
			h = hists.at(i);
			break;
		}
	}
	if( h == NULL ) return h;
	
	for(int i=0; i<hists.size(); i++){
		if( I == i ) continue;
		if( hists.at(i) != NULL){
			h->Add(hists.at(i) );
		}
	}

	return h;
}
TH1D* sumBG(std::vector<TH1D*> hvec){
	TH1D* h = NULL;
	//find one that isnt null
	int I;
	for(int i=0; i<hvec.size(); i++){
		if(hvec.at(i) != NULL){
			h = (TH1D*) hvec.at(i)->Clone();
			I=i;
			break;
		}
	}
	if(h != NULL){

		for(int i=0; i<hvec.size(); i++){
			if(I != i){
				if( hvec.at(i) != NULL){
				h->Add(hvec.at(i));
				}
			}
		}
	}
	return h;
	

}
void loopBin(TH1D* h,int nbinsx, std::string str, ofstream& fstream, std::string regionName, int nl, int nj){
	//fstream<<str<<" ";
	/*for(int j=1; j<=nbinsx; j++){
			if( h != NULL ){
                        	fstream<<h->GetBinContent(j)<<"+/-"<<h->GetBinError(j)<<" ";
                        }
                        else{
                        	fstream<< "-1+/-0 ";
                        }
		}
	if( h == NULL){ 
		fstream<< "0 ";
	}
	else{
		fstream<< h->Integral()<<" ";
	}
	fstream<<std::endl;
	*/
	//"RegionName PType BinN NL NJ Yield Error
	for(int j=1; j<=nbinsx; j++){
		fstream<<regionName<<" "<<str<<" "<<j<<" "<<nl<<" "<<nj<<" ";
		if( h != NULL ){
			fstream<<h->GetBinContent(j)<<" "<<h->GetBinError(j)<<"\n";
		}
		if( h==NULL){
			fstream<< "-999 0\n";
		}
	}
}

int IDJets( std::string jstring ){
	//2iL 0j0svS 0jge1svS 1j0bS 1j1bS 1jS 2j0bS 2jS 2jge1bS ge3j0bS ge3jS ge3jge1bS
	std::size_t found0 = jstring.find("0j");
	std::size_t found1 = jstring.find("1j");
	std::size_t found2 = jstring.find("2j");
	std::size_t found3 = jstring.find("3j");
	std::size_t found4 = jstring.find("4j");
	std::size_t found5 = jstring.find("5j");
	std::size_t found6 = jstring.find("inclS");
	if(found0!=std::string::npos) return 0;
	if(found1!=std::string::npos) return 1;
	if(found2!=std::string::npos) return 2;
	if(found3!=std::string::npos) return 3;
	if(found4!=std::string::npos) return 4;
	if(found5!=std::string::npos) return 5;
	if(found6!=std::string::npos) return 0;//this may need to be different (returning 0j for 3L SSS inclS)
	return -1;
}


vector<vector<double> >  mapbins(int channel, int jets){
		vector< vector<double> > Bins;		
		vector<double> Bin;//indices 0,1 RISR indices 2+ Mperp
		
		if(channel == 0){
			if(jets == 0){
			  Bins.push_back({0.95,0.985,0,40});
			  Bins.push_back({0.985,1.0,0,5,10,40});
			}
			if(jets == 1){
			  Bins.push_back({0.8,0.9,0,100});
			  Bins.push_back({0.9,0.93,0,20,100});
			  Bins.push_back({0.93,0.96,0,20,100});
			  Bins.push_back({0.96,1.0,0,15,100});
			}
			if(jets == 2){
			  Bins.push_back({0.65,0.75,0,50,120});
			  Bins.push_back({0.75,0.85,0,40,120});
			  Bins.push_back({0.85,0.9,0,30,120});
			  Bins.push_back({0.9,0.95,0,20,120});
			  Bins.push_back({0.95,1.0,0,120});
			}
			if(jets == 3){
			  Bins.push_back({0.55,0.65,0,110,200});
			  Bins.push_back({0.65,0.75,0,90,200});
			  Bins.push_back({0.75,0.85,0,70,200});
			  Bins.push_back({0.85,0.9,0,50,200});
			  Bins.push_back({0.9,1.0,0,200});
			}
			if(jets == 4){
			  Bins.push_back({0.55,0.65,0,150,300});
			  Bins.push_back({0.65,0.75,0,100,300});
			  Bins.push_back({0.75,0.85,0,80,300});
			  Bins.push_back({0.85,1.0,0,300});
			}
			if(jets == 5){
			 Bins.push_back({0.5,0.6,0,210,400});
			 Bins.push_back({0.6,0.7,0,180,400});
			 Bins.push_back({0.7,0.8,0,150,400});
			 Bins.push_back({0.8,1.0,0,400});
			}

		}//end channel 0 check
		if(channel == 1){
		  if(jets == 0){
			Bins.push_back({0.9,0.96,0,40});
			Bins.push_back({0.96,0.98,0,10,40});
			Bins.push_back({0.98,1.0,0,5,10,40});
		  }
		  if(jets == 1){
			Bins.push_back({0.65,0.75,0,50,120});
			Bins.push_back({0.75,0.85,0,40,120});
			Bins.push_back({0.85,0.9,0,30,120});
			Bins.push_back({0.9,0.95,0,20,120});
			Bins.push_back({0.95,1.0,0,120});
	          }
		  if(jets == 2){
			Bins.push_back({0.55,0.65,0,110,200});
			Bins.push_back({0.65,0.75,0,90,200});
			Bins.push_back({0.75,0.85,0,70,200});
			Bins.push_back({0.85,0.9,0,50,200});
			Bins.push_back({0.9,1.0,0,200});
		  }
		  if(jets == 3){
			Bins.push_back({0.55,0.65,0,150,300});
			Bins.push_back({0.65,0.75,0,100,300});
			Bins.push_back({0.75,0.85,0,80,300});
			Bins.push_back({0.85,1.0,0,300});
		  }
		  if(jets == 4){	
			 Bins.push_back({0.5,0.6,0,210,400});
			 Bins.push_back({0.6,0.7,0,180,400});
			 Bins.push_back({0.7,0.8,0,150,400});
			 Bins.push_back({0.8,1.0,0,400});
		  }

		}//end channel 1 check
		if(channel == 2){
		  if(jets == 0){
      			 Bins.push_back({0.7, 0.8, 0.,40.,120.});
			 Bins.push_back({0.8, 0.9, 0.,30.,120.});
			 Bins.push_back({0.9, 0.95, 0.,20.,120.});
			 Bins.push_back({0.95,1.0,0,15,120});
		  }
		  if(jets == 1){
     			Bins.push_back({0.55, 0.7, 0.,80.,200.});
                         Bins.push_back({0.7, 0.8, 0.,60.,200.});
                         Bins.push_back({0.8, 0.9, 0.,40.,200.});
                         Bins.push_back({0.9,1.0,0,30,200});
		  }
		  if(jets ==2){
			 Bins.push_back({0.5, 0.65, 0.,100.,300.});
                         Bins.push_back({0.65, 0.75, 0.,80.,300.});
                         Bins.push_back({0.75, 0.85, 0.,60.,300.});
                         Bins.push_back({0.85,1.0,0,300});

		  }
		  if(jets ==3){
			Bins.push_back({0.5,0.65, 0.,130.,400.});
		        Bins.push_back({0.65,0.8, 0.,100.,400.});
      			Bins.push_back({0.8,1.0,  0.,400.});

		 }
       		}//end channel 2 check
		if(channel == 3){
		  if(jets == 0){
			Bins.push_back({0.6,0.7,0,250});
			Bins.push_back({0.7,0.8,0,250});
			Bins.push_back({0.8,0.9,0,250});
			Bins.push_back({0.9,1.0,0,250});
	          }
		  if(jets == 1){
			Bins.push_back({0.55,0.7,0,250});
			Bins.push_back({0.7,0.85,0,250});
			Bins.push_back({0.85,1.0,0,250});
		  }

		}
		return Bins;
}
void unrollBins(vector<vector<double> > bins, ofstream& fstream ){

	fstream<<"RISRBIN ";
	for(int i=0; i<bins.size(); i++){
		for(int j=0; j<bins.at(i).size()-3; j++){
			fstream<< bins.at(i).at(0)<<","<<bins.at(i).at(1)<<" ";
		}
	}	
	fstream<<std::endl;
	fstream<<"MPERPBIN ";
	for(int i=0; i<bins.size(); i++){
		for(int j=2; j<bins.at(i).size()-1; j++){
			fstream<< bins.at(i).at(j)<<","<<bins.at(i).at(j+1)<<" ";
		}
	}
	fstream<<std::endl;
}
void macroBG(std::string chnlName, int chnlnum, std::string BFIname){
	//
	//read in TCHIWZ which has BG rolled into it for bg readouts	

	TFile* f = TFile::Open(BFIname.c_str());

	TList* list = f->GetListOfKeys();
//	TList* list2 = f2->GetListOfKeys();
	//list->Print();
	std::set<std::string> jets;
	std::vector<std::string> str_list;
//	std::vector<std::string> str_list2;
	//std::string channelName = "Ch3L";   ///change this
//	int CHANNELNUM = 3;                 ///and change this per run
	std::string channelName = chnlName;
	int CHANNELNUM = chnlnum;
	for(int i=0; i<list->GetSize(); i++){
		std::string keyname( list->At(i)->GetName() );
		std::size_t found = keyname.find(channelName);
  		if (found!=std::string::npos){
			str_list.push_back(keyname);
		}
		
	}

	//vector<vector<double> > bins = IDJets
	int nbinsx;
	for(int i=0; i<str_list.size(); i++){
// make each region to a single file
	ofstream regionfile;
	regionfile.open(str_list[i]+".csv");
		
//		regionfile<<str_list[i]<<std::endl;
		vector<string> sp1 = split(std::string(str_list[i]), '_');
		//vector<string> sp2 = split(sp1[1],'-');
		vector<string> sp2 = sp1;
		jets.insert(sp2[3]);

		//header csv
		regionfile<<"RegionName PType BinN NL NJ Yield Error\n";
		
		vector<vector<double> > bins;
		int nj;
		if(CHANNELNUM == 0){
		//bins = mapbins(CHANNELNUM, IDJets(sp2[1]));
			nj = IDJets(sp2[2]);
		}
		else{
		//bins = mapbins(CHANNELNUM, IDJets(sp2[2]));
			nj = IDJets(sp2[3]);
		}
		 //unrollBins( bins,regionfile);
	
	 	 //regionfile<<"RISRBIN ";
		//vector<string> bins;	
		//bins = risrmap[sp2[2]];
		/*for(int i=0; i<bins.size(); i++){
			regionfile<<bins[i]<<" ";
		}
		regionfile<<std::endl;
		regionfile<<"MPERPBIN ";
		bins = mmap[sp2[2]];
		for(int i=0; i<bins.size(); i++){
			regionfile<<bins[i]<<" ";
		}
		regionfile<<std::endl;*/

//modify for this to collect only BG	
		TH1D* data_obs = (TH1D*) f->Get((str_list[i]+"/data_obs").c_str());
//		ttbar ST ZDY DB Wjets TB QCD
		TH1D* ttbar = collectBG(f,str_list[i]+"/ttbar",str_list[i],"ttbar_");
		TH1D* ST    = collectBG(f, str_list[i]+"/ST",str_list[i],"ST_");
		TH1D* ZDY   = collectBG(f, str_list[i]+"/ZDY",str_list[i],"ZDY_");
		TH1D* DB    = collectBG(f, str_list[i]+"/DB",str_list[i],"DB_");
		TH1D* Wjets = collectBG(f, str_list[i]+"/Wjets",str_list[i],"Wjets_");
		TH1D* TB    = collectBG(f, str_list[i]+"/TB",str_list[i],"TB_");
		TH1D* QCD   = collectBG(f, str_list[i]+"/QCD",str_list[i],"QCD_");
		
		vector<TH1D*> allbgs = {ttbar, ST, ZDY, DB, Wjets, TB, QCD};
		TH1D* bgsum = sumBG(allbgs);

/*		TH1D* TChiWZ_2750268 = (TH1D*) f->Get((str_list[i]+"/TChiWZ_2750268").c_str());
		TH1D* TChiWZ_2750235 = (TH1D*) f->Get((str_list[i]+"/TChiWZ_2750235").c_str());
		TH1D* TChiWZ_2750183 = (TH1D*) f->Get((str_list[i]+"/TChiWZ_2750183").c_str());

		TH1D* TChiWZ_2000190  = (TH1D*) f->Get((str_list[i]+"/TChiWZ_2000190").c_str());
		TH1D* TChiWZ_2000170  = (TH1D*) f->Get((str_list[i]+"/TChiWZ_2000170").c_str());
		TH1D* TChiWZ_2000110  = (TH1D*) f->Get((str_list[i]+"/TChiWZ_2000110").c_str());

		TH1D* T2tt_5000490 = (TH1D*) f2->Get((str_list[i]+"/T2tt_5000490").c_str());
		TH1D* T2tt_5000450 = (TH1D*) f2->Get((str_list[i]+"/T2tt_5000450").c_str());
		TH1D* T2tt_5000413 = (TH1D*) f2->Get((str_list[i]+"/T2tt_5000413").c_str());
		TH1D* TSlepSlep_1750170 = (TH1D*) f3->Get((str_list[i]+"/TSlepSlep_1750170").c_str());
		TH1D* TSlepSlep_1750145 = (TH1D*) f3->Get((str_list[i]+"/TSlepSlep_1750145").c_str());
		TH1D* TSlepSlep_1750100 = (TH1D*) f3->Get((str_list[i]+"/TSlepSlep_1750100").c_str());

		TH1D* T2bW_3500270 = (TH1D*) f4->Get((str_list[i]+"/T2bW_3500270").c_str());
		TH1D* T2bW_3500300 = (TH1D*) f4->Get((str_list[i]+"/T2bW_3500300").c_str());
		TH1D* T2bW_3500340 = (TH1D*) f4->Get((str_list[i]+"/T2bW_3500340").c_str());

*/
//void loopBin(TH1D* h,int nbinsx, std::string str, ofstream& fstream, std::stri
//ng regionName, int nl, int nj)
		//dataobs appears to not be present in shape?
		
		//loop all bgs, find non null and get nbinsx
		for(int i=0; i<allbgs.size(); i++){
			if(allbgs.at(i) != NULL){
				nbinsx = allbgs.at(i)->GetNbinsX();
				break;	
			}	
		}
		//nbinsx = data_obs->GetNbinsX();
		loopBin(data_obs,nbinsx,"dataobs",regionfile,str_list[i],CHANNELNUM, nj);
		loopBin(ttbar,nbinsx,"ttbar",regionfile,str_list[i],CHANNELNUM, nj);
		loopBin(ST,nbinsx,"ST",regionfile,str_list[i],CHANNELNUM, nj);
		loopBin(ZDY,nbinsx,"ZDY",regionfile,str_list[i],CHANNELNUM, nj);
		loopBin(DB,nbinsx,"DB",regionfile,str_list[i],CHANNELNUM, nj);
		loopBin(Wjets,nbinsx,"Wjets",regionfile,str_list[i],CHANNELNUM, nj);
		loopBin(TB,nbinsx,"TB",regionfile,str_list[i],CHANNELNUM, nj);
		loopBin(QCD,nbinsx,"QCD",regionfile,str_list[i],CHANNELNUM, nj);
		loopBin(bgsum, nbinsx, "all-bkg",regionfile,str_list[i],CHANNELNUM, nj);
/*		loopBin(TChiWZ_2750268,nbinsx,"WZ2750268",regionfile);
		loopBin(TChiWZ_2750235,nbinsx,"WZ2750235",regionfile);
		loopBin(TChiWZ_2750183,nbinsx,"WZ2740183",regionfile);
		loopBin(TChiWZ_2000190,nbinsx,"WZ2000190",regionfile);
		loopBin(TChiWZ_2000170,nbinsx,"WZ2000170",regionfile);
		loopBin(TChiWZ_2000110,nbinsx,"WZ2000110",regionfile);
		loopBin(T2tt_5000490,nbinsx,"TT5000490",regionfile);
		loopBin(T2tt_5000450,nbinsx,"TT5000450",regionfile);
		loopBin(T2tt_5000413,nbinsx,"TT5000413",regionfile);
		loopBin(TSlepSlep_1750170,nbinsx,"SS1750170",regionfile);
		loopBin(TSlepSlep_1750145,nbinsx,"SS1750145",regionfile);
		loopBin(TSlepSlep_1750100,nbinsx,"SS1750100",regionfile);
		loopBin(T2bW_3500270,nbinsx,"bW3500270",regionfile);
		loopBin(T2bW_3500300,nbinsx,"bW3500300",regionfile);
		loopBin(T2bW_3500340,nbinsx,"bW3500340",regionfile);
*/	
		regionfile.close();			
//		if(i == 10)	break;
//		break;
	}
	//f->cd("Ch2L_OSmumu-muGmuG-0j0svS-ge1j0bISR-PTISR0-gamT0");
//	TDirectory* hdir = (TDirectory*) f2->Get("Ch2L_OSmumu-muGmuG-0j0svS-ge1j0bISR-PTISR0-gamT0");
//	TList* hlist = hdir->GetListOfKeys();
//	hlist->Print();

	TH1D* data_obs = (TH1D*) f->Get((str_list[0]+"/data_obs").c_str());
//	data_obs->Draw();

	TH1D* sig = (TH1D*) f->Get("Ch2L_OSmumu_muGmuG_0j0svS_ge1j0bISR_PTISR0_gamT0/TChiWZ_2750268");
	
//	sig->Draw();
	set<std::string >::iterator itr;
    cout << "\nThe set jets is : \n";
    for (itr = jets.begin(); itr != jets.end(); itr++)
    {
        cout << *itr<<" ";
    }
    cout << endl;

}
