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

// 單元題目可使用的分母  [][0] = 分母數量  [][1~11] = 分母
const int UNIT_1[12][12] = {
	{ 5, 2, 4, 6, 8, 12, 0, 0, 0, 0, 0, 0},
	{ 2, 2, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 3, 2, 4, 8, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 4, 2, 4, 5, 6, 0, 0, 0, 0, 0, 0, 0 },
	{ 5, 2, 4, 5, 6, 8, 0, 0, 0, 0, 0, 0 },
	{ 7, 2, 4, 5, 6, 8, 10, 12, 0, 0, 0, 0 },
    { 5, 2, 4, 6, 8, 12, 0, 0, 0, 0, 0, 0},
    { 2, 2, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 3, 2, 4, 8, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 4, 2, 4, 5, 6, 0, 0, 0, 0, 0, 0, 0 },
    { 5, 2, 4, 5, 6, 8, 0, 0, 0, 0, 0, 0 },
    { 7, 2, 4, 5, 6, 8, 10, 12, 0, 0, 0, 0 } };

const int UNIT_2[12][12] = {
    { 5, 2, 4, 6, 8, 12, 0, 0, 0, 0, 0, 0},
    { 2, 2, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 3, 2, 4, 8, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 4, 2, 4, 5, 6, 0, 0, 0, 0, 0, 0, 0 },
    { 5, 2, 4, 5, 6, 8, 0, 0, 0, 0, 0, 0 },
    { 7, 2, 4, 5, 6, 8, 10, 12, 0, 0, 0, 0 },
    { 5, 2, 4, 6, 8, 12, 0, 0, 0, 0, 0, 0},
    { 2, 2, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 3, 2, 4, 8, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 4, 2, 4, 5, 6, 0, 0, 0, 0, 0, 0, 0 },
    { 5, 2, 4, 5, 6, 8, 0, 0, 0, 0, 0, 0 },
    { 7, 2, 4, 5, 6, 8, 10, 12, 0, 0, 0, 0 } };

const int UNIT_3[12][12] = {
    { 5, 2, 4, 6, 8, 12, 0, 0, 0, 0, 0, 0},
    { 2, 2, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 3, 2, 4, 8, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 4, 2, 4, 5, 6, 0, 0, 0, 0, 0, 0, 0 },
    { 5, 2, 4, 5, 6, 8, 0, 0, 0, 0, 0, 0 },
    { 7, 2, 4, 5, 6, 8, 10, 12, 0, 0, 0, 0 },
    { 5, 2, 4, 6, 8, 12, 0, 0, 0, 0, 0, 0},
    { 2, 2, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 3, 2, 4, 8, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 4, 2, 4, 5, 6, 0, 0, 0, 0, 0, 0, 0 },
    { 5, 2, 4, 5, 6, 8, 0, 0, 0, 0, 0, 0 },
    { 7, 2, 4, 5, 6, 8, 10, 12, 0, 0, 0, 0 } };

const int UNIT_4[3][12] = {
	{ 7, 2, 3, 4, 5, 6, 8, 10, 0, 0, 0, 0 },
	{ 5, 2, 3, 4, 5, 6, 0, 0, 0, 0, 0, 0 },
	{ 7, 2, 3, 4, 5, 6, 8, 10, 0, 0, 0, 0 } };

const int UNIT_5[2][12] = {
	{ 7, 2, 3, 4, 5, 6, 8, 10, 0, 0, 0, 0 },
	{ 5, 2, 3, 4, 5, 6, 0, 0, 0, 0, 0, 0 } };

/*
// 單元題目可使用的分母  [][0] = 分母數量  [][1~11] = 分母
//可變１
const int UNIT_1[12][12] = {
    { 11, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12},
    { 11, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12},
    { 11, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12},
    { 11, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12},
    { 11, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12},
    { 11, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12},
    { 11, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12},
    { 11, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12},
    { 11, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12},
    { 11, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12},
    { 11, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12},
    { 11, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}};

//認識帶分數
const int UNIT_2[12][12] = {
    { 11, 2, 3, 4, 5, 6, 7, 8, 9,10,11,12},
    { 11, 2, 3, 4, 5, 6, 7, 8, 9,10,11,12},
    {  5, 2, 3, 4, 5, 6, 0, 0, 0, 0, 0, 0},
    { 10, 3, 4, 5, 6, 7, 8, 9,10,11,12, 0},
    {  6, 2, 3, 4, 5, 6, 7, 0, 0, 0, 0, 0},
    { 11, 2, 3, 4, 5, 6, 7, 8, 9,10,11,12},
    {  7, 2, 3, 4, 5, 6, 7, 8, 0, 0, 0, 0},
    {  5, 2, 3, 4, 5, 6, 0, 0, 0, 0, 0, 0},
    { 11, 2, 3, 4, 5, 6, 7, 8, 9,10,11,12},
    {  7, 2, 3, 4, 5, 6, 7, 8, 0, 0, 0, 0},
    {  7, 2, 3, 4, 5, 6, 7, 8, 0, 0, 0, 0},
    { 11, 2, 3, 4, 5, 6, 7, 8, 9,10,11, 2}};

//帶分數假分數互換
const int UNIT_3[12][12] = {
    { 11, 2, 3, 4, 5, 6, 7, 8, 9,10,11,12},
    { 11, 2, 3, 4, 5, 6, 7, 8, 9,10,11,12},
    { 10, 3, 4, 5, 6, 7, 8, 9,10,11,12, 0},
    {  8, 5, 6, 7, 8, 9,10,11,12, 0, 0, 0},
    {  9, 4, 5, 6, 7, 8, 9,10,11,12, 0, 0},
    {  8, 5, 6, 7, 8, 9,10,11,12, 0, 0, 0},
    {  6, 6, 7, 8, 9,11,12, 0, 0, 0, 0, 0},
    {  7, 4, 5, 7, 8,10,11,12, 0, 0, 0, 0},
    {  5, 7, 8, 9,10,11, 0, 0, 0, 0, 0, 0},
    {  5, 3, 5, 7, 9,11, 0, 0, 0, 0, 0, 0},
    {  6, 5, 6, 7, 9,10,11, 0, 0, 0, 0, 0},
    {  5, 8, 9,10,11,12, 0, 0, 0, 0, 0, 0}};

const int UNIT_4[3][12] = {
    { 7, 2, 3, 4, 5, 6, 8, 10, 0, 0, 0, 0 },
    { 5, 2, 3, 4, 5, 6, 0, 0, 0, 0, 0, 0 },
    { 7, 2, 3, 4, 5, 6, 8, 10, 0, 0, 0, 0 } };

const int UNIT_5[2][12] = {
    { 7, 2, 3, 4, 5, 6, 8, 10, 0, 0, 0, 0 },
    { 5, 2, 3, 4, 5, 6, 0, 0, 0, 0, 0, 0 } };

*/
