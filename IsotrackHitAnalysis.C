#define IsotrackHitAnalysis_cxx
#include "IsotrackHitAnalysis.h"
#include "ClusterContainer.h"
#include "Tools.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <iostream>
#include <string>

#include "selections/BasicEventSelection.h"
#include "selections/BasicTrackSelection.h"
#include "selections/TruthIsolatedTrackSelection.h"
#include "selections/MipShowerClassifier.h"

#include "modules/EOverPModule.h"
#include "modules/ChecksModule.h"
#include "modules/HitEnergyAndBackgroundModule.h"
#include "modules/RadiusSizeModule.h"
#include "modules/EnergyRadiusOptimizationModule.h"


void IsotrackHitAnalysis::Loop(){
    // Get the number of entries in the TChain
    long nentries = fChainT->GetEntries();

    ///////////////////////////////////////////////////
    // Initializations go here

    TFile* outputFile = new TFile(OUTPUT_FILENAME.c_str(), "RECREATE");

    //initEOverPModule(); // calculate E/p from towers and from g4hits 
    initChecksModule(); // check including tower number, track rate, mip/shower classification rates
    //initRadiusSizeModule(); // calculate the mip/shower size in emcal from g4hits
    //initEnergyRadiusOptimizationModule(); // calculate mip/shower purity and efficiency in emcal from towers
    //initHitEnergyAndBackgroundModule(); // calculate signal and background energy deposition from g4hits 

    ///////////////////////////////////////////////////

    for(Long64_t jentry=0;jentry<nentries;jentry++) {
        //if (jentry > 50000) continue;
        LoadTree(jentry);
        GetEntry(jentry);
        processEvent();
    
        if(jentry % 1000 == 0)
            std::cout << jentry << "/" << nentries << " have been processed" << std::endl;
    }

    // Saving output file
    outputFile->Write();
}

// Process an event
void IsotrackHitAnalysis::processEvent(){
    
    if (basicEventSelection()) {
        for (int i = 0; i < n_tracks; i++){
            if (basicTrackSelection(i)){
                assert(tr_cemc_eta[i] > -98 && tr_cemc_phi[i] > -98 && fabs(tr_cemc_eta[i]) <= 1.0);
                //std::cout << "pass track selection" << std::endl;
                if (!USE_TRUTH_INFO || (USE_TRUTH_INFO && truthIsolatedTrackSelection(i))) {
                    processTrack(i);
                }  
            }
        }
    } 
}

void IsotrackHitAnalysis::processTrack(int id){
    
    MatchedClusterContainer cemcClusters;
    MatchedClusterContainer ihcalClusters;
    MatchedClusterContainer ohcalClusters;

    cemcClusters  = getMatchedSimTowers(id,cemc,CEMC_MATCHING_DR_CUT);
    ihcalClusters = getMatchedSimTowers(id,ihcal,IHCAL_MATCHING_DR_CUT);
    ohcalClusters = getMatchedSimTowers(id,ohcal,OHCAL_MATCHING_DR_CUT);
    
    // Calculate energy of matched clusters
    float totalCemcEnergy = cemcClusters.getTotalEnergy();
    float totalIhcalEnergy = ihcalClusters.getTotalEnergy();
    float totalOhcalEnergy = ohcalClusters.getTotalEnergy();
    
    float totalEnergy = totalCemcEnergy + totalIhcalEnergy + totalOhcalEnergy;

    ///////////////////////////////////////////
    // Analysis modules should be added here //
    ///////////////////////////////////////////

    //eOverPModule(id, cemcClusters, ihcalClusters, ohcalClusters);
    checksModule(id, cemcClusters, ihcalClusters, ohcalClusters);
    //radiusSizeModule(id);
    //energyRadiusOptimizationModule(id, cemcClusters, totalIhcalEnergy, totalOhcalEnergy);
    //hitEnergyAndBackgroundModule(id, cemcClusters, ihcalClusters, ohcalClusters);
    
}

