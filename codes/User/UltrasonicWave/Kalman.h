#ifndef __KALMAN_H
#define	__KALMAN_H

// һά�˲�����Ϣ�ṹ��
typedef  struct{
	double filterValue[2];  //k-1ʱ�̵��˲�ֵ������k-1ʱ�̵�ֵ,��һ��ֵ��ʾ���룬�ڶ���ֵ��ʾ�ٶ�
	double kg[2];   //   Kalamn���� 
	double Q[2];   //Ԥ���������ƫ��ķ���, Q[0]���������� Q[1]�ٶȹ������
	double R;   //��������ƫ�(ϵͳ����Ժ�ͨ������ͳ��ʵ����)
	double P[2][2];   //�������Э����
	double dt;    //ʱ�����
}  KalmanInfo;

void Init_Kalman(void);
double KalmanFilter(int i,double Measurement);	

#endif
