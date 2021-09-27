#include "./src/MidiFile.h"
#include "./src/Options.h"
#include <iostream>

using namespace std;
using namespace smf;

int main(int argc, char** argv) {

int noteMatrix[8][2] = {
    {60, 70},
    {61, 71},
    {62, 72},
    {64, 74},
    {65, 75},
    {66, 76},
    {67, 77},
    {68, 78}      
};

struct midiConv{
    int noteBefore;
    int noteAfter;
    string instrument;
    string pluginBefore;
    string pluginAfter;
};

midiConv midiConvArray[8] =
{
    {60,70,"KICK","SSD5","GGD4"},
    {62,72,"SNARE","SSD5","GGD4"},
    {64,74,"TOM_LO","SSD5","GGD4"},
    {65,75,"TOM_HI","SSD5","GGD4"},
    {66,76,"HIHAT","SSD5","GGD4"},
    {67,77,"CRASH_LE","SSD5","GGD4"},
    {68,78,"CRASH_RI","SSD5","GGD4"},
    {69,79,"RIDE","SSD5","GGD4"}
};

cout << sizeof(midiConvArray)/sizeof(midiConvArray[0]) << endl;

// not used atm
int midiConvArraySize = sizeof(midiConvArray)/sizeof(midiConvArray[0]);

int noteMatrixSize = sizeof(noteMatrix)/sizeof(noteMatrix[0]);


for (int c = 0; c < noteMatrixSize; c++)
{
    cout << noteMatrix[c][0] << endl;
}

cout << "------------------------------" << endl;


Options options;
options.define("t|transpose=i:10", "Semitones to transpose by");
options.process(argc, argv);

MidiFile midifile;
if (options.getArgCount() == 0) midifile.read(cin);
else midifile.read(options.getArg(1));
if (!midifile.status()) {
    cerr << "Could not read MIDI file" << endl;
    return 1;
}

//int transpose = options.getInteger("transpose");
int transpose = 5;

for (int i=0; i<midifile.getTrackCount(); i++) {
    for (int j=0; j<midifile[i].getEventCount(); j++) {
        if (!midifile[i][j].isNote()) continue;
        if (midifile[i][j].getChannel() == 9) continue;
        for (int c = 0; c < noteMatrixSize; c++)
        {
            cout << midifile[i][j].getP1() << endl;
            cout << noteMatrix[c][0] << endl;
            //cout << noteMatrix[c][0] << endl;
            if (midifile[i][j].getP1() == noteMatrix[c][0]){
                midifile[i][j].setP1(noteMatrix[c][1]);
                cout << "match" << endl;
                break;
                //cout << "match - old: " + noteMatrix[c][0] << "new: " + noteMatrix[c][1] << endl;
            }

        }
        cout << "out of loop" << endl;
        /*if (midifile[i][j].getP1() == 60){
            cout << "60 gefunden!" << endl;
            midifile[i][j].setP1(noteMatrix[0][1]);
            cout << "70 geschrieben!" << endl;
        }
        int newkey = transpose + midifile[i][j].getP1();
        midifile[i][j].setP1(newkey);*/





    }
}

if (options.getArgCount() < 2) cout << midifile;
else midifile.write(options.getArg(2));
return 0;
}