#include "./src/MidiFile.h"
#include "./src/Options.h"
#include "./src/Binasc.h"
#include "./src/MidiEvent.h"
#include "./src/MidiEventList.h"
#include "./src/MidiMessage.h"


//#include <Options>
#include <iostream>
#include <iomanip>
#include <string>

using namespace std;
using namespace smf;

int main(int argc, char** argv) {

   cout << "----Start program here----" << endl;

   int noteMatrix[4][2] = {
      {60, 70},
      {61, 71},
      {62, 72},
      {63, 73}      
   };

   cout << noteMatrix[2][1] << endl;




   Options options;
   options.process(argc, argv);

   MidiFile midifile;

   if (options.getArgCount() == 0) midifile.read(cin);
   else midifile.read(options.getArg(1));

   midifile.doTimeAnalysis();
   midifile.linkNotePairs();

   int tracks = midifile.getTrackCount();

   cout << "TPQ: " << midifile.getTicksPerQuarterNote() << endl;

   if (tracks > 1) cout << "TRACKS: " << tracks << endl;

   for (int track=0; track<tracks; track++) 
   {
      if (tracks > 1) cout << "\nTrack " << track << endl;

      cout << "Tick\tSeconds\tDur\tMessage" << endl;

      for (int event=0; event<midifile[track].size(); event++) 
      {
         cout << dec << midifile[track][event].tick;
         cout << '\t' << dec << midifile[track][event].seconds;
         cout << '\t';

         if (midifile[track][event].isNoteOn())
            cout << midifile[track][event].getDurationInSeconds();

         cout << '\t' << hex;

         


         // Midi Message in hex
         for (int i=0; i<midifile[track][event].size(); i++)
            cout << (int)midifile[track][event][i] << ' ';

            //cout << midifile[track][event][];

            cout << "    "+ (int)midifile[track][event].getP1();

         cout << endl;
      }
   }

   return 0;
}


void printLine(){
   cout << "-----------------------------" << endl;

}