void setup()
{
  Serial.begin(9600);
}

void loop()
{
  if (Serial.available())
  {
    if (Serial.read() == 'a')
    {
      Serial.print('^');
      Serial.print(analogRead(0));
      Serial.print('$');
    }
  }

  delay(20);
}
