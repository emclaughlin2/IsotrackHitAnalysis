#pragma once
#include "../IsotrackHitAnalysis.h"
#include <TVector3.h>
#include <string>
#include <set> 
#include <map>
#include <vector>

void IsotrackHitAnalysis::initDDIhcalMipModule() {
  emcal_raw = new TH1F("emcal_raw","", 1000, 0, 10);
  emcal_raw_mip = new TH1F("emcal_raw_mip","", 1000, 0, 10);
  ihcal_raw_mip = new TH1F("ihcal_raw_mip","", 1000, 0, 10);
  ihcal_raw_mip_0 = new TH1F("ihcal_raw_mip_0","", 1000, 0, 10);
  ihcal_raw_mip_1 = new TH1F("ihcal_raw_mip_1","", 1000, 0, 10);
  ihcal_raw_mip_2 = new TH1F("ihcal_raw_mip_2","", 1000, 0, 10);
  ihcal_mip_mip = new TH1F("ihcal_mip_mip","", 1000, 0, 10);
  ihcal_mip_shower = new TH1F("ihcal_mip_shower","", 1000, 0, 10);
  ihcal_mip_other = new TH1F("ihcal_mip_other","", 1000, 0, 10);
  emcal_raw_mip_0 = new TH1F("emcal_raw_mip_0","", 1000, 0, 10);
  emcal_raw_mip_1 = new TH1F("emcal_raw_mip_1","", 1000, 0, 10);
  emcal_raw_mip_2 = new TH1F("emcal_raw_mip_2","", 1000, 0, 10);
  emcal_mip_mip = new TH1F("emcal_mip_mip","", 1000, 0, 10);
  emcal_mip_shower = new TH1F("emcal_mip_shower","", 1000, 0, 10);
  emcal_mip_other = new TH1F("emcal_mip_other","", 1000, 0, 10);
}

