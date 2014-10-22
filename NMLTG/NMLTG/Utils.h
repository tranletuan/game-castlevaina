#ifndef __UTILS_H_
#define __UTILS_H_

#include <d3d9.h>
#include <string>
#include "Global.h"

using namespace std;

LPDIRECT3DSURFACE9 CreateSurfaceFromFile(LPDIRECT3DDEVICE9 d3ddv, LPWSTR FilePath);
void DisplayText(string text);
void GLMessage(LPCWSTR text);
void GLMessage(string text);
#endif