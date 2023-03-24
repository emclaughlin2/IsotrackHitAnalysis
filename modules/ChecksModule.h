#pragma once
#include "../IsotrackHitAnalysis.h"
#include "../selections/MipShowerClassifier.h"
#include <TVector3.h>
#include <string>

void IsotrackHitAnalysis::initChecksModule() {
	histTrackTotal = new TH1F("total_track_rate","",20,0,20);
	std::string detector[] = {"cemc","ihcal","ohcal"};
	for (int i = 0; i < 3; i++) {
    	histTowerNumber[i] = new TH1F(TString::Format("tower_region_number_%s",detector[i].c_str()),"",100,-0.5,99.5);
  	}
  	histTruthClassRates = new TH2F("truth_classification_rates","",20,0,20,7,0.5,7.5);

}

void IsotrackHitAnalysis::checksModule(int id, MatchedClusterContainer cemcClusters, MatchedClusterContainer ihcalClusters, MatchedClusterContainer ohcalClusters) {
	histTrackTotal->Fill(tr_p[id]);
	histTowerNumber[0]->Fill(cemcClusters.getNumberOfClusters());
	histTowerNumber[1]->Fill(ihcalClusters.getNumberOfClusters());
	histTowerNumber[2]->Fill(ohcalClusters.getNumberOfClusters());
	histTruthClassRates->Fill(tr_p[id], mipShowerClassifier(id));
}