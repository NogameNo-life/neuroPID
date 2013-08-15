//����� ��������.
//  �������� �������� �������, ������� ������������ ���������� ��������� ����.
#ifndef MLP_H
#define MLP_H

#ifdef WIN32
#define printf_ printf
//---------------------------------------------------------------------------------------
//��������
//  �����, ������� ������������ ��������� ��������� �������.
class i_learn_samples
    {
    public:
        //���������� ���������� ��������� � ��������� �������.    
        //������������ ��������.
        //   ���������� ��������� � ��������� �������.        
        virtual int get_samples_cnt() const;

        //���������� ������� � �������� �������.
        //���������.
        //   index   - ����� ��������� �������;
        //   samle_x - ��������� �������� ������.
        //   samle_y - ��������� �������� �������.
        //������������ ��������.
        // > 0 - OK;
        // <=0 - ������.        
        virtual float* get_sample_x( int index ) = 0;
        virtual float* get_sample_y( int index ) = 0;

        //��������� ���������� �������.
        virtual int get_inputs_cnt()  const;
        virtual int get_outputs_cnt() const;

        //���������� ������������� �� ����� � ��������� ����.
        //���������.
        //   file_name - ��� �����.
        //������������ ��������.
        //   0 - OK;
        // < 0 - ������.        
        virtual int load_from_file( char *file_name ) = 0;

        //���������� ������������� � ���� � ��������� ����.
        //���������.
        //   file_name - ��� �����.
        //������������ ��������.
        //   0 - OK;
        // < 0 - ������.        
        virtual int save_to_file( char *file_name ) = 0;

    protected:
        int window_size;
        int samples_cnt;
    };
//---------------------------------------------------------------------------------------
//��������
//  �����, ������� ������������ ��������� ��������� ������� ��� ��������� �������.
class function_sample: public i_learn_samples
    {
    public:
        //�����������.
        //���������.
        //   x_start        - ��������� �������� �;
        //   x_end          - �������� �������� �;
        //   dx             - �������� ���� dx;
        //   window_size    - ���������� ��������� � ����.
        function_sample( float x_start, float x_end, float dx, int window_size );

        function_sample()
            {
            }

        //���������� ������� � �������� �������.
        //���������.
        //   index   - ����� ��������� �������;
        //   samle_x - ��������� �������� ������.
        //   samle_y - ��������� �������� �������.
        //������������ ��������.
        // > 0 - ��������� �� ������ �������;
        //   0 - ������.        
        float* get_sample_x( int index );
        float* get_sample_y( int index );

        void print();

        int load_from_file( char *file_name );
        int save_to_file( char *file_name );

    protected:
        float **x; //��������� �����.
        float **y; //��������� ������.
    };
//---------------------------------------------------------------------------------------
//��������
//  �����, ������� ������������ ��������� ��������� ������� ��� ��������� �������.
class function_sample_with_time: public function_sample
    {
    public:
        //�����������.
        //���������.
        //   x_start        - ��������� �������� �;
        //   x_end          - �������� �������� �;
        //   dx             - �������� ���� dx;
        //   window_size    - ���������� ��������� � ����.
        function_sample_with_time( float x_start, float x_end, float dx, int window_size );
    };
//---------------------------------------------------------------------------------------
//��������
//  �����, ������� ������������ ��������� �������, ������� ����������� �� �����. ���� �����
//  ��������� ���������:
//    ����� ���������� (�������� ������);
//    ����� ������ (����� ������);
//    ����. ��������, �� ���� ����� �������� �����, ����� �������� �������� < 1;
//    ����� ���� ������ � ��������.
//  ������, sample.txt:
//  3
//  5
//  200
//  122 134 234 
//  102 134  34 
//  122 134   9 
//  102 234  34 
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
        float* get_sample_x( int index );
        float* get_sample_y( int index );

        //������� ��������� �������.
        //���������.
        //   window_size - ������ ����;
        //   exclude_every_i  - ������������ ������ i-� ������ ��� ������������
        //      ��������� ������. ���� ����� 1, ������������ ��� ������.
        int create_learn_sample( int window_size, int learn_samples_count = -1, 
            int exclude_every_i = 1, int etalon_column_number = 0 );

        void print();

        int load_from_file( char *file_name );
        int load_from_file( char *file_name, char is_ignore_first_column );
        int save_to_file( char *file_name );

    private:        
        int column_cnt;
        int row_cnt;
        int factor_k;

        float **data;   //��������� ��������
        float **x;      //���������� �����.
        float **y;      //���������� ������.  
    };
