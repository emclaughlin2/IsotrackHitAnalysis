#pragma once
#include "../IsotrackHitAnalysis.h"
#include <TVector3.h>
#include <string>
#include <set> 

void IsotrackHitAnalysis::initHitEnergyAndBackgroundModule() {
  std::string eta_list[] = {"central","forward"};
  int centrality_list[] = {30,50,70,90};

  // want to know 
  // total energy of primary particles
  // ratio of total energy deposited to total energy of primary particles
  // ratio of ohcal energy to total energy of primary particles
  // ratio of cemc + ihcal energy to total energy of primary particles 
  // ohcal energy 
  // cemc + ihcal energy 
  // cemc + ihcal energy in donut
  
  ePrimary = new TH2F("ePrimary","",20,0,20,2000,0,40);
  eDepOverPrimary = new TH2F("eDepOverPrimary","",20,0,20,2000,0,10);
  eOhcalDepOverPrimary = new TH2F("eOhcalDepOverPrimary","",20,0,20,2000,0,10);
  eCemcIhcalDepOverPrimary = new TH2F("eCemcIhcalDepOverPrimary","",20,0,20,2000,0,10);
  eOhcalDep = new TH2F("eOhcalDep","",20,0,20,2000,0,40);
  eOhcalDep2 = new TH2F("eOhcalDep2","",20,0,20,2000,0,40);
  eCemcIhcalDep = new TH2F("eCemcIhcalDep","",20,0,20,2000,0,40);
  eCemcIhcalDep2 = new TH2F("eCemcIhcalDep2","",20,0,20,2000,0,40);
  
}

