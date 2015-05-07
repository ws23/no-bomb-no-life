/*
File: controlCon.h controlCon.cpp
IDE: Visual Studio 2013
Authors: Hung, Chung Chun(NaiveRed)
Email: jason841201@gmail.com
*/
#pragma once

void SetConsoleSize(int Width, int Height);
void gotoXY(short x, short y);
void FillConsole(char ch=' ',short left_x = 0, short top_y = 0, unsigned int area = 0);

