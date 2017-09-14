#include "maxcpp6.h"

#ifdef __APPLE__
#include "Chord-Detector-and-Chromagram-master/src/ChordDetector.h"
#include "Chord-Detector-and-Chromagram-master/src/Chromagram.h"
#else
#include ".\Chord-Detector-and-Chromagram-master\src\ChordDetector.h"
#include ".\Chord-Detector-and-Chromagram-master\src\Chromagram.h"
#endif

/*
 chordid~
 
 Simon Blakely - si.blakely@googlemail.com
 
 This external implements the Chromagram/ChordDetector by Adam Stark.
 (https://github.com/adamstark/Chord-Detector-and-Chromagram)
 
 I have extensively modified the ChordDetector code to change the classification
 scheme, and have extended the range of detectable chords. This may create
 errors of classification - please let me know if you find any.
 
 My thanks also to Fabrizio Poce (J74 Harmotools), who reviewed my initial
 VST implemention. This external is much better, I think. I'm glad I came back to it.
 http://fabriziopoce.com/HarmoTools.html
 
 I have also used the maxmpp C++ template as the basis of this external.
 https://github.com/grrrwaaa/maxcpp
 My thanks to Graham Wakefield for this template - it made my introduction to
 Max/MSP external programming much easier.
 
 Any issues with the code are mine: please contact me if you have queries
 or suggestions for improvement.
 
 * This program is free software : you can redistribute it and / or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 *but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.If not, see <http://www.gnu.org/licenses/>.
 */

class Chromagram;
class ChordDetector;

// inherit from the MSP base class, template-specialized for myself:

class Chordid : public MspCpp6<Chordid> {
    
public:
    
    int frameSize = 512;
    int sampleRate = 44100;
    int currentchord = 0;
    int lastchord = 0;
    
    void **	m_outlets;
    int numoutlets = 4; // specified outlets
    double rms_cutoff = 0.0025; // initial rms cutoff value
    std::string chord_name = "";
    
    std::vector<double> frame;
    // double frame[512];
    ChordDetector chordspotter;
    Chromagram c;
    
    int currentsamples = 0;
    
    Chordid(t_symbol * sym, long ac, t_atom * av)
    : c(frameSize, sampleRate), chordspotter()
    {
        c.setChromaCalculationInterval(512);
        frame.resize(frameSize);
        m_outlets = (void **)sysmem_newptr(sizeof(void *) * numoutlets);
        for (unsigned int i = 0; i < numoutlets; i++){
            m_outlets[numoutlets - i - 1] = outlet_new(this, NULL); // generic outlet
        }
        setupIO(1, 1);
        // post("object created");
    }
    
    ~Chordid() {
        // post("object freed");
    }
    
    // methods:
    void bang(long inlet) {
        int this_root;
        int this_num;
        
        this_root = int(currentchord / 10000);
        this_num = currentchord - (10000 * this_root);
        const char *this_chordname = chord_name.c_str();
        outlet_anything(m_outlets[0], gensym(this_chordname), 0, NULL);
        outlet_int(m_outlets[1], currentchord);
        midilist(this_root, this_num);
        
    }
    void rate(long inlet, t_symbol * s, long ac, t_atom * av) {
        t_atom * this_atom;
        long this_number;
        
        this_atom = &av[0];
        this_number = atom_getlong(this_atom);
        if (this_number > 0) {
            int new_rate = this_number * 512;
            c.setChromaCalculationInterval(512 * this_number);
        }
    }
    void rms(long inlet, t_symbol * s, long ac, t_atom * av) {
        // set the rms cutoff value (float)
        t_atom * this_atom;
        float this_number;
        
        this_atom = &av[0];
        this_number = atom_getfloat(this_atom);
        if (this_number > 0.00001){
            rms_cutoff = this_number;
        }
    }
    void assist(void *b, long m, long a, char *s) {
        if (m == ASSIST_INLET) { //inlet
            switch (a) {
                case 0: sprintf(s, "\nrate <int> - set the number of 512 sample frames to allow prior to chord identification\nrms <float> - set the rms cutoff value");
                    break;
            }
        }
        else {	// outlet
            switch (a) {
                case 0 : sprintf(s, "signal out");
                    break;
                case 1: sprintf(s, "text Chordname");
                    break;
                case 2: sprintf(s, "int chord id");
                    break;
                case 3: sprintf(s, "list midi notes of chord");
                    break;
                case 4: sprintf(s, "signal - 0 for no recognisable signal, 1 otherwise");
                    break;
            }
        }
    }
    
    void midilist(int base_note, int chord_type) {
        int root;
        int index;
        int notes;
        t_atom list_out[12];
        int note_count = 0;
        
        root = 60 + base_note;
        notes = chord_type;
        for (index = 0; index < 12; index++){
            notes *= 2;
            if (notes > 4095) {
                atom_setlong(&list_out[note_count], t_atom_long (root + index));
                notes = notes - 4096;
                note_count++;
            }
        }
        outlet_anything(m_outlets[2], gensym("midi_notes"), note_count, &list_out[0]);
    }
    
    // default signal processing method is called 'perform'
    void perform(double **ins, long numins, double **outs, long numouts, long sampleframes) {
        //
        char *this_chordname;
        std::vector<double> chroma;
        chroma.resize(12);
        double rms, rms_tot;
        int q;
        rms = 0;
        rms_tot = 0;
        for (long channel = 0; channel < numouts; channel++) {
            double * in = ins[channel];
            double * out = outs[channel];
            for (long i=0; i < sampleframes; i++) {
                out[i] = in[i];
                // we only want to process on channel 0
                if (channel == 0) {
                    if (currentsamples < frameSize - 1) {
                        frame[currentsamples] = in[i];
                        currentsamples++;
                    }
                    else {
                        currentsamples = 0;
                        for (q = 0; q < frameSize; q++) {
                            rms_tot += pow(frame[q],2);
                        }
                        rms = rms_tot / frameSize;
                        if (rms > rms_cutoff){
                            c.processAudioFrame(frame);
                            outlet_int(m_outlets[3], 1);
                        }
                        else {
                            outlet_int(m_outlets[3], 0);
                        }
                        if (c.isReady()) {
                            std::vector<double> chroma = c.getChromagram();
                            chordspotter.detectChord(chroma);
                            currentchord = 10000 * chordspotter.rootNote + chordspotter.chord_num;
                            chord_name = chordspotter.chord_name;
                            const char *this_chordname = chord_name.c_str();
                            if (currentchord != lastchord) {
                                outlet_anything(m_outlets[0], gensym(this_chordname), 0, NULL);
                                outlet_int(m_outlets[1], currentchord);
                                midilist(chordspotter.rootNote, chordspotter.chord_num);
                            }
                            lastchord = currentchord;
                        }
                    }
                }
                
            }
        }
    }
    
    //	// optional method: gets called when the dsp chain is modified
    //	// if not given, the MspCpp will use Chordid::perform by default
    //	void dsp(t_object * dsp64, short *count, double samplerate, long maxvectorsize, long flags) { 
    //		// specify a perform method manually:
    //		REGISTER_PERFORM(Chordid, perform);
    //	}
    
};

C74_EXPORT int main(void) {
    // create a class with the given name:
    Chordid::makeMaxClass("chordid~");
    REGISTER_METHOD(Chordid, bang);
    REGISTER_METHOD_GIMME(Chordid, rate);
    REGISTER_METHOD_GIMME(Chordid, rms);
    REGISTER_METHOD_ASSIST(Chordid, assist);
}
