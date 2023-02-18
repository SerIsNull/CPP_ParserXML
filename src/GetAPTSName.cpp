# include "../src-lib/tinyxml2.h"
# include <string>

std::string GetAPTSName(tinyxml2::XMLNode *pAPTS){
// Get APTS Name
      return pAPTS->ToElement()->Attribute("name");
}
