#ifndef PLANT
#define PLANT

class plant
    {
    public:
        plant();

        //��������� ������ ������ ������� �� ������ ��������� ������������ �����������.
        float get_new_out( float control_value );

        float get_current_out() const;

        void set_k( float new_k )
            {
            k = new_k;
            }

        float get_k() const
            {
            return k;
            }

        void set_T( float new_T )
            {
            T = new_T;
            }

        float get_T() const
            {
            return T;
            }

    private:
        float k;
        float T;

        float h;

        float prev_obj_v1;          //���������� �������� ������ ������� ����������.

        float current_obj_value;    //������� �������� ������ ������� ����������.
        
        float prev_control_v1;      //t-1  �������� ������������ �����������.
        float prev_control_v2;      //t-2 �������� ������������ �����������.
        float prev_control_v3;      //t-3 �������� ������������ �����������.
        float prev_control_v4;      //t-4 �������� ������������ �����������.
        float prev_control_v5;      //t-5 �������� ������������ �����������.
    };
#endif // PLANT