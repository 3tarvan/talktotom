#include "stdafx.h"
#include <iostream>
#include "Matrix.h"
#include <math.h>

using namespace std;


//һ�㹹�캯��
CMatrix::CMatrix(int row, int col)
:m_matrix(NULL), m_row(0), m_col(0)
{
	int length = 0;

	//�ж������������Ƿ�Ϻ��涨
	if ((row < 1) || (col < 1))
	{
		return;
	}

	length = row * col;

	m_matrix = new double[length]; //Ϊ��������ڴ�ռ�
	if (NULL == m_matrix)
	{
		return;
	}
	else
	{
		m_row = row;
		m_col = col;

		//������0�����������������Ԫ��
		memset(m_matrix, 0, length * sizeof(double));
	}

}

//��������
CMatrix::~CMatrix()
{
	if (NULL != m_matrix)
	{
		delete [] m_matrix; //�ͷž�����ռ�õ��ڴ�
	}
}

//�������캯��
CMatrix::CMatrix(const CMatrix &rhs)
:m_matrix(NULL), m_row(rhs.m_row), m_col(rhs.m_col)
{
	int length = 0;

	if (NULL == rhs.m_matrix) //����rhsΪ��
	{
		return;
	}

	length = m_row * m_col;

	m_matrix = new double[length]; //Ϊ��������ڴ�ռ�
	if (NULL == m_matrix)
	{
		m_row = 0;
		m_col = 0;

		return;
	}
	else
	{
		//��rhs���������Ԫ������䱾����
		memcpy(m_matrix, rhs.m_matrix, length * sizeof(double) );
	}

}

//��ֵ�����
CMatrix& CMatrix::operator=(const CMatrix &rhs)
{
	int length = 0;

	//�ж��Ƿ��Ը�ֵ
	if (this != &rhs)
	{
		//�ͷ�ԭ������ռ�õ��ڴ�
		delete [] m_matrix;
		m_matrix = NULL;
		m_row = 0;
		m_col = 0;

		//����rhs�Ƿ�Ϊ��
		if (rhs.m_matrix != NULL)
		{
			length = rhs.m_row * rhs.m_col;

			m_matrix = new double [length]; //Ϊ��������ڴ�ռ�
			if (m_matrix != NULL)
			{
				m_row = rhs.m_row;
				m_col = rhs.m_col;

				//��rhs���������Ԫ������䱾����
				memcpy(m_matrix, rhs.m_matrix, length * sizeof(double) );
			}

		} //if ((rhs.m_row > 0) && (rhs.m_col > 0))

	}

	return *this; //���ر����������

}

//������
bool CMatrix::setMatrix(const double *array, int size)
{
	if ((NULL == m_matrix) || (NULL == array))
	{
		return false;
	}

	if (size != (m_row * m_col)) //���Ȳ����
	{
		return false;
	}
	else
	{
		//������array�����ֵ����䱾����
		memcpy(m_matrix, array, size * sizeof(double));

		return true;

	}

}

//��ȡ�����е�����Ԫ��
bool CMatrix::getMatrix(double *array, int size)
{
	int length = 0;

	if (    (NULL == m_matrix) 
		||  (NULL == array)
		||  (size != m_col * m_row))
	{
		return false;
	}
	else
	{
		length = m_row * m_col;

		//������array�����ر�����������Ԫ��ֵ
		memcpy(array, m_matrix, length * sizeof(double) );

		return true;

	}

}

//��ȡ���������
void CMatrix::getRow(int &row)
{
	row = m_row;
}

//��ȡ���������
void CMatrix::getCol(int &col)
{
	col = m_col;
}

//��ʾ����
bool CMatrix::display(void)
{
	if (NULL == m_matrix) //������Ϊ��
	{
		return false;
	}
	else
	{
		//�����������
		for (int row = 0; row < m_row; ++row)
		{
			for (int col = 0; col < m_col; ++col)
			{
				printf("%5f\t",m_matrix[row * m_col + col]); //ͬһ���еľ���Ԫ��֮����һ��tab ����
			}

			cout << '\n'; //׼�������һ��

		}

		return true;

	}

}

//�������
bool CMatrix::Add(const CMatrix &rhs)
{
	bool b = false;

	//�ж���������������������Ƿ�ֱ����
	if ((m_row == rhs.m_row) && (m_col == rhs.m_col))
	{
		if (NULL == m_matrix)
		{
			return b; 
		}
		else
		{
			b = true;

			int length = m_row * m_col;

			for (int index = 0; index < length; ++index)
			{
				m_matrix[index] = m_matrix[index] + rhs.m_matrix[index]; //���
			}

		} //if ((m_row < 1) || (m_col < 1))

	}

	return b;
}

