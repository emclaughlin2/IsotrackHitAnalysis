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
                    float projection_eta = 0.5 * (tr_cemc_eta[id] + tr_ihcal_eta[id]);
                    float projection_phi = 0.5 * (tr_cemc_phi[id] + tr_ihcal_phi[id]);
                    track.SetPtEtaPhi(1.0, projection_eta, projection_phi); // for the track we only need the direction!
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
                    track.SetPtEtaPhi(1.0, tr_ihcal_eta[id], tr_ihcal_phi[id]); // for the track we only need the direction!
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
                    track.SetPtEtaPhi(1.0, tr_ohcal_eta[id], tr_ohcal_phi[id]); // for the track we only need the direction!
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