// Компилятор GCC
// Не рекомендуется ошибаться в написании длины передаваемого массива, защитный механизм не отрабатывает из-за ошибок во время компиляции
// Добавление последующего массива в список можно было бы делать через создание и добавление ссылки на новый список, но хотелось поэкспеиментировать, получилась, если честно, каша
#include<stdio.h>
#include<stdlib.h>
#include <time.h>
#include <stdbool.h>

#define _Check true

using namespace std;


class Homework
{
    // Реализация FIFO
    private:   
    struct _Node
    {
        unsigned char _Bit;
        unsigned int _PacketId;
        unsigned int _DataCount;
        struct _Node *_Next;
    } _Spisok;
    struct _Node *root = 0;

    struct _Node *_List_filling(unsigned char *_data, unsigned int _dataCount, unsigned int _packetId){
        struct _Node *head;
        head = (struct _Node*)malloc(sizeof(struct _Node));
        struct _Node *memory = head;
        int Counter = 0;      
        head->_DataCount = _dataCount;
        head->_PacketId = _packetId;                                                  
        while(*_data != '\0')
        {   
            head->_Bit = *_data;
            head->_Next = (struct _Node*)malloc(sizeof(struct _Node));
            head = head->_Next;
            _data++;                                
            Counter++;                          
        }
        if(Counter != _dataCount) {
            free(memory);
            memory = 0;
        }
        return memory;
    }

    struct _Node * _Push_front(struct _Node *head, unsigned char *_data, unsigned int _dataCount, unsigned int _packetId, bool &Error){
        struct _Node *memory = head;
        if(head != 0)
        {
            while (head->_Next != 0)
            {
                head = head->_Next;
            }
        }
        head->_Next = (struct _Node*)malloc(sizeof(struct _Node));
        // head = head->_Next; Не работает должным образом, при отсутвии действия и использования перед этими шагами _Delete_front(), записывает в последнюю ячейку, при наличии строки возникает еще один лишний элемент списка, в который происходит запись
        int Counter = 0;      
        head->_DataCount = _dataCount;
        head->_PacketId = _packetId;                                                  
        while(*_data != '\0')
        {   
            head->_Bit = *_data;
            head->_Next = (struct _Node*)malloc(sizeof(struct _Node));
            head = head->_Next;
            _data++;                                
            Counter++;                          
        }
        if(Counter != _dataCount) 
        {
            for(int i = Counter; i >= 0; i--)
            {
                _Delete_front(&memory);
            }
             Error = true;
             return memory;
        }
        head->_Next = 0;
        if(Counter != _dataCount) {
            free(head);
            head = 0;
        }
        Error = false;
        return memory;
    }

    bool _Plese_stup(struct _Node *head){
        if(head == 0)
            return true;
        return false;
    }

    bool _Edit_back(struct _Node *head, unsigned int _packetId = 0)
    {
        if(_packetId != 0) head->_PacketId = _packetId;
        //head->_DataCount = _dataCount; Нужен функционал по перемещению и пересчета следующего пакета, а так же удаления излишней информации в пакете
        if(_packetId == head->_PacketId) return true;
        return false;
    }

    void _Clear(struct _Node *head)
    {
        free(head);
        head = 0;
    }

    void _Delete_back(struct _Node **head){
        struct _Node *memory;
        memory = (*head)->_Next;
        free(*head);
        *head = memory;
    }

   void _Delete_front(struct _Node **head)
{
    struct _Node *memory;
    memory = (*head);
            while ((*head)->_Next->_Next != 0) {
                (*head) = (*head)->_Next;
            }
        free((*head)->_Next);
        (*head)->_Next = 0;
        (*head)->_Next;
        *head = memory;
}

    bool _Read_Packet(struct _Node *head, unsigned char *_buffer, unsigned int _bufferSize, unsigned int _dataCount, unsigned int _packetId){
        if(_bufferSize < head->_DataCount) return false;
        _dataCount = head->_DataCount;
        _packetId = head->_PacketId;
        for(int i = 0; i < _dataCount; i++) 
        {
            _buffer[i] = head->_Bit;
           _Delete_back(&head); 
        }
        root = head;
        return true;
    }
    public:

    bool Push(unsigned char *_data, unsigned int _dataCount, unsigned int _packetId)
    {
        if(_Plese_stup(root)) 
        {
            root = _List_filling(_data, _dataCount, _packetId);
            return true;
        }
        bool Error;   
        _Push_front(root, _data, _dataCount, _packetId, Error);
        if(Error) return false;
        return true;                                                               
    }
    
    bool Pop(unsigned char *_buffer, unsigned int _bufferSize, unsigned int &_dataCount, unsigned int &_packetId)
    {       
        if(_Plese_stup(root)) return false;
        return _Read_Packet(root, _buffer, _bufferSize, _dataCount, _packetId );
    }

    bool Clear_buffer()
    {
        _Clear(root);
        if(root == 0) return true;
        return false;
    }

    bool _Edit_The_First_Packet_ID(unsigned int _packetId){
        return _Edit_back(root, _packetId);
    }
};

int main()
{
    // Переменные
    unsigned char _buffer_1[100], _buffer_2[100], _buffer_3[100] ;
    unsigned int _bufferSize_1 = 100, _bufferSize_2 = 100, _bufferSize_3 = 100;
    unsigned int _dataCount_1 = 0 , _dataCount_2 = 0, _dataCount_3 = 0;
    unsigned int _packetId_1 = 0, _packetId_2 = 0, _packetId_3 = 0;
    unsigned char _stream_1[] = "Gigobit Ethernet not found 404";
    unsigned char _stream_2[] = "Gigobit Ethernet ENABLE";
    unsigned char _stream_3[] = "My name is NOT FOUND";
    // Объявления класса
    Homework _class;
    //  Вливаем данные
  
    _class.Push(_stream_2, sizeof(_stream_2)-1, 200);
    _class.Push(_stream_1, sizeof(_stream_1)-1, 100);  
    _class.Push(_stream_3, sizeof(_stream_3)-1, 1);              
    _class.Pop(_buffer_1, _bufferSize_1, _dataCount_1, _packetId_1);
    _class.Pop(_buffer_2, _bufferSize_2, _dataCount_2, _packetId_2);
    _class.Pop(_buffer_3, _bufferSize_3, _dataCount_3, _packetId_3);
    return 0;
}
