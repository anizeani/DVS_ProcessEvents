#include <iostream>
#include "Event.h"
#include <vector>
#include <fstream>
#include <sstream>
#include "utils.h"

#include <unistd.h>
#define GetCurrentDir getcwd

#include <iterator>
#include <algorithm>
#include <sqltypes.h>
#include <future>

// This is a C++ implementation of code written by Tobi Delbruck in Java for jAER

using namespace std;

std::vector<Event> read_from_txt_to_EventBuffer() {

/*  //To write into an output File
    std::ofstream myfile;
    myfile.open ("outputFileWithCommas.txt");
*/

    ifstream fileIn("/home/msc20h13/CLionProjects/untitled/events.txt");

    vector<Event> EventBuffer;

    vector<string> vecOfStrs;
    string str;

    // cout << get_current_dir() << endl; //get current directory to check where files are stored

    int i = 0;
    while (getline(fileIn, str))
    {
        if (str.size() > 0)
        { //If there is any string at all do...

            // replace spaces with commas between elements
            /*replace(str.begin(),str.end(),' ',',');
            vecOfStrs.push_back(str);*/

            // if I want to add curly braces and commas between lines
            /*str.insert(0,"{");
            str.insert(str.end(),'}');
            str.insert(str.end(),',');*/

            if(EventBuffer.size() < 1000)
            {
                string TSstring = str.substr(0, str.find(' '));
                float timestamp = stof(TSstring);

                int posXBeg = nthSubstr(1, str, " ")+1;
                int posXEnd = nthSubstr(2, str, " ");
                int deltaX = posXEnd - posXBeg;
                string XStr = str.substr(posXBeg,deltaX);
                int x = stoi(XStr);

                int posYBeg = nthSubstr(2, str, " ")+1;
                int posYEnd = nthSubstr(3, str, " ");
                int deltaY = posYEnd - posYBeg;
                string yStr = str.substr(posYBeg,deltaY);
                int y = stoi(yStr);

                int posPolBeg = nthSubstr(3, str, " ")+1;
                string polarity = str.substr(posPolBeg,str.size());
                bool pol = polarity != "0";

                //cout << timestamp << " " << x << " " << y << " " << pol << endl;

                Event Event(timestamp,x,y,pol);
                EventBuffer.push_back(Event);
                //EventBuffer[i];
                //++i;
            }
            else {
                cout << "FrameSize == 1000 \n";
                return EventBuffer;
            }
        }
    }

    /* to write into an output file comment out and also in the beginning where myfile is defined
    ostream_iterator<string> output_iterator(myfile, "\n");
    copy(vecOfStrs.begin(), vecOfStrs.end(), output_iterator);
    myfile.close();*/

    return EventBuffer;
}



int main() {
    // the management of the eventFlow here should be handled by an eventHandler
    std::vector<Event> EventBuffer;
//    EventBuffer = std::async(read_from_txt_to_EventBuffer()); //doesn't work yet, need to check how to implement async tasks in c++
    std::vector<Event> FilteredEventBuffer = BackGroundActivityFilter(EventBuffer);

    return 0;
}
