#pragma once

#define BOTTOM_LEVEL 1
#define WHITEBOARD_LEVEL 2
#define INTERFACE_LEVEL 3
#define SWITCHBOARD_LEVEL 4
// for hand drawing
#define HAND_MODE    1
#define PEN_MODE     2
#define ERASER_MODE  3

//每單元題目數量
const int QUEDATA[5] = { 12,12,12,3,2 };

//              0       1     2     3      4       5       6      7     8      9    10    11
//enum Object{PANCAKE,PAPER,WATER,BAMBOO,RIBBON,DISTANCE,BANANA,GRAPE,FLOWER,BRANCH,NUT,TOMATO};
//const int UNIT_OBJ[5][12] = {
//    {2,0,6,3,10,7,8,5,1,11,4,9},
//    {0,10,6,3,11,1,7,8,2,5,9,4},
//    {2,3,0,5,4,1,6,10,7,8,11,9},
//    {0,0,0,0,0,0,0,0,0,0,0,0},
//    {0,0,0,0,0,0,0,0,0,0,0,0}};

const int UNIT_OBJ[5][12] = {
    {2,1,6,2,10,3,8,4,11,7,9,5},
    {0,10,6,0,11,0,7,8,0,5,9,0},
    {0,0,0,5,0,0,6,10,7,8,11,9},
    {0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0}};

// 單元題目可使用的分母  [][0] = 分母數量  [][1~11] = 分母
const int UNIT_1[12][12] = {
	{ 6, 2, 3, 4, 5, 6, 7, 0, 0, 0, 0, 0},
    { 11, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12},
	{ 3, 2, 4, 8, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 3, 2, 4, 8, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 3, 2, 4, 8, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 3, 2, 4, 8, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 5, 2, 3, 4, 6, 12, 0, 0, 0, 0, 0, 0 },
    { 5, 2, 3, 4, 6, 12, 0, 0, 0, 0, 0, 0 },
    { 5, 2, 3, 4, 6, 12, 0, 0, 0, 0, 0, 0 },
    { 5, 2, 3, 4, 6, 12, 0, 0, 0, 0, 0, 0 },
    { 3, 2, 4, 8, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 1, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }};

const int UNIT_2[12][12] = {
    { 11, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12},
    { 3, 2, 4, 8, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 3, 2, 4, 8, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 11, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12},
    { 5, 2, 3, 4, 6, 12, 0, 0, 0, 0, 0, 0 },
    { 5, 2, 3, 4, 6, 12, 0, 0, 0, 0, 0, 0 },
    { 5, 2, 3, 4, 6, 12, 0, 0, 0, 0, 0, 0 },
    { 5, 2, 3, 4, 6, 12, 0, 0, 0, 0, 0, 0 },
    { 11, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12},
    { 1, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 3, 2, 4, 8, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 11, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}};

const int UNIT_3[12][12] = {
    { 11, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12},
    { 11, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12},
    { 11, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12},
    { 1, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 11, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12},
    { 11, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12},
    { 3, 2, 4, 8, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 3, 2, 4, 8, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 5, 2, 3, 4, 6, 12, 0, 0, 0, 0, 0, 0 },
    { 3, 2, 4, 8, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 5, 2, 3, 4, 6, 12, 0, 0, 0, 0, 0, 0 },
    { 3, 2, 4, 8, 0, 0, 0, 0, 0, 0, 0, 0 }};

const int UNIT_4[3][12] = {
	{ 7, 2, 3, 4, 5, 6, 8, 10, 0, 0, 0, 0 },
	{ 5, 2, 3, 4, 5, 6, 0, 0, 0, 0, 0, 0 },
	{ 7, 2, 3, 4, 5, 6, 8, 10, 0, 0, 0, 0 } };

const int UNIT_5[2][12] = {
	{ 7, 2, 3, 4, 5, 6, 8, 10, 0, 0, 0, 0 },
	{ 5, 2, 3, 4, 5, 6, 0, 0, 0, 0, 0, 0 } };

