//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Fri Jan 13 11:10:55 2023 by ROOT version 6.26/10
// from TTree tracktree/Tree of svtx tracks
// found on file: isotrack_output.root
//////////////////////////////////////////////////////////

#pragma once
#ifndef IsotrackHitAnalysis_h
#define IsotrackHitAnalysis_h

#include "ClusterContainer.h"
#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TH1F.h>
#include <TH2F.h>
#include <TRandom3.h>
#include <TEfficiency.h>
#include <iostream>
#include <fstream>
#include <string> 

// Header file for the classes stored in the TTree if any.

class IsotrackHitAnalysis {
    private :

        ////////////////////////////
        // Input option variables //
        ////////////////////////////
       
        std::string OUTPUT_FILENAME;

        bool USE_TOWER_INFO;
        bool USE_TRUTH_INFO;
        bool USE_CENTRALITY;
        bool USE_PARTICLE_GUN;

        float CENTRALITY_CUT;

        // track cuts
        float D0_CUT; // m
        float Z0_CUT; // m
        float PT_CUT;  // GeV

        // cuts for matching to other tracks
        float MATCHED_PT_CUT; // GeV
        float MATCHED_DR_CUT;
        float MATCHED_ETA_CUT; 

        // cuts for matching to neutral truth particles
        float MATCHED_NEUTRAL_TRUTH_PT_CUT; // GeV
        float MATCHED_NEUTRAL_TRUTH_ETA_CUT;
        float MATCHED_NEUTRAL_TRUTH_DR_CUT;

        // cuts for cluster matching
        float CEMC_MATCHING_DR_CUT;
        float IHCAL_MATCHING_DR_CUT;
        float OHCAL_MATCHING_DR_CUT;

        // MIP cuts
        float CEMC_MIP_ENERGY; // GeV
        float IHCAL_MIP_ENERGY; // GeV

        bool TRACKING_LOCATION;

        /////////////
        // TChains //
        /////////////
  
        TChain          *fChainT; //!pointer to the analyzed TTree or TChain
        Int_t           fCurrent; //!current Tree number in a TChain

        // Fixed size dimensions of array or collections stored in the TTree if any.
        
        ///////////////////////////////////////////////
        // Calorimeter g4hits variables and branches //
        ///////////////////////////////////////////////
        
        // Declaration of leaf types
        Int_t           n_truth;
        Float_t         *truthenergy = new Float_t[500000];
        Float_t         *trutheta = new Float_t[500000];
        Float_t         *truthphi = new Float_t[500000];
        Float_t         *truthpt = new Float_t[500000];
        Float_t         *truthp = new Float_t[500000];
        Int_t           *truthpid = new Int_t[500000];
        Int_t           *truth_track_id = new Int_t[500000];
        Int_t           *truth_parent_id = new Int_t[500000];
        Int_t           *truth_vertex_id = new Int_t[500000];
        Int_t           n_vertex;
        Int_t           *vertex_id = new Int_t[500000];
        Float_t         *vertex_x = new Float_t[500000];
        Float_t         *vertex_y = new Float_t[500000];
        Float_t         *vertex_z = new Float_t[500000];
        Int_t           n_tracks; 
        Float_t         tr_p[2000];   //[n_tracks]
        Float_t         tr_pt[2000];   //[n_tracks]
        Float_t         tr_phi[2000];   //[n_tracks]
        Float_t         tr_eta[2000];   //[n_tracks]
        Float_t         tr_cemc_eta[2000];   //[n_tracks]
        Float_t         tr_cemc_phi[2000];   //[n_tracks]
        Float_t         tr_ihcal_eta[2000];   //[n_tracks]
        Float_t         tr_ihcal_phi[2000];   //[n_tracks]
        Float_t         tr_ohcal_eta[2000];   //[n_tracks]
        Float_t         tr_ohcal_phi[2000];   //[n_tracks]
        Int_t           tr_truth_track_id[2000];   //[n_tracks]
        Float_t         centrality;
        Int_t           EM_n;
        Float_t         *EM_x = new Float_t[500000];
        Float_t         *EM_y = new Float_t[500000];
        Float_t         *EM_z = new Float_t[500000];
        Float_t         *EM_e = new Float_t[500000];
        Int_t           *EM_track_id = new Int_t[500000];
        Int_t           IH_n;
        Float_t         *IH_x = new Float_t[500000];
        Float_t         *IH_y = new Float_t[500000];
        Float_t         *IH_z = new Float_t[500000];
        Float_t         *IH_e = new Float_t[500000];
        Int_t           *IH_track_id = new Int_t[500000];
        Int_t           OH_n;
        Float_t         *OH_x = new Float_t[500000];
        Float_t         *OH_y = new Float_t[500000];
        Float_t         *OH_z = new Float_t[500000];
        Float_t         *OH_e = new Float_t[500000];
        Int_t           *OH_track_id = new Int_t[500000];
        Int_t           n_twr_cemc;
        Float_t         twr_cemc_e[25000];   //[n_twr_cemc]
        Float_t         twr_cemc_eta[25000];   //[n_twr_cemc]
        Float_t         twr_cemc_phi[25000];   //[n_twr_cemc]
        Int_t           n_twr_ihcal;
        Float_t         twr_ihcal_e[2000];   //[n_twr_ihcal]
        Float_t         twr_ihcal_eta[2000];   //[n_twr_ihcal]
        Float_t         twr_ihcal_phi[2000];   //[n_twr_ihcal]
        Int_t           n_twr_ohcal;
        Float_t         twr_ohcal_e[2000];   //[n_twr_ohcal]
        Float_t         twr_ohcal_eta[2000];   //[n_twr_ohcal]
        Float_t         twr_ohcal_phi[2000];   //[n_twr_ohcal]

