#include "Kalman.h"
#include "UltrasonicWave.h"

static KalmanInfo Kalman[AVER_NUM_ALL];

/**
* @brief Init_Kalman   ��ʼ���˲����ĳ�ʼֵ
*/
void Init_Kalman()
{
	int i;
	for( i = 0; i < AVER_NUM_ALL; ++i )
	{
		Kalman[i].P[0][0] = 1;
		Kalman[i].P[0][1] = 1;
		Kalman[i].P[1][0] = 1;
		Kalman[i].P[1][1] = 1;
		Kalman[i].Q[0] = 30;    //Ԥ�⣨���̣��������� Ӱ���������ʣ����Ը���ʵ���������
		Kalman[i].Q[1] = 0.5; 
		Kalman[i].R = 60;    //�������۲⣩�������� ����ͨ��ʵ���ֶλ��
		Kalman[i].filterValue[0] = 200;// �����ĳ�ʼֵ
		Kalman[i].filterValue[1] = 1;// �����ĳ�ʼֵ
		Kalman[i].dt = 0.06;		
	}       
}

/**
* @brief Init_Kalman   �����ݽ����˲�
* @param Measurement   ��������
* @param i  ������� 
* @return �˲�����
*/
KalmanType KalmanFilter(int i, KalmanType Measurement)
{
	//ϵͳԤ��ֵ
	Kalman[i].filterValue[0] +=  Kalman[i].filterValue[1]* Kalman[i].dt;           

    //��Э����
	Kalman[i].P[0][0] += Kalman[i].P[0][1]*Kalman[i].dt + Kalman[i].P[1][0]*Kalman[i].dt + Kalman[i].Q[0];
	Kalman[i].P[0][1] += Kalman[i].P[1][1]*Kalman[i].dt;
	Kalman[i].P[1][0] += Kalman[i].P[1][1]*Kalman[i].dt;
	Kalman[i].P[1][1] += Kalman[i].Q[1];

	//����������
	Kalman[i].kg[0] = Kalman[i].P[0][0] / (Kalman[i].P[0][0] + Kalman[i].R); 
	Kalman[i].kg[1] = Kalman[i].P[1][0] / (Kalman[i].P[1][0] + Kalman[i].R);

	//��������
    Kalman[i].filterValue[0] += Kalman[i].kg[0] * (Measurement -Kalman[i].filterValue[0]);

	//����Э����
	Kalman[i].P[0][0] -= Kalman[i].P[0][0] * Kalman[i].kg[0];
	Kalman[i].P[0][1] -= Kalman[i].P[0][1] * Kalman[i].kg[0];
	Kalman[i].P[1][0] -= Kalman[i].P[0][0] * Kalman[i].kg[1];
	Kalman[i].P[1][1] -= Kalman[i].P[0][1] * Kalman[i].kg[1];
	
	return Kalman[i].filterValue[0];
}





