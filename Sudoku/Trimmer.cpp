#include "Trimmer.h"

void Trimmer::trim(std::string& s){
    ltrim(s);
    rtrim(s);
}

void Trimmer::ltrim(std::string& s){
    s.erase(s.begin(), std::find_if(s.begin(), s.end(),
        [](unsigned char ch) { return !std::isspace(ch); }));
}

void Trimmer::rtrim(std::string& s){
    s.erase(std::find_if(s.rbegin(), s.rend(),
        [](unsigned char ch) { return !std::isspace(ch); }).base(), s.end());
}
