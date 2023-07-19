#pragma once
#include "../IsotrackHitAnalysis.h"
#include <TVector3.h>
#include <string>
#include <set> 
#include <map>

void IsotrackHitAnalysis::initIhcalMipModule() {
  /*
  std::string mip_shower_list[] = {"shower","mip"};
  for (int i = 0; i < 2; i++) {

    E2_ohcal[i] = new TH1F(TString::Format("E2_ohcal_%s",mip_shower_list[i].c_str()), ";E [GeV];Entries", 1000, 0.0, 10);
    E2_emcal[i] = new TH1F(TString::Format("E2_emcal_%s",mip_shower_list[i].c_str()), ";E [GeV],Entries", 1000, 0.0, 10);
    E2_ihcal[i] = new TH1F(TString::Format("E2_ihcal_%s",mip_shower_list[i].c_str()), ";E [GeV],Entries", 1000, 0.0, 10);
    E2_all[i] = new TH1F(TString::Format("E2_all_%s",mip_shower_list[i].c_str()), ";E [GeV],Entries", 2000, 0.0, 20);
    E1_emcal[i] = new TH1F(TString::Format("E1_emcal_%s",mip_shower_list[i].c_str()), ";E [GeV],Entries", 1000, 0.0, 10);
    E1_ihcal[i] = new TH1F(TString::Format("E1_ihcal_%s",mip_shower_list[i].c_str()), ";E [GeV],Entries", 1000, 0.0, 10);
    buffer2_emcal[i] = new TH1F(TString::Format("buffer2_emcal_%s",mip_shower_list[i].c_str()), ";E [GeV],Entries", 1000, 0.0, 10);
    buffer2_ihcal[i] = new TH1F(TString::Format("buffer2_ihcal_%s",mip_shower_list[i].c_str()), ";E [GeV],Entries", 1000, 0.0, 10);
    buffer2_mip_emcal[i] = new TH1F(TString::Format("buffer2_mip_emcal_%s",mip_shower_list[i].c_str()),";E [Gev],Entries", 1000, 0.0, 10);
    buffer2_mip_ihcal[i] = new TH1F(TString::Format("buffer2_mip_ihcal_%s",mip_shower_list[i].c_str()),";E [GeV],Entries", 1000, 0.0, 10);
    buffer3_ohcal[i] = new TH1F(TString::Format("buffer3_ohcal_%s",mip_shower_list[i].c_str()), ";E [GeV];Entries", 1000, 0.0, 10);
    buffer3_all[i] = new TH1F(TString::Format("buffer3_all_%s",mip_shower_list[i].c_str()), ";E [GeV],Entries", 1000, 0.0, 10);
    buffer4_ohcal[i] = new TH1F(TString::Format("buffer4_ohcal_%s",mip_shower_list[i].c_str()), ";E [GeV];Entries", 1000, 0.0, 10);
    buffer4_all[i] = new TH1F(TString::Format("buffer4_all_%s",mip_shower_list[i].c_str()), ";E [GeV],Entries", 1000, 0.0, 10);
    buffer3_mip_ohcal[i] = new TH1F(TString::Format("buffer3_mip_ohcal_%s",mip_shower_list[i].c_str()), ";E [GeV];Entries", 1000, 0.0, 10);
    buffer3_mip_all[i] = new TH1F(TString::Format("buffer3_mip_all_%s",mip_shower_list[i].c_str()), ";E [GeV],Entries", 1000, 0.0, 10);
    buffer4_mip_ohcal[i] = new TH1F(TString::Format("buffer4_mip_ohcal_%s",mip_shower_list[i].c_str()), ";E [GeV];Entries", 1000, 0.0, 10);
    buffer4_mip_all[i] = new TH1F(TString::Format("buffer4_mip_all_%s",mip_shower_list[i].c_str()), ";E [GeV],Entries", 1000, 0.0, 10);
  }*/
}

