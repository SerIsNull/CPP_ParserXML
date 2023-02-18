# include <iostream>
# include "../src-lib/tinyxml2.h"
# include <string>
# include "GetGRKName.hpp"
# include "GetAPTSName.hpp"

tinyxml2::XMLNode* FindAPTS(tinyxml2::XMLNode *pAPTS, tinyxml2::XMLNode *pGRK){
	std::string 
	APTSNameInAPTS = GetAPTSName(pAPTS),
	APTSNameInGRK = "";
	
tinyxml2::XMLNode *pTmpGRK = pGRK;

// Search APTS in GRK File
std::cout<<"Start search New APTS: "<<GetAPTSName(pAPTS)<<" "<<" in "<<GetGRKName(pGRK)<<std::endl;// DBG
for(pTmpGRK;pTmpGRK;pTmpGRK=pTmpGRK->NextSibling()){
	APTSNameInGRK=GetAPTSName(pTmpGRK);
	if (APTSNameInGRK == APTSNameInAPTS){
		std::cout<<"Finded!!!"<<std::endl;
		return pTmpGRK;
	}
}
std::cout<<"Error. Not Finded!!!"<<std::endl;
return nullptr;
}
