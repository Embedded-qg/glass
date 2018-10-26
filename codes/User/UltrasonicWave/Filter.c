/**
* ���������˲�����
**/
#include "Fliter.h"
#include<stdlib.h>

static struct Filter smooth; 

 /**
* @brief Init_Smooth_n   n���˲������ʼ��
* @param size  �ֱ��size�����ݽ����˲��Ż�
* @param inital   ���ݳ�ʼֵ
* @return no
*/
void Init_Smooth_n(int size, smooth_type inital,int degree)
{
	int i;
	smooth.size = size;
	smooth.degree = degree;
	smooth.data = (smooth_type*)malloc(sizeof(smooth_type) * degree*size);
	for( i = 0; i < size*degree; i++ )
		smooth.data[i] = inital;
}


 /**
* @brief smoothAverage   �����ݽ����˲�,
* @param Measurement   ��������
* @param num  ������� num: 0~x
* @return �˲�����
*/
smooth_type smooth_n( int num, smooth_type data)
{
	int i;
	double temp;
	if( num >= smooth.size )     //���ݲ���������������ڣ�ֱ�ӷ���ԭֵ
		return data;
	smooth.index = (smooth.index+1) %smooth.degree;
	smooth.data[num*smooth.degree+smooth.index] = data; 
	for( i = 0, temp = 0; i < smooth.degree; i++ )
	{
		printf("##: %d", smooth.data[num*smooth.degree+i]);
		temp += smooth.data[num*smooth.degree+i];
	}	
	printf("\r\n");
	return temp/smooth.degree + 0.5;
}

