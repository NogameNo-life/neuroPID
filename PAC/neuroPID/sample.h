#ifndef SAMPLE_H
#define SAMPLE_H

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
        virtual float* get_sample_x( int index ) = 0;

        /// <summary>
        /// ��������� ���������� �������� � �������� �������.
        /// </summary>
        /// <param name="index">����� ���������� ��������.</param>
        /// <returns> > 0 - ��������� �������� ������, 0 - ������.  </returns>
        virtual float* get_sample_y( int index ) = 0;

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
        /// <param name="in_sample_size">������ ���� (����� ��� ���� ����������)</param>
        /// <param name="in_variables_count">���������� ����������.</param>
        /// <param name="outputs_cnt"></param>
        /// <param name="max_var_value">������������ �������� ����������, ��� ��������������� �������� � ��������� [0; 1].</param>
        /// <returns></returns>
        rt_sample( int samples_cnt, int in_sample_size, int in_variables_count,
            int outputs_cnt, int max_var_value ):
            i_learn_samples( samples_cnt, inputs_cnt, outputs_cnt )
            {            
            }

        //���������� ������������ �������� ����������.
        int get_max_var_value() const
            {
            return max_var_value;
            }

        //���������� ������� � �������� �������.
        //���������.
        //   index   - ����� ��������� �������;
        //   samle_x - ��������� �������� ������.
        //   samle_y - ��������� �������� �������.
        //������������ ��������.
        // > 0 - ��������� �� ������ �������;
        //   0 - ������.        
        float* get_sample_x( int index ) const
            {
            }

        float* get_sample_y( int index ) const
            {
            }

        void print()
            {
            }

    private:     

        int column_cnt;
        int row_cnt;
        int max_var_value;

        float **data;   ///��������� ��������
        float **x;      ///��������� �����.
        float **y;      ///��������� ������.  
    };
#endif // SAMPLE_H