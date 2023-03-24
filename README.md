# IsotrackTreesAnalysis

Usage:

1. Clone from git
2. Create a build folder
3. Set the build path in the makefile
4. Issue "make" and then run the executable

Add any new modules in the "processEvent(...)" and "processTrack(...)" functions.
A module with a single function should be added as a member function to the IsotrackTreesAnalysis class. The definition of the function should go in a separate \*.C file - it is not needed to include .h file.
