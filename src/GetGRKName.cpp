# include <iostream>
# include "../src-lib/tinyxml2.h"
# include <string>

std::string GetGRKName(tinyxml2::XMLNode *pGRK){
   tinyxml2::XMLNode *pTmpGRK = pGRK;
   std::string GRKName = "";
// Get GRK Name
   for(pTmpGRK;pTmpGRK;pTmpGRK=pTmpGRK->NextSibling()){
      GRKName=pTmpGRK->ToElement()->Attribute("name");
      std::size_t Founded=GRKName.find("ГРК");
       	if (Founded!=std::string::npos){
	       return GRKName;
	}	       
   }
   GRKName = "";
   return GRKName;
}
