# sort-conv-calib
排序算法
float convert_Q2V(float _dn, float qn);
float convert_V2Q(float _dn, float vn);
float convert_Auto_N2n(float flow, uint16_t out_s, uint32_t press, float temp);
float convert_Auto_n2N(float flow, uint16_t out_s, uint32_t press, float temp);

void _Float2ByteArray(float data, uint8_t* array);
void _ByteArray2Float(uint8_t* array, float* data);

void Current_4mACalibration(float Ivalue, uint16_t* v4, uint16_t v20);
void Current_20mACalibration(float Ivalue, uint16_t v4, uint16_t* v20);

类型转换



电流校准
