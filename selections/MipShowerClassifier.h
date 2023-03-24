#pragma once
#include <TVector3.h>
#include <set>
#include "../IsotrackHitAnalysis.h"

int IsotrackHitAnalysis::mipShowerClassifier(int id) {

    // classify tracker showers as 1, emcal showers as 2, ihcal showers as 3, magnet showers as 4, ohcal showers as 5, full mips as 6
    const float emcal_inner = 92;
    const float emcal_outer = 116;
    const float ihcal_inner = 117.27;
    const float ihcal_outer = 134.42;
    const float ohcal_inner = 183.3;
    const float ohcal_outer = 274.317;

    // assert(m_tr_truth_track_id[id] == 1); // writing this currently only for use for particle gun !! 
    //std::cout << "p " << tr_p[id] <<" n_truth " << n_truth << " n_vertex " << n_vertex << std::endl;
    int child;
    std::set<int> vertex;
    float v_radius, v_rad;

    // check where particle showers
    for (int i = 0; i < n_truth; i++) {
        if (truth_track_id[i] < 0 && truth_parent_id[i] == tr_truth_track_id[id] && abs(truthpid[i]) != 11 && truthpid[i] != 22) {
            vertex.insert(truth_vertex_id[i]); 
            //std::cout << "child_id: " << truth_track_id[i] << " pid: " << truthpid[i] << " vertex_id: " << truth_vertex_id[i] << std::endl;
        }
    }
    //std::cout << "vertex set:" << std::endl;
    v_radius = ohcal_outer + 1;
    for (std::set<int>::iterator it = vertex.begin(); it != vertex.end(); it++) {
        child = 0;
        for (int i = 0 ; i < n_truth; i++) {
            if (truth_track_id[i] < 0 && truth_vertex_id[i] == *it && abs(truthpid[i]) != 11 && truthpid[i] != 22) child++;
        }
        if (child > 1) {
            // now find the location of the shower vertex
            for (int v = 0; v < n_vertex; v++) {
                if (vertex_id[v] == *it) {
                    v_rad = sqrt(vertex_x[v]*vertex_x[v] + vertex_y[v]*vertex_y[v]);
                    /*
                    std::cout << *it << " " << vertex_id[v] << " v_rad " << v_rad << " n_child " << child << " child pids ";
                    for (int i = 0; i < n_truth; i++) {
                        if (truth_track_id[i] < 0 && truth_vertex_id[i] == vertex_id[v]) std::cout << truthpid[i] << " ";
                    }
                    */
                    if (v_rad < v_radius) v_radius = v_rad;
                }
            }
            //std::cout << std::endl;
        }
    }
    //std::cout << std::endl;
    // find which calorimeter it is in 
    if (v_radius < emcal_inner) {
        return 1; // showers in tracker
    } else if (v_radius >= emcal_inner && v_radius <= ihcal_inner) {
        return 2; // showers in emcal
    } else if (v_radius >= ihcal_inner && v_radius <= ihcal_outer) {
        return 3; // showers in ihcal
    } else if (v_radius > ihcal_outer && v_radius < ohcal_inner) {
        return 4; // showers in magnet 
    } else if (v_radius >= ohcal_inner && v_radius <= ohcal_outer) {
        return 5; // showers in ohcal 
    } else if (v_radius > ohcal_outer) {
        return 6; // mips
    }
    return 7;
}
