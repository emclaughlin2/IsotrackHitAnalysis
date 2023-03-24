#pragma once
#include "../IsotrackHitAnalysis.h"
#include "../selections/MipShowerClassifier.h"
#include <TVector3.h>
#include <string>

void IsotrackHitAnalysis::initEOverPModule() {

  // now that we know our cuts for the emcal should be dR = 0.2 and E < 0.3 GeV
  // we can look at the e/p distributions and background in the hcals
  ep_towers = new TH2F("ep_towers","",20,0,20,1000,0,10);
  ep_g4hits = new TH2F("ep_g4hits","",20,0,20,1000,0,10);
  ep_g4hits_full = new TH2F("ep_g4hits_full","",20,0,20,1000,0,10);
}

void IsotrackHitAnalysis::eOverPModule(int id, MatchedClusterContainer cemcClusters, MatchedClusterContainer ihcalClusters, MatchedClusterContainer ohcalClusters){
  
  // want to calculate the e/p distribution using energy in the hcals

  // first check if particle passes emcal cut
  if (cemcClusters.getTotalEnergy(CEMC_MATCHING_DR_CUT) > CEMC_MIP_ENERGY) { return; }

  TVector3 v1, v2;
  // method to find the energy deposition from matched towers 
  float total_energy = ihcalClusters.getTotalEnergy(IHCAL_MATCHING_DR_CUT) + ohcalClusters.getTotalEnergy(OHCAL_MATCHING_DR_CUT);
  ep_towers->Fill(tr_p[id],total_energy/tr_p[id]);
  
  // method to find the energy deposition from g4hits
  float emcal_sf = 0.02;
  float ihcal_sf = 0.162166;
  float ohcal_sf = 0.0338021;

  // find the total shower of the particle 
  std::set<int> shower_ids;
  shower_ids.insert(tr_truth_track_id[id]);
  for (int i = 0; i < n_truth; i++) {
    if (shower_ids.find(truth_parent_id[i]) != shower_ids.end()) {
      shower_ids.insert(truth_track_id[i]);
    }
  }

  float ihcal_energy = 0;
  float ihcal_energy_full = 0;
  float ohcal_energy = 0;
  float ohcal_energy_full = 0;

  v1.SetPtEtaPhi(tr_pt[id], tr_ihcal_eta[id], tr_ihcal_phi[id]);
  for (int i = 0; i < IH_n; i++) {
    if (shower_ids.find(IH_track_id[i]) != shower_ids.end()) {
      float r = sqrt(IH_x[i]*IH_x[i] + IH_y[i]*IH_y[i] + IH_z[i]*IH_z[i]);
      float eta = atanh(IH_z[i]/r);
      float phi = atan2(IH_y[i],IH_x[i]);
      ihcal_energy_full += IH_e[i];
      v2.SetPtEtaPhi(1,eta,phi);
      if (v1.DeltaR(v2) < IHCAL_MATCHING_DR_CUT) ihcal_energy += IH_e[i];
    }
  }

  v1.SetPtEtaPhi(tr_pt[id], tr_ohcal_eta[id], tr_ohcal_phi[id]);
  for (int i = 0; i < OH_n; i++) {
    if (shower_ids.find(OH_track_id[i]) != shower_ids.end()) {
      float r = sqrt(OH_x[i]*OH_x[i] + OH_y[i]*OH_y[i] + OH_z[i]*OH_z[i]);
      float eta = atanh(OH_z[i]/r);
      float phi = atan2(OH_y[i],OH_x[i]);
      ohcal_energy_full += OH_e[i];
      v2.SetPtEtaPhi(1,eta,phi);
      if (v1.DeltaR(v2) < OHCAL_MATCHING_DR_CUT) ohcal_energy += OH_e[i];
    }
  }

  ihcal_energy /= ihcal_sf;
  ihcal_energy_full /= ihcal_sf;
  ohcal_energy /= ohcal_sf;
  ohcal_energy_full /= ohcal_sf;
  
}
