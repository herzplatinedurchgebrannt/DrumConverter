#include "./src/MidiFile.h"
#include "./src/Options.h"
#include <iostream>

using namespace std;
using namespace smf;

int main(int argc, char** argv) {

   int noteMatrix[9][2] = {
      {36,24},
      {38,26},
      {46,26},
      {57,56},
      {55,54},
      {42,23},
      {48,41},
      {50,38},
      {43,41}    
   };

struct midiConv{
    int noteBefore;
    int noteAfter;
    string instrument;
    string pluginBefore;
    string pluginAfter;
};

midiConv midiConvArray[9] =
{
    {36,24,"KICK","SSD5","GGD4"},
    {38,26,"SNARE","SSD5","GGD4"},
    {46,26,"TOM_LO","SSD5","GGD4"},
    {57,56,"TOM_HI","SSD5","GGD4"},
    {55,54,"HIHAT","SSD5","GGD4"},
    {42,23,"CRASH_LE","SSD5","GGD4"},
    {48,41,"CRASH_RI","SSD5","GGD4"},
    {50,28,"RIDE","SSD5","GGD4"},
    {43,41,"RIDE","SSD5","GGD4"}
};

std::cout << midiConvArray[1].noteAfter << std::endl;

int daa = midiConvArray[1].noteAfter;


cout << sizeof(midiConvArray)/sizeof(midiConvArray[0]) << endl;

// not used atm
int midiConvArraySize = sizeof(midiConvArray)/sizeof(midiConvArray[0]);

int noteMatrixSize = sizeof(noteMatrix)/sizeof(noteMatrix[0]);

// -------- PLAYGROUND //
for (int c = 0; c < midiConvArraySize; c++)
{
    cout << midiConvArray[c].noteAfter << endl;
}

//return 0;


// END OF PLAYGROUND


/*
for (int c = 0; c < noteMatrixSize; c++)
{
    cout << noteMatrix[c][0] << endl;
}

cout << "------------------------------" << endl;*/


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
        for (int c = 0; c < midiConvArraySize; c++)
        {
            cout << midifile[i][j].getP1() << endl;
            cout << midiConvArray[c].noteBefore << endl;
            //cout << noteMatrix[c][0] << endl;
            if (midifile[i][j].getP1() == midiConvArray[c].noteBefore){
                midifile[i][j].setP1(midiConvArray[c].noteAfter);
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