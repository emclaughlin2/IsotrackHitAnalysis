#pragma once
#include "../IsotrackHitAnalysis.h"
#include <TVector3.h>
#include <string>
#include <set> 

void IsotrackHitAnalysis::initIhcalBacksplashModule() {
  bs_e = new TH1F("bs_e","",200,0,5);
  bs_e_vs_sigma_eta = new TH2F("bs_e_vs_sigma_eta","",200,0,1,200,0,5);
  bs_e_vs_sigma_phi = new TH2F("bs_e_vs_sigma_phi","",200,0,1,200,0,5);
}

void IsotrackHitAnalysis::ihcalBacksplashModule(int id){

  // first want to look only at ihcal showers 
  int classify = mipShowerClassifier(id);
  // to look at ihcal backsplash rates
  if (classify != 3) { return; }
  // to look at ohcal and magnet backsplash rates
  //if (classify != 4 && classify != 5) { return; }

  // Want to find all the particles in the shower and the vertex of the ihcal shower in (eta, phi)

  int child, v_id;
  std::set<int> vertex;
  float v_radius, v_rad;
  float v_eta = -99;
  float v_phi = -99;
  float v_xyz = -99;
  float emcal_sf = 0.02;
  std::set<int> shower_ids;
  shower_ids.insert(tr_truth_track_id[id]);

  // check where particle showers
  for (int i = 0; i < n_truth; i++) {
    if (shower_ids.find(truth_parent_id[i]) != shower_ids.end()) { shower_ids.insert(truth_track_id[i]); }
    if (truth_track_id[i] < 0 && truth_parent_id[i] == tr_truth_track_id[id] && abs(truthpid[i]) != 11 && truthpid[i] != 22) { vertex.insert(truth_vertex_id[i]); }
    }
  v_radius = 300;
  for (std::set<int>::iterator it = vertex.begin(); it != vertex.end(); it++) {
    child = 0;
    for (int i = 0 ; i < n_truth; i++) {
      if (truth_track_id[i] < 0 && truth_vertex_id[i] == *it && abs(truthpid[i]) != 11 && truthpid[i] != 22) { child++; }
    }
    if (child > 1) {
      // now find the location of the shower vertex
      for (int v = 0; v < n_vertex; v++) {
        if (vertex_id[v] == *it) {
          v_rad = sqrt(vertex_x[v]*vertex_x[v] + vertex_y[v]*vertex_y[v]);
          if (v_rad < v_radius) {
            v_radius = v_rad;
            v_xyz = sqrt(vertex_x[v]*vertex_x[v] + vertex_y[v]*vertex_y[v] + vertex_z[v]*vertex_z[v]);
            v_eta = atanh(vertex_z[v]/v_xyz);
            v_phi = atan2(vertex_y[v], vertex_x[v]);
            v_id = vertex_id[v];
          }
        }
      } 
    }
  }

  if (v_xyz == -99 || v_eta == -99 || v_phi == -99) { return; }
  // find the first track_id associated with the shower
  // only want to look for backsplash from shower particles with track_ids later than the first shower vertex track_ids
  std::set<int> vertex_children;
  int max_child;
  for (int i = 0; i < n_truth; i++) {
    if (truth_vertex_id[i] == v_id) { vertex_children.insert(truth_track_id[i]); }
  }
  if (vertex_children.empty()) { return; }
  max_child = *(vertex_children.rbegin());

  float avg_eta = 0;
  float avg_phi = 0;
  float total_energy = 0;
  float sigma2_eta = 0;
  float sigma2_phi = 0;
  float sigma_eta = 0;
  float sigma_phi = 0;

  // now check the emcal for energy desposited by the shower particles and the distance between those g4hits and the shower vertex
  float e_backsplash = 0;
  for (int i = 0; i < EM_n; i++) {
    if (shower_ids.find(EM_track_id[i]) != shower_ids.end()) {
      float r = sqrt(EM_x[i]*EM_x[i] + EM_y[i]*EM_y[i] + EM_z[i]*EM_z[i]);
      float eta = atanh(EM_z[i]/r);
      float phi = atan2(EM_y[i],EM_x[i]);
      avg_eta += EM_e[i]*eta;
      avg_phi += EM_e[i]*phi;
      total_energy += EM_e[i];
      if (EM_track_id[i] <= max_child) e_backsplash += EM_e[i];
    }
  }

  avg_eta /= total_energy;
  avg_phi /= total_energy;

  for (int i = 0; i < EM_n; i++) {
    if (shower_ids.find(EM_track_id[i]) != shower_ids.end()) {
      float r = sqrt(EM_x[i]*EM_x[i] + EM_y[i]*EM_y[i] + EM_z[i]*EM_z[i]);
      float eta = atanh(EM_z[i]/r);
      float phi = atan2(EM_y[i],EM_x[i]);
      sigma2_eta += EM_e[i] * (eta - avg_eta) * (eta - avg_eta);
      sigma2_phi += EM_e[i] * (phi - avg_phi) * (phi - avg_phi);
    }
  }

  sigma2_eta /= total_energy;
  sigma2_phi /= total_energy;
  sigma_eta = sqrt(sigma2_eta);
  sigma_phi = sqrt(sigma2_phi);
  e_backsplash /= emcal_sf;

  bs_e->Fill(e_backsplash);
  bs_e_vs_sigma_eta->Fill(sigma_eta, e_backsplash);
  bs_e_vs_sigma_phi->Fill(sigma_phi, e_backsplash);

}
