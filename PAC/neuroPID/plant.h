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

    private:
        float k;

        float prev_obj_value;      //���������� �������� ������ ������� ����������.
        float current_obj_value;   //������� �������� ������ ������� ����������.
        float prev_control_value;  //���������� �������� ������������ �����������.
    };
#endif // PLANT