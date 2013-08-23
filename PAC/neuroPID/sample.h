#ifndef SAMPLE_H
#define SAMPLE_H

#include <windows.h>

#include <string>
#include <wchar.h>
//------------------------------------------------------------------------------
/// @brief ��������� ��������� �������.
class i_learn_samples
    {
    public:
        /// <summary>
        /// ����������� � �������� ����������. 
        /// </summary>
        /// <param name="samples_cnt">���������� �������.</param>
        /// <param name="inputs_cnt">���������� ������� ���������� �������.</param>
        /// <param name="outputs_cnt">���������� �������� ���������� �������.</param>
        i_learn_samples( int samples_cnt, int inputs_cnt, int outputs_cnt ): 
            inputs_cnt( inputs_cnt ), outputs_cnt( outputs_cnt ), 
            samples_cnt( samples_cnt )
            {                
            }

        /// <summary>
        /// ��������� ���������� ������� � ��������� �������. 
        /// </summary>
        /// <returns></returns>
        virtual int get_samples_cnt() const;

        /// <summary>
        /// ��������� ������ � �������� �������.
        /// </summary>
        /// <param name="index">����� ������.</param>
        /// <returns> > 0 - �����, 0 - ������. </returns>
        virtual float* get_sample_x( int index ) const = 0;

        /// <summary>
        /// ��������� ���������� �������� � �������� �������.
        /// </summary>
        /// <param name="index">����� ���������� ��������.</param>
        /// <returns> > 0 - ��������� �������� ������, 0 - ������.  </returns>
        virtual float* get_sample_y( int index ) const = 0;

        /// <summary>
        /// ��������� ���������� ������� ���������� �������.
        /// </summary>
        /// <returns></returns>
        virtual int get_inputs_cnt()  const;

        /// <summary>
        /// ��������� ���������� �������� ���������� �������.
        /// </summary>
        /// <returns></returns>
        virtual int get_outputs_cnt() const;

    protected:
        int inputs_cnt;  /// ���������� ������� ���������� �������.
        int outputs_cnt; /// ���������� �������� ���������� �������.

        int samples_cnt; /// ���������� �������.
    };
//------------------------------------------------------------------------------
/// <summary>
///  ��������� �������, ������� �������� � ������� � ����������� ������.
/// </summary>
/// <remarks>
/// �������� ������������ 3 ������. ����� ������� �������� ���:
/// [o - 2, o - 1, o].
/// ��� 
///  o     - ������� �����, 
///  o - 1 - ����� � ���������� ������ ������� - ���� ���� �����,
///  o - 2 - ����� ��� ����� �����.
/// �������� ��� ��������������� ������������ ����������� t1 � t2, �����������
/// ����������� u1. ����� ����� �������� ��������� ������� (������ ���� ����� 3 - 
/// ����� ��� ���� ������� ����������):
///  [t1 - 2, t1 - 1, t1,   t2 - 2, t2 - 1, t2,   u1 - 2, u1 - 1, u1].
/// ��� 
///  t1     - ������� �����������, 
///  t1 - 1 - ����������� � ���������� ������ ������� - ���� ���� �����,
///  t1 - 2 - ����������� ��� ����� �����.
/// ���������� ��������������� t2 � u1.
/// � ������ �������� n ����� �������, ��� ���������� ����� ������ ������
/// ����������:
///  [o - 2, o - 1, o] -> [o - 1, o, o] -> [o - 1, o, o'].
/// ��� ������� ������ ���� ��������������� ��������� �������� e:
/// [e - 2, e - 1, e].
/// ��������� �������� ����� ������ �� �������� ���������� ���������:
/// e = [u + 1, u + 2, q + 1, q + 2]
/// </remarks>
class rt_sample: public i_learn_samples
    {
    public:
        /// <summary>
        /// �������� �������.
        /// </summary>
        /// <param name="samples_cnt"></param>
        /// <param name="in_size">���������� ������.</param>
        /// <param name="in_var_count">���������� ������� ����������.</param>
        /// <param name="out_size">���������� �������.</param>
        /// <param name="out_var_count">���������� �������� ����������.</param>
        /// <param name="max_var_value">������������ �������� ����������, ��� ��������������� �������� � ��������� [0; 1].</param>
        /// <returns></returns>
        rt_sample( int samples_cnt, int in_size, int in_var_count,
            int out_size, int out_var_count, int max_var_value ) throw (...) :
            i_learn_samples( samples_cnt, in_size, out_size ),
            max_var_value ( max_var_value )
            {     
            if ( in_size % in_var_count )
            	{
                char msg[ 200 ];
                _snprintf( msg, sizeof( msg ),
                    "rt_sample::rt_sample() - ������: ����� ������ (%d) ������ ���� ������ ����� ���������� (%d).",
                    in_size, in_var_count );

                throw msg;
            	}
            if ( out_size % out_var_count )
                {
                char msg[ 200 ];
                _snprintf( msg, sizeof( msg ),
                    "rt_sample::rt_sample() - ������: ����� ������� (%d) ������ ���� ������ ����� ���������� (%d).",
                    out_size, out_var_count );

                throw msg;
                }

            x = new float*[ samples_cnt ];
            for ( int i = 0; i < samples_cnt; i++ )
                {
                x[ i ] = new float[ in_size ];
                }

            y = new float*[ samples_cnt ];
            for ( int i = 0; i < samples_cnt; i++ )
                {
                y[ i ] = new float[ out_size ];
                }

            fake_image = new float[ out_size > in_size ? out_size : in_size ];
            }

        //���������� ������������ �������� ����������.
        int get_max_var_value() const
            {
            return max_var_value;
            }

        /// <summary>
        /// ��������� �������� ������ � �������� �������.
        /// </summary>
        /// <param name="index">����� ������ (� ����).</param>
        /// <returns>����� � �������� ������� ��� �������� ��� ������.</returns>
        float* get_sample_x( int index ) const
            {
            if ( index < samples_cnt && index >= 0 )
            	{
                return x[ index ];
            	}
            else
                {
                char msg[ 200 ];
                _snprintf( msg, sizeof( msg ),
                    "rt_sample::get_sample_x(...) - ������: ������ (%d) ������"
                    " ���� ������ ����� ������� (%d).",
                    index, samples_cnt );

                //throw msg;
                }

            return fake_image;
            }

        /// <summary>
        /// ��������� ��������� ������ � �������� �������.
        /// </summary>
        /// <param name="index">����� ������ (� ����).</param>
        /// <returns>����� � �������� ������� ��� �������� ��� ������.</returns>
        float* get_sample_y( int index ) const
            {
            if ( index < samples_cnt && index >= 0 )
                {
                return y[ index ];
                }
            else
                {
                char msg[ 200 ];
                _snprintf( msg, sizeof( msg ),
                    "rt_sample::get_sample_x(...) - ������: ������ (%d) ������ "
                    "���� ������ ����� ������� (%d).",
                    index, samples_cnt );

                //throw msg;
                }

            return fake_image;
            }

        void print()
            {
            }

    private:     

        int in_var_count;
        int out_var_count;

        int max_var_value;
                
        float **x;      ///��������� �����.
        float **y;      ///��������� ������.  

        float *fake_image;
    };
#endif // SAMPLE_H