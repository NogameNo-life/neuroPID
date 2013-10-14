#ifndef _PID_H
#define _PID_H

class PID 
    { 
    enum STATES 
        {
        STATE_OFF,
        STATE_ON,  
        };

    float uk_1;
    float ek_1;
    float ek_2;
    float q0;
    float q1;
    float q2;
    float Uk;
    float dUk;
    unsigned long startTime;
    unsigned long lastTime;

    char prevManualMode;

    char isDownToInAccelMode;  //���� �� ��� ������ ���������� ���������, � �� ����������� �������� ��������.

    public:
        float par[ 20 ];
        int state;

        int startParamIndex;  
        enum PARAM 
            {
            PAR_Z,            //0 ��������� ��������.
            PAR_k,            //1 �������� k.
            PAR_Ti,           //2 �������� Ti.
            PAR_Td,           //3 �������� Td.
            PAR_dt,           //4 �������� �������
            PAR_dmax,         //5 �ax �������� ������� ��������.
            PAR_dmin,         //6 �in �������� ������� ��������.
            PAR_AccelTime,    //7 ����� ������ �� ����� �������������.
            PAR_IsManualMode, //8 ������ �����.
            PAR_UManual,      //9 �������� ������ �������� ��������� �������.
            PAR_Uk,           //10 ����� ���.
            }; 

        int startWorkParamsIndex;
        enum WORK_PARAMS 
            {
            WPAR_Uk,          //1 ����� ���-����������.
            WPAR_Z,           //2 ��������� �������� ���.
            };

        PID( int startParamIndex = 0, int startWorkParamsIndex = 10 );
        ~PID(); 

        void  On( char isDownToInAccelMode = 0 );
        void  Off();
        float Eval( float currentValue, int deltaSign = 1 );
        void  Reset();
        void  Reset( float new_uk_1 );
        void  SetZ ( float newZ );        //���������� ����� ������� ���.

        float get_z() const
            {
            return par[ startParamIndex + PAR_Z ];
            }

        float get_p() const
            {
            return par[ startParamIndex + PAR_k ];
            }

        float get_i() const
            {
            return par[ startParamIndex + PAR_Ti ];
            }

        float get_d() const
            {
            return par[ startParamIndex + PAR_Td ];
            }

        void set_p( float p ) 
            {
            par[ startParamIndex + PAR_k ] = p;
            }
        
        void set_i( float i ) 
            {
            par[ startParamIndex + PAR_Ti ] = i;
            }

        void set_d( float d ) 
            {
            par[ startParamIndex + PAR_Td ] = d;
            }
    };
#endif