        // List of branches
        TBranch        *b_n_truth;   //!
        TBranch        *b_truthenergy;   //!
        TBranch        *b_trutheta;   //!
        TBranch        *b_truthphi;   //!
        TBranch        *b_truthpt;   //!
        TBranch        *b_truthp;   //!
        TBranch        *b_truthpid;   //!
        TBranch        *b_truth_track_id;   //!
        TBranch        *b_truth_vertex_id;   //!
        TBranch        *b_truth_parent_id;   //!
        TBranch        *b_n_vertex;   //!
        TBranch        *b_vertex_id;   //!
        TBranch        *b_vertex_x;   //!
        TBranch        *b_vertex_y;   //!
        TBranch        *b_vertex_z;   //! 
        TBranch        *b_n_tracks;   //! 
        TBranch        *b_tr_p;   //! 
        TBranch        *b_tr_pt;   //!
        TBranch        *b_tr_phi;   //!
        TBranch        *b_tr_eta;   //!
        TBranch        *b_tr_cemc_eta;   //!
        TBranch        *b_tr_cemc_phi;   //!
        TBranch        *b_tr_ihcal_eta;   //!
        TBranch        *b_tr_ihcal_phi;   //!
        TBranch        *b_tr_ohcal_eta;   //!
        TBranch        *b_tr_ohcal_phi;   //!
        TBranch        *b_tr_truth_track_id;   //!
        TBranch        *b_centrality;   //!
        TBranch        *b_EM_n;   //!
        TBranch        *b_EM_x;   //!
        TBranch        *b_EM_y;   //!
        TBranch        *b_EM_z;   //!
        TBranch        *b_EM_e;
        TBranch        *b_EM_track_id;   //!
        TBranch        *b_IH_n;   //!
        TBranch        *b_IH_x;   //!
        TBranch        *b_IH_y;   //!
        TBranch        *b_IH_z;   //!
        TBranch        *b_IH_e;
        TBranch        *b_IH_track_id;   //!
        TBranch        *b_OH_n;   //!
        TBranch        *b_OH_x;   //!
        TBranch        *b_OH_y;   //!
        TBranch        *b_OH_z;   //!
        TBranch        *b_OH_e;
        TBranch        *b_OH_track_id;   //!
        TBranch        *b_n_twr_cemc;   //!
        TBranch        *b_twr_cemc_e;   //!
        TBranch        *b_twr_cemc_eta;   //!
        TBranch        *b_twr_cemc_phi;   //!
        TBranch        *b_n_twr_ihcal;   //!
        TBranch        *b_twr_ihcal_e;   //!
        TBranch        *b_twr_ihcal_eta;   //!
        TBranch        *b_twr_ihcal_phi;   //!
        TBranch        *b_n_twr_ohcal;   //!
        TBranch        *b_twr_ohcal_e;   //!
        TBranch        *b_twr_ohcal_eta;   //!
        TBranch        *b_twr_ohcal_phi;   //! 
        

        enum caloType{cemc=0, ihcal=1, ohcal=2};

        ////////////////
        // Histograms //
        ////////////////

