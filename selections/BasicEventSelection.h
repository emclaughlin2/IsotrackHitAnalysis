// Code for basic event selection

#include "../IsotrackHitAnalysis.h"

bool IsotrackHitAnalysis::basicEventSelection(){
    // Centrality cut
    if (!USE_CENTRALITY) { return true; } 
    if (n_truth == 500000) { return false; }
    return (centrality > CENTRALITY_CUT);
}
