#include "api/BamReader.h"
#include "api/BamWriter.h"
#include <string>
#include <map>
#include <vector>
#include <iostream>
#include <fstream>
using namespace BamTools;
using namespace std;
int main(int argc, char *argv[])
{
	const string splash=
	      "\nlengd        generate read length histogram data\n"
		"Version: 1.0	Author: Danny Antaki <dantaki@ucsd.edu>\n\n"
		"Usage: lengd -i <in.bam> -q <INT> -o <output.txt>\n\n"
		"Options:\n"
		"    -i        Input: BAM filename\n"
		"    -q        Mapping quality threshold [10]\n"
		"    -o        Output: filename\n";
	string ifh; 
	string ofh;
	int Q=10;
	if ( (argc==1) ||
	     (argc==2 && string(argv[1]) == "-h") ||
	     (argc==2 && string(argv[1]) == "-help") ||
	     (argc==2 && string(argv[1]) == "--help")) {
		cout << splash << endl;
		return 1;
	}
	for(int i=1; i<argc; i++){
		if(string(argv[i]) == "-i" || string(argv[i]) == "--in" || string(argv[i]) == "-in"){ ifh = string(argv[i+1]); i++; continue; }
		if(string(argv[i]) == "-o" || string(argv[i]) == "--out" || string(argv[i]) == "-out"){ ofh = string(argv[i+1]); i++; continue; }
		if(string(argv[i]) == "-q" || string(argv[i]) == "--q"){ Q = atoi(argv[i+1]); i++; continue; }
		cerr << "ERROR: Unknown option "<<string(argv[i])<< endl;
		return 1;
	}
	if(ifh == "") { cerr << "ERROR: No BAM file given\n\n"<< splash << endl; return 1; }
	if(ofh == ""){ ofh = ifh.substr(0,ifh.find_last_of('.'))+"_lengd.txt";  }		
	BamReader reader;
	if (!reader.Open(ifh)){
		cerr << "ERROR: " << ifh << " could not be opened!\n\n"<< splash << endl; 
		return 1;
	}
	BamAlignment al;
	const RefVector refs = reader.GetReferenceData();
	map<int32_t, map<int,int> > COV;
	while (reader.GetNextAlignmentCore(al)){
		if(al.MapQuality < Q || 
			al.IsDuplicate()==true || 
			al.IsFailedQC()==true || 
			al.IsMapped()==false || 
			al.IsPrimaryAlignment()==false) 
			{ continue; } 	
		unsigned int rlen=0;
		vector<CigarOp> cigar = al.CigarData;
		for(vector<CigarOp>::iterator it= cigar.begin(); it != cigar.end(); ++it)
		{if (it->Type == 'M' || it->Type == '=' || it->Type== 'X') { rlen+=it->Length;}}
		if(rlen!=0){ COV[al.RefID][rlen]++;}
	}
	reader.Close();
	ofstream fout;
	fout.open (ofh.c_str());	
	fout << "CONTIG\tREAD_LENGTH\tN_READS" << endl;
	map<uint64_t, uint64_t> GEN;
	for(map<int32_t, map<int,int> >::iterator i=COV.begin(); i != COV.end(); ++i){
		for(map<int,int>::iterator j=COV[(*i).first].begin(); j != COV[(*i).first].end(); ++j){
			fout << refs[(*i).first].RefName << '\t' << (*j).first << '\t' << (*j).second << endl;
			GEN[(*j).first]+=(*j).second;	
		}
	}
	for(map<uint64_t,uint64_t>::iterator i=GEN.begin(); i!=GEN.end(); ++i){ 
		fout << "GENOME\t" << (*i).first << '\t' << (*i).second << endl; 
	}
	fout.close();
	return 0;
}
