//=======================================================================
/** @file ChordDetector.cpp
 *  @brief ChordDetector - a class for estimating chord labels from chromagram input
 *  @author Adam Stark
 *  @copyright Copyright (C) 2008-2014  Queen Mary University of London

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

#include "ChordDetector.h"
#include <math.h>

//=======================================================================
ChordDetector::ChordDetector()
{
	bias = 1.06;

	note_names[0] = "C";
	note_names[1] = "C#";
	note_names[2] = "D";
	note_names[3] = "D#";
	note_names[4] = "E";
	note_names[5] = "F";
	note_names[6] = "F#";
	note_names[7] = "G";
	note_names[8] = "G#";
	note_names[9] = "A";
	note_names[10] = "A#";
	note_names[11] = "B";

	makeChordProfiles();

		
}

//=======================================================================
void ChordDetector::detectChord(std::vector<double> chroma)
{
    detectChord(&chroma[0]);
}

//=======================================================================
void ChordDetector::detectChord(double *chroma)
{
	for (int i = 0;i < 12;i++)
	{
		chromagram[i] = chroma[i];
	}

	classifyChromagram();
}


//=======================================================================
void ChordDetector::classifyChromagram()
{
	int i;
	int j;
	int fifth;
	int chordindex;
	
	// remove some of the 5th note energy from chromagram
	for (i = 0;i < 12;i++)
	{
		fifth = (i+7) % 12;
		chromagram[fifth] = chromagram[fifth] - (0.1*chromagram[i]);
		
		if (chromagram[fifth] < 0)
		{
			chromagram[fifth] = 0;
		}
		
	}
	
	
	// major chords 
	for (j=0;j < 12;j++)
	{
		chord[j] = calculateChordScore(chromagram,chordProfiles[j],bias,3);
	}
	
	// minor chords 
	for (j=12;j < 24;j++)
	{
		chord[j] = calculateChordScore(chromagram,chordProfiles[j],bias,3);
	}
	
	// diminished 5th chords
	for (j=24;j < 36;j++)
	{
		chord[j] = calculateChordScore(chromagram,chordProfiles[j],bias,3);
	}
	
	// augmented 5th chords
	for (j=36;j < 48;j++)
	{
		chord[j] = calculateChordScore(chromagram,chordProfiles[j],bias,3);
	}
	
	// sus2 chords
	for (j=48;j < 60;j++)
	{
		chord[j] = calculateChordScore(chromagram,chordProfiles[j],1,3);
	}
	
	// sus4 chords
	for (j=60;j < 72;j++)
	{
		chord[j] = calculateChordScore(chromagram,chordProfiles[j],1,3);
	}
	
	// major 7th chords
	for (j=72;j < 84;j++)
	{
		chord[j] = calculateChordScore(chromagram,chordProfiles[j],1,4);
	}
	
	// minor 7th chords
	for (j=84;j < 96;j++)
	{
		chord[j] = calculateChordScore(chromagram,chordProfiles[j],bias,4);
	}

	// dominant 7th chords
	for (j=96;j < 108;j++)
	{
		chord[j] = calculateChordScore(chromagram,chordProfiles[j],bias,4);
	}

	/* additional chord types for future development

	// 5th chords
	for (j = 108; j < 120; j++)
	{
		chord[j] = calculateChordScore(chromagram, chordProfiles[j], bias, 2);
	}

	// 6th chords
	for (j = 120; j < 132; j++)
	{
		chord[j] = calculateChordScore(chromagram, chordProfiles[j], bias, 4);
	}

	// min6th chords
	for (j = 132; j < 144; j++)
	{
		chord[j] = calculateChordScore(chromagram, chordProfiles[j], bias, 4);
	}

	// 9th chords
	for (j = 144; j < 156; j++)
	{
		chord[j] = calculateChordScore(chromagram, chordProfiles[j], bias, 5);
	}

	// min9th chords
	for (j = 156; j < 168; j++)
	{
		chord[j] = calculateChordScore(chromagram, chordProfiles[j], bias, 5);
	}

	// maj9th chords
	for (j = 168; j < 180; j++)
	{
		chord[j] = calculateChordScore(chromagram, chordProfiles[j], bias, 5);
	}

	// minmaj9th chords
	for (j = 180; j < 192; j++)
	{
		chord[j] = calculateChordScore(chromagram, chordProfiles[j], bias, 5);
	}

	// 11th chords
	for (j = 192; j < 204; j++)
	{
		chord[j] = calculateChordScore(chromagram, chordProfiles[j], bias, 6);
	}

	// min11th chords
	for (j = 204; j < 216; j++)
	{
		chord[j] = calculateChordScore(chromagram, chordProfiles[j], bias, 6);
	}

	// Maj11th chords
	for (j = 216; j < 228; j++)
	{
		chord[j] = calculateChordScore(chromagram, chordProfiles[j], bias, 6);
	}

	// minMaj11th chords
	for (j = 228; j < 240; j++)
	{
		chord[j] = calculateChordScore(chromagram, chordProfiles[j], bias, 6);
	}

	// 13th chords
	for (j = 240; j < 252; j++)
	{
		chord[j] = calculateChordScore(chromagram, chordProfiles[j], bias, 6);
	}

	// min13th chords
	for (j = 252; j < 264; j++)
	{
		chord[j] = calculateChordScore(chromagram, chordProfiles[j], bias, 6);
	}

	// Maj13th chords
	for (j = 264; j < 276; j++)
	{
		chord[j] = calculateChordScore(chromagram, chordProfiles[j], bias, 6);
	}

	// minMaj13th chords
	for (j = 276; j < 288; j++)
	{
		chord[j] = calculateChordScore(chromagram, chordProfiles[j], bias, 6);
	}

	// Add9 chords
	for (j = 288; j < 300; j++)
	{
		chord[j] = calculateChordScore(chromagram, chordProfiles[j], bias, 4);
	}

	// minAdd9 chords
	for (j = 300; j < 312; j++)
	{
		chord[j] = calculateChordScore(chromagram, chordProfiles[j], bias, 4);
	}

	// 6Add9 chords
	for (j = 312; j < 324; j++)
	{
		chord[j] = calculateChordScore(chromagram, chordProfiles[j], bias, 5);
	}

	// min6Add9 chords
	for (j = 324; j < 336; j++)
	{
		chord[j] = calculateChordScore(chromagram, chordProfiles[j], bias, 5);
	}

	// Dom7Add11 chords
	for (j = 336; j < 348; j++)
	{
		chord[j] = calculateChordScore(chromagram, chordProfiles[j], bias, 5);
	}

	// Maj7Add11 chords
	for (j = 348; j < 360; j++)
	{
		chord[j] = calculateChordScore(chromagram, chordProfiles[j], bias, 5);
	}

	// min7Add11 chords
	for (j = 360; j < 372; j++)
	{
		chord[j] = calculateChordScore(chromagram, chordProfiles[j], bias, 5);
	}

	// minMaj7Add11 chords
	for (j = 372; j < 384; j++)
	{
		chord[j] = calculateChordScore(chromagram, chordProfiles[j], bias, 5);
	}

	// dom7Add13 chords
	for (j = 384; j < 396; j++)
	{
		chord[j] = calculateChordScore(chromagram, chordProfiles[j], bias, 5);
	}

	// Maj7Add13 chords
	for (j = 396; j < 408; j++)
	{
		chord[j] = calculateChordScore(chromagram, chordProfiles[j], bias, 5);
	}

	// min7Add13 chords
	for (j = 408; j < 420; j++)
	{
		chord[j] = calculateChordScore(chromagram, chordProfiles[j], bias, 5);
	}

	// minMaj7Add13 chords
	for (j = 420; j < 432; j++)
	{
		chord[j] = calculateChordScore(chromagram, chordProfiles[j], bias, 5);
	}

	// 7b5 chords
	for (j = 432; j < 444; j++)
	{
		chord[j] = calculateChordScore(chromagram, chordProfiles[j], bias, 4);
	}

	// 7#5 chords
	for (j = 444; j < 456; j++)
	{
		chord[j] = calculateChordScore(chromagram, chordProfiles[j], bias, 4);
	}

	// 7b9 chords
	for (j = 456; j < 468; j++)
	{
		chord[j] = calculateChordScore(chromagram, chordProfiles[j], bias, 5);
	}

	// 7#9 chords
	for (j = 468; j < 480; j++)
	{
		chord[j] = calculateChordScore(chromagram, chordProfiles[j], bias, 5);
	}

	// 7#5b9 chords
	for (j = 480; j < 492; j++)
	{
		chord[j] = calculateChordScore(chromagram, chordProfiles[j], bias, 5);
	}

	// m7b5 chords
	for (j = 492; j < 504; j++)
	{
		chord[j] = calculateChordScore(chromagram, chordProfiles[j], bias, 4);
	}

	// m7#5 chords
	for (j = 504; j < 516; j++)
	{
		chord[j] = calculateChordScore(chromagram, chordProfiles[j], bias, 4);
	}

	// m7b9 chords
	for (j = 516; j < 528; j++)
	{
		chord[j] = calculateChordScore(chromagram, chordProfiles[j], bias, 5);
	}

	// 9#11 chords
	for (j = 528; j < 540; j++)
	{
		chord[j] = calculateChordScore(chromagram, chordProfiles[j], bias, 6);
	}

	// 9b13 chords
	for (j = 540; j < 552; j++)
	{
		chord[j] = calculateChordScore(chromagram, chordProfiles[j], bias, 6);
	}

	// 6sus4 chords
	for (j = 552; j < 564; j++)
	{
		chord[j] = calculateChordScore(chromagram, chordProfiles[j], bias, 4);
	}

	// 7sus4 chords
	for (j = 564; j < 576; j++)
	{
		chord[j] = calculateChordScore(chromagram, chordProfiles[j], bias, 4);
	}

	// Maj7sus4 chords
	for (j = 576; j < 588; j++)
	{
		chord[j] = calculateChordScore(chromagram, chordProfiles[j], bias, 4);
	}

	// 9sus4 chords
	for (j = 588; j < 600; j++)
	{
		chord[j] = calculateChordScore(chromagram, chordProfiles[j], bias, 5);
	}

	// Maj9sus4 chords
	for (j = 600; j < 612; j++)
	{
		chord[j] = calculateChordScore(chromagram, chordProfiles[j], bias, 5);
	}

	// Maj7b5 chords
	for (j = 612; j < 624; j++)
	{
		chord[j] = calculateChordScore(chromagram, chordProfiles[j], bias, 4);
	}

	// 7#9#11 chords
	for (j = 624; j < 636; j++)
	{
		chord[j] = calculateChordScore(chromagram, chordProfiles[j], bias, 6);
	}

	// 7#11 chords
	for (j = 636; j < 648; j++)
	{
		chord[j] = calculateChordScore(chromagram, chordProfiles[j], bias, 5);
	}

	// 7b9b13 chords
	for (j = 648; j < 660; j++)
	{
		chord[j] = calculateChordScore(chromagram, chordProfiles[j], bias, 6);
	}

	// 7b9/13 chords
	for (j = 660; j < 672; j++)
	{
		chord[j] = calculateChordScore(chromagram, chordProfiles[j], bias, 6);
	}

	// 7/sus2 chords
	for (j = 672; j < 684; j++)
	{
		chord[j] = calculateChordScore(chromagram, chordProfiles[j], bias, 4);
	}

	// dim7 chords
	for (j = 684; j < 696; j++)
	{
		chord[j] = calculateChordScore(chromagram, chordProfiles[j], bias, 4);
	}

	// flat5 chords
	for (j = 696; j < 708; j++)
	{
		chord[j] = calculateChordScore(chromagram, chordProfiles[j], bias, 3);
	}

	*/

	chordindex = minimumIndex(chord,108);

	noise_floor = chord[chordindex];
	
	// major 2192
	if (chordindex < 12)
	{
		rootNote = chordindex;
		quality = Major;
		intervals = 0;
		chord_num = 2192;
		chord_name = note_names[rootNote] + "";
	}
	
	// minor 2320
	if ((chordindex >= 12) && (chordindex < 24))
	{
		rootNote = chordindex-12;
		quality = Minor;
		intervals = 0;
		chord_num = 2320;
		chord_name = note_names[rootNote] + "min";
	}
	
	// diminished 5th 2336
	if ((chordindex >= 24) && (chordindex < 36))
	{
		rootNote = chordindex-24;
		quality = Dimished5th;
		intervals = 0;
		chord_num = 2336;
		chord_name = note_names[rootNote] + "Dim5";
	}
	
	// augmented 5th 2184
	if ((chordindex >= 36) && (chordindex < 48))
	{
		rootNote = chordindex-36;
		quality = Augmented5th;
		intervals = 0;
		chord_num = 2184;
		chord_name = note_names[rootNote] + "Aug5";
	}
	
	// sus2 2576
	if ((chordindex >= 48) && (chordindex < 60))
	{
		rootNote = chordindex-48;
		quality = Suspended;
		intervals = 2;
		chord_num = 2576;
		chord_name = note_names[rootNote] + "sus2";
	}
	
	// sus4 2128
	if ((chordindex >= 60) && (chordindex < 72))
	{
		rootNote = chordindex-60;
		quality = Suspended;
		intervals = 4;
		chord_num = 2128;
		chord_name = note_names[rootNote] + "sus4";
	}
	
	// major 7th 2193
	if ((chordindex >= 72) && (chordindex < 84))
	{
		rootNote = chordindex-72;
		quality = Major;
		intervals = 7;
		chord_num = 2193;
		chord_name = note_names[rootNote] + "Maj7";
	}
	
	// minor 7th 2322
	if ((chordindex >= 84) && (chordindex < 96))
	{
		rootNote = chordindex-84;
		quality = Minor;
		intervals = 7;
		chord_num = 2322;
		chord_name = note_names[rootNote] + "min7";
	}
	
	// dominant 7th 2194
	if ((chordindex >= 96) && (chordindex < 108))
	{
		rootNote = chordindex-96;
		quality = Dominant;
		intervals = 7;
		chord_num = 2194;
		chord_name = note_names[rootNote] + "7th";
	}

	/* for future development

	// 5th 2064
	if ((chordindex >= 120) && (chordindex < 132))
	{
		rootNote = chordindex - 120;
		quality = Dominant;
		intervals = 7;
		chord_num = 2064;
		chord_name = note_names[rootNote] + "5";
	}

	// 6th 2196
	if ((chordindex >= 132) && (chordindex < 144))
	{
		rootNote = chordindex - 132;
		quality = Dominant;
		intervals = 7;
		chord_num = 2196;
		chord_name = note_names[rootNote] + "6th";
	}

	// minor 6th 2324
	if ((chordindex >= 144) && (chordindex < 156))
	{
		rootNote = chordindex - 144;
		quality = Dominant;
		intervals = 7;
		chord_num = 2324;
		chord_name = note_names[rootNote] + "min6th";
	}

	// 9th 2706
	if ((chordindex >= 156) && (chordindex < 168))
	{
		rootNote = chordindex - 156;
		quality = Dominant;
		intervals = 7;
		chord_num = 2706;
		chord_name = note_names[rootNote] + "9th";
	}

	// min9th 2834
	if ((chordindex >= 168) && (chordindex < 180))
	{
		rootNote = chordindex - 168;
		quality = Dominant;
		intervals = 7;
		chord_num = 2834;
		chord_name = note_names[rootNote] + "min9th";
	}

	// maj9th 2705
	if ((chordindex >= 180) && (chordindex < 192))
	{
		rootNote = chordindex - 180;
		quality = Dominant;
		intervals = 7;
		chord_num = 2705;
		chord_name = note_names[rootNote] + "Maj9th";
	}

	// minmaj9th 2833
	if ((chordindex >= 192) && (chordindex < 204))
	{
		rootNote = chordindex - 192;
		quality = Dominant;
		intervals = 7;
		chord_num = 2833;
		chord_name = note_names[rootNote] + "minMaj9th";
	}

	// 11th 2770
	if ((chordindex >= 204) && (chordindex < 216))
	{
		rootNote = chordindex - 204;
		quality = Dominant;
		intervals = 7;
		chord_num = 2770;
		chord_name = note_names[rootNote] + "11th";
	}

	// min11th 2898
	if ((chordindex >= 216) && (chordindex < 228))
	{
		rootNote = chordindex - 216;
		quality = Dominant;
		intervals = 7;
		chord_num = 2898;
		chord_name = note_names[rootNote] + "min11th";
	}

	// Maj11th 2769
	if ((chordindex >= 228) && (chordindex < 240))
	{
		rootNote = chordindex - 228;
		quality = Dominant;
		intervals = 7;
		chord_num = 2769;
		chord_name = note_names[rootNote] + "Maj11th";
	}

	// minMaj11th 2897
	if ((chordindex >= 240) && (chordindex < 252))
	{
		rootNote = chordindex - 240;
		quality = Dominant;
		intervals = 7;
		chord_num = 2897;
		chord_name = note_names[rootNote] + "minMaj11th";
	}

	// 13th 2710
	if ((chordindex >= 252) && (chordindex < 264))
	{
		rootNote = chordindex - 252;
		quality = Dominant;
		intervals = 7;
		chord_num = 2710;
		chord_name = note_names[rootNote] + "13th";
	}

	// min13th 2838
	if ((chordindex >= 264) && (chordindex < 276))
	{
		rootNote = chordindex - 264;
		quality = Dominant;
		intervals = 7;
		chord_num = 2838;
		chord_name = note_names[rootNote] + "min13th";
	}

	// Maj13th 2709
	if ((chordindex >= 276) && (chordindex < 288))
	{
		rootNote = chordindex - 276;
		quality = Dominant;
		intervals = 7;
		chord_num = 2709;
		chord_name = note_names[rootNote] + "Maj13th";
	}

	// minMaj13th 2837
	if ((chordindex >= 288) && (chordindex < 300))
	{
		rootNote = chordindex - 288;
		quality = Dominant;
		intervals = 7;
		chord_num = 2837;
		chord_name = note_names[rootNote] + "minMaj13th";
	}

	// Add9 2837
	if ((chordindex >= 300) && (chordindex < 312))
	{
		rootNote = chordindex - 300;
		quality = Dominant;
		intervals = 7;
		chord_num = 2837;
		chord_name = note_names[rootNote] + "Add9";
	}

	// minAdd9 2832
	if ((chordindex >= 312) && (chordindex < 324))
	{
		rootNote = chordindex - 312;
		quality = Dominant;
		intervals = 7;
		chord_num = 2832;
		chord_name = note_names[rootNote] + "minAdd9";
	}

	// 6Add9 2708
	if ((chordindex >= 324) && (chordindex < 336))
	{
		rootNote = chordindex - 324;
		quality = Dominant;
		intervals = 7;
		chord_num = 2708;
		chord_name = note_names[rootNote] + "6Add9";
	}

	// min6Add9 2836
	if ((chordindex >= 336) && (chordindex < 348))
	{
		rootNote = chordindex - 336;
		quality = Dominant;
		intervals = 7;
		chord_num = 2836;
		chord_name = note_names[rootNote] + "min6Add9";
	}

	// dom7Add11 2258
	if ((chordindex >= 348) && (chordindex < 360))
	{
		rootNote = chordindex - 348;
		quality = Dominant;
		intervals = 7;
		chord_num = 2258;
		chord_name = note_names[rootNote] + "dom7Add11";
	}

	// Maj7Add11 2257
	if ((chordindex >= 360) && (chordindex < 372))
	{
		rootNote = chordindex - 360;
		quality = Dominant;
		intervals = 7;
		chord_num = 2257;
		chord_name = note_names[rootNote] + "_Maj7Add11";
	}

	// min7Add11 2386
	if ((chordindex >= 372) && (chordindex < 384))
	{
		rootNote = chordindex - 372;
		quality = Dominant;
		intervals = 7;
		chord_num = 2386;
		chord_name = note_names[rootNote] + "min7Add11";
	}

	// minMaj7Add11 2385
	if ((chordindex >= 384) && (chordindex < 396))
	{
		rootNote = chordindex - 384;
		quality = Dominant;
		intervals = 7;
		chord_num = 2385;
		chord_name = note_names[rootNote] + "minMaj7Add11";
	}

	// dom7Add13 2198
	if ((chordindex >= 396) && (chordindex < 408))
	{
		rootNote = chordindex - 396;
		quality = Dominant;
		intervals = 7;
		chord_num = 2198;
		chord_name = note_names[rootNote] + "dom7Add13";
	}

	// Maj7Add13 2197
	if ((chordindex >= 408) && (chordindex < 420))
	{
		rootNote = chordindex - 408;
		quality = Dominant;
		intervals = 7;
		chord_num = 2197;
		chord_name = note_names[rootNote] + "_Maj7Add13";
	}

	// min7Add13 2326
	if ((chordindex >= 420) && (chordindex < 432))
	{
		rootNote = chordindex - 420;
		quality = Dominant;
		intervals = 7;
		chord_num = 2326;
		chord_name = note_names[rootNote] + "min7Add13";
	}

	// minMaj7Add13 2325
	if ((chordindex >= 432) && (chordindex < 444))
	{
		rootNote = chordindex - 432;
		quality = Dominant;
		intervals = 7;
		chord_num = 2325;
		chord_name = note_names[rootNote] + "minMaj7Add13";
	}

	// 7b5 2210
	if ((chordindex >= 444) && (chordindex < 456))
	{
		rootNote = chordindex - 444;
		quality = Dominant;
		intervals = 7;
		chord_num = 2210;
		chord_name = note_names[rootNote] + "7b5";
	}

	// 7#5 2186
	if ((chordindex >= 456) && (chordindex < 468))
	{
		rootNote = chordindex - 446;
		quality = Dominant;
		intervals = 7;
		chord_num = 2186;
		chord_name = note_names[rootNote] + "7#5";
	}

	// 7b9 3218
	if ((chordindex >= 468) && (chordindex < 480))
	{
		rootNote = chordindex - 468;
		quality = Dominant;
		intervals = 7;
		chord_num = 3218;
		chord_name = note_names[rootNote] + "7b9";
	}

	// 7#9 2450
	if ((chordindex >= 480) && (chordindex < 492))
	{
		rootNote = chordindex - 480;
		quality = Dominant;
		intervals = 7;
		chord_num = 2450;
		chord_name = note_names[rootNote] + "7#9";
	}

	// 7#5b9 3210
	if ((chordindex >= 492) && (chordindex < 504))
	{
		rootNote = chordindex - 492;
		quality = Dominant;
		intervals = 7;
		chord_num = 3210;
		chord_name = note_names[rootNote] + "7#5b9";
	}

	// m7b5 2338
	if ((chordindex >= 504) && (chordindex < 516))
	{
		rootNote = chordindex - 504;
		quality = Dominant;
		intervals = 7;
		chord_num = 2338;
		chord_name = note_names[rootNote] + "m7b5";
	}

	// m7#5 2314
	if ((chordindex >= 516) && (chordindex < 528))
	{
		rootNote = chordindex - 516;
		quality = Dominant;
		intervals = 7;
		chord_num = 2314;
		chord_name = note_names[rootNote] + "m7#5";
	}

	// m7b9 3346
	if ((chordindex >= 528) && (chordindex < 540))
	{
		rootNote = chordindex - 528;
		quality = Dominant;
		intervals = 7;
		chord_num = 3346;
		chord_name = note_names[rootNote] + "m7b9";
	}

	// 9#11 2738
	if ((chordindex >= 540) && (chordindex < 552))
	{
		rootNote = chordindex - 540;
		quality = Dominant;
		intervals = 7;
		chord_num = 2738;
		chord_name = note_names[rootNote] + "9#11";
	}

	// 9b13 2714
	if ((chordindex >= 552) && (chordindex < 564))
	{
		rootNote = chordindex - 540;
		quality = Dominant;
		intervals = 7;
		chord_num = 2714;
		chord_name = note_names[rootNote] + "9b13";
	}

	// 6sus4 2132
	if ((chordindex >= 564) && (chordindex < 576))
	{
		rootNote = chordindex - 564;
		quality = Dominant;
		intervals = 7;
		chord_num = 2132;
		chord_name = note_names[rootNote] + "6sus4";
	}

	// 7sus4 2130
	if ((chordindex >= 576) && (chordindex < 588))
	{
		rootNote = chordindex - 576;
		quality = Dominant;
		intervals = 7;
		chord_num = 2130;
		chord_name = note_names[rootNote] + "7sus4";
	}

	// Maj7sus4 2129
	if ((chordindex >= 588) && (chordindex < 600))
	{
		rootNote = chordindex - 588;
		quality = Dominant;
		intervals = 7;
		chord_num = 2129;
		chord_name = note_names[rootNote] + "_Maj7sus4";
	}

	// 9sus4 2642
	if ((chordindex >= 600) && (chordindex < 612))
	{
		rootNote = chordindex - 600;
		quality = Dominant;
		intervals = 7;
		chord_num = 2642;
		chord_name = note_names[rootNote] + "9sus4";
	}

	// Maj9sus4 2641
	if ((chordindex >= 612) && (chordindex < 624))
	{
		rootNote = chordindex - 612;
		quality = Dominant;
		intervals = 7;
		chord_num = 2641;
		chord_name = note_names[rootNote] + "_Maj9sus4";
	}

	// Maj7b5 2209
	if ((chordindex >= 624) && (chordindex < 636))
	{
		rootNote = chordindex - 624;
		quality = Dominant;
		intervals = 7;
		chord_num = 2209;
		chord_name = note_names[rootNote] + "_Maj7b5";
	}

	// 7#9#11 2482
	if ((chordindex >= 636) && (chordindex < 648))
	{
		rootNote = chordindex - 636;
		quality = Dominant;
		intervals = 7;
		chord_num = 2482;
		chord_name = note_names[rootNote] + "7#9#11";
	}

	// 7#11 2226
	if ((chordindex >= 648) && (chordindex < 660))
	{
		rootNote = chordindex - 648;
		quality = Dominant;
		intervals = 7;
		chord_num = 2226;
		chord_name = note_names[rootNote] + "7#11";
	}

	// 7b9b13 3226
	if ((chordindex >= 660) && (chordindex < 672))
	{
		rootNote = chordindex - 660;
		quality = Dominant;
		intervals = 7;
		chord_num = 3226;
		chord_name = note_names[rootNote] + "7b9b13";
	}

	// 7b9/13 3222
	if ((chordindex >= 672) && (chordindex < 684))
	{
		rootNote = chordindex - 672;
		quality = Dominant;
		intervals = 7;
		chord_num = 3222;
		chord_name = note_names[rootNote] + "7b9/13";
	}

	// 7/sus2 2578
	if ((chordindex >= 684) && (chordindex < 696))
	{
		rootNote = chordindex - 684;
		quality = Dominant;
		intervals = 7;
		chord_num = 2578;
		chord_name = note_names[rootNote] + "7/sus2";
	}

	// dim7 2340
	if ((chordindex >= 696) && (chordindex < 708))
	{
		rootNote = chordindex - 696;
		quality = Dominant;
		intervals = 7;
		chord_num = 2340;
		chord_name = note_names[rootNote] + "dim7";
	}

	// flat5 2208
	if ((chordindex >= 708) && (chordindex < 720))
	{
		rootNote = chordindex - 708;
		quality = Dominant;
		intervals = 7;
		chord_num = 2208;
		chord_name = note_names[rootNote] + "flat5";
	}

	*/
}