//---------------------------------------------------------------------------------------
//��������
//  �����, ������� ������������ ��������� ��������� ������� ��� �������� �������.
class test_sample: public i_learn_samples
    {
    public:
        //�����������.
        //���������.
        //   x_start        - ��������� �������� �;
        //   x_end          - �������� �������� �;
        //   dx             - �������� ���� dx;
        //   window_size    - ���������� ��������� � ����.
        test_sample( float x_start, float x_end, float dx, int window_size );

        //���������� ������� � �������� �������.
        //���������.
        //   index   - ����� ��������� �������;
        //   samle_x - ��������� �������� ������.
        //   samle_y - ��������� �������� �������.
        //������������ ��������.
        // > 0 - ��������� �� ������ �������;
        //   0 - ������.        
        float* get_sample_x( int index )
            {            
            if ( index >= samples_cnt )
                {
                return 0;
                }

            return x[ index ];
            }

        float* get_sample_y( int index )
            {
            if ( index >= samples_cnt )
                {
                return 0;
                }

            return y[ index ] ;
            }

        void print() {}

        int load_from_file( char *file_name )
            {
            return 0;
            }

        int save_to_file( char *file_name )
            {
            return 0;
            }

        int get_factor_k() const
            {
            return 1;
            }
        
        int get_column_window_size() const
            {
            return 1;
            }

        float** get_sample_x()
            {
            return x;
            }

    private:
        float **x; //��������� �����.
        float **y; //��������� ������.
    };
//---------------------------------------------------------------------------------------
//��������
//  ����������� ���������� (��� �������� ����).
class slp  
    {
    public: 
        //�����������. 
        //���������.
        //   inputs_cnt  - ����� ������;
        //   outputs_cnt - ����� ������.
        slp( int inputs_cnt, int outputs_cnt );

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
        int learn( float e, i_learn_samples *sample, int max_iteration_cnt );

        //����� �� ������� ������������� �����������.
        void print();

        //������������ �������� �������.
        //���������.
        //   cnt   - ������� �������� ���������������;
        //   x_in  - ��������� ��������;
        //   y_out - ������ ����������������� ��������.
        //������������ ��������.
        //   0 - OK;
        // < 0 - ������.        
        int prognose( int cnt, float *x_in, float *y_out );

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

    private:
        int inputs_cnt; //���������� ������.
        int outputs_cnt;//���������� �������.

        float **w;      //������� ������������.
        float *T;       //��������� ��������.

        float *x;       //������� ��������.
        float *y;       //�������� ��������.  

        //�������� �������� ������� �� ��� ��������� �������� ������.
        float* solve_out( float *x_in );

        static const int MAX_BUFF_SIZE;

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
    };
#endif // WIN32

#ifdef PAC
#define printf_ Print
#endif // PAC
//---------------------------------------------------------------------------------------
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
#ifdef PAC 
        //����������� �������� ������� �� ������ �����.
        mlp( char *filename );

        //���������� ���� �� ��������� �� ������ �������� �� �����.
        int set_default_weight( );
#endif // PAC

#ifdef WIN32
        //�����������. 
        //���������.
        //   inputs_cnt  - ����� ������;
        //   in_cnt      - ����� �������� � ������� ����;
        //   outputs_cnt - ����� �������.
        mlp( int inputs_cnt, int in_cnt, int outputs_cnt );

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
        int static_learn( float e, i_learn_samples *sample, int max_iteration_cnt );

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
#endif // WIN32
                     
        //����� �� ������� ������������� �����������.
        void print();

        //�������� �������� ������� �� ��� ��������� �������� ������.
        //���������.
        //   x_in  - ������� ��� ���������������. 
        //������������ ��������.
        //   �������������� �����.
        float* solve_out( float *x_in );

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

    private:
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

        //�������� �������� ������� ���� �� ��� ��������� �������� ������.
        float* solve_layer_out( float *x_in, int layer_type, int activation_f_type );

        enum VAL_RANGE
            {
            VR_MIN = -20,
            VR_MAX = 20,
            };
         
        static const int MAX_BUFF_SIZE;

#ifdef PAC
        char mlp_filename[ 13 ];    //���� � ��������� ���������.
