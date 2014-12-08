#include "CDatabase.h"

CDatabase::CDatabase()
{
}

int CDatabase::readHighScore(string namePath)
{
	std::ifstream file(namePath);
	string line;
	while (file >> std::ws && std::getline(file, line));
	return atoi(line.c_str());
}


void CDatabase::writeHighScore(string namePath, int highscore)
{
	ofstream _fileOut;
	_fileOut.open(namePath, ios_base::app);
	_fileOut << "\n" + to_string(highscore);
	_fileOut.close();
}

CDatabase::~CDatabase()
{

}