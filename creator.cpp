// Template generator for resPES maps for SpecsLab2
// Licence: Lesser GNU Public License 2.1 (LGPL)
// Author: Matthias Richter
#define date "2012-09-30"

#include <iostream>
#include <fstream>
#include <string.h>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <ostream>
#include <time.h>
#include <math.h>
#include <cmath>
#include <limits>
using namespace std;
using std::ios_base;


struct parameters{
    string analysis_method; // FixedAnalyzerTransmission for wallpapers
    string analyzer_lens;
    string analyzer_slit;
    string scan_mode;
    unsigned long num_scans;
    unsigned long curves_per_scan;
    unsigned long values_per_curve;
    double dwell_time;
    double scan_delta;
    double excitation_energy;
    double kinetic_energy;
    double pass_energy;
    double bias_voltage;
    double detector_voltage;
    double effective_workfunction; // do not change; given value is for the SPECS PHOIBOS 150
    unsigned long colorcode; //color of lines
    bool interpolation; //turn on Schmeißer's interpolation in SpecsLab
    string filename; // the xml filename
    unsigned int regions; //how many regions
    string groupname; //name of the group of regions
    string regionname;
    bool first; //first region in group? yes or no
};


static string myheader(string datetime){
    stringstream str;    
    str << "<?xml version=\"1.0\"?>\n"
    "<!-- CORBA XML document created by XMLSerializer2 1.3 at "<< datetime <<", from SL 2.53-r17444 built 2010-03-18 08:03:38 UTC -->\n"
    "<!DOCTYPE any [\n"
    "<!ELEMENT any (any|typecode|sequence|array|struct|union|exception|string|objectref|enum|boolean|char|octet|short|ushort|long|ulong|float|double)?>\n"
    "<!ATTLIST any name NMTOKEN #IMPLIED type_id CDATA #IMPLIED type_name NMTOKEN #IMPLIED label NMTOKEN #IMPLIED version CDATA #IMPLIED>\n"
    "<!ELEMENT typecode (any|typecode|sequence|array|struct|union|exception|string|objectref|enum|boolean|char|octet|short|ushort|long|ulong|float|double)?>\n"
    "<!ATTLIST typecode name NMTOKEN #IMPLIED type_id CDATA #IMPLIED type_name NMTOKEN #IMPLIED label NMTOKEN #IMPLIED>\n"
    "<!ELEMENT sequence ((any|typecode|sequence|array|struct|union|exception|string|objectref)+|(enum|boolean|char|octet|short|ushort|long|ulong|float|double))?>\n"
    "<!ATTLIST sequence name NMTOKEN #IMPLIED type_id CDATA #IMPLIED type_name NMTOKEN #IMPLIED length NMTOKEN #REQUIRED bound NMTOKEN #IMPLIED label NMTOKEN #IMPLIED>\n"
    "<!ELEMENT array ((any|typecode|sequence|array|struct|union|exception|string|objectref)+|(enum|boolean|char|octet|short|ushort|long|ulong|float|double))?>\n"
    "<!ATTLIST array name NMTOKEN #IMPLIED type_id CDATA #IMPLIED type_name NMTOKEN #IMPLIED length NMTOKEN #REQUIRED label NMTOKEN #IMPLIED>\n"
    "<!ELEMENT struct (any|typecode|sequence|array|struct|union|exception|string|objectref|enum|boolean|char|octet|short|ushort|long|ulong|float|double)*>\n"
    "<!ATTLIST struct name NMTOKEN #IMPLIED type_id CDATA #REQUIRED type_name NMTOKEN #IMPLIED label NMTOKEN #IMPLIED>\n"
    "<!ELEMENT union (any|typecode|sequence|array|struct|union|exception|string|objectref|enum|boolean|char|octet|short|ushort|long|ulong|float|double)*>\n"
    "<!ATTLIST union name NMTOKEN #IMPLIED type_id CDATA #REQUIRED type_name NMTOKEN #IMPLIED label NMTOKEN #IMPLIED>\n"
    "<!ELEMENT exception (any|typecode|sequence|array|struct|union|exception|string|objectref|enum|boolean|char|octet|short|ushort|long|ulong|float|double)*>\n"
    "<!ATTLIST exception name NMTOKEN #IMPLIED type_id CDATA #REQUIRED type_name NMTOKEN #IMPLIED label NMTOKEN #IMPLIED>\n"
    "<!ELEMENT string (#PCDATA)>\n"
    "<!ATTLIST string name NMTOKEN #IMPLIED type_id CDATA #IMPLIED type_name NMTOKEN #IMPLIED bound NMTOKEN #IMPLIED label NMTOKEN #IMPLIED>\n"
    "<!ELEMENT objectref (#PCDATA)>\n"
    "<!ATTLIST objectref name NMTOKEN #IMPLIED type_id CDATA #REQUIRED type_name NMTOKEN #IMPLIED label NMTOKEN #IMPLIED>\n"
    "<!ELEMENT enum (#PCDATA)>\n"
    "<!ATTLIST enum name NMTOKEN #IMPLIED type_id CDATA #REQUIRED type_name NMTOKEN #IMPLIED values NMTOKENS #REQUIRED label NMTOKEN #IMPLIED>\n"
    "<!ELEMENT boolean (#PCDATA)>\n"
    "<!ATTLIST boolean name NMTOKEN #IMPLIED type_id CDATA #IMPLIED type_name NMTOKEN #IMPLIED label NMTOKEN #IMPLIED>\n"
    "<!ELEMENT char (#PCDATA)>\n"
    "<!ATTLIST char name NMTOKEN #IMPLIED type_id CDATA #IMPLIED type_name NMTOKEN #IMPLIED label NMTOKEN #IMPLIED>\n"
    "<!ELEMENT octet (#PCDATA)>\n"
    "<!ATTLIST octet name NMTOKEN #IMPLIED type_id CDATA #IMPLIED type_name NMTOKEN #IMPLIED label NMTOKEN #IMPLIED>\n"
    "<!ELEMENT short (#PCDATA)>\n"
    "<!ATTLIST short name NMTOKEN #IMPLIED type_id CDATA #IMPLIED type_name NMTOKEN #IMPLIED label NMTOKEN #IMPLIED>\n"
    "<!ELEMENT ushort (#PCDATA)>\n"
    "<!ATTLIST ushort name NMTOKEN #IMPLIED type_id CDATA #IMPLIED type_name NMTOKEN #IMPLIED label NMTOKEN #IMPLIED>\n"
    "<!ELEMENT long (#PCDATA)>\n"
    "<!ATTLIST long name NMTOKEN #IMPLIED type_id CDATA #IMPLIED type_name NMTOKEN #IMPLIED label NMTOKEN #IMPLIED>\n"
    "<!ELEMENT ulong (#PCDATA)>\n"
    "<!ATTLIST ulong name NMTOKEN #IMPLIED type_id CDATA #IMPLIED type_name NMTOKEN #IMPLIED label NMTOKEN #IMPLIED>\n"
    "<!ELEMENT float (#PCDATA)>\n"
    "<!ATTLIST float name NMTOKEN #IMPLIED type_id CDATA #IMPLIED type_name NMTOKEN #IMPLIED label NMTOKEN #IMPLIED>\n"
    "<!ELEMENT double (#PCDATA)>\n"
    "<!ATTLIST double name NMTOKEN #IMPLIED type_id CDATA #IMPLIED type_name NMTOKEN #IMPLIED label NMTOKEN #IMPLIED>\n"
    "]>\n";
    return str.str();
}


