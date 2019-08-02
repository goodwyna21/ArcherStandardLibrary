#ifndef OUTPUTS_HEADER_H
#define OUTPUTS_HEADER_H

//includes
#include <iostream>
#include <fstream>
#include <bitset>
#include <vector>
#include <string>
#include <cmath>
using namespace std;

//constants
#define byte unsigned char
#define uint unsigned int

//font
const string GLYPHS[]={
"XXXX XX XX XXXX",//0
"  X  X  X  X  X",//1
"XXX  XXXXX  XXX",//2
"XXXX  XXXX  XXX",//3
"X XX XXXX  X  X",//4
"XXXX  XX   XXX ",//5
" XXX  XX X X X ",//6
"XXX  X  X  X  X",//7
"XXXX XXXXX XXXX",//8
"XXXX XXXX  X  X",//9
" X X XXXXX XX X",//a
"XX X XXX X XXX ",//b
" XXX  X  X   XX",//c
"XX X XX XX XXX ",//d
"XXXX  XXXX  XXX",//e
"XXXX  XX X  X  ",//f
" XXX  X XX X XX",//g
"X XX XXXXX XX X",//h
"XXX X  X  X XXX",//i
"  X  X  XX XXXX",//j
"X  X  X XXX X X",//k
"X  X  X  X  XXX",//l
"   X XXXXX XX X",//m
"   X  XX X XX X",//n
" X X XX XX X X ",//o
"XX X XXX X  X  ",//p
" XXX X XX  X  X",//q
"XX X XXX XX X X",//r
" XXX  XXX  XXX ",//s
"XXX X  X  X  X ",//t
"X XX XX XX XXXX",//u
"      X XX X X ",//v
"   X XXXXXXX X ",//w
"X XX X X X XX X",//X
"X XX XXXX X  X ",//y
"XXX  X X X  XXX",//z
"               ",//space
"            X  ",//.
"         X  X  ",//,
"XXX  X XX    X ",//?
"  X  X  X     X",//!
"      XXX      ",//-
" XXX  X  X   XX",//(
"XX   X  X  XXX ",//)
};

const string GLYPHLIST =
"0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ .,?!-()";

const int GLYPHWIDTH = 3;
const int GLYPHHEIGHT = 5;
const char GLYPHSETPX = 'X';

#endif
