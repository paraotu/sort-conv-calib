 /**
  ******************************************************************************
  * @file    tt_typeconv.c
  * @author  dijh
  * @version V1.0
  * @date    2021-12-15
  * @brief   ����ת�� 
  ******************************************************************************
  * @attention
  *
  * Ԥ����;��
  *
  ******************************************************************************
  */

#include "tt_typeconv.h"


/* �����㷨 */
/**
	* @brief  ���������ʼ���������������������ͣ�
	* @param  ��������
	* @param  ����ʹ����
  * @retval ��
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
	* @brief  �����㷨�������������������ͣ�
	* @param  Ҫ�������
	* @param  ��������
	* @param  ����ʹ����
  * @retval ��
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







/* ת���������� */
/**
	* @brief  ����ת��Ϊ����
	* @param  �ܾ� ����ֵ
  * @retval ����ֵ
  */
float convert_Q2V(float _dn, float qn)
{
	return qn / (_dn * _dn * 0.00000078539816f);
}
/**
	* @brief  ����ת��Ϊ����
	* @param  �ܾ� ����ֵ
  * @retval ����ֵ
  */
float convert_V2Q(float _dn, float vn)
{
	return vn *_dn * _dn * 0.00000078539816f;
}

/**
	* @brief  ���״���Զ�ת��
	* @param  ����
	* @param  ��־λ
	* @param  ѹ�����¶�
  * @retval ���ֵ
  */
float convert_Auto_N2n(float flow, uint16_t out_s, uint32_t press, float temp)
{
	if(out_s)// �����¼���
	{
		flow = 345.642163f * (273.15f + temp) / (float)(press + 101325) * flow;
	}
	return flow;
}
/**
	* @brief  ���״���Զ�ת��
	* @param  ����
	* @param  ��־λ
	* @param  ѹ�����¶�
  * @retval ���ֵ
  */
float convert_Auto_n2N(float flow, uint16_t out_s, uint32_t press, float temp)
{
	if(out_s)// �����¼���
	{
		flow = flow * (float)(press + 101325) / (345.642163f * (273.15f + temp));
	}
	return flow;
}


/* �����洢 ת�� */
/**
	* @brief  ��������ת��Ϊ4�ֽ�����
	* @param  float
	* @param  ByteArray
	* @retval ��
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
	* @brief  4�ֽ�����ת��Ϊ��������
	* @param  array
	* @param  float
	* @retval ��
  */
void _ByteArray2Float(uint8_t* array, float* data)
{
	for(uint8_t i = 0; i < 4; i++)
	{
		*((uint8_t*)data + i) = array[i];
	}
}

/**
	* @brief  ����������
	* @param  ����ֵ
	* @param  4mA��DAֵָ��
	* @param  20mA��DAֵ
	* @retval ��
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
	* @brief  �����������
	* @param  ����ֵ
	* @param  4mA��DAֵ
	* @param  20mA��DAֵָ��
	* @retval ��
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







