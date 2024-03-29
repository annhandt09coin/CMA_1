/*
 * ngõ ra cân là rs232, tốc độ baud 9600, tần số 10hz
 * 
z Text Command
CR (0DH) The end of data
LF (0AH) The end of text
0 - 9 (30H-39H) Numeric data
- (2DH) Minus
. (2EH) Decimal Point
STX (02H) Start of Text
SOH (01H) Weight stable flag
NUL (00H) Weight un-stable flag 
0~9 là 30->39H
. 2EH
, 2CH
- 2DH 
stable flag là 01H-00H 01~Stable 00~unstable
Header :(0) 30H ->net weight
         (4) 34H->tare  
Net Weight = - 1.20 lb. Tare Weight = 0.45lb. 

STX* |Stable flag| CR |*Header |Net weight| CR| *Header| Tare weight|CR |LF
1          1        1      1           7     1     1          7       1   1 

Vd gửi dữ liệu
02 01 0D 30 34 35 36 2E 30 30 30 0D 34  32 31 30 2E 36 35 32 0D 0A
 */
extern volatile uint8_t can_rxbuf[40];
extern volatile uint8_t canbuff;
extern volatile uint8_t rfidbuff;
extern volatile uint8_t rfid_rxbuf[40];
extern volatile uint8_t rfid_data[20];

void TaskCAN( void * pvParameters ){
  double giatri=0;
  const TickType_t xTicksToWait = pdMS_TO_TICKS(5);
  int tam= 1;
  int hangtram=0;
  data_user Data;
  Data.id = 1;
    while(true){
     if( xSemaphoreTake( xCountingSemaphore, ( TickType_t ) 5 ) == pdTRUE )
     {
      for (int j=0;j<2;j++){
        giatri=0;
        tam=1;
        for (int tang=(j*9)+1;tang<(j*9)+8; tang++){
           if((rfid_data[tang] == 0x2C) || (rfid_data[tang] == 0x2E)) {hangtram = tang-1; break;}
        }
        hangtram=hangtram-1;
        for (int tang1=(j*9)+1;tang1<(j*9)+8; tang1++){
          if (rfid_data[tang1] == 0x2D){tam = -1;}
          else if ((rfid_data[tang1] == 0x2C) || (rfid_data[tang1] == 0x2E)){hangtram=hangtram+1;}
          else{
           giatri+=(float)((rfid_data[tang1]-48)*pow(10,hangtram-(tang1-1)));
            }
        }
        if (rfid_data[j*9] == 0x30){Data.data_weight=giatri*tam;}
        else{Data.data_tare=giatri*tam;} 
      }
      xQueueSend( Queue_can, &Data, xTicksToWait );
     // printf("Can weight: %f \n",Data.data_weight);
     // printf("Can tare: %f \n", Data.data_tare);
     }
      vTaskDelay(20);
        
    }
    vTaskDelete(NULL) ;
}
