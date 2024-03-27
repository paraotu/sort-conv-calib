#ifndef __TT_TYPECONV_H
#define __TT_TYPECONV_H

#include "stm32l4xx.h"


#define FILTER_NUM		300
typedef struct{
	uint16_t width;
	uint16_t p2sDex;
	uint16_t point2s[FILTER_NUM];
	uint16_t s2point[FILTER_NUM];
	float senquence[FILTER_NUM];
}SORT_ARRRY;

void TT_Sort(float data, SORT_ARRRY* sArray, uint16_t maxNum);

float convert_Q2V(float _dn, float qn);
float convert_V2Q(float _dn, float vn);
float convert_Auto_N2n(float flow, uint16_t out_s, uint32_t press, float temp);
float convert_Auto_n2N(float flow, uint16_t out_s, uint32_t press, float temp);

void _Float2ByteArray(float data, uint8_t* array);
void _ByteArray2Float(uint8_t* array, float* data);

void Current_4mACalibration(float Ivalue, uint16_t* v4, uint16_t v20);
void Current_20mACalibration(float Ivalue, uint16_t v4, uint16_t* v20);


#endif /* __TT_TYPECONV_H */

