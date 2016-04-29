
#ifndef __DATACOM_H
#define __DATACOM_H

#define DataOK   0
#define DataErr -1

class TDataCom {
 protected:
   int  RetCode;              // Код завершения
   int  SetRetCode(int ret) { // Установить код завершения
     return RetCode=ret; 
   }
 public:
   TDataCom () : RetCode(DataOK) {};
   virtual ~TDataCom() {};
   int  GetRetCode()   {      // Получить код завершения
     int temp=RetCode; RetCode=DataOK; return temp;
   }
};
/* Notes:
     TDataCom является общим базовым классом
*/
#endif