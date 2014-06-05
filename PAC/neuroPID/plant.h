#ifndef PLANT
#define PLANT

#include "vector"

class plant
    {
    public:
        plant( float h, int z, float U );

        //��������� ������ ������ ������� �� ������ ��������� ������������ �����������.
        float get_new_out( float control_value );

        float get_current_out() const;
        float get_current_control_v() const;

        void set_k1( float new_k1 )
            {
            k1 = new_k1;
            }

        float get_k1() const
            {
            return k1;
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
        enum CONSTANTS
            {
            Z = 3,
            };

        float k1;
        float K;
        float T;

        float U;                //������������ �������� ������������ �����������.
        float h;
        int z;                  //��������.

        float previous_obj_v1;  //���������� �������� ������ ������� ����������.
        float current_obj_v;    //������� �������� ������ ������� ����������.
        
        std::vector< float > prev_control; //t-1  �������� ������������ �����������.   
    };
#endif // PLANT