static string mygroupheader(string groupname, string length){
    stringstream str;
    str << "<any version=\"1.3\">\n"
    "<sequence length=\"1\" type_id=\"IDL:specs.de/Serializer/RegionGroupSeq:1.0\" type_name=\"RegionGroupSeq\">\n"
    "<struct type_id=\"IDL:specs.de/Serializer/RegionGroup:1.0\" type_name=\"RegionGroup\">\n"
    "<string name=\"name\">"<< groupname <<"</string>\n"
    "<sequence name=\"regions\" length=\""<< length <<"\" type_id=\"IDL:specs.de/Serializer/RegionDataSeq:1.0\" type_name=\"RegionDataSeq\">\n";
    return str.str();
}


static string myregion(parameters paramxml){
    stringstream str;
    str << "<struct type_id=\"IDL:specs.de/Serializer/RegionData:1.0\" type_name=\"RegionData\">\n"
    "<string name=\"name\">"<< paramxml.regionname <<"</string>\n"
    "<struct name=\"region\" type_id=\"IDL:specs.de/SurfaceAnalysis/RegionDef:1.0\" type_name=\"RegionDef\">\n"
    "<string name=\"analysis_method\">"<< paramxml.analysis_method <<"</string>\n"
    "<string name=\"analyzer_lens\">"<< paramxml.analyzer_lens <<"</string>\n"
    "<string name=\"analyzer_slit\">"<< paramxml.analyzer_slit <<"</string>\n"
    "<struct name=\"scan_mode\" type_id=\"IDL:specs.de/SurfaceAnalysis/ScanMode:1.0\" type_name=\"ScanMode\">\n"
    "<string name=\"name\">"<< paramxml.scan_mode <<"</string>\n"
    "<ulong name=\"flags\" type_id=\"IDL:specs.de/SurfaceAnalysis/ScanModeFlags:1.0\" type_name=\"ScanModeFlags\">2</ulong>\n"
    "</struct>\n"
    "<ulong name=\"num_scans\">"<< paramxml.num_scans <<"</ulong>\n"
    "<ulong name=\"curves_per_scan\">"<< paramxml.curves_per_scan <<"</ulong>\n"
    "<ulong name=\"values_per_curve\">"<< paramxml.values_per_curve <<"</ulong>\n"
    "<double name=\"dwell_time\">"<< paramxml.dwell_time <<"</double>\n"
    "<double name=\"scan_delta\">"<< paramxml.scan_delta <<"</double>\n"
    "<double name=\"excitation_energy\">"<< paramxml.excitation_energy <<"</double>\n"
    "<double name=\"kinetic_energy\">"<< paramxml.kinetic_energy <<"</double>\n"
    "<double name=\"pass_energy\">"<< paramxml.pass_energy <<"</double>\n"
    "<double name=\"bias_voltage\">"<< paramxml.bias_voltage <<"</double>\n"
    "<double name=\"detector_voltage\">"<< paramxml.detector_voltage <<"</double>\n"
    "<double name=\"effective_workfunction\">"<< paramxml.effective_workfunction <<"</double>\n"
    "</struct>\n"
    "<ulong name=\"mcd_head\">0</ulong>\n"
    "<ulong name=\"mcd_tail\">0</ulong>\n"
    "<struct name=\"analyzer_info\" type_id=\"IDL:specs.de/SurfaceAnalysis/AnalyzerInfo:1.0\" type_name=\"AnalyzerInfo\">\n"
    "<string name=\"name\"/>\n"
    "<sequence name=\"detectors\" length=\"0\" type_id=\"IDL:specs.de/SurfaceAnalysis/DetectorSeq:1.0\" type_name=\"DetectorSeq\"/>\n"
    "<sequence name=\"parameters\" length=\"0\" type_id=\"IDL:specs.de/SurfaceAnalysis/ParameterSeq:1.0\" type_name=\"ParameterSeq\"/>\n"
    "</struct>\n"
    "<struct name=\"source_info\" type_id=\"IDL:specs.de/SurfaceAnalysis/SourceInfo:1.0\" type_name=\"SourceInfo\">\n"
    "<string name=\"name\"/>\n"
    "<sequence name=\"excitations\" length=\"0\" type_id=\"IDL:specs.de/SurfaceAnalysis/ExcitationSeq:1.0\" type_name=\"ExcitationSeq\"/>\n"
    "<sequence name=\"parameters\" length=\"0\" type_id=\"IDL:specs.de/SurfaceAnalysis/ParameterSeq:1.0\" type_name=\"ParameterSeq\"/>\n"
    "<boolean name=\"intensity_scaling\">1</boolean>\n"
    "</struct>\n"
    "<struct name=\"remote_info\" type_id=\"IDL:specs.de/SurfaceAnalysis/RemoteInfo:1.0\" type_name=\"RemoteInfo\">\n"
    "<string name=\"name\"/>\n"
    "<enum name=\"frequency\" values=\"Never PerRegion PerScan PerValue AfterRegion AfterScan AfterValue\" type_id=\"IDL:specs.de/SurfaceAnalysis/RemoteFrequency:1.0\" type_name=\"RemoteFrequency\">Never</enum>\n"
    "<sequence name=\"parameters\" length=\"0\" type_id=\"IDL:specs.de/SurfaceAnalysis/ParameterSeq:1.0\" type_name=\"ParameterSeq\"/>\n"
    "<sequence name=\"channel_names\" length=\"0\" type_id=\"IDL:specs.de/SurfaceAnalysis/StringSeq:1.0\" type_name=\"StringSeq\"/>\n"
    "<sequence name=\"channel_units\" length=\"0\" type_id=\"IDL:specs.de/SurfaceAnalysis/StringSeq:1.0\" type_name=\"StringSeq\"/>\n"
    "</struct>\n"
    "<sequence name=\"cycles\" length=\"0\" type_id=\"IDL:specs.de/Serializer/CycleSeq:1.0\" type_name=\"CycleSeq\"/>\n"
    "<sequence name=\"compact_cycles\" length=\"0\" type_id=\"IDL:specs.de/Serializer/CompactCycleSeq:1.0\" type_name=\"CompactCycleSeq\"/>\n"
    "<sequence name=\"transmission\" length=\"0\" type_id=\"IDL:specs.de/SurfaceAnalysis/DoubleSeq:1.0\" type_name=\"DoubleSeq\"/>\n"
    "<sequence name=\"parameters\" length=\"6\" type_id=\"IDL:specs.de/SurfaceAnalysis/ParameterSeq:1.0\" type_name=\"ParameterSeq\">\n"
    "<struct type_id=\"IDL:specs.de/SurfaceAnalysis/Parameter:1.0\" type_name=\"Parameter\">\n"
    "<string name=\"name\">Color</string>\n"
    "<any name=\"value\">\n"
    "<ulong>"<< paramxml.colorcode <<"</ulong>\n"
    "</any>\n"
    "</struct>\n"
    "<struct type_id=\"IDL:specs.de/SurfaceAnalysis/Parameter:1.0\" type_name=\"Parameter\">\n"
    "<string name=\"name\">Interpolation</string>\n"
    "<any name=\"value\">\n"
    "<boolean>"<< paramxml.interpolation <<"</boolean>\n"
    "</any>\n"
    "</struct>\n"
    "<struct type_id=\"IDL:specs.de/SurfaceAnalysis/Parameter:1.0\" type_name=\"Parameter\">\n"
    "<string name=\"name\">File</string>\n"
    "<any name=\"value\">\n"
    "<string>"<< paramxml.filename <<"</string>\n"
    "</any>\n"
    "</struct>\n"
    "<struct type_id=\"IDL:specs.de/SurfaceAnalysis/Parameter:1.0\" type_name=\"Parameter\">\n"
    "<string name=\"name\">Group</string>\n"
    "<any name=\"value\">\n"
    "<string>"<< paramxml.groupname <<"</string>\n"
    "</any>\n"
    "</struct>\n"
    "<struct type_id=\"IDL:specs.de/SurfaceAnalysis/Parameter:1.0\" type_name=\"Parameter\">\n"
    "<string name=\"name\">First of group</string>\n"
    "<any name=\"value\">\n"
    "<boolean>"<< paramxml.first <<"</boolean>\n"
    "</any>\n"
    "</struct>\n"
    "<struct type_id=\"IDL:specs.de/SurfaceAnalysis/Parameter:1.0\" type_name=\"Parameter\">\n"
    "<string name=\"name\">Style</string>\n"
    "<any name=\"value\">\n"
    "<string>solid_line</string>\n"
    "</any>\n"
    "</struct>\n"
    "</sequence>\n"
    "</struct>\n";  
    return str.str();
}


