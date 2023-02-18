# include "../src-lib/tinyxml2.h"
tinyxml2::XMLNode* GetAPTS(tinyxml2::XMLDocument *pDocument){

return pDocument->FirstChildElement("TechObjects")->
	     FirstChildElement("branches")->
	     FirstChildElement("TechObject");
}