#endif // PAC

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
//---------------------------------------------------------------------------------------
#ifdef PAC
//��������
//�����, ��������������� ��� ���������� ������ � ������ � �������� ��������� �������.
//����� �������� ��������� �������, �������� ��� ��������������� ������������ �����������
//t1 � t2, ����������� ����������� u1. ����� ����� �������� ��������� ������� (������ ����
//����� 3): [ t1 - 2, t1 - 1, t1,   t2 - 2, t2 - 1, t2,   u1 - 2, u1 - 1, u1 ]. ��� 
//t1     - ������� �����������, 
//t1 - 1 - ����������� � ���������� ������ ������� - ���� ���� �����,
//t1 - 2 - ����������� ��� ����� �����.
//���������� ��������������� t2 � u1.
class MLP_sample
    {
    public:
        //�����������.
        //���������.
        //   window_size     - ������ ���� (����� ��� ���� ����������);
        //   variables_count - ���������� ����������;
        //   max_var_value   - ������������ �������� ����������,
        //                     ��� ��������������� �������� � ��������� [ 0; 1 ].
        MLP_sample( int window_size, int variables_count, int max_var_value );

        //���������� ������, �� ��������� ������� �������� �������.
        float* get_sample_for_prognose();

        //���������� ���������� ������, �� ��������� ������� �������� �������.
        float* get_prev_sample_for_prognose();

        //��������� ����� ������ � ������� ��� ���������������, ��� ����
        //�������� ������ � �������.
        //���������.
        //   variable_number - ����� ����������, ��� ������� ����������� ������;
        //   value           - ����������� ��������.
        //������������ ��������.
        //   0 - OK;
        // < 0 - ������. 
        int add_new_data( int variable_number, float value );

        //���������� ������������ �������� ����������.
        int get_max_var_value() const;

#ifdef DEBUG
        void print();
#endif // DEBUG

    private:
        int     variables_count;    //���������� ����������, ������� �������� �������.
        float   *data;              //������, ���������� �������. 

        int     window_size;        //������ ���� (����� ��� ���� ����������).
        int     max_var_value;      //������������ �������� ����������,
                                    //��� ��������������� �������� � ��������� [ 0; 1 ].
    };
//---------------------------------------------------------------------------------------
////��������
////  ���������������.
//class n_controller
//    {
//    public:
//        TParams *par;        
//        enum PARAM 
//            {
//            PAR_Z,            //0 ��������� ��������.
//            PAR_dt,           //1 �������� �������
//            PAR_dmax,         //2 �ax �������� ������� ��������.
//            PAR_dmin,         //3 �in �������� ������� ��������.
//            PAR_AccelTime,    //4 ����� ������ �� ����� �������������.
//            PAR_IsManualMode, //5 ������ �����.
//            PAR_UManual,      //6 �������� ������ �������� ��������� �������.
//            PAR_Uk,           //7 ����� ���.
//            };         
//        enum WORK_PARAMS 
//            {
//            WPAR_Uk,          //0 ����� ���-����������.
//            WPAR_Z,           //1 ��������� �������� ���.
//            };
//
//        //�����������. ������� ��������� ������������ �� ������ �������� �� �����.
//        //���������.
//        //   par        - ��������� �� ���������;
//        //   file_name  - ������ � ������ �����, ����������� ��������� ������������;
//        n_controller( TParams* par, char file_name = "n_contr.txt",
//            int startParamIndex = 0, int startWorkParamsIndex = 8 );
//        //~n_controller(); 
//
//        void  On( char isDownToInAccelMode = 0 );
//        void  Off();
//
//        float Eval( float currentValue, int deltaSign = 1 );
//        void  Reset( float new_uk_1 = 0 );
//
//        void  SetZ ( float newZ );        //���������� ����� ������� ���.
//
//    private:
//        mlp *n_control;         //���������������.
//        mlp *n_emulator;        //�������������.
//
//        enum STATES 
//            {
//            ST_OFF,
//            ST_ON,  
//            };
//        int state;
//
//        int startParamIndex;  
//        int startWorkParamsIndex;
//
//        unsigned long startTime;
//        unsigned long lastTime;
//
//        char prevManualMode;
//
//        char isDownToInAccelMode;  //���� �� ��� ������ ���������� ���������, � �� ����������� �������� ��������.
//    };
#endif // PAC

#endif // MLP_H