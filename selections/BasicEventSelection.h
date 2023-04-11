// Code for basic event selection

#include "../IsotrackHitAnalysis.h"

bool IsotrackHitAnalysis::basicEventSelection(){
    // Centrality cut
    if (n_truth == 500000 || n_vertex == 500000 ) { return false; }
    if (!USE_CENTRALITY) { return true; } 
    return (centrality > CENTRALITY_CUT);
}
