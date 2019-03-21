#include <TFile.h>
#include <TH1F.h>
#include <TTree.h>
#include <TBranch.h>
#include <TLeaf.h>
#include <TLorentzVector.h>
#include <vector>
#include <iostream>
#include <math.h>

using namespace std ;

int main()
{
	//Load the data
	TFile *in = TFile::Open("pp_z_dimuons_7TeV_result.root");
	//create the new file to store the result
	TFile *out = new TFile("Zdrop_dimuons_delphes_7TeV.root" , "recreate" ) ;
	TTree *Candidates ;
	TTree *outtree = new TTree("ZCandidates" , "ZCandidates" ) ;

	//Load the data into Candidates
	in -> GetObject( "nt" , Candidates ) ;
	int PID[3000] ;
        double e[3000] , px[3000], py[3000], pz[3000], pt[3000], eta[3000], phi[3000] ;
	int c ;
	int status[3000] ;
	int counting = 0 ;

	int n_particles ; 
//	double s_electron ;
	double Mass ;
	double M ;
	double Z_pT ;
	double Z_drop ;

//	double Pt_plus ;
//	double Pt_minus ;

	//output branch
	outtree -> Branch ("Mass" , &Mass , "Mass/D" ) ;
	outtree -> Branch ("n_particles" , &n_particles , "n_particles/I" ) ;
	outtree -> Branch ("Z_drop" , &Z_drop , "Z_drop/D" ) ;	
	outtree -> Branch ("Z_pT" , &Z_pT , "Z_pT/D" ) ;
	outtree -> Branch ("M" , &M , "M/D" ) ;

	//For particles
	TLorentzVector LV_particles_variables ; 
	vector<TLorentzVector> LV_particles ;

	//For muons
	TLorentzVector LV_dimuon ; 
	vector<TLorentzVector> LV_muon_plus ;
	vector<TLorentzVector> LV_muon_minus ;

	//For electrons
	TLorentzVector LV_dielectron ; 
	vector<TLorentzVector> LV_electron_plus ;
	vector<TLorentzVector> LV_electron_minus ;


	TLorentzVector LV_jet ;

	Candidates -> SetBranchAddress("PID" , PID ) ;
	Candidates -> SetBranchAddress("e" , e ) ;
	Candidates -> SetBranchAddress("px" , px ) ;
	Candidates -> SetBranchAddress("py" , py ) ;
	Candidates -> SetBranchAddress("pz" , pz ) ;
	Candidates -> SetBranchAddress("pt" , pt ) ;
	Candidates -> SetBranchAddress("eta" , eta ) ;
	Candidates -> SetBranchAddress("phi" , phi ) ;
	Candidates -> SetBranchAddress("c"   , &c ) ;
	Candidates -> SetBranchAddress("status"  , status ) ;

	//Loop all events
	for ( int evt = 0 ; evt < Candidates -> GetEntries()  ; evt++ ) 
	{

		Candidates -> GetEntry(evt) ;

		LV_particles.clear() ;
		LV_muon_plus.clear() ;
		LV_muon_minus.clear() ;
		LV_electron_plus.clear() ;
		LV_electron_minus.clear() ;

		//Loop for all particles in an event
		for ( int i = 0 ; i < c ; i++ ) 
		{
			if ( status[i] != 1 )
				continue ;
						
			LV_particles_variables.SetPxPyPzE  ( px[i] , py[i] , pz[i] , e[i] ) ; 
	
			if ( PID[i] == -13 )
			{
//				if ( pt[i] > 30. && eta[i] < 1.4 )
//				{
					LV_muon_plus.push_back ( LV_particles_variables ) ;	
//				}
			}
			if ( PID[i] == 13 )
			{
//				if ( pt[i] > 30. && eta[i] < 1.4 ) 
//				{	
					LV_muon_minus.push_back ( LV_particles_variables ) ;	
//				}
			}


			else
			{
				LV_particles.push_back ( LV_particles_variables ) ;		
			}	


		}


		if ( LV_muon_plus.size() == 0 || LV_muon_minus.size() == 0 )
		{ 
//			cout << "Plus  = " << LV_muon_plus.size() << endl ;
//			cout << "Minus = " << LV_muon_minus.size() << endl << endl ;
			counting++ ;
		}


		
//		if ( int(LV_muon_plus.size()) > 6 || int(LV_muon_minus.size()) > 6 )
//			continue ;

		for ( int i = 0 ; i < int(LV_muon_plus.size() ) ; i++ )
		{
			for ( int j = 0 ; j < int(LV_muon_minus.size() ) ; j++ )
			{
				//Z_drop
				//isolated
//				Pt_plus = 0. ;
//				Pt_minus = 0. ;
				n_particles = 0 ;
				Mass = 0. ;
				LV_jet = TLorentzVector( 0. , 0. , 0. , 0. ) ;
				M = 0. ;
				Z_pT = 0. ;

//				for ( int k = 0 ; k < int(LV_particles.size() ) ; k++ )
//				{
//					//If deltaR < .... , pt_all / pt_muon 
//					if ( LV_muon_plus[i].DeltaR(LV_particles[k] ) < 0.8 ) 
//					{
//						Pt_plus +=LV_particles[k].Pt() ;
//						LV_jet += LV_particles[k] ;
//					}
//					if ( LV_muon_minus[j].DeltaR(LV_particles[k] ) < 0.8 ) 
//					{
//						Pt_minus +=LV_particles[k].Pt() ;
//						LV_jet += LV_particles[k] ;
//					}
//						
//				}
				
//				Pt_plus = LV_muon_plus[i].Pt() / Pt_plus ;
//				Pt_minus = LV_muon_minus[j].Pt() / Pt_minus;
//				cout << "Pt_plus = " << Pt_plus << endl ;
//				cout << "Pt_minus = " << Pt_minus << endl ;

//				if ( Pt_plus < 0.3 && Pt_minus < 0.3 ) 
//				{
				LV_dimuon = LV_muon_plus[i] + LV_muon_minus[j] ;
				Mass = LV_dimuon.M() ;
				Z_pT = LV_dimuon.Pt() ;
				//select events near mass = 91.2eV
				for ( int k = 0 ; k < int(LV_particles.size() ) ; k++ )
				{
					if ( LV_dimuon.DeltaR(LV_particles[k] ) < 0.8 )
					{
						LV_jet += LV_particles[k] ;
						n_particles++ ;
					}
				}
				LV_jet += LV_dimuon ;
				M = LV_jet.M() ;
				Z_drop = ( pow(M,2) - pow(Mass,2) ) / (2*Z_pT) ;

//				cout << "M = " << M << endl ;
//				cout << "Mass = " << Mass << endl ;
//				cout << "Z_drop = " << Z_drop << endl << endl ;
				
				outtree -> Fill() ;


//				}		
			}
		}

//		for ( int i = 0 ; i < int(LV_electron_plus.size() ) ; i++ )
//		{
//			for ( int j = 0 ; j < int(LV_electron_minus.size() ) ; j++ )
//			{
//				LV_dielectron = LV_electron_plus[i] + LV_electron_minus[j] ;
//				s_electron = LV_dielectron.M() ;
//				h2 -> Fill(s_electron) ;		 
//			}
//		}

	if ( evt%100 == 0 || evt == Candidates -> GetEntries() ) 
	cout << "Complete " <<  evt << "th event in " << Candidates -> GetEntries() << "events. " << endl ;  
	}
		LV_particles.clear() ;
		LV_muon_plus.clear() ;
		LV_muon_minus.clear() ;

		LV_electron_plus.clear() ;
		LV_electron_minus.clear() ;

	cout << "Number of events without dimuons = " << counting << "/" << Candidates -> GetEntries() << endl ;


	in -> Close() ;
	out -> Write() ;
	out -> Close() ;
}	
