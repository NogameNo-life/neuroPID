class plant
    {
    public:
        plant();

        //��������� ������ ������ ������� �� ������ ��������� ������������ �����������.
        double get_new_out( double control_value );

        double get_current_out() const;

        void set_k( double new_k )
            {
            k = new_k;
            }

        double get_k() const
            {
            return k;
            }

    private:
        double k;

        double prev_obj_value;      //���������� �������� ������ ������� ����������.
        double current_obj_value;   //������� �������� ������ ������� ����������.
        double prev_control_value;  //���������� �������� ������������ �����������.
    };