# sort-conv-calib
排序算法
void TT_Sort(float data, SORT_ARRRY* sArray, uint16_t maxNum);
每次运行把新数插入排序数组，同时将最早的数据剔除，排序数组从小到大排序
运行速度不稳定，最短为1，最长为N

类型转换
流量流速转换
float convert_Q2V(float _dn, float qn);
float convert_V2Q(float _dn, float vn);
标况工况转换
float convert_Auto_N2n(float flow, uint16_t out_s, uint32_t press, float temp);
float convert_Auto_n2N(float flow, uint16_t out_s, uint32_t press, float temp);
浮点数和字节数组转换
void _Float2ByteArray(float data, uint8_t* array);
void _ByteArray2Float(uint8_t* array, float* data);

电流校准
void Current_4mACalibration(float Ivalue, uint16_t* v4, uint16_t v20);
void Current_20mACalibration(float Ivalue, uint16_t v4, uint16_t* v20);
使用时必须先进行4mA校准，再进行20mA校准
