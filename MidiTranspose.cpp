#include "./src/MidiFile.h"
#include "./src/Options.h"
#include <iostream>
#include <list>
#include <algorithm>
#include <vector>

using namespace std;
using namespace smf;

int main(int argc, char** argv)
{

    //std::cout << argv[1] << std::endl;

    bool logConvert = true;
    std::list<int> missedNotes;

    std::vector<int> v;

    struct midiConv{
        int noteBefore;
        int noteAfter;
        string instrument;
        string pluginBefore;
        string pluginAfter;
    };

    midiConv midiConvArray[20] =
    {
        {36,24,"KICK","SSD5","GGD4"},
        {38,26,"SNARE","SSD5","GGD4"},
        {46,26,"TOM_LO","SSD5","GGD4"},
        {57,56,"TOM_HI","SSD5","GGD4"},
        {55,54,"HIHAT","SSD5","GGD4"},
        {42,23,"CRASH_LE","SSD5","GGD4"},
        {48,41,"CRASH_RI","SSD5","GGD4"},
        {50,28,"RIDE","SSD5","GGD4"},
        {43,41,"RIDE","SSD5","GGD4"},
        {24,24,"KICK","SSD5","GGD4"},
        {26,26,"SNARE","SSD5","GGD4"},
        {60,43,"HH_CL_2","SSD5","GGD4"},
        {66,42,"HH_CL_1","SSD5","GGD4"},
        {51,61,"RIDE","SSD5","GGD4"},
        {54,42,"HH_CL_1","SSD5","GGD4"},
        {56,61,"RIDE","SSD5","GGD4"},
        {40,47,"RIDE","SSD5","GGD4"},
        {65,56,"RIDE","SSD5","GGD4"},
        {59,54,"RIDE","SSD5","GGD4"},
        {47,47,"RIDE","SSD5","GGD4"}


    };

    //cout << sizeof(midiConvArray)/sizeof(midiConvArray[0]) << endl;

    int midiConvArraySize = sizeof(midiConvArray)/sizeof(midiConvArray[0]);

    /*
    for (int c = 0; c < midiConvArraySize; c++)
    {
        cout << midiConvArray[c].noteAfter << endl;
    }*/



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
    //int transpose = 5;

    bool foundMatch = false;

    for (int i=0; i<midifile.getTrackCount(); i++) {
        for (int j=0; j<midifile[i].getEventCount(); j++)
        {
            if (!midifile[i][j].isNote()) continue;
            if (midifile[i][j].getChannel() == 9) continue;

            // loop matrix to find notes
            for (int c = 0; c < midiConvArraySize; c++)
            {
                foundMatch = false;

                if (logConvert == false)
                {
                    cout << midifile[i][j].getP1() << endl;
                    cout << midiConvArray[c].noteBefore << endl;
                }

                if (midifile[i][j].getP1() == midiConvArray[c].noteBefore /*| midiConvArray[c].noteBefore == midiConvArray[c].noteAfter*/)
                {
                    foundMatch = true;
                    midifile[i][j].setP1(midiConvArray[c].noteAfter);
                    if (logConvert == false)
                        cout << "match" << endl;
                    break;
                    //cout << "match - old: " + noteMatrix[c][0] << "new: " + noteMatrix[c][1] << endl;
                }
            }
            // note not found in matrix -> add notes to matrix
            if (/*logConvert == false &&*/ foundMatch == false){
                //cout << "out of loop: " << midifile[i][j].getP1() << endl;
                //missedNotes.push_back(midifile[i][j].getP1());

                // write first value to vector
                if (v.empty())
                {
                    v.push_back(midifile[i][j].getP1());
                    //cout << "add first item" << endl;
                }
                // check if vector contains value
                else
                {
                    bool addMissedNote = true;
                    for (int k = 0; k < (int)v.size(); k++)
                    {
                        if (v.at(k) == midifile[i][j].getP1())
                        {
                            addMissedNote = false;
                            break;
                        }
                    }
                    if (addMissedNote == true)
                    {
                        v.push_back(midifile[i][j].getP1());
                    }
                }
            }

        }
        if (logConvert == true){

            if (v.size() > 0){
                cout << "Missing notes! :-(" << endl;
                cout << "add those notes to matrix: " << endl;
                std::sort(std::begin(v), std::end(v));
                for (int n : v){
                    cout << "{" << n << "," << n << ",Instrument," << midiConvArray[0].pluginBefore << "," << midiConvArray[0].pluginAfter << "},"<< endl;
                }
            }
            else
            {
                cout << "Success!" << endl;
            }
        }
    }

    if (options.getArgCount() < 2)
    {
        cout << midifile;
    }
    else
    {

        string newFileName = options.getArg(1);

    //    newFileName.replace(".mid", "_Con_" + midiConvArray[0].pluginBefore + "To" + midiConvArray[0].pluginAfter + ".mid");
        newFileName.replace(newFileName.size() - 4,4, "_Con_" + midiConvArray[0].pluginBefore + "To" + midiConvArray[0].pluginAfter + ".mid");

        cout << "New file created: " + newFileName << endl;

        midifile.write(newFileName);

        //cout << options.getArg(2) << endl;
        //midifile.write(options.getArg(2));

    }
    return 0;
}