static string myfooter(string filename, string comment){
    stringstream str;
    str << "<sequence name=\"parameters\" length=\"2\" type_id=\"IDL:specs.de/SurfaceAnalysis/ParameterSeq:1.0\" type_name=\"ParameterSeq\">\n"
    "<struct type_id=\"IDL:specs.de/SurfaceAnalysis/Parameter:1.0\" type_name=\"Parameter\">\n"
    "<string name=\"name\">File</string>\n"
    "<any name=\"value\">\n"
    "<string>" << filename << "</string>\n"
    "</any>\n"
    "</struct>\n"
    "<struct type_id=\"IDL:specs.de/SurfaceAnalysis/Parameter:1.0\" type_name=\"Parameter\">\n"
    "<string name=\"name\">Comment</string>\n"
    "<any name=\"value\">\n"
    "<string>" << comment << "</string>\n"
    "</any>\n"
    "</struct>\n"
    "</sequence>\n"
    "</struct>\n"
    "</sequence>\n"
    "</any>";
    return str.str();
}


int main(int argc, char* argv[])
{
    cout << "Template generator for resPES maps for SpecsLab2, Version " << date << endl;
    stringstream str;
    string tmps= "";
    int std = 0, min = 0, sec = 0;
    parameters paramxml;

    double photonstart  = 0.0;
    double photonstop   = 0.0;
    double photondelta  = 0.0;
    double bindingstart = 0.0;
    double bindingstop  = 0.0;
    double bindingdelta = 0.0;
    double bindingdwell = 0.0;
    double pass_energy  = 0.0;
    
    cout << "Filenname:" << endl;
    str.str("");
    str.clear();
    cin >> paramxml.filename;
    str << paramxml.filename << ".xml";
    paramxml.filename = str.str();
    
    
    while ((cout << "Photonenergy start (85..<1890 for U49/2-PGM2): ")
              && !(cin >> photonstart)) {
         cout << "That's not a number; ";
         cin.clear();
         cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    while ((cout << "Photonenergy end ("<< photonstart << "<..1890): ")
              && (!(cin >> photonstop) ||  photonstop <= photonstart)) {
         cout << "That's not a number greater than photonenergy start; ";
         cin.clear();
         cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    while ((cout << "Photonenergy delta (0<..<="<< photonstop-photonstart <<"): ")
              && (!(cin >> photondelta) ||  photondelta > (photonstop-photonstart) || photondelta <=0)) {
         cout << "That's not a number smaller than photonenergy stop-start; ";
         cin.clear();
         cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    while ((cout << "Bindingenergy start (+xy): ")
              && !(cin >> bindingstart)) {
         cout << "That's not a number; ";
         cin.clear();
         cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    
    while ((cout << "Bindingenergy end (<"<< bindingstart <<"): ")
              && (!(cin >> bindingstop) ||  bindingstop >= bindingstart)) {
         cout << "That's not a number smaller than bindingenergy start; ";
         cin.clear();
         cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    
    while ((cout << "Bindingenergy delta (0<.."<< bindingstart-bindingstop <<"): ")
              && (!(cin >> bindingdelta) ||  bindingdelta > (bindingstart-bindingstop) || bindingdelta <=0)) {
         cout << "That's not a number smaller than photonenergy start-stop; ";
         cin.clear();
         cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }    
    
    while ((cout << "Dwelltime (0<):")
              && (!(cin >> bindingdwell) ||  bindingdwell <= 0)) {
         cout << "That's not a number greater than ZERO; ";
         cin.clear();
         cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    
    while ((cout << "pass energy (0< .. 100): ")
              && (!(cin >> pass_energy) ||  pass_energy <= 0 || pass_energy > 100)) {
         cout << "That's not a number greater between 0< and <=100; ";
         cin.clear();
         cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    
    

    paramxml.analysis_method        = "XPS";
    paramxml.analyzer_lens          = "MediumArea:1.5kV";
    paramxml.analyzer_slit          = "1:0.2x20\\1:0.25x20";
    paramxml.scan_mode              = "FixedAnalyzerTransmission";
    paramxml.num_scans              = 1;
    paramxml.curves_per_scan        = 1;
    paramxml.dwell_time             = bindingdwell;
    paramxml.scan_delta             = bindingdelta;
    paramxml.excitation_energy      = photonstart;
    paramxml.kinetic_energy         = photonstart-bindingstart;
    paramxml.pass_energy            = pass_energy;
    paramxml.bias_voltage           = 80;
    paramxml.detector_voltage       = 1950;
    paramxml.effective_workfunction = 4.387; // BTU SPECS Phoibos150
    paramxml.colorcode              = 16711935;
    paramxml.interpolation          = false;
    paramxml.values_per_curve       = int((bindingstart - bindingstop)/bindingdelta+1);
    paramxml.regions                = int((photonstop-photonstart)/photondelta+1);

    //cout << (bindingstop+bindingdelta*paramxml.values_per_curve) << endl;
    //cout << paramxml.values_per_curve << endl;
    if ((bindingstop+bindingdelta*(paramxml.values_per_curve-1)) < bindingstart){
        paramxml.values_per_curve += 1;
    }
    cout << (photonstart+paramxml.regions*photondelta) << endl;
    cout << paramxml.regions << endl;
    if ((photonstart+(paramxml.regions-1)*photondelta)<photonstop){
        paramxml.regions += 1;
    }


    paramxml.groupname = "Group1";
    paramxml.regionname = "Region1";
    paramxml.first = true;
    ofstream myoutput;
    myoutput.open(paramxml.filename.c_str(), ios_base::in | ios_base::out | ios_base::trunc);
    //write Specslab XML Header
    time_t mytime;
    mytime = time(NULL);
    cout << ctime(&mytime);
    myoutput << myheader(ctime(&mytime));
    //create new group (name and #Regions)
    str.str("");
    str.clear();
    str << paramxml.regions;
    myoutput << mygroupheader(paramxml.groupname, str.str());
    //create regions (loop #Regions)
    paramxml.first = true;
    for(int i=0;i<paramxml.regions;i++){
        str.str("");
        str.clear();
        str << "Region" << i+1;
        paramxml.regionname = str.str();
        paramxml.excitation_energy = photonstart+i*photondelta;
        paramxml.kinetic_energy = paramxml.excitation_energy-bindingstart;
        cout << paramxml.regionname        << " ; excitation: " \
             << paramxml.excitation_energy << " ; kin. energy: " \
             << paramxml.kinetic_energy    << " ; points: " \
             << paramxml.values_per_curve  <<  endl;
        myoutput << myregion(paramxml);
        paramxml.first = false;
    }
    //write end of group
    myoutput << "</sequence>\n";
    //write xmlfooter
    myoutput << myfooter(paramxml.filename, "no comment");
    myoutput.close();
    
    //calculation of measurement time
    sec = int(paramxml.regions*paramxml.num_scans*paramxml.dwell_time*(paramxml.values_per_curve+2.65484*pow(paramxml.scan_delta,-0.79638))+20*paramxml.regions*paramxml.num_scans+.5f);
    min = sec/60; sec%=60;
    std = min/60; min%=60;
    cout << "estimated measurement time: " << std << "h " << min << "min " << sec <<"sec (must be <8h for BESSY II)" << endl;
    cout << "Press <Enter> key to continue...";
    cin.ignore();
    cin.get();
    return 0;
}