        // RadiusSizeModule
        TH1F* emcal_eta[6];
        TH1F* emcal_phi[6];
        TH1F* emcal_eta_sigma[6];
        TH1F* emcal_phi_sigma[6];
        TH2F* pt_eta_sigma[6];
        TH2F* pt_phi_sigma[6];
        TH2F* pt_avg_eta;
        TH2F* pt_avg_phi;
        TH2F* pt_eta_dist;
        TH2F* pt_phi_dist;
        TH1F* ohcal_eta_sigma_total;
        TH1F* ohcal_phi_sigma_total;
        TH1F* ohcal_eta_sigma[6];
        TH1F* ohcal_phi_sigma[6];
        // EnergyRadiusOptimzationModule
        TEfficiency* energy_radius_efficiency;
        TEfficiency* energy_radius_purity;
        TH1F* energy_dist_mip;
        TH1F* energy_dist_g4hits_mip;
        TH1F* energy_dist_shower;
        TH2F* ep_selected_mip[35];
        TH2F* ep_true_selected_mip[35];
        // ChecksModule
        TH1F* histTrackTotal;
        TH1F* histTowerNumber[3];
        TH2F* histTruthClassRates;
        // HitEnergyModule
        TH2F* ePrimary;
        TH2F* eDepOverPrimary;
        TH2F* eOhcalDepOverPrimary;
        TH2F* eCemcIhcalDepOverPrimary;
        TH2F* eOhcalDep;
        TH2F* eOhcalDep2;
        TH2F* eCemcIhcalDep;
        TH2F* eCemcIhcalDep2;
        // EOverPModule
        TH2F* ep_towers;
        TH2F* ep_g4hits;
        TH2F* ep_g4hits_full;
        // MipShowerClassifierSelection
        TH1F* vertex_r;
        TH1F* vertex_xyz;
        TH1F* vertex_eta;
        TH1F* vertex_phi;
        // IhcalBacksplashModule
        TH1F* bs_e;
        TH2F* bs_e_vs_sigma_eta;
        TH2F* bs_e_vs_sigma_phi;
        
        /////////////////////////////
        // Random number generator //
        /////////////////////////////
    
        TRandom3* rand = new TRandom3(123);

    public:

        IsotrackHitAnalysis(std::string inputFilename, std::string outputFilename, bool useTowerInfo, bool useTruthInfo, bool useCentrality, bool useParticleGun, float centralityCut, float d0Cut, float z0Cut, float ptCut, float matchedPtCut, float matchedDrCut, float matchedNeutralTruthPtCut, float matchedNeutralTruthEtaCut, float matchedNeutralTruthDrCut, float cemcMatchingDrCut, float ihcalMatchingDrCut, float ohcalMatchingDrCut, float cemcMipEnergy, float ihcalMipEnergy);
        virtual ~IsotrackHitAnalysis();
        virtual Int_t    Cut(Long64_t entry);
        virtual void    GetEntry(Long64_t entry);
        virtual Long64_t LoadTree(Long64_t entry);
        virtual void     Init();
        virtual void     Loop();
        virtual Bool_t   Notify();
        virtual void     Show(Long64_t entry = -1);

        void processEvent();
        void processTrack(int id);
        
        bool basicEventSelection();
        bool basicTrackSelection(int id);
        bool truthIsolatedTrackSelection(int id);
        void initMipShowerClassifier();
        int mipShowerClassifier(int id);

        MatchedClusterContainer getMatchedSimTowers(int id, caloType type, float dRThreshold);
        float energyFromG4hits(int id, float dr);

        void initEOverPModule();
        void eOverPModule(int id, MatchedClusterContainer cemcClusters, MatchedClusterContainer ihcalClusters, MatchedClusterContainer ohcalClusters);

        void initRadiusSizeModule();
        void radiusSizeModule(int id);

        void initEnergyRadiusOptimizationModule();
        void energyRadiusOptimizationModule(int id, MatchedClusterContainer cemcClusters, float totalIhcalEnergy, float totalOhcalEnergy);
        
        void initChecksModule();
        void checksModule(int id, MatchedClusterContainer cemcClusters, MatchedClusterContainer ihcalClusters, MatchedClusterContainer ohcalClusters);

        void initHitEnergyAndBackgroundModule();
        void hitEnergyAndBackgroundModule(int id, MatchedClusterContainer cemcClusters, MatchedClusterContainer ihcalClusters, MatchedClusterContainer ohcalClusters);

        void initIhcalBacksplashModule();
        void ihcalBacksplashModule(int id);
        
};

#endif

