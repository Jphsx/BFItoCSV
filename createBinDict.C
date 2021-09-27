

/*class VD{
	public:
	std::vector<double> vec{};
	void a(double value){
		vec.push_back(value);
	};
};*/
using namespace std;
class VD : public vector<double> {
public:
  VD() {}

  VD(const vector<double>& vd){
    for(auto d : vd)
      *this += d;
  }

  VD& a(double d){
    (*this).push_back(d);
    return *this;
  }

  virtual ~VD() {}

  VD& operator += (double d){
    this->push_back(d);
    return *this;
  }

  VD& operator += (const VD& list){
    for(int i = 0; i < int(list.size()); i++)
      this->push_back(list[i]);

    return *this;
  }
};

class RBin{
	public:
  	double _Rlow;
	double _Rhigh;
	std::vector<double> _mbins{};
	RBin(double Rlow, double Rhigh, const std::vector<double>& mbins){
		_Rlow = Rlow;
		_Rhigh = Rhigh;
		_mbins = mbins;
	};
};

void printRBins(int lep, int jet, std::vector<RBin> RBins, ofstream& f ){
	int binctr=1;
//	std::cout<<"printing bins\n";
//	std::cout<<RBins.size()<<std::endl;
	for(int i=0; i<RBins.size(); i++){
	//	std::cout<<RBins.at(i)._mbins.size()<<std::endl;
		for(int j=0; j<RBins.at(i)._mbins.size()-1; j++){
			f<<lep<<"_"<<jet<<"_"<<binctr<<" "<<RBins.at(i)._Rlow<<" "<<RBins.at(i)._Rhigh<<" ";
			f<<RBins.at(i)._mbins.at(j)<<" "<<RBins.at(i)._mbins.at(j+1)<<"\n";
			binctr++;
		}
	}
}	
void populateBins( int Nlep, int index, std::vector<RBin>& RBins ){
bool maskSR= false;

  if(Nlep == 0){
    if(index == 0){
      RBins.push_back(RBin(0.95,  0.985, VD().a(0.).a(40.)));
      if(!maskSR)
        RBins.push_back(RBin(0.985, 1.00,  VD().a(0.).a(5.).a(10.).a(40.)));
    }
    if(index == 1){
      RBins.push_back(RBin(0.8,   0.90,  VD().a(0.).a(100.)));
      RBins.push_back(RBin(0.90,  0.93,  VD().a(0.).a(20.).a(100.)));
      if(!maskSR){
        RBins.push_back(RBin(0.93,  0.96,  VD().a(0.).a(20.).a(100.)));
        RBins.push_back(RBin(0.96,  1.0,   VD().a(0.).a(15.).a(100.)));
      }
    }
    if(index == 2){
      RBins.push_back(RBin(0.65,  0.75,  VD().a(0.).a(50.).a(120.)));
      RBins.push_back(RBin(0.75,  0.85,  VD().a(0.).a(40.).a(120.)));
      if(!maskSR){
        RBins.push_back(RBin(0.85,  0.9,   VD().a(0.).a(30.).a(120.)));
        RBins.push_back(RBin(0.9,   0.95,  VD().a(0.).a(20.).a(120.)));
        RBins.push_back(RBin(0.95,  1.0,   VD().a(0.).a(120.)));
      }
    }
    if(index == 3){
      RBins.push_back(RBin(0.55,  0.65, VD().a(0.).a(110.).a(200.)));
      RBins.push_back(RBin(0.65,  0.75, VD().a(0.).a(90.).a(200.)));
      if(!maskSR){
        RBins.push_back(RBin(0.75,  0.85, VD().a(0.).a(70.).a(200.)));
        RBins.push_back(RBin(0.85,  0.9,  VD().a(0.).a(50.).a(200.)));
        RBins.push_back(RBin(0.9,   1.0,  VD().a(0.).a(200.)));
      }
    }
    if(index == 4){
      RBins.push_back(RBin(0.55,  0.65, VD().a(0.).a(150.).a(300.)));
      RBins.push_back(RBin(0.65,  0.75, VD().a(0.).a(100.).a(300.)));
      if(!maskSR){
        RBins.push_back(RBin(0.75,  0.85, VD().a(0.).a(80.).a(300.)));
        RBins.push_back(RBin(0.85,  1.0,  VD().a(0.).a(300.)));
      }
    }
    if(index == 5){
      RBins.push_back(RBin(0.5,   0.6,  VD().a(0.).a(210.).a(400.)));
      RBins.push_back(RBin(0.6,   0.7,  VD().a(0.).a(180.).a(400.)));
      if(!maskSR){
        RBins.push_back(RBin(0.7,   0.8,  VD().a(0.).a(150.).a(400.)));
        RBins.push_back(RBin(0.8,   1.0,  VD().a(0.).a(400.)));
      }
    }
  }

  if(Nlep == 1){
    if(index == 0){
      RBins.push_back(RBin(0.9,   0.96,   VD().a(0.).a(40.)));
      RBins.push_back(RBin(0.96,  0.98,   VD().a(0.).a(10.).a(40.)));
      if(!maskSR){
        RBins.push_back(RBin(0.98,  1.00,   VD().a(0.).a(5.).a(10.).a(40.)));
      }
    }
    if(index == 1){
      RBins.push_back(RBin(0.65,  0.75,  VD().a(0.).a(50.).a(120.)));
      RBins.push_back(RBin(0.75,  0.85,  VD().a(0.).a(40.).a(120.)));
      if(!maskSR){
        RBins.push_back(RBin(0.85,  0.9,   VD().a(0.).a(30.).a(120.)));
        RBins.push_back(RBin(0.9,   0.95,  VD().a(0.).a(20.).a(120.)));
        RBins.push_back(RBin(0.95,  1.0,   VD().a(0.).a(120.)));
      }
    }
    if(index == 2){
      RBins.push_back(RBin(0.55,  0.65, VD().a(0.).a(110.).a(200.)));
      RBins.push_back(RBin(0.65,  0.75, VD().a(0.).a(90.).a(200.)));
      if(!maskSR){
        RBins.push_back(RBin(0.75,  0.85, VD().a(0.).a(70.).a(200.)));
        RBins.push_back(RBin(0.85,  0.9,  VD().a(0.).a(50.).a(200.)));
        RBins.push_back(RBin(0.9,   1.0,  VD().a(0.).a(200.)));
      }
    }
    if(index == 3){
      RBins.push_back(RBin(0.55,  0.65, VD().a(0.).a(150.).a(300.)));
      RBins.push_back(RBin(0.65,  0.75, VD().a(0.).a(100.).a(300.)));
      if(!maskSR){
        RBins.push_back(RBin(0.75,  0.85, VD().a(0.).a(80.).a(300.)));
        RBins.push_back(RBin(0.85,  1.0,  VD().a(0.).a(300.)));
      }
    }
    if(index == 4){
      RBins.push_back(RBin(0.5,   0.6,  VD().a(0.).a(210.).a(400.)));
      RBins.push_back(RBin(0.6,   0.7,  VD().a(0.).a(180.).a(400.)));
      if(!maskSR){
        RBins.push_back(RBin(0.7,   0.8,  VD().a(0.).a(150.).a(400.)));
        RBins.push_back(RBin(0.8,   1.0,  VD().a(0.).a(400.)));
      }
    }
  }

  if(Nlep == 2){
    if(index == 0){
       RBins.push_back(RBin(0.7,   0.8,   VD().a(0.).a(40.).a(120.)));
       RBins.push_back(RBin(0.8,   0.9,   VD().a(0.).a(30.).a(120.)));
       //RBins.push_back(RBin(0.8,   0.9,   VD().a(0.).a(30.).a(70.).a(120.))); // 5-3
       if(!maskSR){
         RBins.push_back(RBin(0.9,   0.95,  VD().a(0.).a(20.).a(120.)));
	//RBins.push_back(RBin(0.9,   0.95,  VD().a(0.).a(20.).a(50.).a(120.)));//5-3
         RBins.push_back(RBin(0.95,  1.0,   VD().a(0.).a(15.).a(120.)));
       }
    }
    if(index == 1){
      RBins.push_back(RBin(0.55,  0.7,  VD().a(0.).a(80.).a(200.)));
      RBins.push_back(RBin(0.7,   0.8,  VD().a(0.).a(60.).a(200.)));
     // RBins.push_back(RBin(0.7,   0.8,  VD().a(0.).a(60.).a(120.).a(200.)));//5-3
      if(!maskSR){
        RBins.push_back(RBin(0.8,   0.9,  VD().a(0.).a(40.).a(200.)));
     //  RBins.push_back(RBin(0.8,   0.9,  VD().a(0.).a(40.).a(100.).a(200.)));//5-3
	  RBins.push_back(RBin(0.9,   1.0,  VD().a(0.).a(30.).a(200.)));
      }
    }
    if(index == 2){
      RBins.push_back(RBin(0.5,   0.65,  VD().a(0.).a(100.).a(300.)));
      RBins.push_back(RBin(0.65,  0.75,  VD().a(0.).a(80.).a(300.)));
      if(!maskSR){
        RBins.push_back(RBin(0.75,  0.85,  VD().a(0.).a(60.).a(300.)));
        RBins.push_back(RBin(0.85,  1.0,   VD().a(0.).a(300.)));
      }
    }
    if(index == 3){
      RBins.push_back(RBin(0.5,   0.65,  VD().a(0.).a(130.).a(400.)));
      if(!maskSR){
        RBins.push_back(RBin(0.65,  0.8,   VD().a(0.).a(100.).a(400.)));
        RBins.push_back(RBin(0.8,   1.0,   VD().a(0.).a(400.)));
      }
    }
  }

  if(Nlep == 3){
    if(index == 0){
       RBins.push_back(RBin(0.6,  0.7,  VD().a(0.).a(250.)));
       RBins.push_back(RBin(0.7,  0.8,  VD().a(0.).a(250.)));
       if(!maskSR){
         RBins.push_back(RBin(0.8,  0.9,  VD().a(0.).a(250.)));
         RBins.push_back(RBin(0.9,  1.0,  VD().a(0.).a(250.)));
       }
    }
    if(index == 1){
      RBins.push_back(RBin(0.55,   0.7,  VD().a(0.).a(250.)));
      if(!maskSR){
        RBins.push_back(RBin(0.7,    0.85, VD().a(0.).a(250.)));
        RBins.push_back(RBin(0.85,   1.0,  VD().a(0.).a(250.)));
      }
    }
  }






}



void createBinDict(){
	//std::vector<RBin> RBins{};
//	populateBins(0,1,RBins);
//	printRBins(0, 1, RBins );
	ofstream f;
	f.open("bindict_b51.csv");
	//f.open("bindict_b53.csv");
	f<<"binKey Rlow Rhigh Mplow Mphigh\n";
	for(int lep=0; lep<=3; lep++){
		for(int jet=0;jet<=5; jet++){
			std::vector<RBin> RBins{};
			populateBins(lep,jet,RBins);
			if(RBins.size()>0){
				printRBins(lep,jet,RBins, f);
			}
		}
	}
	f.close();

}
















