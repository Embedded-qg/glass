#ifndef __FILTER_H
#define	__FILTER_H

typedef int smooth_type;
struct Filter
{
	int size;     //�˲��������
	int degree ;       //�˲���������
	smooth_type* data;  //�������ݣ���Ҫ���⿪�ٿռ�
	int index;         //�������ݴ洢λ��
};

void Init_Smooth_n(int size, smooth_type inital,int degree);
smooth_type smooth_n( int num, smooth_type data);
#endif
