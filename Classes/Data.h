#pragma once

#define BOTTOM_LEVEL 1
#define WHITEBOARD_LEVEL 2
#define INTERFACE_LEVEL 3
#define SWITCHBOARD_LEVEL 4
// for hand drawing
#define HAND_MODE    1
#define PEN_MODE     2
#define ERASER_MODE  3

//每單元故事數量
const int STORYDATA[5] = {2,1,3,2,2};

//每單元題目數量
const int QUEDATA[5] = { 12,12,12,12,12 };

//題目目類型
// 1-一般  2-變量  3-比例尺  4-倍數  5-線段  11-分子1  12-分子2
const int UNIT_QUE[5][12] = {
    {1,1,1,1,1,1,1,1,1,1,1,1},
    {1,1,111,1,111,1,1,211,1,1,211,1},
    {1,1,1,1,1,1,112,212,312,412,512,612},  //  第6題要改5
    {1,1,1,1,1,1,1,1,1,1,1,1},  //{1,1,1,1,1,1,102,202,202,202,102,202},
    {4,4,3,3,4,3,4,4,4,4,4,4} };  //{4,4,3,3,4,3,4,4,4,4,4,4} };

//            0       1     2     3      4       5       6      7     8      9    10    11    12    13     14    15     16        17      18
enum OBJECT{PANCAKE,PAPER,WATER,BAMBOO,RIBBON,DISTANCE,BANANA,GRAPE,FLOWER,BRANCH,NUT,TOMATO,APPLE,SUGAR,COOKIE,PEAR,BIGBAMBOO,BIGRODE,BIGRIBBON,};
const int UNIT_OBJ[5][12] = {
    {2,0,6,3,10,7,8,5,1,11,4,9},
    {0,10,6,3,12,1,7,8,2,5,9,4},   //4??公斤？緞帶？
    {2,3,0,5,4,1,6,10,7,8,12,9},  //12->15
    {2,0,3,5,0,4,6,10,7,8,12,9},  //0_2 pizza??
    {2,0,3,5,0,4,6,10,7,0,12,9}}; //{2,13,16,17,0,18,6,10,7,14,15,9}};

const int PIECE[14][12] = {
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
    { 3, 2, 4, 8, 0, 0, 0, 0, 0, 0, 0, 0},       //12 頻果
    { 11, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}};  //13 大竹子 //待改


const int PIECE_U2[2][12] = {
    {6,2,3,4,5,6,7,0,0,0,0,0},
    {10,2,3,4,5,6,7,8,9,10,11,0},};

const int PIECE_U3[6][12] = {
    { 5, 4, 5, 6, 7, 8, 0, 0, 0, 0, 0, 0},  //4
    { 2, 2, 3, 4, 0, 0, 0, 0, 0, 0, 0, 0},  //2
    { 5, 4, 5, 6, 7, 8, 0, 0, 0, 0, 0, 0},  //4
    { 3, 2, 3, 4, 0, 0, 0, 0, 0, 0, 0, 0},  //2
    { 5, 4, 5, 6, 7, 8, 0, 0, 0, 0, 0, 0},  //4
    { 4, 3, 4, 5, 6, 0, 0, 0, 0, 0, 0, 0},  //3
};

const int PIECE_U4[2][12] = {
    { 7, 3, 4, 5, 6, 8, 9,10, 0,0,0,0},
    { 8, 3, 4, 5, 6, 8, 9,10,12,0,0,0}};

const int UNIT5_b[12] = { 3,2,0,0,3,0,2,5,3,4,1,2}; //第5章分子設定

const int PIECE_U5[12][12] = {
    { 4, 4, 5, 6, 7, 0, 0, 0, 0, 0, 0, 3},   //[11]-分子設定  後面是選單設定
    { 4, 4, 5, 6, 7, 0, 0, 0, 0, 0, 0, 2},
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    { 9, 4, 5, 6, 7, 8, 9,10,11,12, 0, 3},
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    { 2, 4, 8, 0, 0, 0, 0, 0, 0, 0, 0, 2},
    { 3, 2, 4, 8, 0, 0, 0, 0, 0, 0, 0, 1},
    { 3, 4, 6,12, 0, 0, 0, 0, 0, 0, 0, 3},
    { 2, 5,10, 0, 0, 0, 0, 0, 0, 0, 0, 4},
    { 3, 2, 3, 6, 0, 0, 0, 0, 0, 0, 0, 1},
    { 5, 2, 3, 4, 6,12, 0, 0, 0, 0, 0, 2}};

        //    分母.倍數.分子
const int UNIT5[12][6][5] = {  //1是可以用得值
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
