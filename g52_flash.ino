byte ledPins [] = { A0, A1, A2, A3, A4, A5 };
byte segPins [] = { 13, 12, 11, 10, 9, 8, 7 };
byte btnPins [] = { 5, 4, 3, 2 };
int flashBtnPin = 6;
int startTime;

int brightness = 1023;

byte segDigits [ 10 ] [ 7 ] = 
{
  { 1, 1, 1, 1, 1, 1, 0 },
  { 0, 1, 1, 0, 0, 0, 0 },
  { 1, 1, 0, 1, 1, 0, 1 },
  { 1, 1, 1, 1, 0, 0, 1 },
  { 0, 1, 1, 0, 0, 1, 1 },
  { 1, 0, 1, 1, 0, 1, 1 },
  { 1, 0, 1, 1, 1, 1, 1 },
  { 1, 1, 1, 0, 0, 0, 0 },
  { 1, 1, 1, 1, 1, 1, 1 },
  { 1, 1, 1, 1, 0, 1, 1 }
};

void setup ()
{
  Serial.begin ( 9600 );

  pinMode ( flashBtnPin, INPUT );

  for ( int i = 0; i < 6; i ++ )
  {
    pinMode ( ledPins [ i ], OUTPUT );
  }

  for ( int i = 0; i < 7; i ++ )
  {
    pinMode ( segPins [ i ], OUTPUT );
  }

  for ( int i = 0; i < 4; i ++ )
  {
    pinMode ( btnPins [ i ], INPUT );
    digitalWrite ( btnPins [ i ], LOW );
  }

  startTime = -7000;
}

void loop ()
{
  if ( digitalRead ( flashBtnPin ) == HIGH )
  {
    flash ();
  }
  
  for ( int i = 0; i < 4; i ++ )
  {
    if ( digitalRead ( btnPins [ i ] ) == HIGH )
    {
      Serial.println ( i + 1 );

      segDisplay ( i + 1 );
    }
  }
}

void segDisplay ( int displayNum )
{
  for ( int i = 0; i < 7; i ++ )
  {
    digitalWrite ( segPins [ i ], segDigits [ displayNum ] [ i ] );
  }
}

void flash ()
{
  if ( millis () - startTime >= 7000 )
  {
    for ( int i = 0; i < 6; i ++ )
    {
      analogWrite ( ledPins [ i ], brightness );
    }

    startTime = millis ();
    delay ( 200 );

    for ( int i = 0; i < 6; i ++ )
    {
      analogWrite ( ledPins [ i ], 0 );
    }
  }
}