//=======================================================================
double ChordDetector::calculateChordScore(double *chroma,double *chordProfile,double biasToUse, double N)
{
	double sum = 0;
	double delta;

	for (int i=0;i < 12;i++)
	{
		sum = sum + ((1-chordProfile[i])*(chroma[i]*chroma[i]));
	}

	delta = sqrt(sum) / ((12 - N)*biasToUse);
	
	return delta;
}

//=======================================================================
int ChordDetector::minimumIndex(double *array,int arrayLength)
{
	double minValue = 100000;
	int minIndex = 0;
	int i;
	
	for (i = 0;i < arrayLength;i++)
	{
		if (array[i] < minValue)
		{
			minValue = array[i];
			minIndex = i;
		}
	}
	
	return minIndex;
}

//=======================================================================
void ChordDetector::makeChordProfiles()
{
	int i;
	int t;
	int j = 0;
	int root;
	int third;
	int fifth;
	int seventh;
	int ninth;
	int eleventh;
	
	double v1 = 1;
	double v2 = 1;
	double v3 = 1;
	
	// set profiles matrix to all zeros
	for (j = 0;j < 108;j++)
	{
		for (t = 0;t < 12;t++)
		{
			chordProfiles[j][t] = 0;
		}
	}
	
	// reset j to zero to begin creating profiles
	j = 0;
	
	// major chords
	for (i = 0;i < 12;i++)
	{
		root = i % 12;
		third = (i+4) % 12;
		fifth = (i+7) % 12;
		
		chordProfiles[j][root] = v1;
		chordProfiles[j][third] = v2;
		chordProfiles[j][fifth] = v3;
		
		j++;				
	}

	// minor chords
	for (i = 0;i < 12;i++)
	{
		root = i % 12;
		third = (i+3) % 12;
		fifth = (i+7) % 12;
		
		chordProfiles[j][root] = v1;
		chordProfiles[j][third] = v2;
		chordProfiles[j][fifth] = v3;
		
		j++;				
	}

	// diminished chords
	for (i = 0;i < 12;i++)
	{
		root = i % 12;
		third = (i+3) % 12;
		fifth = (i+6) % 12;
		
		chordProfiles[j][root] = v1;
		chordProfiles[j][third] = v2;
		chordProfiles[j][fifth] = v3;
		
		j++;				
	}	
	
	// augmented chords 
	for (i = 0;i < 12;i++)
	{
		root = i % 12;
		third = (i+4) % 12;
		fifth = (i+8) % 12;
		
		chordProfiles[j][root] = v1;
		chordProfiles[j][third] = v2;
		chordProfiles[j][fifth] = v3;
		
		j++;				
	}	
	
	// sus2 chords 2576
	for (i = 0;i < 12;i++)
	{
		root = i % 12;
		third = (i+2) % 12;
		fifth = (i+7) % 12;
		
		chordProfiles[j][root] = v1;
		chordProfiles[j][third] = v2;
		chordProfiles[j][fifth] = v3;
		
		j++;				
	}
	
	// sus4 chords 2128
	for (i = 0;i < 12;i++)
	{
		root = i % 12;
		third = (i+5) % 12;
		fifth = (i+7) % 12;
		
		chordProfiles[j][root] = v1;
		chordProfiles[j][third] = v2;
		chordProfiles[j][fifth] = v3;
		
		j++;				
	}		
	
	// major 7th chords 2193
	for (i = 0;i < 12;i++)
	{
		root = i % 12;
		third = (i+4) % 12;
		fifth = (i+7) % 12;
		seventh = (i+11) % 12;
		
		chordProfiles[j][root] = v1;
		chordProfiles[j][third] = v2;
		chordProfiles[j][fifth] = v3;
		chordProfiles[j][seventh] = v3;
		
		j++;				
	}	
	
	// minor 7th chords 2322
	for (i = 0;i < 12;i++)
	{
		root = i % 12;
		third = (i+3) % 12;
		fifth = (i+7) % 12;
		seventh = (i+10) % 12;
		
		chordProfiles[j][root] = v1;
		chordProfiles[j][third] = v2;
		chordProfiles[j][fifth] = v3;
		chordProfiles[j][seventh] = v3;
		
		j++;				
	}

	/* for future development
	
	// 5th chords 2064
	for (i = 0;i < 12;i++)
	{
		root = i % 12;
		fifth = (i+7) % 12;
		
		chordProfiles[j][root] = v1;
		chordProfiles[j][fifth] = v3;
		
		j++;				
	}

	// 6th chords 2196
	for (i = 0; i < 12; i++)
	{
		root = i % 12;
		third = (i + 4) % 12;
		fifth = (i + 7) % 12;
		seventh = (i + 9) % 12;

		chordProfiles[j][root] = v1;
		chordProfiles[j][third] = v2;
		chordProfiles[j][fifth] = v3;
		chordProfiles[j][seventh] = v3;

		j++;
	}

	// minor 6th chords 2324
	for (i = 0; i < 12; i++)
	{
		root = i % 12;
		third = (i + 3) % 12;
		fifth = (i + 7) % 12;
		seventh = (i + 9) % 12;

		chordProfiles[j][root] = v1;
		chordProfiles[j][third] = v2;
		chordProfiles[j][fifth] = v3;
		chordProfiles[j][seventh] = v3;

		j++;
	}

	// 9th chords 2706
	for (i = 0; i < 12; i++)
	{
		root = i % 12;
		third = (i + 4) % 12;
		fifth = (i + 7) % 12;
		seventh = (i + 10) % 12;
		ninth = (i + 2) % 12;

		chordProfiles[j][root] = v1;
		chordProfiles[j][third] = v2;
		chordProfiles[j][fifth] = v3;
		chordProfiles[j][seventh] = v3;
		chordProfiles[j][ninth] = v3;


		j++;
	}

	// min9th chords 2834
	for (i = 0; i < 12; i++)
	{
		root = i % 12;
		ninth = (i + 2) % 12;
		third = (i + 3) % 12;
		fifth = (i + 7) % 12;
		seventh = (i + 10) % 12;

		chordProfiles[j][root] = v1;
		chordProfiles[j][third] = v2;
		chordProfiles[j][fifth] = v3;
		chordProfiles[j][seventh] = v3;
		chordProfiles[j][ninth] = v3;


		j++;
	}

	// maj9th chords 2705
	for (i = 0; i < 12; i++)
	{
		root = i % 12;
		ninth = (i + 2) % 12;
		third = (i + 4) % 12;
		fifth = (i + 7) % 12;
		seventh = (i + 11) % 12;

		chordProfiles[j][root] = v1;
		chordProfiles[j][third] = v2;
		chordProfiles[j][fifth] = v3;
		chordProfiles[j][seventh] = v3;
		chordProfiles[j][ninth] = v3;


		j++;
	}

	// minmaj9th chords 2833
	for (i = 0; i < 12; i++)
	{
		root = i % 12;
		ninth = (i + 2) % 12;
		third = (i + 3) % 12;
		fifth = (i + 7) % 12;
		seventh = (i + 11) % 12;

		chordProfiles[j][root] = v1;
		chordProfiles[j][third] = v2;
		chordProfiles[j][fifth] = v3;
		chordProfiles[j][seventh] = v3;
		chordProfiles[j][ninth] = v3;


		j++;
	}

	// 11th chords 2770
	for (i = 0; i < 12; i++)
	{
		root = i % 12;
		ninth = (i + 2) % 12;
		third = (i + 4) % 12;
		fifth = (i + 5) % 12;
		seventh = (i + 7) % 12;
		eleventh = (i + 10) % 12;

		chordProfiles[j][root] = v1;
		chordProfiles[j][third] = v2;
		chordProfiles[j][fifth] = v3;
		chordProfiles[j][seventh] = v3;
		chordProfiles[j][ninth] = v3;
		chordProfiles[j][eleventh] = v3;


		j++;
	}

	// min11th chords 2898
	for (i = 0; i < 12; i++)
	{
		root = i % 12;
		ninth = (i + 2) % 12;
		third = (i + 3) % 12;
		fifth = (i + 5) % 12;
		seventh = (i + 7) % 12;
		eleventh = (i + 10) % 12;

		chordProfiles[j][root] = v1;
		chordProfiles[j][third] = v2;
		chordProfiles[j][fifth] = v3;
		chordProfiles[j][seventh] = v3;
		chordProfiles[j][ninth] = v3;
		chordProfiles[j][eleventh] = v3;


		j++;
	}

	// Maj11th chords 2769
	for (i = 0; i < 12; i++)
	{
		root = i % 12;
		ninth = (i + 2) % 12;
		third = (i + 4) % 12;
		fifth = (i + 5) % 12;
		seventh = (i + 7) % 12;
		eleventh = (i + 11) % 12;

		chordProfiles[j][root] = v1;
		chordProfiles[j][third] = v2;
		chordProfiles[j][fifth] = v3;
		chordProfiles[j][seventh] = v3;
		chordProfiles[j][ninth] = v3;
		chordProfiles[j][eleventh] = v3;


		j++;
	}

	// minMaj11th chords 2897
	for (i = 0; i < 12; i++)
	{
		root = i % 12;
		ninth = (i + 2) % 12;
		third = (i + 3) % 12;
		fifth = (i + 5) % 12;
		seventh = (i + 7) % 12;
		eleventh = (i + 11) % 12;

		chordProfiles[j][root] = v1;
		chordProfiles[j][third] = v2;
		chordProfiles[j][fifth] = v3;
		chordProfiles[j][seventh] = v3;
		chordProfiles[j][ninth] = v3;
		chordProfiles[j][eleventh] = v3;

		j++;
	}

	// 13th chords 2710
	for (i = 0; i < 12; i++)
	{
		root = i % 12;
		ninth = (i + 2) % 12;
		third = (i + 4) % 12;
		fifth = (i + 7) % 12;
		seventh = (i + 9) % 12;
		eleventh = (i + 10) % 12;

		chordProfiles[j][root] = v1;
		chordProfiles[j][third] = v2;
		chordProfiles[j][fifth] = v3;
		chordProfiles[j][seventh] = v3;
		chordProfiles[j][ninth] = v3;
		chordProfiles[j][eleventh] = v3;

		j++;
	}

	// min13th chords 2838
	for (i = 0; i < 12; i++)
	{
		root = i % 12;
		ninth = (i + 2) % 12;
		third = (i + 3) % 12;
		fifth = (i + 7) % 12;
		seventh = (i + 9) % 12;
		eleventh = (i + 10) % 12;

		chordProfiles[j][root] = v1;
		chordProfiles[j][third] = v2;
		chordProfiles[j][fifth] = v3;
		chordProfiles[j][seventh] = v3;
		chordProfiles[j][ninth] = v3;
		chordProfiles[j][eleventh] = v3;

		j++;
	}

	// Maj13th chords 2709
	for (i = 0; i < 12; i++)
	{
		root = i % 12;
		ninth = (i + 2) % 12;
		third = (i + 4) % 12;
		fifth = (i + 7) % 12;
		seventh = (i + 9) % 12;
		eleventh = (i + 11) % 12;

		chordProfiles[j][root] = v1;
		chordProfiles[j][third] = v2;
		chordProfiles[j][fifth] = v3;
		chordProfiles[j][seventh] = v3;
		chordProfiles[j][ninth] = v3;
		chordProfiles[j][eleventh] = v3;

		j++;
	}

	// minMaj13th chords 2709
	for (i = 0; i < 12; i++)
	{
		root = i % 12;
		ninth = (i + 2) % 12;
		third = (i + 3) % 12;
		fifth = (i + 7) % 12;
		seventh = (i + 9) % 12;
		eleventh = (i + 11) % 12;

		chordProfiles[j][root] = v1;
		chordProfiles[j][third] = v2;
		chordProfiles[j][fifth] = v3;
		chordProfiles[j][seventh] = v3;
		chordProfiles[j][ninth] = v3;
		chordProfiles[j][eleventh] = v3;

		j++;
	}

	// add9 chords 2704
	for (i = 0; i < 12; i++)
	{
		root = i % 12;
		third = (i + 4) % 12;
		fifth = (i + 7) % 12;
		ninth = (i + 2) % 12;

		chordProfiles[j][root] = v1;
		chordProfiles[j][third] = v2;
		chordProfiles[j][fifth] = v3;
		chordProfiles[j][ninth] = v3;

		j++;
	}

	// minAdd9 chords 2832
	for (i = 0; i < 12; i++)
	{
		root = i % 12;
		third = (i + 3) % 12;
		fifth = (i + 7) % 12;
		ninth = (i + 2) % 12;

		chordProfiles[j][root] = v1;
		chordProfiles[j][third] = v2;
		chordProfiles[j][fifth] = v3;
		chordProfiles[j][ninth] = v3;

		j++;
	}

	// 6Add9 chords 2708
	for (i = 0; i < 12; i++)
	{
		root = i % 12;
		third = (i + 4) % 12;
		fifth = (i + 7) % 12;
		seventh = (i + 9) % 12;
		ninth = (i + 2) % 12;

		chordProfiles[j][root] = v1;
		chordProfiles[j][third] = v2;
		chordProfiles[j][fifth] = v3;
		chordProfiles[j][seventh] = v3;
		chordProfiles[j][ninth] = v3;

		j++;
	}

	// min6Add9 chords 2836
	for (i = 0; i < 12; i++)
	{
		root = i % 12;
		third = (i + 3) % 12;
		fifth = (i + 7) % 12;
		seventh = (i + 9) % 12;
		ninth = (i + 2) % 12;

		chordProfiles[j][root] = v1;
		chordProfiles[j][third] = v2;
		chordProfiles[j][fifth] = v3;
		chordProfiles[j][seventh] = v3;
		chordProfiles[j][ninth] = v3;

		j++;
	}

	// dom7Add11 chords 2258
	for (i = 0; i < 12; i++)
	{
		root = i % 12;
		third = (i + 4) % 12;
		fifth = (i + 5) % 12;
		seventh = (i + 7) % 12;
		ninth = (i + 10) % 12;

		chordProfiles[j][root] = v1;
		chordProfiles[j][third] = v2;
		chordProfiles[j][fifth] = v3;
		chordProfiles[j][seventh] = v3;
		chordProfiles[j][ninth] = v3;

		j++;
	}

	// Maj7Add11 chords 2257
	for (i = 0; i < 12; i++)
	{
		root = i % 12;
		third = (i + 4) % 12;
		fifth = (i + 5) % 12;
		seventh = (i + 7) % 12;
		ninth = (i + 11) % 12;

		chordProfiles[j][root] = v1;
		chordProfiles[j][third] = v2;
		chordProfiles[j][fifth] = v3;
		chordProfiles[j][seventh] = v3;
		chordProfiles[j][ninth] = v3;

		j++;
	}

	// min7Add11 chords 2386
	for (i = 0; i < 12; i++)
	{
		root = i % 12;
		third = (i + 3) % 12;
		fifth = (i + 5) % 12;
		seventh = (i + 7) % 12;
		ninth = (i + 10) % 12;

		chordProfiles[j][root] = v1;
		chordProfiles[j][third] = v2;
		chordProfiles[j][fifth] = v3;
		chordProfiles[j][seventh] = v3;
		chordProfiles[j][ninth] = v3;

		j++;
	}

	// minMaj7Add11 chords 2385
	for (i = 0; i < 12; i++)
	{
		root = i % 12;
		third = (i + 3) % 12;
		fifth = (i + 5) % 12;
		seventh = (i + 7) % 12;
		ninth = (i + 11) % 12;

		chordProfiles[j][root] = v1;
		chordProfiles[j][third] = v2;
		chordProfiles[j][fifth] = v3;
		chordProfiles[j][seventh] = v3;
		chordProfiles[j][ninth] = v3;

		j++;
	}

	// dom7Add13 chords 2198
	for (i = 0; i < 12; i++)
	{
		root = i % 12;
		third = (i + 4) % 12;
		fifth = (i + 7) % 12;
		seventh = (i + 9) % 12;
		ninth = (i + 10) % 12;

		chordProfiles[j][root] = v1;
		chordProfiles[j][third] = v2;
		chordProfiles[j][fifth] = v3;
		chordProfiles[j][seventh] = v3;
		chordProfiles[j][ninth] = v3;

		j++;
	}

	// Maj7Add13 chords 2197
	for (i = 0; i < 12; i++)
	{
		root = i % 12;
		third = (i + 4) % 12;
		fifth = (i + 7) % 12;
		seventh = (i + 9) % 12;
		ninth = (i + 11) % 12;

		chordProfiles[j][root] = v1;
		chordProfiles[j][third] = v2;
		chordProfiles[j][fifth] = v3;
		chordProfiles[j][seventh] = v3;
		chordProfiles[j][ninth] = v3;

		j++;
	}

	// min7Add13 chords 2326
	for (i = 0; i < 12; i++)
	{
		root = i % 12;
		third = (i + 3) % 12;
		fifth = (i + 7) % 12;
		seventh = (i + 9) % 12;
		ninth = (i + 10) % 12;

		chordProfiles[j][root] = v1;
		chordProfiles[j][third] = v2;
		chordProfiles[j][fifth] = v3;
		chordProfiles[j][seventh] = v3;
		chordProfiles[j][ninth] = v3;

		j++;
	}

	// minMaj7Add13 chords 2325
	for (i = 0; i < 12; i++)
	{
		root = i % 12;
		third = (i + 3) % 12;
		fifth = (i + 7) % 12;
		seventh = (i + 9) % 12;
		ninth = (i + 11) % 12;

		chordProfiles[j][root] = v1;
		chordProfiles[j][third] = v2;
		chordProfiles[j][fifth] = v3;
		chordProfiles[j][seventh] = v3;
		chordProfiles[j][ninth] = v3;

		j++;
	}

	// 7b5 chords 2210
	for (i = 0; i < 12; i++)
	{
		root = i % 12;
		third = (i + 4) % 12;
		fifth = (i + 6) % 12;
		seventh = (i + 10) % 12;
//		ninth = (i + 11) % 12;

		chordProfiles[j][root] = v1;
		chordProfiles[j][third] = v2;
		chordProfiles[j][fifth] = v3;
		chordProfiles[j][seventh] = v3;
//		chordProfiles[j][ninth] = v3;

		j++;
	}

	// 7#5 chords 2186
	for (i = 0; i < 12; i++)
	{
		root = i % 12;
		third = (i + 4) % 12;
		fifth = (i + 8) % 12;
		seventh = (i + 10) % 12;
		//		ninth = (i + 11) % 12;

		chordProfiles[j][root] = v1;
		chordProfiles[j][third] = v2;
		chordProfiles[j][fifth] = v3;
		chordProfiles[j][seventh] = v3;
		//		chordProfiles[j][ninth] = v3;

		j++;
	}

	// 7b9 chords 3218
	for (i = 0; i < 12; i++)
	{
		root = i % 12;
		third = (i + 1) % 12;
		fifth = (i + 4) % 12;
		seventh = (i + 7) % 12;
		ninth = (i + 10) % 12;

		chordProfiles[j][root] = v1;
		chordProfiles[j][third] = v2;
		chordProfiles[j][fifth] = v3;
		chordProfiles[j][seventh] = v3;
		chordProfiles[j][ninth] = v3;

		j++;
	}

	// 7#9 chords 2450
	for (i = 0; i < 12; i++)
	{
		root = i % 12;
		third = (i + 3) % 12;
		fifth = (i + 4) % 12;
		seventh = (i + 7) % 12;
		ninth = (i + 10) % 12;

		chordProfiles[j][root] = v1;
		chordProfiles[j][third] = v2;
		chordProfiles[j][fifth] = v3;
		chordProfiles[j][seventh] = v3;
		chordProfiles[j][ninth] = v3;

		j++;
	}

	// 7#5b9 chords 3210
	for (i = 0; i < 12; i++)
	{
		root = i % 12;
		third = (i + 1) % 12;
		fifth = (i + 4) % 12;
		seventh = (i + 8) % 12;
		ninth = (i + 10) % 12;

		chordProfiles[j][root] = v1;
		chordProfiles[j][third] = v2;
		chordProfiles[j][fifth] = v3;
		chordProfiles[j][seventh] = v3;
		chordProfiles[j][ninth] = v3;

		j++;
	}

	// m7b5 chords 2338
	for (i = 0; i < 12; i++)
	{
		root = i % 12;
		third = (i + 3) % 12;
		fifth = (i + 6) % 12;
		seventh = (i + 10) % 12;
		//ninth = (i + 10) % 12;

		chordProfiles[j][root] = v1;
		chordProfiles[j][third] = v2;
		chordProfiles[j][fifth] = v3;
		chordProfiles[j][seventh] = v3;
		//chordProfiles[j][ninth] = v3;

		j++;
	}

	// m7b5 chords 2314
	for (i = 0; i < 12; i++)
	{
		root = i % 12;
		third = (i + 3) % 12;
		fifth = (i + 8) % 12;
		seventh = (i + 10) % 12;
		//ninth = (i + 10) % 12;

		chordProfiles[j][root] = v1;
		chordProfiles[j][third] = v2;
		chordProfiles[j][fifth] = v3;
		chordProfiles[j][seventh] = v3;
		//chordProfiles[j][ninth] = v3;

		j++;
	}

	// m7b9 chords 3346
	for (i = 0; i < 12; i++)
	{
		root = i % 12;
		third = (i + 1) % 12;
		fifth = (i + 3) % 12;
		seventh = (i + 7) % 12;
		ninth = (i + 10) % 12;

		chordProfiles[j][root] = v1;
		chordProfiles[j][third] = v2;
		chordProfiles[j][fifth] = v3;
		chordProfiles[j][seventh] = v3;
		chordProfiles[j][ninth] = v3;

		j++;
	}

	// 9#11 chords 2738
	for (i = 0; i < 12; i++)
	{
		root = i % 12;
		third = (i + 2) % 12;
		fifth = (i + 4) % 12;
		seventh = (i + 6) % 12;
		ninth = (i + 7) % 12;
		eleventh = (i + 10) % 12;

		chordProfiles[j][root] = v1;
		chordProfiles[j][third] = v2;
		chordProfiles[j][fifth] = v3;
		chordProfiles[j][seventh] = v3;
		chordProfiles[j][ninth] = v3;
		chordProfiles[j][eleventh] = v3;

		j++;
	}

	// 9b13 chords 2714
	for (i = 0; i < 12; i++)
	{
		root = i % 12;
		third = (i + 2) % 12;
		fifth = (i + 4) % 12;
		seventh = (i + 7) % 12;
		ninth = (i + 8) % 12;
		eleventh = (i + 10) % 12;

		chordProfiles[j][root] = v1;
		chordProfiles[j][third] = v2;
		chordProfiles[j][fifth] = v3;
		chordProfiles[j][seventh] = v3;
		chordProfiles[j][ninth] = v3;
		chordProfiles[j][eleventh] = v3;

		j++;
	}

	// 6sus4 chords 2132
	for (i = 0; i < 12; i++)
	{
		root = i % 12;
		third = (i + 5) % 12;
		fifth = (i + 7) % 12;
		seventh = (i + 9) % 12;
		//ninth = (i + 8) % 12;
		//eleventh = (i + 10) % 12;

		chordProfiles[j][root] = v1;
		chordProfiles[j][third] = v2;
		chordProfiles[j][fifth] = v3;
		chordProfiles[j][seventh] = v3;
		//chordProfiles[j][ninth] = v3;
		//chordProfiles[j][eleventh] = v3;

		j++;
	}

	// 7sus4 chords 2130
	for (i = 0; i < 12; i++)
	{
		root = i % 12;
		third = (i + 5) % 12;
		fifth = (i + 7) % 12;
		seventh = (i + 10) % 12;
		//ninth = (i + 8) % 12;
		//eleventh = (i + 10) % 12;

		chordProfiles[j][root] = v1;
		chordProfiles[j][third] = v2;
		chordProfiles[j][fifth] = v3;
		chordProfiles[j][seventh] = v3;
		//chordProfiles[j][ninth] = v3;
		//chordProfiles[j][eleventh] = v3;

		j++;
	}

	// Maj7sus4 chords 2129
	for (i = 0; i < 12; i++)
	{
		root = i % 12;
		third = (i + 5) % 12;
		fifth = (i + 7) % 12;
		seventh = (i + 11) % 12;
		//ninth = (i + 8) % 12;
		//eleventh = (i + 10) % 12;

		chordProfiles[j][root] = v1;
		chordProfiles[j][third] = v2;
		chordProfiles[j][fifth] = v3;
		chordProfiles[j][seventh] = v3;
		//chordProfiles[j][ninth] = v3;
		//chordProfiles[j][eleventh] = v3;

		j++;
	}

	// 9sus4 chords 2642
	for (i = 0; i < 12; i++)
	{
		root = i % 12;
		third = (i + 2) % 12;
		fifth = (i + 5) % 12;
		seventh = (i + 7) % 12;
		ninth = (i + 10) % 12;
		//eleventh = (i + 10) % 12;

		chordProfiles[j][root] = v1;
		chordProfiles[j][third] = v2;
		chordProfiles[j][fifth] = v3;
		chordProfiles[j][seventh] = v3;
		chordProfiles[j][ninth] = v3;
		//chordProfiles[j][eleventh] = v3;

		j++;
	}

	// Maj9sus4 chords 2641
	for (i = 0; i < 12; i++)
	{
		root = i % 12;
		third = (i + 2) % 12;
		fifth = (i + 5) % 12;
		seventh = (i + 7) % 12;
		ninth = (i + 11) % 12;
		//eleventh = (i + 10) % 12;

		chordProfiles[j][root] = v1;
		chordProfiles[j][third] = v2;
		chordProfiles[j][fifth] = v3;
		chordProfiles[j][seventh] = v3;
		chordProfiles[j][ninth] = v3;
		//chordProfiles[j][eleventh] = v3;

		j++;
	}

	// Maj7b5 chords 2209
	for (i = 0; i < 12; i++)
	{
		root = i % 12;
		third = (i + 4) % 12;
		fifth = (i + 6) % 12;
		seventh = (i + 11) % 12;
		//ninth = (i + 11) % 12;
		//eleventh = (i + 10) % 12;

		chordProfiles[j][root] = v1;
		chordProfiles[j][third] = v2;
		chordProfiles[j][fifth] = v3;
		chordProfiles[j][seventh] = v3;
		//chordProfiles[j][ninth] = v3;
		//chordProfiles[j][eleventh] = v3;

		j++;
	}

	// 7#9#11 chords 2482
	for (i = 0; i < 12; i++)
	{
		root = i % 12;
		third = (i + 3) % 12;
		fifth = (i + 4) % 12;
		seventh = (i + 6) % 12;
		ninth = (i + 7) % 12;
		eleventh = (i + 10) % 12;

		chordProfiles[j][root] = v1;
		chordProfiles[j][third] = v2;
		chordProfiles[j][fifth] = v3;
		chordProfiles[j][seventh] = v3;
		chordProfiles[j][ninth] = v3;
		chordProfiles[j][eleventh] = v3;

		j++;
	}

	// 7#11 chords 2226
	for (i = 0; i < 12; i++)
	{
		root = i % 12;
		third = (i + 4) % 12;
		fifth = (i + 6) % 12;
		seventh = (i + 7) % 12;
		ninth = (i + 10) % 12;
		//eleventh = (i + 10) % 12;

		chordProfiles[j][root] = v1;
		chordProfiles[j][third] = v2;
		chordProfiles[j][fifth] = v3;
		chordProfiles[j][seventh] = v3;
		chordProfiles[j][ninth] = v3;
		//chordProfiles[j][eleventh] = v3;

		j++;
	}

	// 7b9b13 chords 3226
	for (i = 0; i < 12; i++)
	{
		root = i % 12;
		third = (i + 1) % 12;
		fifth = (i + 4) % 12;
		seventh = (i + 7) % 12;
		ninth = (i + 8) % 12;
		eleventh = (i + 10) % 12;

		chordProfiles[j][root] = v1;
		chordProfiles[j][third] = v2;
		chordProfiles[j][fifth] = v3;
		chordProfiles[j][seventh] = v3;
		chordProfiles[j][ninth] = v3;
		chordProfiles[j][eleventh] = v3;

		j++;
	}

	// 7b9/13 chords 3222
	for (i = 0; i < 12; i++)
	{
		root = i % 12;
		third = (i + 1) % 12;
		fifth = (i + 4) % 12;
		seventh = (i + 7) % 12;
		ninth = (i + 9) % 12;
		eleventh = (i + 10) % 12;

		chordProfiles[j][root] = v1;
		chordProfiles[j][third] = v2;
		chordProfiles[j][fifth] = v3;
		chordProfiles[j][seventh] = v3;
		chordProfiles[j][ninth] = v3;
		chordProfiles[j][eleventh] = v3;

		j++;
	}

	// 7/sus2 chords 2578
	for (i = 0; i < 12; i++)
	{
		root = i % 12;
		third = (i + 2) % 12;
		fifth = (i + 7) % 12;
		seventh = (i + 10) % 12;
		//ninth = (i + 9) % 12;
		//eleventh = (i + 10) % 12;

		chordProfiles[j][root] = v1;
		chordProfiles[j][third] = v2;
		chordProfiles[j][fifth] = v3;
		chordProfiles[j][seventh] = v3;
		//chordProfiles[j][ninth] = v3;
		//chordProfiles[j][eleventh] = v3;

		j++;
	}

	// dim7 chords 2340
	for (i = 0; i < 12; i++)
	{
		root = i % 12;
		third = (i + 3) % 12;
		fifth = (i + 6) % 12;
		seventh = (i + 9) % 12;
		//ninth = (i + 9) % 12;
		//eleventh = (i + 10) % 12;

		chordProfiles[j][root] = v1;
		chordProfiles[j][third] = v2;
		chordProfiles[j][fifth] = v3;
		chordProfiles[j][seventh] = v3;
		//chordProfiles[j][ninth] = v3;
		//chordProfiles[j][eleventh] = v3;

		j++;
	}
	// flat5 chords 2208
	for (i = 0; i < 12; i++)
	{
		root = i % 12;
		third = (i + 4) % 12;
		fifth = (i + 6) % 12;
		//seventh = (i + 9) % 12;
		//ninth = (i + 9) % 12;
		//eleventh = (i + 10) % 12;

		chordProfiles[j][root] = v1;
		chordProfiles[j][third] = v2;
		chordProfiles[j][fifth] = v3;
		//chordProfiles[j][seventh] = v3;
		//chordProfiles[j][ninth] = v3;
		//chordProfiles[j][eleventh] = v3;

		j++;
	}

	*/
}