#ifdef IsotrackHitAnalysis_cxx
IsotrackHitAnalysis::IsotrackHitAnalysis(std::string inputFilename, std::string outputFilename, bool useTowerInfo, bool useTruthInfo, bool useCentrality, bool useParticleGun, float centralityCut, float d0Cut, float z0Cut, float ptCut, float matchedPtCut, float matchedDrCut, float matchedNeutralTruthPtCut, float matchedNeutralTruthEtaCut, float matchedNeutralTruthDrCut, float cemcMatchingDrCut, float ihcalMatchingDrCut, float ohcalMatchingDrCut, float cemcMipEnergy, float ihcalMipEnergy) :
  USE_TOWER_INFO(useTowerInfo),
  USE_TRUTH_INFO(useTruthInfo),
  USE_CENTRALITY(useCentrality),
  USE_PARTICLE_GUN(useParticleGun),
  CENTRALITY_CUT(centralityCut),
  D0_CUT(d0Cut),
  Z0_CUT(z0Cut),
  PT_CUT(ptCut),
  MATCHED_PT_CUT(matchedPtCut),
  MATCHED_DR_CUT(matchedDrCut),
  MATCHED_NEUTRAL_TRUTH_PT_CUT(matchedNeutralTruthPtCut),
  MATCHED_NEUTRAL_TRUTH_ETA_CUT(matchedNeutralTruthEtaCut),
  MATCHED_NEUTRAL_TRUTH_DR_CUT(matchedNeutralTruthDrCut),
  CEMC_MATCHING_DR_CUT(cemcMatchingDrCut),
  IHCAL_MATCHING_DR_CUT(ihcalMatchingDrCut),
  OHCAL_MATCHING_DR_CUT(ohcalMatchingDrCut),
  CEMC_MIP_ENERGY(cemcMipEnergy),
  IHCAL_MIP_ENERGY(ihcalMipEnergy)
{
  OUTPUT_FILENAME = outputFilename;
  TRACKING_LOCATION = false;

// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
  std::ifstream infile(inputFilename);
  TString filename;
  fChainT           = new TChain("T");

  while(infile >> filename){
    fChainT->Add(filename);
  }

  Init();
}

IsotrackHitAnalysis::~IsotrackHitAnalysis()
{
  delete fChainT;
  delete[] truthenergy;
  delete[] trutheta;
  delete[] truthphi;
  delete[] truthpt;
  delete[] truthp;
  delete[] truthpid;
  delete[] truth_track_id;
  delete[] truth_parent_id;
  delete[] truth_vertex_id;
  delete[] vertex_id;
  delete[] vertex_x;
  delete[] vertex_y;
  delete[] vertex_z;
  delete[] EM_x;
  delete[] EM_y;
  delete[] EM_z;
  delete[] EM_e;
  delete[] EM_track_id;
  delete[] IH_x;
  delete[] IH_y;
  delete[] IH_z;
  delete[] IH_e;
  delete[] IH_track_id;
  delete[] OH_x;
  delete[] OH_y;
  delete[] OH_z;
  delete[] OH_e;
  delete[] OH_track_id;

}

void IsotrackHitAnalysis::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if(fChainT)
     fChainT->GetEntry(entry);
}
Long64_t IsotrackHitAnalysis::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   /*if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;*/

  return 0;
}

