//=======================================================================
/** @file ChordDetector.h
 *  @brief ChordDetector - a class for estimating chord labels from chromagram input
 *  @author Adam Stark
 *  @copyright Copyright (C) 2008-2014  Queen Mary University of London
 *
 * Extended by 
 * Simon Blakely 2015 si.blakely@googlemail.com
 * additional chord types detected, text chord name output, integer chord type
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
//=======================================================================

#ifndef CHORDDETECT_H
#define CHORDDETECT_H

#include <vector>
#include <string>

//=======================================================================
/** A class for estimating chord labels from chromagram input */
class ChordDetector
{
public:
    
    /** An enum describing the chord qualities used in the algorithm */
    enum ChordQuality
    {
        Minor,
        Major,
        Suspended,
        Dominant,
        Dimished5th,
        Augmented5th,
    };
    
	/** Constructor */
	ChordDetector();
    
    /** Detects the chord from a chromagram. This is the vector interface 
     * @param chroma a vector of length 12 containing the chromagram
     */
    void detectChord(std::vector<double> chroma);
    
    /** Detects the chord from a chromagram. This is the array interface
     * @param chroma an array of length 12 containing the chromagram
     */
    void detectChord(double *chroma);
	
    /** The root note of the detected chord */
	int rootNote;
    
    /** The quality of the detected chord (Major, Minor, etc) */
	int quality;
    
    /** Any other intervals that describe the chord, e.g. 7th */
	int intervals;

	/** chord_num 12-bit chord identifier*/
	int chord_num;
	
	/* chord_name*/
	std::string chord_name;

private:
	void makeChordProfiles();

	void classifyChromagram();
	
	double calculateChordScore(double *chroma,double *chordProfile,double biasToUse, double N);

	int minimumIndex(double *array,int length);

	double chromagram[12];
	double chordProfiles[708][12];
	
	double chord[708];
	
	double bias;

	int noise_floor;

	std::string note_names[12];
};

#endif
