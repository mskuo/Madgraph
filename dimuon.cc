#include "stdlib.h"
#include <iostream>

#include "TFile.h"
#include "TH1F.h"
#include "TNtupleD.h"
#include "TClonesArray.h"
#include "TLorentzVector.h"

#include "classes/DelphesClasses.h"

#include "ExRootAnalysis/ExRootTreeReader.h"
#include "ExRootAnalysis/ExRootTreeBranch.h"

using namespace std;

int main()
{
	TFile *fout ;
	fout = new TFile("pp_z_dimuons_7TeV_result.root","recreate") ;

	TChain *chain = new TChain("Delphes") ;
	chain->Add("pp_z_dimuons_7TeV.root") ;
   
	ExRootTreeReader *treeReader = new ExRootTreeReader(chain) ;
    
	TClonesArray *branchParticle = treeReader -> UseBranch("Particle") ;
    
//	TNtupleD *nt = new TNtupleD("nt","","muplus_pt:muplus_eta:muplus_phi:muminus_pt:muminus_eta:muminus_phi:tprod") ;
//	enum { _muplus_pt, _muplus_eta, _muplus_phi, _muminus_pt, _muminus_eta, _muminus_phi, _tprod, _nvar } ;
//	TNtupleD *nt = new TNtupleD("nt","","PID:e:px:py:pz:pt:eta:phi") ;
//	enum { PID, e, px, py, pz, pt, eta, phi, _nvar } ;
 	TTree *outtree ; 
	outtree = new TTree("nt", "nt" )  ;
 
	int n_entries = treeReader->GetEntries() ;

//	outtree -> Branch ("npar" , &npar , "npar/I" ) ;
	
	int c = 0 ;
	int npar ;
	int status[3000] ;
	int PID[3000] ;
     	double e[3000] , px[3000], py[3000], pz[3000], pt[3000], eta[3000], phi[3000] ;

	outtree -> Branch ("c" , &c , "c/I" ) ;
	outtree -> Branch ("PID" , PID , "PID[c]/I" ) ;
	outtree -> Branch ("e" , e , "e[c]/D" ) ;  
	outtree -> Branch ("px" , px , "px[c]/D" ) ;
	outtree -> Branch ("py" , py , "py[c]/D" ) ;
	outtree -> Branch ("pz" , pz , "pz[c]/D" ) ;
	outtree -> Branch ("pt" , pt , "pt[c]/D" ) ;
	outtree -> Branch ("eta", eta, "eta[c]/D" ) ;
	outtree -> Branch ("phi", phi, "phi[c]/D" ) ;
	outtree -> Branch ("status", status, "status[c]/I" ) ;


	for( int entry = 0 ; entry < n_entries ; entry++ ) 
	{
		c = 0 ; 
		npar = 0 ;
		status[3000] = 0 ;
		PID[3000] = 0 ;
	     	e[3000] = 0. ;
		px[3000] = 0. ;
		py[3000] = 0. ;
		pz[3000] = 0. ;
		pt[3000] = 0. ;
		eta[3000] = 0. ;
		phi[3000] = 0.;

		treeReader -> ReadEntry(entry) ;
        
		//Notification for running 
		if ( ((entry+1) % 100) == 0 || entry+1 == n_entries )
			printf( "processing %d/%d.\n", entry+1, n_entries ) ;
        
//		GenParticle *gen_muplus = 0, *gen_muminus = 0 ;
		GenParticle *particles = 0 ;
       		npar = branchParticle -> GetEntries() ; 

		for ( int idx = 0 ; idx < npar ; idx++ ) 
		{
		
//			GenParticle *gen = (GenParticle*) branchParticle -> At(idx) ;
//			particles = (GenParticle*) branchParticle -> At (gen -> Status ) ;
			particles = (GenParticle*) branchParticle -> At (idx) ;

			if ( particles == 0 ) 
				continue ;
			if ( particles -> P4().Pt() < 0.01 || particles -> P4().E() < 0.01 )
				continue ;

//			if ( gen -> PID == +13 ) 
//			{ // mu-
//				gen_muplus = (GenParticle*) branchParticle -> At (gen -> Status ) ;
//			}
//
//			if ( gen -> PID == -13 ) 
//			{ // mu+
//				gen_muminus= (GenParticle*) branchParticle -> At (gen -> Status ) ;
//			}

			//Why selection about Daughter ?    
//			if ( gen -> PID == +15 && (gen->D2 - gen->D1 + 1 ) == 3 ) 
//			{// tau-
//				gen_pim = (GenParticle*)branchParticle->At(gen->D1);
//				if (gen_pim->PID!=-211)
//					gen_pim = 0;
//				
//				gen_tmpi0 = (GenParticle*)branchParticle->At(gen->D1+1);
//				if (gen_tmpi0->PID!=111)
//					gen_tmpi0 = 0;
//			}
//			if ( gen->PID == -15 && ( gen->D2 - gen->D1 + 1) == 3) 
//			{ // tau+
//				gen_pip = (GenParticle*)branchParticle->At(gen->D1);
//				if (gen_pip->PID!=+211) 
//					gen_pip = 0;
//       
//				gen_tppi0 = (GenParticle*)branchParticle->At(gen->D1+1);
//				if (gen_tppi0->PID!=111) 
//					gen_tppi0 = 0;
//			}
        
//		if  (gen_muplus == 0 || gen_muminus == 0 ) 
//			continue ;
//     		if (gen_muplus -> P4().Pt() == 0 || gen_muminus -> P4().Pt() == 0 )
//			continue ; 


        //double triple_prod = gen_pi0->P4().Vect().Dot(gen_pip->P4().Vect().Cross(gen_pim->P4().Vect()));

//		double var[_nvar] ;
			PID[c] = particles -> PID ;	
			px[c]  = particles -> P4().Px() ;
			py[c]  = particles -> P4().Py() ;
			pz[c]  = particles -> P4().Pz() ;
			pt[c]  = particles -> P4().Pt() ;
			e[c]   = particles -> P4().E() ;
			eta[c] = particles -> P4().Eta() ;
			phi[c] = particles -> P4().Phi() ;
			status[c] = particles -> Status ;
			c++ ;		





/*		double var[_nvar];
        
		var[_muplus_pt]  = gen_muplus->P4().Pt();
		var[_muplus_eta] = gen_muplus->P4().Eta();
        	var[_muplus_phi] = gen_muplus->P4().Phi();

        	var[_muminus_pt]  = gen_muminus->P4().Pt();
        	var[_muminus_eta] = gen_muminus->P4().Eta();
        	var[_muminus_phi] = gen_muminus->P4().Phi();
*/        
        	//var[_tprod] = triple_prod;
        	}

		outtree -> Fill() ;


				
	}


	fout -> Write() ;
	fout -> Close() ;
}

