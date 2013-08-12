#ifndef _PID_H
#define _PID_H

class PID 
    { 
    enum STATES 
        {
        STATE_OFF,
        STATE_ON,  
        };

    double uk_1;
    double ek_1;
    double ek_2;
    double q0;
    double q1;
    double q2;
    double Uk;
    double dUk;
    unsigned long startTime;
    unsigned long lastTime;

    char prevManualMode;

    char isDownToInAccelMode;  //���� �� ��� ������ ���������� ���������, � �� ����������� �������� ��������.

    public:
        double par[ 20 ];
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
        double Eval( double currentValue, int deltaSign = 1 );
        void  Reset();
        void  Reset( double new_uk_1 );
        void  SetZ ( double newZ );        //���������� ����� ������� ���.
    };
#endif