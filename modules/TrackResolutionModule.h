#pragma once
#include "../IsotrackHitAnalysis.h"
#include <TVector3.h>
#include <TRandom3.h>
#include <TH2F.h>

const int DISTORTIONS[5] = {0,300,400,500,700};

double ptResolution(double pt, int distortion, double scale){
  //double a = distortion*0.91982657801648 + 0.00798245252991571;
  double a = 0.0, b = 0.0;

  switch(distortion){
    case 0:
      a = 0.000885438147627331;
      b = 0.00978112839672971;
      break;
    case 300:
      a = 0.00237697580047898;
      b = 0.00942910542272066;
      break;
    case 400:
      a = 0.00306811664575797;
      b = 0.00955644597998534;
      break;
    case 500:
      a = 0.00371139216245887;
      b = 0.0110248830574131;
      break;
    case 700:
      a = 0.00503286950050454;
      b = 0.0133511646499965;
      break;
  }

  return scale*(a*pt+b);
}

void IsotrackHitAnalysis::initTrackResolutionModule(){
  for(int i = 0; i < 5; i++){
    histEoverP_2D[i] = new TH2F(Form("trackresolution_e_over_p_2D_distortion%d",DISTORTIONS[i]),";E/p;p_{T} [GeV]", 100,0.0,4.0, 19,1.0,20.0);
  }
}


void IsotrackHitAnalysis::trackResolutionModule(int id, float totalEnergy){

    TVector3 track;

    for(int i = 0; i < 5; i++){
        float ptRelativeSigma = ptResolution(m_tr_pt[id], DISTORTIONS[i], 1.0);
        float smearedPt = rand->Gaus(m_tr_pt[id],m_tr_pt[id]*ptRelativeSigma);
        track.SetPtEtaPhi(smearedPt,m_tr_eta[id],m_tr_phi[id]);

        histEoverP_2D[i]->Fill( totalEnergy / track.Mag() , track.Pt() );
    }
}