void IsotrackHitAnalysis::hitEnergyAndBackgroundModule(int id, MatchedClusterContainer cemcClusters, MatchedClusterContainer ihcalClusters, MatchedClusterContainer ohcalClusters){

  const std::set<int> neutral_pid = {-3322,-3212,-3122,-2112,-421,-14,-12,12,14,22,111,130,310,421,
                    2112,3122,3212,3322};
  float cemc_sf = 0.02;
  float ihcal_sf = 0.162166;
  float ohcal_sf = 0.0338021;

  // calculate energy of matched clusters as a function of delta_R
  float R1CemcEnergy = cemcClusters.getTotalEnergy(0.1);
  float R1IhcalEnergy = ihcalClusters.getTotalEnergy(0.1);
    
  float R2CemcEnergy = cemcClusters.getTotalEnergy(0.2);
  float R2IhcalEnergy = ihcalClusters.getTotalEnergy(0.2);
  float R2OhcalEnergy = ohcalClusters.getTotalEnergy(0.2);

  float centrality_array[] = {20,40,60,80,100};
  
  if (R1CemcEnergy < CEMC_MIP_ENERGY && R1IhcalEnergy < IHCAL_MIP_ENERGY && R2OhcalEnergy/tr_p[id] > 0.4) {

    float R1Energy = R1CemcEnergy + R1IhcalEnergy;
    float R2Energy = R2CemcEnergy + R2IhcalEnergy;

    float e_cemc = 0;
    float e_cemc1 = 0;
    float e_cemc2 = 0;
    float e_ihcal = 0;
    float e_ihcal1 = 0;
    float e_ihcal2 = 0;
    float e_ohcal = 0;
    float e_ohcal2 = 0;

    float e_primary = 0;
    float dr = 0;

    TVector3 v1, v2;
    v1.SetPtEtaPhi(tr_pt[id], tr_cemc_eta[id], tr_cemc_phi[id]);

    //std::cout << "Neutral neighbor check: p = " << tr_p[id] << std::endl;      
    std::set<int> primary_pi0;
    std::set<int> neighbors;
    for (int j = 0; j < n_truth; j++) {
      // find primary particles 
      if ((neutral_pid.find(truthpid[j]) != neutral_pid.end() && truth_parent_id[j] == 0 && truthpt[j] > MATCHED_NEUTRAL_TRUTH_PT_CUT) 
        || (primary_pi0.find(truth_parent_id[j]) != primary_pi0.end() && truthpid[j] == 22)) {
        if (fabs(trutheta[j]) > MATCHED_NEUTRAL_TRUTH_ETA_CUT) { continue; }
        v2.SetPtEtaPhi(truthpt[j], trutheta[j], truthphi[j]);
        dr = v1.DeltaR(v2);
        if (dr < 0.2) {
          //std::cout << "Primary particle: pid = " << truthpid[j] << " track_id = " << truth_track_id[j] << " parent_id = " << truth_parent_id[j] << " energy = " << truthenergy[j] << " dr = " << dr << std::endl;
          // neutral em particles
          if (truthpid[j] == 111) { 
            primary_pi0.insert(truth_track_id[j]);
            continue;
          } else {
            e_primary += truthenergy[j];
            neighbors.insert(truth_track_id[j]);
          }
        } 
        // find particles associated with the primary particles' showers 
      } else {
        if (neighbors.find(truth_parent_id[j]) != neighbors.end()) {
          //std::cout << "Shower particle: pid = " << truthpid[j] << " track_id = " << truth_track_id[j] << " parent_id = " << truth_parent_id[j] << " energy = " << truthenergy[j] << " dr = " << dr << std::endl;
          neighbors.insert(truth_track_id[j]);
        }
      }
    }
    /*
    std::cout << "Neighbors set:";
    for (auto it = neighbors.begin(); it != neighbors.end(); ++it) {
      std::cout << ' ' << *it;
    }
    std::cout << std::endl;
    */
    // now to run over g4hits 
    for (int j = 0; j < EM_n; j++) {
      if (neighbors.find(EM_track_id[j]) == neighbors.end()) { continue; }
      float r = EM_x[j]*EM_x[j] + EM_y[j]*EM_y[j] + EM_z[j]*EM_z[j];
      float eta = atanh(EM_z[j]/r);
      float phi = atan2(EM_y[j],EM_x[j]);
      v2.SetPtEtaPhi(1,eta,phi);
      dr = v1.DeltaR(v2);
      std::cout << "particle in emcal: track_id = " << EM_track_id[j] << " e_dep = " << EM_e[j] << " dr = " << dr << std::endl;
      std::cout << "    track: eta = " << tr_cemc_eta[id] << " phi = " << tr_cemc_phi[id] << std::endl;
      std::cout << "    g4hit: eta = " << eta << " phi = " << phi << std::endl;
      std::cout << "    g4hit: x = " << EM_x[j] << " y = " << EM_y[j] << " z = " << EM_z[j] << std::endl;
      e_cemc += EM_e[j];
      if (dr < 0.1) e_cemc1 += EM_e[j];
      if (dr < 0.2) e_cemc2 += EM_e[j];
    }

    v1.SetPtEtaPhi(tr_pt[id], tr_ihcal_eta[id], tr_ihcal_phi[id]);
    for (int j = 0; j < IH_n; j++) {
      if (neighbors.find(IH_track_id[j]) == neighbors.end()) { continue; }
      float r = IH_x[j]*IH_x[j] + IH_y[j]*IH_y[j] + IH_z[j]*IH_z[j];
      float eta = atanh(IH_z[j]/r);
      float phi = atan2(IH_y[j],IH_x[j]);
      v2.SetPtEtaPhi(1,eta,phi);
      dr = v1.DeltaR(v2);
      std::cout << "particle in ihcal: track_id = " << IH_track_id[j] << " e_dep = " << IH_e[j] << " dr = " << dr << std::endl;
      std::cout << "    track: eta = " << tr_ihcal_eta[id] << " phi = " << tr_ihcal_phi[id] << std::endl;
      std::cout << "    g4hit: eta = " << eta << " phi = " << phi << std::endl;
      std::cout << "    g4hit: x = " << IH_x[j] << " y = " << IH_y[j] << " z = " << IH_z[j] << std::endl;
      e_ihcal += IH_e[j];
      if (dr < 0.1) e_ihcal1 += IH_e[j];
      if (dr < 0.2) e_ihcal2 += IH_e[j];
    }

     v1.SetPtEtaPhi(tr_pt[id], tr_ohcal_eta[id], tr_ohcal_phi[id]);
    for (int j = 0; j < OH_n; j++) {
      if (neighbors.find(OH_track_id[j]) == neighbors.end()) { continue; }
      float r = OH_x[j]*OH_x[j] + OH_y[j]*OH_y[j] + OH_z[j]*OH_z[j];
      float eta = atanh(OH_z[j]/r);
      float phi = atan2(OH_y[j],OH_x[j]);
      v2.SetPtEtaPhi(1,eta,phi);
      dr = v1.DeltaR(v2);
      std::cout << "particle in ohcal: track_id = " << OH_track_id[j] << " e_dep = " << OH_e[j] << " dr = " << dr << std::endl;
      std::cout << "    track: eta = " << tr_ohcal_eta[id] << " phi = " << tr_ohcal_phi[id] << std::endl;
      std::cout << "    g4hit: eta = " << eta << " phi = " << phi << std::endl;
      std::cout << "    g4hit: x = " << OH_x[j] << " y = " << OH_y[j] << " z = " << OH_z[j] << std::endl;
      e_ohcal += OH_e[j];
      if (dr < 0.2) e_ohcal2 += OH_e[j];
    }

    e_cemc /= cemc_sf;
    e_cemc1 /= cemc_sf;
    e_cemc2 /= cemc_sf;
    e_ihcal /= ihcal_sf;
    e_ihcal1 /= ihcal_sf;
    e_ihcal2 /= ihcal_sf;
    e_ohcal /= ohcal_sf;
    e_ohcal2 /= ohcal_sf;

    ePrimary->Fill(tr_p[id], e_primary);
    eDepOverPrimary->Fill(tr_p[id], (e_cemc + e_ihcal + e_ohcal)/e_primary);
    eOhcalDepOverPrimary->Fill(tr_p[id], e_ohcal/e_primary);
    eCemcIhcalDepOverPrimary->Fill(tr_p[id], (e_cemc + e_ihcal)/e_primary);
    eOhcalDep->Fill(tr_p[id], e_ohcal);
    eOhcalDep2->Fill(tr_p[id], e_ohcal2);
    eCemcIhcalDep->Fill(tr_p[id], e_cemc + e_ihcal);
    eCemcIhcalDep2->Fill(tr_p[id], e_cemc2 + e_ihcal2 - e_cemc1 - e_ihcal1);
  }
}
