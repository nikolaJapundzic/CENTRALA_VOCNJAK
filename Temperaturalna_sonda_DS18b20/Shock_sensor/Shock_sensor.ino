int led = 13; // светодиод на 13-й пин
int shockSensor = 10; // подключаем выход датчика к 10-му пину
int value; // некая переменная состояния для датчика
int brojac = 0;
void setup ()
{
  Serial.begin(9600);
  pinMode (led, OUTPUT) ; // задаём 13-й пин как выход (для светодиода)
  pinMode (shockSensor, INPUT) ; // задаём 10-й пин как вход
}
void loop ()
{
  value = digitalRead (shockSensor) ; // читаем состояния датчика
  if (value == HIGH) // когда датчик срабатывает, светодиод загорается 
  {
    digitalWrite (led, LOW);    
  }
  else
  {
    digitalWrite (led, HIGH);
    brojac++;
    Serial.print("Neko je kvrcnuo");
    Serial.print(" ");
    Serial.println(brojac);
  }
}
