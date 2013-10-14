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
///  ��������� �������, ������� �������� � ������� �� �����.
/// </summary>
/// <remarks>
/// ���� ����� ��������� ���������:
///   ����� ���������� (�������� ������);
///   ����� ������ (����� ������);
///   ����. ��������, �� ���� ����� �������� �����, ����� �������� �������� < 1;
///   ����� ���� ������ � ��������.
/// ������, sample.txt:
/// 3
/// 5
/// 200
/// 122 134 234 
/// 102 134  34 
/// 122 134   9 
/// 102 234  34 
/// </remarks>
class stored_sample: public i_learn_samples
    {
    public:

        //���������� ����������� ��������������� �������� �������.
        int get_factor_k() const;

        //���������� ������ ���� ��� ���������� �������.
        int get_column_window_size() const;

        //�����������.
        stored_sample();

        //���������� ��������� �������. ����� �� �� ������ ����� ��������������
        //��������.
        float** get_sample_x();

        //���������� ������� � �������� �������.
        //���������.
        //   index   - ����� ��������� �������;
        //   samle_x - ��������� �������� ������.
        //   samle_y - ��������� �������� �������.
        //������������ ��������.
        // > 0 - ��������� �� ������ �������;
        //   0 - ������.        
        float* get_sample_x( int index ) const;
        float* get_sample_y( int index ) const;

        /// <summary>
        /// �������� ��������� �������.
        /// </summary>
        /// <param name="window_size">������ ����.</param>
        /// <param name="learn_samples_count">���������� �������.</param>
        /// <param name="exclude_every_i">������������ ������ i-� ������ ��� ������������ ��������� ������. ���� ����� 1, ������������ ��� ������.</param>
        /// <param name="etalon_column_number"></param>
        /// <returns></returns>
        int create_learn_sample( int window_size, int learn_samples_count = -1, int exclude_every_i = 1, int etalon_column_number = 0, int etalon_columns_cnt = 1, bool exclude_etalons = false );

        void print();

        int load_from_file( char *file_name );
        int load_from_file( char *file_name, char is_ignore_first_column );
        int save_to_file( char *file_name );

    private:        
        int column_cnt;
        int row_cnt;
        int factor_k;

        float **data;   //��������� ��������
        float **x;      //��������� �����.
        float **y;      //��������� ������.  
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
        rt_sample( int samples_cnt, int in_size, int in_var_count,
            int out_size, int out_var_count, int max_var_value ) throw (...) :
        i_learn_samples( samples_cnt, in_size, out_size ),
            max_var_value ( max_var_value ),
            in_var_count( in_var_count ),
            out_var_count( out_var_count )
            {     
            if ( in_size % in_var_count )
                {
                char msg[ 200 ];
                _snprintf( msg, sizeof( msg ),
                    "rt_sample::rt_sample() - ������: ����� ������ (%d) ������ "
                    "���� ������ ����� ���������� (%d).",
                    in_size, in_var_count );

                throw msg;
                }
            if ( out_size % out_var_count )
                {
                char msg[ 200 ];
                _snprintf( msg, sizeof( msg ),
                    "rt_sample::rt_sample() - ������: ����� ������� (%d) ������ "
                    "���� ������ ����� ���������� (%d).",
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

            for ( int i = 0; i < samples_cnt; i++ )
                {
                for ( int j = 0; j < inputs_cnt; j++ )
                    {
                    x[ i ][ j ] = 0;
                    }                
                }

            for ( int i = 0; i < samples_cnt; i++ )
                {
                for ( int j = 0; j < outputs_cnt; j++ )
                    {
                    y[ i ][ j ] = 0;
                    }                
                }

            fake_image = new float[ out_size > in_size ? out_size : in_size ];
            }

        /// <summary>
        /// ��������� ������������� �������� ����������.
        /// </summary>
        int get_max_var_value() const
            {
            return max_var_value;
            }

        /// <summary>
        /// ����� ����� ����������� ������ ������.
        /// </summary>
        void shift_images()
            {
            for ( int i = 0; i < samples_cnt - 1; i++ )
                {
                for ( int j = 0; j < inputs_cnt; j++ )
                	{
                    x[ i ][ j ] = x[ i + 1 ][ j ];
                	}                
                }

            for ( int i = 0; i < samples_cnt - 1; i++ )
                {
                for ( int j = 0; j < outputs_cnt; j++ )
                    {
                    y[ i ][ j ] = y[ i + 1 ][ j ];
                    }                
                }
            }

        /// <summary>
        /// ���������� ������ �������� ������� ����������.
        /// </summary>
        void add_new_val_to_in_image( int var_n, float val )
            {
            static int var_total_size = inputs_cnt / in_var_count;

            int start_idx = var_n * var_total_size;
            int finish_idx = start_idx + var_total_size - 1;

            if ( start_idx >= inputs_cnt )
            	{
#ifdef _DEBUG
                printf( "rt_sample::add_new_val_to_in_image(...) - "
                    "������: ����� �� �������� (%d).",
                    var_n );
#endif // _DEBUG
            	}

            for ( int i = start_idx; i < finish_idx; i++ )
            	{
                x[ samples_cnt - 1 ][ i ] = x[ samples_cnt - 1 ][ i + 1 ];
            	}
            
            x[ samples_cnt - 1 ][ finish_idx ] = val /*/ max_var_value*/;
            }

        /// <summary>
        /// ���������� ������ �������� �������� ����������.
        /// </summary>
        void add_new_val_to_out_image( int var_n, float val )
            {
            static int var_total_size = outputs_cnt / out_var_count;

            int start_idx = var_n * var_total_size;
            int finish_idx = start_idx + var_total_size - 1;

            if ( start_idx >= inputs_cnt )
                {
#ifdef _DEBUG
                printf( "rt_sample::add_new_val_to_in_image(...) - "
                    "������: ����� �� �������� (%d).",
                    var_n );
#endif // _DEBUG
                }
            
            for ( int i = start_idx; i < finish_idx; i++ )
                {
                y[ samples_cnt - 1 ][ i ] = y[ samples_cnt - 1 ][ i + 1 ];
                }

            y[ samples_cnt - 1 ][ finish_idx ] = val/* / max_var_value*/;
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
        /// ��������� ���������� �������� ������.
        /// </summary>
        /// <returns>��������� �����.</returns>
        float* get_last_sample_x() const
            {
            return x[ samples_cnt - 1 ];
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
            for ( int i = 0; i < samples_cnt; i++ )
                {
                printf( "%3d: [", i );
                for ( int j = 0; j < inputs_cnt; j++ )
                    {
                    printf( "%.2f ", x[ i ][ j ] );
                    }
                printf( "] -> [" );

                for ( int j = 0; j < outputs_cnt; j++ )
                    {
                    printf( "%.2f ", y[ i ][ j ] );
                    }     
                printf( "]\n" );
                }   
            printf( "\n");
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