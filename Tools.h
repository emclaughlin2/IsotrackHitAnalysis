#pragma once
#include "ClusterContainer.h"
//#include "IsotrackHitAnalysis.h"
#include <TVector.h>

MatchedClusterContainer IsotrackHitAnalysis::getMatchedSimTowers(int id, caloType type, float dRThreshold){
    
    MatchedClusterContainer clusterContainer;
    TVector3 track, cluster;
    float cemc_sf = 0.02;
    float ihcal_sf = 0.162166;
    float ohcal_sf = 0.0338021;

    switch(type){

        case cemc:
            // Check if EMCal is reached
            for(int i = 0; i < n_twr_cemc; i++){ 
                if(tr_cemc_eta[id] > -998 && tr_ihcal_eta[id] > -998){
                    track.SetPtEtaPhi(1.0, m_tr_cemc_eta[id], 0.5*(m_tr_cemc_phi[id]+m_tr_ihcal_phi[id])); // for the track we only need the direction!
                    cluster.SetPtEtaPhi(twr_cemc_e[i]/(cemc_sf*cosh(twr_cemc_eta[i])), twr_cemc_eta[i], twr_cemc_phi[i]);
                    float dR = track.DeltaR(cluster);
                    if(dR < dRThreshold){
                        clusterContainer.addCluster(cluster, dR);
                    }
                }
            }
            break;

        case ihcal:
            // Check if IHCal is reached
            for(int i = 0; i < n_twr_ihcal; i++){ 
                if(tr_ihcal_eta[id] > -998){
                    track.SetPtEtaPhi(1.0, m_tr_ihcal_eta[id], m_tr_ihcal_phi[id] - m_tr_charge[id]*0.09); // for the track we only need the direction!
                    cluster.SetPtEtaPhi(twr_ihcal_e[i]/(ihcal_sf*cosh(twr_ihcal_eta[i])), twr_ihcal_eta[i], twr_ihcal_phi[i]);
                    float dR = track.DeltaR(cluster);
                    if(dR < dRThreshold){
                        clusterContainer.addCluster(cluster, dR);
                    }
                }
            }
            break;

        case ohcal:
            // Check if OHCal is reached
            for(int i = 0; i < n_twr_ohcal; i++){
                if(tr_ohcal_eta[id] > -998){
                    track.SetPtEtaPhi(1.0, m_tr_ohcal_eta[id], m_tr_ohcal_phi[id] + m_tr_charge[id] * 0.04); // for the track we only need the direction!
                    cluster.SetPtEtaPhi(twr_ohcal_e[i]/(ohcal_sf*cosh(twr_ohcal_eta[i])), twr_ohcal_eta[i], twr_ohcal_phi[i]);
                    float dR = track.DeltaR(cluster);
                    if(dR < dRThreshold){
                        clusterContainer.addCluster(cluster, dR);
                    }
                }
            }
            break;
    }

    return clusterContainer;
}