void IsotrackHitAnalysis::ddIhcalMipModule(){

  const float eta[] = {-1.05417,-0.9625,-0.870833,-0.779167,-0.6875,-0.595833,-0.504167,-0.4125,-0.320833,-0.229167,-0.1375,
  -0.0458333,0.0458333,0.1375,0.229167,0.320833,0.4125,0.504167,0.595833,0.6875,0.779167,0.870833,0.9625,1.05417};
  const float phi[] = {0.0936424,0.191817,0.289992,0.388167,0.486341,0.584516,0.682691,0.780866,0.879041,0.977215,1.07539,1.17356,
  1.27174,1.36991,1.46809,1.56626,1.66444,1.76261,1.86079,1.95896,2.05714,2.15531,2.25349,2.35166,2.44984,2.54801,2.64619,2.74436,
  2.84254,2.94071,3.03889,3.13706,-3.04795,-2.94978,-2.8516,-2.75343,-2.65525,-2.55708,-2.4589,-2.36073,-2.26255,-2.16438,-2.0662,
  -1.96803,-1.86985,-1.77168,-1.6735,-1.57533,-1.47715,-1.37898,-1.2808,-1.18263,-1.08445,-0.98628,-0.888105,-0.789931,-0.691756,
  -0.593581,-0.495406,-0.397231,-0.299057,-0.200882,-0.102707,-0.0045324};
  const float eta_em[] = {-1.12318,-1.10191,-1.08023,-1.05875,-1.03686,-1.01518,-0.993083,-0.971197,-0.948893,-0.926804,-0.904295,
  -0.882004,-0.859292,-0.836801,-0.813886,-0.791195,-0.768079,-0.745189,-0.721872,-0.698783,-0.675264,-0.651976,-0.628256,-0.604768,
  -0.580845,-0.557155,-0.533027,-0.509133,-0.484798,-0.460697,-0.43615,-0.411838,-0.387076,-0.362547,-0.337564,-0.312813,-0.287601,
  -0.26262,-0.237171,-0.211952,-0.186257,-0.160788,-0.135722,-0.111796,-0.0874366,-0.0633955,-0.0389474,-0.0148467,0.0148467,
  0.0389474,0.0633955,0.0874366,0.111796,0.135722,0.160788,0.186257,0.211952,0.237171,0.26262,0.287601,0.312813,0.337564,0.362547,
  0.387076,0.411838,0.43615,0.460697,0.484798,0.509133,0.533027,0.557155,0.580845,0.604768,0.628256,0.651976,0.675264,0.698783,
  0.721872,0.745189,0.768079,0.791195,0.813886,0.836801,0.859292,0.882004,0.904295,0.926804,0.948893,0.971197,0.993083,1.01518,
  1.03686,1.05875,1.08023,1.10191,1.12318};
  const float phi_em[] = {1.48489,1.50944,1.53398,1.55852,1.58307,1.60761,1.63216,1.6567,1.68124,1.70579,1.73033,1.75487,1.77942,
  1.80396,1.82851,1.85305,1.87759,1.90214,1.92668,1.95122,1.97577,2.00031,2.02485,2.0494,2.07394,2.09849,2.12303,2.14757,2.17212,
  2.19666,2.2212,2.24575,2.27029,2.29484,2.31938,2.34392,2.36847,2.39301,2.41755,2.4421,2.46664,2.49118,2.51573,2.54027,2.56482,
  2.58936,2.6139,2.63845,2.66299,2.68753,2.71208,2.73662,2.76117,2.78571,2.81025,2.8348,2.85934,2.88388,2.90843,2.93297,2.95752,
  2.98206,3.0066,3.03115,3.05569,3.08023,3.10478,3.12932,-3.12932,-3.10478,-3.08023,-3.05569,-3.03115,-3.0066,-2.98206,-2.95752,
  -2.93297,-2.90843,-2.88388,-2.85934,-2.8348,-2.81025,-2.78571,-2.76117,-2.73662,-2.71208,-2.68753,-2.66299,-2.63845,-2.6139,
  -2.58936,-2.56482,-2.54027,-2.51573,-2.49118,-2.46664,-2.4421,-2.41755,-2.39301,-2.36847,-2.34392,-2.31938,-2.29484,-2.27029,
  -2.24575,-2.2212,-2.19666,-2.17212,-2.14757,-2.12303,-2.09849,-2.07394,-2.0494,-2.02485,-2.00031,-1.97577,-1.95122,-1.92668,
  -1.90214,-1.87759,-1.85305,-1.82851,-1.80396,-1.77942,-1.75487,-1.73033,-1.70579,-1.68124,-1.6567,-1.63216,-1.60761,-1.58307,
  -1.55852,-1.53398,-1.50944,-1.48489,-1.46035,-1.43581,-1.41126,-1.38672,-1.36217,-1.33763,-1.31309,-1.28854,-1.264,-1.23946,
  -1.21491,-1.19037,-1.16583,-1.14128,-1.11674,-1.09219,-1.06765,-1.04311,-1.01856,-0.99402,-0.969476,-0.944932,-0.920388,-0.895845,
  -0.871301,-0.846757,-0.822214,-0.79767,-0.773126,-0.748583,-0.724039,-0.699495,-0.674952,-0.650408,-0.625864,-0.60132,-0.576777,
  -0.552233,-0.527689,-0.503146,-0.478602,-0.454058,-0.429515,-0.404971,-0.380427,-0.355884,-0.33134,-0.306796,-0.282252,-0.257709,
  -0.233165,-0.208621,-0.184078,-0.159534,-0.13499,-0.110447,-0.0859029,-0.0613592,-0.0368155,-0.0122718,0.0122718,0.0368155,
  0.0613592,0.0859029,0.110447,0.13499,0.159534,0.184078,0.208621,0.233165,0.257709,0.282252,0.306796,0.33134,0.355884,0.380427,
  0.404971,0.429515,0.454058,0.478602,0.503146,0.527689,0.552233,0.576777,0.60132,0.625864,0.650408,0.674952,0.699495,0.724039,
  0.748583,0.773126,0.79767,0.822214,0.846757,0.871301,0.895845,0.920388,0.944932,0.969476,0.99402,1.01856,1.04311,1.06765,1.09219,
  1.11674,1.14128,1.16583,1.19037,1.21491,1.23946,1.264,1.28854,1.31309,1.33763,1.36217,1.38672,1.41126,1.43581,1.46035};
  
  float cemctowers[96][256] = {0};
  float ihcaltowers[24][64] = {0};
  float ohcaltowers[24][64] = {0};

  std::vector<float> interest_eta;
  std::vector<float> interest_phi;
  std::vector<int> interest_ieta;
  std::vector<int> interest_iphi;
  std::vector<int> ihcal_interest_eta;
  std::vector<int> ihcal_interest_phi;
  
  float cemc_sf = 0.02;
  float ihcal_sf = 0.162166;
  float ohcal_sf = 0.0338021; 

  float epsilon = 0.001;

  TVector3 v1, v2;

  for (int i = 0; i < n_twr_cemc; i++) {
    int temp_eta = 0;
    int temp_phi = 0;
    for (int ieta = 0; ieta < 96; ieta++) {
      if (fabs(eta_em[ieta] - twr_cemc_eta[i]) < epsilon) { 
        temp_eta = ieta;
        break; 
      }
    }
    for (int iphi = 0; iphi < 256; iphi++) {
      if (fabs(phi_em[iphi] - twr_cemc_phi[i]) < epsilon) { 
        temp_phi = iphi;
        break; 
      }
    }
    cemctowers[temp_eta][temp_phi] = twr_cemc_e[i]/cemc_sf;
  }

  for (int i = 0; i < n_twr_ihcal; i++) {
    int temp_eta = 0;
    int temp_phi = 0;
    for (int ieta = 0; ieta < 24; ieta++) {
      if (fabs(eta[ieta] - twr_ihcal_eta[i]) < epsilon) {
        temp_eta = ieta;
        break; 
      }
    }
    for (int iphi = 0; iphi < 64; iphi++) {
      if (fabs(phi[iphi] - twr_ihcal_phi[i]) < epsilon) { 
        temp_phi = iphi;
        break;
      }
    }
    ihcaltowers[temp_eta][temp_phi] = twr_ihcal_e[i]/ihcal_sf;
  }

  for (int i = 0; i < n_twr_ohcal; i++) {
    int temp_eta;
    int temp_phi;
    for (int ieta = 0; ieta < 24; ieta++) {
      if (fabs(eta[ieta] - twr_ohcal_eta[i]) < epsilon) { 
        temp_eta = ieta;
        break; 
      }
    }
    for (int iphi = 0; iphi < 64; iphi++) {
      if (fabs(phi[iphi] - twr_ohcal_phi[i]) < epsilon) { 
        temp_phi = iphi;
        break; 
      }
    }
    ohcaltowers[temp_eta][temp_phi] = twr_ohcal_e[i]/ohcal_sf;
  }
  
  for (int i = 3; i < 93; i++) {
    for (int j = 0; j < 256; j++) {
      bool iso = true;
      if (cemctowers[i][j] < 0.1) continue;
      for (int ie = -3; ie <= 3; ie++) {
        for (int ip = -3; ip <= 3; ip++) {
          if(ie == 0 && ip == 0) continue;
          if(cemctowers[i+ie][(j+ip) % 256] > 0.1){
            iso = false;
            break;
          }
        }
        if (!iso) break;
      }
      if (iso) {
        if (cemctowers[i][j] > 0.15 && cemctowers[i][j] < 0.4) {
          interest_eta.push_back(eta_em[i]);
          interest_phi.push_back(phi_em[j]);
          interest_ieta.push_back(i);
          interest_iphi.push_back(j);
          emcal_raw->Fill(cemctowers[i][j]);
        }
      }
    }
  }
  
  for (int ep = 0; ep < interest_eta.size(); ep++) {
    v1.SetPtEtaPhi(1, interest_eta[ep], interest_phi[ep]);
    for (int i = 0; i < 24; i++) {
      for (int j = 0; j < 64; j++) {
        v2.SetPtEtaPhi(1, eta[i], phi[j]);
        if (v1.DeltaR(v2) < 0.05) {
          ihcal_interest_eta.push_back(i);
          ihcal_interest_phi.push_back(j);
        }
      }
    }
  }
    
  float E2_ohcal;
  std::vector<int> ihcal_mip_id;
  for (int ep = 0; ep < ihcal_interest_eta.size(); ep++) {
    ihcal_mip_id.clear();
    if (ihcaltowers[ihcal_interest_eta[ep]][ihcal_interest_phi[ep]] < 0.01) continue;
    if (ihcaltowers[ihcal_interest_eta[ep]-1][(ihcal_interest_phi[ep]-1)%64] > 0.01 || ihcaltowers[ihcal_interest_eta[ep]-1][(ihcal_interest_phi[ep]+1)%64] > 0.1) continue;
    if (ihcaltowers[ihcal_interest_eta[ep]+1][(ihcal_interest_phi[ep]-1)%64] > 0.01 || ihcaltowers[ihcal_interest_eta[ep]+1][(ihcal_interest_phi[ep]+1)%64] > 0.1) continue;
    E2_ohcal = 0;
    for (int ie = -2; ie <= 2; ie++) {
      for (int ip = -2; ip <= 2; ip++) {
        E2_ohcal += ohcaltowers[ihcal_interest_eta[ep]+ie][(ihcal_interest_phi[ep]+ip) % 64];
      }
    }
    if (ohcaltowers[ihcal_interest_eta[ep]][ihcal_interest_phi[ep]] > 1.0 && E2_ohcal > 1.0) {
      ihcal_raw_mip->Fill(ihcaltowers[ihcal_interest_eta[ep]][ihcal_interest_phi[ep]]);
      emcal_raw_mip->Fill(cemctowers[interest_ieta[ep]][interest_iphi[ep]]);
      // classify the contributions to the ihcal_raw_mip histogram
      v1.SetPtEtaPhi(1, eta[ihcal_interest_eta[ep]], phi[ihcal_interest_phi[ep]]);
      for (int i = 0; i < IH_n; i++) {
        if (IH_track_id[i] < 0) continue;
        int temp_eta = atan2(IH_y[i],IH_x[i]);
        int temp_phi = -atanh(IH_z[i]/(IH_x[i]*IH_x[i] + IH_y[i]*IH_y[i] + IH_z[i]*IH_z[i]));
        v2.SetPtEtaPhi(1,temp_eta,temp_phi);
        if (v1.DeltaR(v2) < 0.04) { ihcal_mip_id.push_back(IH_track_id[i]); }
      }
      if (ihcal_mip_id.size() == 0) {
        // no primary particles in isolated tower
        ihcal_raw_mip_0->Fill(ihcaltowers[ihcal_interest_eta[ep]][ihcal_interest_phi[ep]]);
        emcal_raw_mip_0->Fill(cemctowers[interest_ieta[ep]][interest_iphi[ep]]);
      } else if (ihcal_mip_id.size() == 1) {
        ihcal_raw_mip_1->Fill(ihcaltowers[ihcal_interest_eta[ep]][ihcal_interest_phi[ep]]);
        emcal_raw_mip_1->Fill(cemctowers[interest_ieta[ep]][interest_iphi[ep]]);
        int mip = 2; 
        int classify = 7;
        for (int i = 0; i < n_tracks; i++) {
          if (tr_truth_track_id[i] == ihcal_mip_id[0]) {
            classify = mipShowerClassifier(i);
            break;
          }
        }
        if (classify <= 3) { 
          mip = 0; 
          ihcal_mip_mip->Fill(ihcaltowers[ihcal_interest_eta[ep]][ihcal_interest_phi[ep]]);
          emcal_mip_mip->Fill(cemctowers[interest_ieta[ep]][interest_iphi[ep]]);
        } else if (classify > 3 && classify < 7) { 
          mip = 1; 
          ihcal_mip_shower->Fill(ihcaltowers[ihcal_interest_eta[ep]][ihcal_interest_phi[ep]]);
          emcal_mip_shower->Fill(cemctowers[interest_ieta[ep]][interest_iphi[ep]]);
        } else {
          ihcal_mip_other->Fill(ihcaltowers[ihcal_interest_eta[ep]][ihcal_interest_phi[ep]]);
          emcal_mip_other->Fill(cemctowers[interest_ieta[ep]][interest_iphi[ep]]);
        }
      } else {
        // more than one primary particle in isolated tower
        ihcal_raw_mip_2->Fill(ihcaltowers[ihcal_interest_eta[ep]][ihcal_interest_phi[ep]]);
        emcal_raw_mip_2->Fill(cemctowers[interest_ieta[ep]][interest_iphi[ep]]);
      }
    }
  }
}
    /*
    int ind = 0;
    for (int i = 10; i <= 15; i++) {
      for (int j = 8; j <= 15; j++) {
        if (ohcaltowers[ihcal_interest_eta[ep]][ihcal_interest_phi[ep]] > 0.1*j && E2_ohcal > 0.1*i) {
          ihcal_mip[ind]->Fill(ihcaltowers[ihcal_interest_eta[ep]][ihcal_interest_phi[ep]]);
          emcal_mip[ind]->Fill(cemctowers[interest_ieta[ep]][interest_iphi[ep]]);
          //ohcal_mip->Fill(ohcaltowers[ihcal_interest_eta[ep]][ihcal_interest_phi[ep]]);
          //ohcal_E2->Fill(E2_ohcal);
        }
        ind++;
      }
    }*/

