# include <string>
# include <iostream>
# include "../src-lib/tinyxml2.h"
# include "GetAPTS.hpp"
# include "FindAPTS.hpp"
# include "GetGRKName.hpp"
# include "GetAPTSName.hpp"

// Common Variable
using docXml=tinyxml2::XMLDocument;
using nodeXml=tinyxml2::XMLNode;
using pathToFile = const char*;

// APTS File.xml. Variable
namespace APTS{
   std::string Name = "";
   pathToFile  _Path = "";
   docXml FileXml;
   nodeXml 
     *pAllAPTS = nullptr,
     *pNewAPTS = nullptr;
}

// GRK File.xml. Variable
namespace GRK{
   std::string Name = "";
   pathToFile _Path = "";
   docXml FileXml;
   nodeXml 
     *pAllAPTS = nullptr,
     *pFindedAPTS = nullptr,
     *pNewAPTS = nullptr;
}


int main (int CntInFile, char *PthToFile[]){
   APTS::_Path = PthToFile[2]; 
   GRK::_Path = PthToFile[1];

// Open input GRK File and APTS File
   APTS::FileXml.LoadFile(APTS::_Path);
   GRK::FileXml.LoadFile(GRK::_Path);

// If not opened Files - exit
   if(APTS::FileXml.Error()||GRK::FileXml.Error()){
      std::cout<<"Error when opening document :"<<APTS::FileXml.ErrorStr()<<std::endl;
      std::cout<<"Error when opening document :"<<GRK::FileXml.ErrorStr()<<std::endl;
   return -1;
}

// Parse APTS File. Get All APTS
   APTS::pAllAPTS = GetAPTS(&APTS::FileXml);

// Parse GRK File. Get All APTS
   GRK::pAllAPTS = GetAPTS(&GRK::FileXml);

// Does the APTS exist in GRK-File and APTS File? 
   if(APTS::pAllAPTS && GRK::pAllAPTS){
      APTS::pNewAPTS = APTS::pAllAPTS;
      APTS::Name = GetAPTSName(APTS::pNewAPTS);
      GRK::Name = GetGRKName(GRK::pAllAPTS);
// Find New APTS in GRK
      std::cout<<"We will search New APTS: "<<APTS::Name<<" in "<<GRK::Name<<std::endl; //DBG
      GRK::pFindedAPTS = FindAPTS(APTS::pNewAPTS, GRK::pAllAPTS);
      if (GRK::pFindedAPTS) {
// Allocate memory for Finded APTS in GRK-File
	 GRK::pNewAPTS = APTS::pNewAPTS->DeepClone(&GRK::FileXml);
// Paste Finded APTS in GRK File
	 if(GRK::pNewAPTS){
	    std::cout<<"We will be adding New APTS: "<<GetAPTSName(GRK::pNewAPTS)<<" in "<<GRK::Name<<std::endl; //DBG 
	    GRK::pFindedAPTS->Parent()->ToElement()->InsertAfterChild(GRK::pAllAPTS,GRK::pNewAPTS);
// Delete Finded APTS from GRK File
	    std::cout<<"We will remove Finded APTS: "<<GetAPTSName(GRK::pFindedAPTS)<<" in "<<GRK::Name<<std::endl; //DBG
	    GRK::FileXml.DeleteNode(GRK::pFindedAPTS);
// Save New GRK File
	    GRK::FileXml.SaveFile(GRK::_Path);
            std::cout<<"We saved new GRK File like : "<<GRK::_Path<<std::endl;
	 } // Pasted->Deleted->Saved
      }// Finded
   }// Get APTS/GRK

else {
	std::cout<<"Error!!! Try again!"<<std::endl;
   }
return 0;
}