void IsotrackHitAnalysis::ihcalMipModule(int id, MatchedClusterContainer cemcClusters, MatchedClusterContainer ihcalClusters, MatchedClusterContainer ohcalClusters){
/*
  int mip;
  int classify = mipShowerClassifier(id);
  if (classify <= 3) { mip = 0; }
  else if (classify > 3 && classify < 7) { mip = 1; }
  else { return; }

  float cemcr1energy = cemcClusters.getTotalEnergy(0.1);
  float cemcr2energy = cemcClusters.getTotalEnergy(0.2);
  float cemcr3energy = cemcClusters.getTotalEnergy(0.3);
  float cemcr4energy = cemcClusters.getTotalEnergy(0.4);
  
  float ihcalr1energy = ihcalClusters.getTotalEnergy(0.1);
  float ihcalr2energy = ihcalClusters.getTotalEnergy(0.2);
  float ihcalr3energy = ihcalClusters.getTotalEnergy(0.3);
  float ihcalr4energy = ihcalClusters.getTotalEnergy(0.4);
  
  float ohcalr2energy = ohcalClusters.getTotalEnergy(0.2);
  float ohcalr3energy = ohcalClusters.getTotalEnergy(0.3);
  float ohcalr4energy = ohcalClusters.getTotalEnergy(0.4);

  float totalr2 = cemcr2energy + ihcalr2energy + ohcalr2energy;
  float totalr3 = cemcr3energy + ihcalr3energy + ohcalr3energy;
  float totalr4 = cemcr4energy + ihcalr4energy + ohcalr4energy;

  E1_emcal[mip]->Fill(cemcr1energy);
  E1_ihcal[mip]->Fill(ihcalr1energy);

  E2_emcal[mip]->Fill(cemcr2energy);
  E2_ihcal[mip]->Fill(ihcalr2energy);
  E2_ohcal[mip]->Fill(ohcalr2energy);

  buffer2_emcal[mip]->Fill(cemcr2energy - cemcr1energy);
  buffer2_mip_emcal[mip]->Fill((cemcr2energy - cemcr1energy) / cemcr1energy);
  buffer2_ihcal[mip]->Fill(ihcalr2energy - ihcalr1energy);
  buffer2_mip_ihcal[mip]->Fill((ihcalr2energy - ihcalr1energy) / ihcalr1energy);
  
  buffer3_ohcal[mip]->Fill(ohcalr3energy - ohcalr2energy);
  buffer4_ohcal[mip]->Fill(ohcalr4energy - ohcalr2energy);
  buffer3_mip_ohcal[mip]->Fill((ohcalr3energy - ohcalr2energy) / ohcalr2energy);
  buffer4_mip_ohcal[mip]->Fill((ohcalr4energy - ohcalr2energy) / ohcalr2energy);

  E2_all[mip]->Fill(totalr2);
  buffer3_all[mip]->Fill(totalr3 - totalr2);
  buffer4_all[mip]->Fill(totalr4 - totalr2);
  buffer3_mip_all[mip]->Fill((totalr3 - totalr2) / totalr2);
  buffer4_mip_all[mip]->Fill((totalr4 - totalr2) / totalr2);

  std::cout << mip << "," << tr_pt[id] << "," << ohcalr2energy << "," << ihcalr2energy << "," << cemcr2energy << "," << ohcalr3energy - ohcalr2energy << ",";
  std::cout << ohcalr4energy - ohcalr2energy << "," << ohcalr4energy - ohcalr2energy << "," << (ohcalr3energy - ohcalr2energy) / ohcalr2energy << ",";
  std::cout << (ohcalr4energy - ohcalr2energy) / ohcalr2energy << "," << totalr2 << "," << totalr3 - totalr2 << "," << totalr4 - totalr2 << ",";
  std::cout << (totalr3 - totalr2) / totalr2 << "," << (totalr4 - totalr2) / totalr2 << "," << cemcr1energy << "," << ihcalr1energy << ",";
  std::cout << cemcr2energy - cemcr1energy << "," << (cemcr2energy - cemcr1energy) / cemcr1energy << "," << ihcalr2energy - ihcalr1energy << ",";
  std::cout << (ihcalr2energy - ihcalr1energy) / ihcalr1energy << std::endl;
*/
}
