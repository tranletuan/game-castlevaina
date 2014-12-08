#ifndef CDATABASE_H
#define CDATABASE_H

#include <string>
#include <iostream>
#include <fstream>

using namespace std;

class CDatabase
{
private:
	
public:
	CDatabase();	
	~CDatabase();

	int readHighScore(string namePath);
	void writeHighScore(string namePath,int highscore);
};

#endif