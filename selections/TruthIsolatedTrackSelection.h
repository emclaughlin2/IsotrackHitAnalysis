#pragma once
#include <TVector3.h>
#include <set>
#include "../IsotrackHitAnalysis.h"

bool IsotrackHitAnalysis::truthIsolatedTrackSelection(int id) {

    const std::set<int> neutral_pid = {-3322,-3212,-3122,-2112,-421,-14,-12,12,14,22,111,130,310,421,
                         2112,3122,3212,3322};

    // Truth isolation condition
    TVector3 v1, v2;
    v1.SetPtEtaPhi(tr_pt[id], tr_cemc_eta[id], tr_cemc_phi[id]);
    for (int j = 0; j < n_truth; j++) {
        if (truth_parent_id[j] != 0 || neutral_pid.find(truthpid[j]) == neutral_pid.end() || truthpt[j] < MATCHED_NEUTRAL_TRUTH_PT_CUT || fabs(trutheta[j]) > MATCHED_NEUTRAL_TRUTH_ETA_CUT) { continue; }

        v2.SetPtEtaPhi(truthpt[j], trutheta[j], truthphi[j]);

        if (v1.DeltaR(v2) < MATCHED_NEUTRAL_TRUTH_DR_CUT) {
            return false;
        }
    }

    return true;
}
