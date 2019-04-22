#ifndef UTIL_H
#define UTIL_H

#include <string>
#include <vector>

class Util{
public:

	static unsigned int split(const std::string &txt, std::vector<std::string> &strs, char chara){
		int pos = txt.find(chara);
		int iniPos = 0;
		strs.clear();

		while (pos !=std::string::npos){
			strs.push_back(txt.substr(iniPos, pos-iniPos+1));
			iniPos =pos+1;

			pos =txt.find(chara, iniPos);
		}

		strs.push_back(txt.substr(iniPos, std::min<int>(pos, txt.size()-(iniPos+1))));

		return strs.size();

	}
};



#endif
