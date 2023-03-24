#pragma once
#include "../IsotrackHitAnalysis.h"
#include <TVector3.h>
#include <string>

// Things that I want to know from the g4hits:
//   When passing my emcal energy cut, what is the e/p distribution in the ihcal+ohcal?
//   When passing my emcal energy cut, what is the e/p distribution in a deltaR < 0.2 cone in the ihcal+ohcal

void IsotrackHitAnalysis::initRadiusSizeModule() {

    // find the wdith of the g4hits distribution in the emcal
    // start simple with g4hits in the emcal 
    eta_sigma = new TH2F("emcal_sigma_eta","",400,0,2,200,0,1);
    phi_sigma = new TH2F("emcal_sigma_phi","",400,0,2,200,0,1);

    emcal_eta = new TH1F("emcal_eta","",400,-1,1);
    emcal_phi = new TH1F("emcal_phi","",400,-1,1);

    pt_eta_sigma = new TH2F("pt_emcal_sigma_eta","",40,0,20,200,0,1);
    pt_phi_sigma = new TH2F("pt_emcal_sigma_phi","",40,0,20,200,0,1);

    pt_avg_eta = new TH2F("pt_emcal_avg_eta","",40,0,20,200,0,1);
    pt_avg_phi = new TH2F("pt_emcal_avg_phi","",40,0,20,200,0,1);

    pt_eta_dist = new TH2F("pt_emcal_eta_dist","",40,0,20,400,-1,1);
    pt_phi_dist = new TH2F("pt_emcal_phi_dist","",40,0,20,400,-1,1);

}

void IsotrackHitAnalysis::radiusSizeModule(int id){
  
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

  // validating my energy cut in the emcal with g4hits
  TVector3 v1, v2;
  float avg_eta = 0;
  float avg_phi = 0;
  float total_energy = 0;
  int num = 0;
  float sigma2_eta = 0;
  float sigma2_phi = 0;
  float sigma_eta = 0;
  float sigma_phi = 0;

  float e_emcal_truth = 0;
  float e_emcal_r2 = 0;
  float e_emcal_r1 = 0;

  float projection_phi = 0.5 * (tr_cemc_phi[id] + tr_ihcal_phi[id]);
  float projection_eta = 0.5 * (tr_cemc_eta[id] + tr_ihcal_eta[id]);

  float dr = 0; 
  v1.SetPtEtaPhi(tr_pt[id], tr_cemc_eta[id], tr_cemc_phi[id]);
  for (int i = 0; i < EM_n; i++) {
    if (shower_ids.find(EM_track_id[i]) != shower_ids.end()) {
      float r = sqrt(EM_x[i]*EM_x[i] + EM_y[i]*EM_y[i] + EM_z[i]*EM_z[i]);
      float eta = atanh(EM_z[i]/r);
      float phi = atan2(EM_y[i],EM_x[i]);
      avg_eta += EM_e[i]*eta;
      avg_phi += EM_e[i]*phi;
      total_energy += EM_e[i];
      num++;
    }
  }
  avg_eta /= total_energy;
  avg_phi /= total_energy;

  pt_avg_eta->Fill(tr_pt[id], avg_eta-projection_eta);
  pt_avg_phi->Fill(tr_pt[id], avg_phi-projection_phi);


  for (int i = 0; i < EM_n; i++) {
    if (shower_ids.find(EM_track_id[i]) != shower_ids.end()) {
      float r = sqrt(EM_x[i]*EM_x[i] + EM_y[i]*EM_y[i] + EM_z[i]*EM_z[i]);
      float eta = atanh(EM_z[i]/r);
      float phi = atan2(EM_y[i],EM_x[i]);
      emcal_eta->Fill(eta-projection_eta,EM_e[i]/total_energy);
      emcal_phi->Fill(phi-projection_phi,EM_e[i]/total_energy);
      pt_eta_dist->Fill(tr_p[id],eta-projection_eta,EM_e[i]/total_energy);
      pt_phi_dist->Fill(tr_p[id],phi-projection_phi,EM_e[i]/total_energy);
      sigma2_eta += EM_e[i] * (eta - avg_eta) * (eta - avg_eta);
      sigma2_phi += EM_e[i] * (phi - avg_phi) * (phi - avg_phi);
    }
  }

  sigma2_eta /= (float(num) - 1.0)/num * total_energy;
  sigma2_phi /= (float(num) - 1.0)/num * total_energy;
  sigma_eta = sqrt(sigma2_eta);
  sigma_phi = sqrt(sigma2_phi);

  eta_sigma->Fill(total_energy/emcal_sf, sigma_eta);
  phi_sigma->Fill(total_energy/emcal_sf, sigma_phi);

  pt_eta_sigma->Fill(tr_pt[id],sigma_eta);
  pt_phi_sigma->Fill(tr_pt[id],sigma_phi);

}
