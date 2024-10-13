#ifndef TRIMMER_H
#define TRIMMER_H

#include <string>

// 工具类 修剪字符串
class Trimmer {
public:
	void trim(std::string& s);
private:
	void ltrim(std::string& s);
	void rtrim(std::string& s);
};

#endif // !TRIMMER_H
