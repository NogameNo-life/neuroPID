//����� ��������.
//  �������� �������� �������, ������� ������������ ���������� ��������� ����.
#ifndef MLP_H
#define MLP_H

#include "sample.h"

#define printf_ printf
//------------------------------------------------------------------------------
//��������
//  ������������ ���������� (1 ������� ����).
class mlp
    {
    public: 
        enum T
            {
            T_SAMPLE_Y = 1,
            T_ERROR,
            };

        enum LAYERS
            {
            L_INPUT = 0,
            L_HIDDEN,
            L_OUTPUT,
            };

        enum F_ACTIVATION
            {
            F_LINEAR = 0,
            F_SYGMOID,
            };

        //�����������. 
        //���������.
        //   inputs_cnt  - ����� ������;
        //   in_cnt      - ����� �������� � ������� ����;
        //   outputs_cnt - ����� �������.
        //   q           - ����������� ��������������� (����� ������� �� ����,
        //                 ����� ����������).
        mlp( int inputs_cnt, int in_cnt, int outputs_cnt, int q = 1 );

        //������������� ������������� ��������� �������.
        void init_weights();

        //��������� ��������� ���� �������� ��� ������� �����������.
        //���������.
        //   � - �������� ������ ��������;
        //   sample - ��������� �������;
        //   max_iteration_cnt - ������������ ����� ��������. �������� ���������������
        //      ��� ��� ����������.
        //������������ ��������.
        //   0 - OK;
        // < 0 - ������.        
        int static_learn( float e, i_learn_samples *sample, int max_iteration_cnt,
            bool is_err = false );

        //������������ �������� �������.
        //���������.
        //   cnt   - ������� �������� ���������������;
        //   x_in  - ��������� ��������;
        //   y_out - ������ ���������������� ��������.
        //������������ ��������.
        //   0 - OK;
        // < 0 - ������.        
        int prognose( int cnt, float *x_in, float *y_out );

        int prognose( int cnt, float k, float data[] );

        int save_prognose_to_file( char *file_name );

        //������������ �������� �������.
        //���������.
        //   cnt   - ������� �������� ���������������;
        //   x_in  - ��������� ��������;
        //   out_col_n - ����� �������, ���� ���������� �������� ��������.
        //������������ ��������.
        //   0 - OK;
        // < 0 - ������.        
        int prognose( int cnt, float **x_in, int out_col_n );

        //���������� ������������� � ���� � ��������� ����.
        //���������.
        //   file_name - ��� �����.
        //������������ ��������.
        //   0 - OK;
        // < 0 - ������.        
        int save_to_file( char *file_name );

        //���������� ������������� �� ����� � ��������� ����.
        //���������.
        //   file_name - ��� �����.
        //������������ ��������.
        //   0 - OK;
        // < 0 - ������.        
        int load_from_file( char *file_name );

        //���������� �������� � ���� � ��������� ����.
        //���������.
        //   file_name - ��� �����;
        //   y_out     - ������ �� ���������� ��������.
        //������������ ��������.
        //   0 - OK;
        // < 0 - ������.        
        int save_prognose_to_file( char *file_name, float *y_out, int cnt );

        //���������� �������� � ���� � ��������� ����.
        //���������.
        //   file_name - ��� �����;
        //   y_out     - ������, 3-� �������� - �������.
        //������������ ��������.
        //   0 - OK;
        // < 0 - ������.        
        int save_prognose_to_file( char *file_name, float **y_out, 
            int cnt, int column_cnt, int column_window_size,
            int factor_k );
                     
        //����� �� ������� ������������� �����������.
        void print();

        //�������� �������� ������� �� ��� ��������� �������� ������.
        //���������.
        //   x_in  - ������� ��� ���������������. 
        //������������ ��������.
        //   �������������� �����.
        float* solve_out( float *x_in );
        float* solve_out( float **x_in );

        int get_q() const
            {
            return q;
            }

    private:
        //���������� ����� �������� ��������.
        //���������.
        //   sample_x           - ������� ��� ��������; 
        //   sample_y_or_error  - ��������� ����� (������ ���������������); 
        //   type               - ��� �������� ( �� ������ ���������� �������� ��� ������); 
        //   E_k                - ������������ ������������������ ������; 
        //   err                - ������� ��� �������� ������ �������� ����; 
        //   is_solve_net_out   - ������������� �� ����� ����.
        void learn_iteration( float *sample_x, float *sample_y_or_error, 
            char type, float &E_k, float **err, char is_solve_net_out );

    
        int inputs_cnt;     //���������� ������.
        int hidden_cnt;     //���������� �������� � ������� ����.
        int outputs_cnt;    //���������� �������.

        float ***w;     //������� ������������.
        float **T;      //��������� ��������.

        float *x;       //������� ��������.
        float *y_hidden;//�������� �������� ��� �������� ����.  
        float *y;       //�������� ��������.  

        float *y_prognose; //���������� ��������.
        int    y_prognose_cnt;

        int q;  //����������� ���������������.

        //�������� �������� ������� ���� �� ��� ��������� �������� ������.
        float* solve_layer_out( float *x_in, int layer_type, int activation_f_type );
        float* solve_layer_out( float **x_in, int layer_type, int activation_f_type );

        enum VAL_RANGE
            {
            VR_MIN = -20,
            VR_MAX = 20,
            };
         
        static const int MAX_BUFF_SIZE;


#ifdef WIN32
        //���������� ������������� � ����� � ��������� ����.
        //���������.
        //   stream - ��������� �� ������ ���� char.
        //������������ ��������.
        //   0 - OK;
        // < 0 - ������.        
        int save_to_stream( char *stream );

        //���������� ������������� �� ������ � ��������� ����.
        //���������.
        //   stream - ��������� �� ������ ���� char.
        //������������ ��������.
        //   0 - OK;
        // < 0 - ������.        
        int load_from_stream( char *stream );
#endif // WIN32
    };

#endif // MLP_H