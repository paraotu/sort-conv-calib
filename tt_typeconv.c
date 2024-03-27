 /**
  ******************************************************************************
  * @file    tt_typeconv.c
  * @author  dijh
  * @version V1.0
  * @date    2021-12-15
  * @brief   类型转换 
  ******************************************************************************
  * @attention
  *
  * 预设用途：
  *
  ******************************************************************************
  */

#include "tt_typeconv.h"


/* 排序算法 */
/**
	* @brief  排序数组初始化（序列数组延续利用型）
	* @param  排序数组
	* @param  数组使用量
  * @retval 无
  */
static void TT_SortInit(SORT_ARRRY* sArray, uint16_t maxNum)
{
	sArray->p2sDex = 0;
	for(uint16_t i = 0; i < maxNum; i++)
	{
		sArray->point2s[i] = i;
		sArray->s2point[i] = i;
		sArray->senquence[i] = 0;
	}
}
/**
	* @brief  排序算法（序列数组延续利用型）
	* @param  要加入的数
	* @param  排序数组
	* @param  数组使用量
  * @retval 无
  */
void TT_Sort(float data, SORT_ARRRY* sArray, uint16_t maxNum)
{
	uint16_t i;
	
	if(sArray->width != maxNum)
	{
		sArray->width = maxNum;
		TT_SortInit(sArray, sArray->width);
	}
	
	if(data > sArray->senquence[sArray->point2s[sArray->p2sDex]])
	{
		for(i = sArray->point2s[sArray->p2sDex]; i < (sArray->width-1); i++)
		{
			if(data < sArray->senquence[i+1])
			{
				break;
			}
			else
			{
				sArray->senquence[i] = sArray->senquence[i+1];
				sArray->s2point[i] = sArray->s2point[i+1];
				sArray->point2s[sArray->s2point[i+1]] -= 1;
			}
		}
		sArray->point2s[sArray->p2sDex] = i;
		sArray->senquence[i] = data;
		sArray->s2point[i] = sArray->p2sDex;
	}
	else
	{
		for(i = sArray->point2s[sArray->p2sDex]; i > 0; i--)
		{
			if(data > sArray->senquence[i-1])
			{
				break;
			}
			else
			{
				sArray->senquence[i] = sArray->senquence[i-1];
				sArray->s2point[i] = sArray->s2point[i-1];
				sArray->point2s[sArray->s2point[i]] += 1;
			}
		}
		sArray->point2s[sArray->p2sDex] = i;
		sArray->senquence[i] = data;
		sArray->s2point[i] = sArray->p2sDex;
	}
	
	sArray->p2sDex++;
	if(sArray->p2sDex >= sArray->width)
	{
		sArray->p2sDex = 0;
	}
}







/* 转换流速流量 */
/**
	* @brief  流量转换为流速
	* @param  管径 流量值
  * @retval 流速值
  */
float convert_Q2V(float _dn, float qn)
{
	return qn / (_dn * _dn * 0.00000078539816f);
}
/**
	* @brief  流速转换为流量
	* @param  管径 流速值
  * @retval 流量值
  */
float convert_V2Q(float _dn, float vn)
{
	return vn *_dn * _dn * 0.00000078539816f;
}

/**
	* @brief  输出状况自动转换
	* @param  流量
	* @param  标志位
	* @param  压力，温度
  * @retval 结果值
  */
float convert_Auto_N2n(float flow, uint16_t out_s, uint32_t press, float temp)
{
	if(out_s)// 工况下计算
	{
		flow = 345.642163f * (273.15f + temp) / (float)(press + 101325) * flow;
	}
	return flow;
}
/**
	* @brief  输出状况自动转换
	* @param  流量
	* @param  标志位
	* @param  压力，温度
  * @retval 结果值
  */
float convert_Auto_n2N(float flow, uint16_t out_s, uint32_t press, float temp)
{
	if(out_s)// 工况下计算
	{
		flow = flow * (float)(press + 101325) / (345.642163f * (273.15f + temp));
	}
	return flow;
}


/* 参数存储 转换 */
/**
	* @brief  浮点数据转换为4字节数组
	* @param  float
	* @param  ByteArray
	* @retval 无
  */
void _Float2ByteArray(float data, uint8_t* array)
{
	uint32_t mid = 0;
	mid = *(uint32_t*)(&data);
	
	for(uint8_t i = 0; i < 4; i++)
	{
		array[i] = (uint8_t)mid;
		mid >>= 8;
	}
}

/**
	* @brief  4字节数组转换为浮点数据
	* @param  array
	* @param  float
	* @retval 无
  */
void _ByteArray2Float(uint8_t* array, float* data)
{
	for(uint8_t i = 0; i < 4; i++)
	{
		*((uint8_t*)data + i) = array[i];
	}
}

/**
	* @brief  电流零点调零
	* @param  电流值
	* @param  4mA的DA值指针
	* @param  20mA的DA值
	* @retval 无
  */
void Current_4mACalibration(float Ivalue, uint16_t* v4, uint16_t v20)
{
	float tempf1, tempf2;
	tempf1 = (Ivalue - 4) * v20;
	tempf1 = tempf1 - 16 * *v4;
	tempf2 = Ivalue - 20;
	tempf1 = tempf1 / tempf2;
	*v4 = (uint16_t)tempf1;
}
/**
	* @brief  电流满点调零
	* @param  电流值
	* @param  4mA的DA值
	* @param  20mA的DA值指针
	* @retval 无
  */
void Current_20mACalibration(float Ivalue, uint16_t v4, uint16_t* v20)
{
	float tempf1, tempf2;
	tempf1 = (Ivalue - 20) * v4;
	tempf1 = tempf1 + 16 * *v20;
	tempf2 = Ivalue - 4;
	tempf1 = tempf1 / tempf2;		
	if(tempf1<=0xfffe)
		*v20 = (uint16_t)tempf1;
}







