#include <iostream>
#include <vector>
#include <random> // для std::mt19937
#include <ctime> 
#include <algorithm>

#define _Check true

using namespace std;


class Homework
{
    // Реализация FIFO
    private:                                        //  Функции вне видимости при инициализации 
    vector<unsigned char> _Data_Vector;             //  Вектор для хранения данных
    struct _MyData                                  //  Структура для хранения данных о хранящихся пакетах
    {
        unsigned int _DataCount;                    //  Длина данных
        unsigned int _PacketId;                     //  Пакетный ID
    };  
    _MyData _Packet_Info;                           //  Инициализация стурктуры для запонения вектора
    vector<_MyData> _PacketInfo;                    //  Инициализаця вектора для хранения данных о хранящихся пакетах
    public:
    // будем считать, что использование шаблонов в данном случае не допускается, поскольку вид функции уже дан

    bool Push(unsigned char *_data, unsigned int _dataCount, unsigned int _packetId)
    {
        int Counter = 0;                            //  Счетчик для проверки длины передаваемого пакета                               
        while(*_data != '\0')
        {   
            _Data_Vector.push_back(*_data);         //  Сохраняем значение 8 bit значение в последующей ячейке
            _data++;                                //  Переходим на следующее значение 
            Counter++;                          
        }
        if(Counter != _dataCount)                   // Проверка на соотвествие
        {   
            _Data_Vector.erase(_Data_Vector.cend()-Counter-1, _Data_Vector.cend()-1);       //  В случае несоотвествия затираем записанную область
            return false;                                                                   //  Возвращаем ошибку
        }
        _Packet_Info._DataCount = _dataCount; _Packet_Info._PacketId = _packetId;           //  Сохраняем данные о хранящемся пакете данных
        _PacketInfo.push_back(_Packet_Info); 
        _Packet_Info._DataCount = 0;
        _Packet_Info._PacketId = 0;
        return true;                                                                        //  Возвращаем значения успеха сохранения
    }
    
    bool Pop(unsigned char *_buffer, unsigned int _bufferSize, unsigned int &_dataCount, unsigned int &_packetId)
    {   
        if(_PacketInfo[0]._DataCount > _bufferSize) return false;        //    Проверка хватит ли буфера для передачи пакета без потери данных
        if(_Data_Vector.size() == 0)  return false;                      //    Проверка на случай пустого вектора
        for(int i = 0; i < _PacketInfo[0]._DataCount; i++)   _buffer[i] = _Data_Vector[i];  // Записываем данные в буфер

        _dataCount = _PacketInfo[0]._DataCount;    
        _packetId = _PacketInfo[0]._PacketId;
        _Data_Vector.erase(_Data_Vector.cbegin(), _Data_Vector.cbegin()+_PacketInfo[0]._DataCount); // Очищаем ненужные данные, которые уже ушли из FIFO
        _PacketInfo.erase(_PacketInfo.cbegin());                                                    //
        return true;
    }

    bool Clear_buffer()
    {
        _PacketInfo.clear();
        _Data_Vector.clear();
        return true;
    }
};

int main()
{
    // Переменные
    unsigned char _buffer_1[100], _buffer_2[100] ;
    unsigned int _bufferSize_1 = 100, _bufferSize_2 = 100;
    unsigned int _dataCount_1 = 0 , _dataCount_2 = 0;
    unsigned int _packetId_1 = 0, _packetId_2 = 0;
    unsigned char _stream_1[] = "Gigobit Ethernet not found 404";
    unsigned char _stream_2[] = "Gigobit Ethernet ENABLE";
    unsigned char _stream_3[] = "My name is NOT FOUND";
    // Объявления класса
    Homework _class;
    //  Вливаем данные
    _class.Push(_stream_2, sizeof(_stream_2)-1, 200);
    _class.Push(_stream_1, sizeof(_stream_1)-2, 100);
    _class.Push(_stream_3, sizeof(_stream_3)-1, 1);
    _class.Pop(_buffer_1, _bufferSize_1, _dataCount_1, _packetId_1);
    _class.Pop(_buffer_2, _bufferSize_2, _dataCount_2, _packetId_2);
    return 0;
}