//�������
bool CMatrix::Minus(const CMatrix &rhs)
{
	CMatrix temp = rhs;

	temp.Multiply(-1);

	return this->Add(temp);
}

//�������
bool CMatrix::Multiply(const CMatrix &rhs)
{
	bool b = false;

	if (m_col == rhs.m_row) //��һ�������������ڶ���������������
	{
		if (NULL == m_matrix)
		{
			return b;
		}
		else
		{
			b = true;

			// ԭ���ľ����� this->m_row ��, rhs.m_col��
			CMatrix tempMatrix(m_row, rhs.m_col);

			for (int row = 0; row < m_row; ++row) //��
			{
				for (int col = 0; col < rhs.m_col; ++col) //��
				{
					for (int index = 0; index < m_col; ++index)
					{
						tempMatrix.m_matrix[row*rhs.m_col+col] += 
							(m_matrix[row*m_col+index] * rhs.m_matrix[index*rhs.m_col+col]);
					}

				}
			}

			// ����ԭ�����ݣ�����������
			delete [] this->m_matrix;
			
			m_col = rhs.m_col;

			m_matrix = new double [m_row*m_col];

			memcpy(m_matrix, tempMatrix.m_matrix, m_col * m_row * sizeof(double) );

		} //if (NULL == m_matrix)

	}

	return b;

}

//������������
bool CMatrix::Multiply(const double constant)
{
	bool b = false;

	//�������Ƿ�Ϊ��
	if (NULL == m_matrix)
	{
		return b;
	}
	else
	{
		b = true;

		int length = m_row * m_col;

		for (int index = 0; index < length; ++index)
		{
			this->m_matrix[index] = m_matrix[index] * constant; //����Ԫ���볣�����
		}
	}

	return b;
}


//����ת�ã����������rhs��
bool CMatrix::TransposeMatrix()
{
	if (this->m_matrix == NULL)
	{
		return false;
	}

	CMatrix temp(m_row, m_col);

	for (int i = 0; i < m_row; i++)
	{
		for (int j = 0; j < m_col;j++)
		{
			*(temp.m_matrix + j * m_col + i) = *(m_matrix + i * m_col + j);
		}
	}

	memcpy( this->m_matrix, temp.m_matrix, m_row * m_col * sizeof(double) );

	return true;
}

//������󣬽��������rhs��
bool CMatrix::InverseMatrix()
{
	bool b = false;
	if (m_col != m_row)
	{
		// ���Ƿ���
		return b;
	}

	b = ContraryMatrix(this->m_matrix, this->m_matrix, m_col);

	return b;
}

//��pMatrix������󣬲������ھ���_pMatrix��
bool CMatrix::ContraryMatrix(double *const pMatrix, double *const _pMatrix, const int &dim)
{ 
	bool b = true;

	double *tMatrix = new double[2*dim*dim];
	for (int i=0; i<dim; i++){
		for (int j=0; j<dim; j++)
			tMatrix[i*dim*2+j] = pMatrix[i*dim+j];        
	}
	for (int i=0; i<dim; i++){
		for (int j=dim; j<dim*2; j++)
			tMatrix[i*dim*2+j] = 0.0;
		tMatrix[i*dim*2+dim+i]  = 1.0;        
	}
	//Initialization over!
	for (int i=0; i<dim; i++)//Process Cols
	{
		double base = tMatrix[i*dim*2+i];
		if (fabs(base) < 1E-300){
			cout << endl << "zero is divied!" << endl;
			b = false;
			return b;
		}
		for (int j=0; j<dim; j++)//row
		{
			if (j == i) continue;
			double times = tMatrix[j*dim*2+i]/base;
			for (int k=0; k<dim*2; k++)//col
			{        
				tMatrix[j*dim*2+k] = tMatrix[j*dim*2+k] - times*tMatrix[i*dim*2+k];
			}
		}        
		for (int k=0; k<dim*2; k++){
			tMatrix[i*dim*2+k] /= base;
		}
	}
	for (int i=0; i<dim; i++)
	{
		for (int j=0; j<dim; j++)
			_pMatrix[i*dim+j] = tMatrix[i*dim*2+j+dim];        
	}    
	delete[] tMatrix;

	return b;
}

////////////////////////////////////////////////////////////////