#pragma once
#include "../IsotrackHitAnalysis.h"
#include <TVector3.h>
#include <string>

// Things that I want to know from the g4hits:
//   When passing my emcal energy cut, what is the e/p distribution in the ihcal+ohcal?
//   When passing my emcal energy cut, what is the e/p distribution in a deltaR < 0.2 cone in the ihcal+ohcal

float IsotrackHitAnalysis::energyFromG4hits(int id, float dr) {
  TVector3 v1, v2;
  float e_emcal_r1 = 0;
  float emcal_sf = 0.02;
  float projection_phi = 0.5 * (tr_cemc_phi[id] + tr_ihcal_phi[id]);
  float projection_eta = 0.5 * (tr_cemc_eta[id] + tr_ihcal_eta[id]);
  v1.SetPtEtaPhi(tr_pt[id], projection_eta, projection_phi);
  std::set<int> shower_ids;
  shower_ids.insert(tr_truth_track_id[id]);
  for (int i = 0; i < n_truth; i++) {
    if (shower_ids.find(truth_parent_id[i]) != shower_ids.end()) {
      shower_ids.insert(truth_track_id[i]);
    }
  }
  for (int i = 0; i < EM_n; i++) {
    if (shower_ids.find(EM_track_id[i]) != shower_ids.end()) {
      float r = sqrt(EM_x[i]*EM_x[i] + EM_y[i]*EM_y[i] + EM_z[i]*EM_z[i]);
      float eta = atanh(EM_z[i]/r);
      float phi = atan2(EM_y[i],EM_x[i]);
      v2.SetPtEtaPhi(1,eta,phi);
      if (v1.DeltaR(v2) < dr) e_emcal_r1 += EM_e[i];
    }
  }
  e_emcal_r1 /= emcal_sf;
  return e_emcal_r1;
}

void IsotrackHitAnalysis::initEnergyRadiusOptimizationModule() {
  energy_radius_purity = new TEfficiency("energy_radius_purity","Mip Purity;DeltaR;Energy (GeV)",15,0.0375,0.4125,17,0.1875,0.6125);
  energy_radius_efficiency = new TEfficiency("energy_radius_eff","Mip Efficiency;DeltaR;Energy (GeV)",15,0.0375,0.4125,17,0.1875,0.6125);
  energy_dist_mip = new TH1F("energy_dist_mip","",800,0,8);
  energy_dist_g4hits_mip = new TH1F("energy_dist_g4hits_mip","",800,0,8);
  energy_dist_shower = new TH1F("energy_dist_shower","",800,0,8);

  int radius[] = {10,15,20,25,30};
  int mip_energy[] = {200,250,300,350,400,450,500};
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 7; j++) {
      ep_selected_mip[7*i+j] = new TH2F(TString::Format("selected_ep_rad_%d_e_%d",radius[i],mip_energy[j]),"",20,0,20,2000,0,10);
      ep_true_selected_mip[7*i+j] = new TH2F(TString::Format("true_selected_ep_rad_%d_e_%d",radius[i],mip_energy[j]),"",20,0,20,2000,0,10);
    }
  }
}

void IsotrackHitAnalysis::energyRadiusOptimizationModule(int id, MatchedClusterContainer cemcClusters, float totalIhcalEnergy, float totalOhcalEnergy){

  // already found the matching cluster containers, want to find the energy in emcal for a certain radius and then fill efficiency plot
  float radii[] = {0.05,0.075,0.1,0.125,0.15,0.175,0.2,0.225,0.25,0.275,0.3,0.325,0.35,0.375,0.4,0.45};
  float energies[] = {0.2,0.225,0.25,0.275,0.3,0.325,0.35,0.375,0.4,0.425,0.45,0.475,0.5,0.525,0.55,0.575,0.6};

  std::set<float> radius = {0.1,0.15,0.2,0.25,0.3};
  std::set<float> mip_energy = {0.2,0.25,0.3,0.35,0.4,0.45,0.5};

  bool mip;
  bool pass_cut;
  int classify = mipShowerClassifier(id);
  if (classify <= 2 || classify == 7) { mip = false; }
  else { mip = true; }

  int ii = 0;
  int jj = 0;
  // calculating the mip purity as a function of deltaR and energy 
  for (int i = 0; i < 15; i++) {
    float cemc_energy = cemcClusters.getTotalEnergy(radii[i]);
    jj = 0;
    for (int j = 0; j < 17; j++) {
      if (cemc_energy < energies[j]) {
        if (radius.find(radii[i]) != radius.end() && mip_energy.find(energies[j]) != mip_energy.end()) {
          //std::cout << "filling " << radii[i] << " " << energies[j] << " " << ii << " " << jj << std::endl;
          ep_selected_mip[7*ii+jj]->Fill(tr_p[id], (totalIhcalEnergy + totalOhcalEnergy) / tr_p[id]);
        }
        energy_radius_purity->Fill(mip, radii[i], energies[j]);
      }
      if (mip_energy.find(energies[j]) != mip_energy.end()) jj++;
    }
    if (radius.find(radii[i]) != radius.end()) ii++;
  }

  ii = 0;
  jj = 0;
  // calculating the mip efficiency as a function of deltaR and energy
  if ( mip == true ) {
    energy_dist_g4hits_mip->Fill(energyFromG4hits(id, 0.2));
    energy_dist_mip->Fill(cemcClusters.getTotalEnergy(0.2));
    for (int i = 0; i < 15; i++) {
      float cemc_energy = cemcClusters.getTotalEnergy(radii[i]);
      jj = 0;
      for (int j = 0; j < 17; j++) {
        if (cemc_energy < energies[j]) { 
          pass_cut = true; 
          if (radius.find(radii[i]) != radius.end() && mip_energy.find(energies[j]) != mip_energy.end()) {
            ep_true_selected_mip[7*ii+jj]->Fill(tr_p[id], (totalIhcalEnergy + totalOhcalEnergy) / tr_p[id]);
          }
        }
        else { pass_cut = false; }
        energy_radius_efficiency->Fill(pass_cut, radii[i], energies[j]);
        if (mip_energy.find(energies[j]) != mip_energy.end()) jj++;
      }
      if (radius.find(radii[i]) != radius.end()) ii++;
    }
  } else {
    energy_dist_shower->Fill(cemcClusters.getTotalEnergy(0.2));
  }
}
