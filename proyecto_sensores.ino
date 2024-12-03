

#include <SoftwareSerial.h>
int sensorPin=A0;
int ledPin=13;
int rxdpin=3;
int txdpin=2;
SoftwareSerial bluetooth(txdpin,rxdpin);
class Sensor_sound
{private:
int _value;
public:
Sensor_sound();
 int getvalue();
 void setvalue();
};
Sensor_sound :: Sensor_sound(){
_value = 0;  
}
int Sensor_sound::getvalue(){
  return _value;
}
void Sensor_sound::setvalue(){
  _value = analogRead(sensorPin);}

class Backup{
  private:
  int *data;
  int capacity;
  int count;
  public:
  Backup();
  ~Backup();
  
  void append(Backup &C,int value);
  int removefirst(Backup &C);
  int getcount(Backup &C);
  };
  Backup::Backup(){
    count=0;
    data = new int[5];
    if(!data){
      printf("out of memory");
      capacity=0;
      return;}
    capacity=2;
  }
  Backup ::~Backup(){
    delete[] data;
  } 
  void Backup::append(Backup &C,int value){
    if (C.count == C.capacity){
      int *newdata = new int[C.capacity+1];
      if(!newdata){
        printf("out of memory");
        return;}
      C.capacity+=1;
      for(int i=0;i<C.count;i++)
        newdata[i]=C.data[i];
      delete[] C.data;
      C.data = newdata;}  
      
    C.data[C.count]=value;
    C.count+=1;

  }
  int Backup :: removefirst(Backup &C){
    int value=C.data[0];
    for(int i=0;i<C.count;i++)
      C.data[i]=C.data[i+1];
    C.count-=1;
    return value;}
  int Backup :: getcount(Backup &C){
    return C.count;
  }
Backup back;
void setup() {
  // put your setup code here, to run once:
  pinMode(ledPin,OUTPUT);
  Serial.begin(9600);
  bluetooth.begin(9600);
  
 
  
  
 

}

void loop() {
  // put your main code here, to run repeatedly:

Sensor_sound s1;

s1.setvalue(); 
back.append(back,s1.getvalue());
if(bluetooth.available()){
  int i =0;
  while(i<back.getcount(back)){
    bluetooth.println(back.removefirst(back));
}
}

Serial.println(s1.getvalue());
delay(1000);
}