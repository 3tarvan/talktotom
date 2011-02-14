#include "stdafx.h"

#ifndef __CMATRIX__
#define __CMATRIX__

class CMatrix //������
{
public:
	//���캯���������������������캯������ֵ�����
	CMatrix(int row, int col);
	~CMatrix();
	CMatrix(const CMatrix &rhs);
	CMatrix& operator=(const CMatrix &rhs);

public:
	//������
	bool setMatrix(const double *array, int size);
	//��ȡ�����е�����Ԫ��
	bool getMatrix(double *array, int size);
	//��ȡ���������
	void getRow(int &row);
	//��ȡ���������
	void getCol(int &col);
	//��ʾ����
	bool display(void);

public:
	//�������
	bool Add(const CMatrix &rhs);
	//�������
	bool Minus(const CMatrix &rhs);
	//�������
	bool Multiply(const CMatrix &rhs);
	//������������
	bool Multiply(const double constant);


public:
	//����ת�ã����������rhs��
	bool TransposeMatrix();

	//������󣬽��������rhs��
	bool InverseMatrix();

private:
	bool ContraryMatrix(double *const pMatrix, double *const _pMatrix, const int &dim);
	CMatrix(){}

private:
	double *m_matrix; //ָ������ָ��
	int    m_row; //���������
	int    m_col; //���������
};


#endif