void IsotrackHitAnalysis::Init()
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
   fCurrent = -1;
   //fChainTracks->SetMakeClass(1);

   fChainT->SetBranchAddress("n_truth", &n_truth, &b_n_truth);
   fChainT->SetBranchAddress("truthenergy", truthenergy, &b_truthenergy);
   fChainT->SetBranchAddress("trutheta", trutheta, &b_trutheta);
   fChainT->SetBranchAddress("truthphi", truthphi, &b_truthphi);
   fChainT->SetBranchAddress("truthpt", truthpt, &b_truthpt);
   fChainT->SetBranchAddress("truthp", truthp, &b_truthp);
   fChainT->SetBranchAddress("truthpid", truthpid, &b_truthpid);
   fChainT->SetBranchAddress("truth_track_id", truth_track_id, &b_truth_track_id);
   fChainT->SetBranchAddress("truth_vertex_id", truth_vertex_id, &b_truth_vertex_id);
   fChainT->SetBranchAddress("truth_parent_id", truth_parent_id, &b_truth_parent_id);
   fChainT->SetBranchAddress("n_vertex", &n_vertex, &b_n_vertex);
   fChainT->SetBranchAddress("vertex_id", vertex_id, &b_vertex_id);
   fChainT->SetBranchAddress("vertex_x", vertex_x, &b_vertex_x);
   fChainT->SetBranchAddress("vertex_y", vertex_y, &b_vertex_y);
   fChainT->SetBranchAddress("vertex_z", vertex_z, &b_vertex_z); 
   fChainT->SetBranchAddress("n_tracks", &n_tracks, &b_n_tracks);
   fChainT->SetBranchAddress("tr_p", tr_p, &b_tr_p);
   fChainT->SetBranchAddress("tr_pt", tr_pt, &b_tr_pt);
   fChainT->SetBranchAddress("tr_phi", tr_phi, &b_tr_phi);
   fChainT->SetBranchAddress("tr_eta", tr_eta, &b_tr_eta);
   fChainT->SetBranchAddress("tr_cemc_eta", tr_cemc_eta, &b_tr_cemc_eta);
   fChainT->SetBranchAddress("tr_cemc_phi", tr_cemc_phi, &b_tr_cemc_phi);
   fChainT->SetBranchAddress("tr_ihcal_eta", tr_ihcal_eta, &b_tr_ihcal_eta);
   fChainT->SetBranchAddress("tr_ihcal_phi", tr_ihcal_phi, &b_tr_ihcal_phi);
   fChainT->SetBranchAddress("tr_ohcal_eta", tr_ohcal_eta, &b_tr_ohcal_eta);
   fChainT->SetBranchAddress("tr_ohcal_phi", tr_ohcal_phi, &b_tr_ohcal_phi);
   fChainT->SetBranchAddress("tr_truth_track_id", tr_truth_track_id, &b_tr_truth_track_id);
   fChainT->SetBranchAddress("centrality", &centrality, &b_centrality);
   fChainT->SetBranchAddress("EM_n", &EM_n, &b_EM_n);
   fChainT->SetBranchAddress("EM_x", EM_x, &b_EM_x);
   fChainT->SetBranchAddress("EM_y", EM_y, &b_EM_y);
   fChainT->SetBranchAddress("EM_z", EM_z, &b_EM_z);
   fChainT->SetBranchAddress("EM_e", EM_e, &b_EM_e);
   fChainT->SetBranchAddress("EM_track_id", EM_track_id, &b_EM_track_id);
   fChainT->SetBranchAddress("IH_n", &IH_n, &b_IH_n);
   fChainT->SetBranchAddress("IH_x", IH_x, &b_IH_x);
   fChainT->SetBranchAddress("IH_y", IH_y, &b_IH_y);
   fChainT->SetBranchAddress("IH_z", IH_z, &b_IH_z);
   fChainT->SetBranchAddress("IH_e", IH_e, &b_IH_e);
   fChainT->SetBranchAddress("IH_track_id", IH_track_id, &b_IH_track_id);
   fChainT->SetBranchAddress("OH_n", &OH_n, &b_OH_n);
   fChainT->SetBranchAddress("OH_x", OH_x, &b_OH_x);
   fChainT->SetBranchAddress("OH_y", OH_y, &b_OH_y);
   fChainT->SetBranchAddress("OH_z", OH_z, &b_OH_z);
   fChainT->SetBranchAddress("OH_e", OH_e, &b_OH_e);
   fChainT->SetBranchAddress("OH_track_id", OH_track_id, &b_OH_track_id);
   fChainT->SetBranchAddress("n_twr_cemc", &n_twr_cemc, &b_n_twr_cemc);
   fChainT->SetBranchAddress("twr_cemc_e", twr_cemc_e, &b_twr_cemc_e);
   fChainT->SetBranchAddress("twr_cemc_eta", twr_cemc_eta, &b_twr_cemc_eta);
   fChainT->SetBranchAddress("twr_cemc_phi", twr_cemc_phi, &b_twr_cemc_phi);
   fChainT->SetBranchAddress("n_twr_ihcal", &n_twr_ihcal, &b_n_twr_ihcal);
   fChainT->SetBranchAddress("twr_ihcal_e", twr_ihcal_e, &b_twr_ihcal_e);
   fChainT->SetBranchAddress("twr_ihcal_eta", twr_ihcal_eta, &b_twr_ihcal_eta);
   fChainT->SetBranchAddress("twr_ihcal_phi", twr_ihcal_phi, &b_twr_ihcal_phi);
   fChainT->SetBranchAddress("n_twr_ohcal", &n_twr_ohcal, &b_n_twr_ohcal);
   fChainT->SetBranchAddress("twr_ohcal_e", twr_ohcal_e, &b_twr_ohcal_e);
   fChainT->SetBranchAddress("twr_ohcal_eta", twr_ohcal_eta, &b_twr_ohcal_eta);
   fChainT->SetBranchAddress("twr_ohcal_phi", twr_ohcal_phi, &b_twr_ohcal_phi);
    
   Notify();
}

Bool_t IsotrackHitAnalysis::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void IsotrackHitAnalysis::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
//   if (!fChain) return;
//   fChain->Show(entry);
}
Int_t IsotrackHitAnalysis::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}


#endif // #ifdef IsotrackHitAnalysis_cxx
