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
const int QUEDATA[5] = { 12,12,12,12,12 };

//            0       1     2     3      4       5       6      7     8      9    10    11       12
enum OBJECT{PANCAKE,PAPER,WATER,BAMBOO,RIBBON,DISTANCE,BANANA,GRAPE,FLOWER,BRANCH,NUT,TOMATO,BIGBAMBOO};

const int UNIT_OBJ[5][12] = {
    {2,0,6,3,10,7,8,5,1,11,4,9},
    {0,10,6,3,11,1,7,8,2,5,9,4},
    {2,3,0,5,4,1,6,10,7,8,11,9},
    {2,0,3,5,0,4,6,10,7,8,11,9},
    {2,0,3,5,0,4,6,10,7,0,11,9}};

const int PIECE[13][12] = {
    { 11, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12},   //0  鬆餅
    { 5, 2, 3, 4, 6, 8, 0, 0, 0, 0, 0, 0},       //1  紙
    { 6, 2, 3, 4, 5, 6, 7, 0, 0, 0, 0, 0 },      //2  水
    { 5, 2, 3, 4, 6, 12, 0, 0, 0, 0, 0, 0 },     //3  竹子
    { 3, 2, 3, 6, 0, 0, 0, 0, 0, 0, 0, 0 },      //4  緞帶
    { 3, 2, 3, 6, 0, 0, 0, 0, 0, 0, 0, 0 },      //5  距離
    { 3, 2, 4, 8, 0, 0, 0, 0, 0, 0, 0, 0 },      //6  香蕉
    { 5, 2, 3, 4, 6, 12, 0, 0, 0, 0, 0, 0 },     //7  葡萄
    { 5, 2, 3, 4, 6, 12, 0, 0, 0, 0, 0, 0 },     //8  花
    { 3, 2, 4, 8, 0, 0, 0, 0, 0, 0, 0, 0 },      //9  樹枝
    { 3, 2, 4, 8, 0, 0, 0, 0, 0, 0, 0, 0 },      //10 果實
    { 5, 2, 3, 4, 6, 12, 0, 0, 0, 0, 0, 0 },     //11 番茄
    { 11, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}};  //12 大竹子

        //    分母.倍數.分子
const int UNIT5[12][6][5] = {
    {{1,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},},        //分母2 倍數為2~7 的分子(1~5)可能
    {{1,1,0,0,0},{1,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},},        //分母3 倍數為2~7 的分子(1~5)可能
    {{1,1,1,0,0},{1,0,0,0,0},{1,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},},        //分母4 倍數為2~7 的分子(1~5)可能
    {{1,1,1,1,0},{1,1,0,0,0},{1,0,0,0,0},{1,0,0,0,0},{0,0,0,0,0},{0,0,0,0,0},},        //分母5 倍數為2~7 的分子(1~5)可能
    {{1,1,1,1,1},{1,1,1,0,0},{1,1,0,0,0},{1,0,0,0,0},{1,0,0,0,0},{0,0,0,0,0},},        //分母6 倍數為2~7 的分子(1~5)可能
    {{1,1,1,1,1},{1,1,1,0,0},{1,1,0,0,0},{1,0,0,0,0},{1,0,0,0,0},{1,0,0,0,0},},        //分母7 倍數為2~7 的分子(1~5)可能
    {{1,1,1,1,1},{1,1,1,1,0},{1,1,1,1,0},{1,1,1,0,0},{1,0,0,0,0},{1,0,0,0,0},},        //分母8 倍數為2~7 的分子(1~5)可能
    {{1,1,1,1,1},{1,1,1,1,1},{1,1,1,0,0},{1,1,0,0,0},{1,0,0,0,0},{1,0,0,0,0},},        //分母9 倍數為2~7 的分子(1~5)可能
    {{1,1,1,1,1},{1,1,1,1,1},{1,1,1,1,0},{1,1,1,0,0},{1,1,0,0,0},{1,0,0,0,0},},        //分母10 倍數為2~7 的分子(1~5)可能
    {{1,1,1,1,1},{1,1,1,1,1},{1,1,1,1,0},{1,1,1,0,0},{1,1,0,0,0},{1,1,0,0,0},},        //分母11 倍數為2~7 的分子(1~5)可能
    {{1,1,1,1,1},{1,1,1,1,1},{1,1,1,1,0},{1,1,1,0,0},{1,1,1,0,0},{1,1,0,0,0},}         //分母12 倍數為2~7 的分子(1~5)可能
};
