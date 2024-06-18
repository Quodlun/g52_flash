byte ledPins [] = { A0, A1, A2, A3, A4, A5 }; // A6, A7
byte segPins [] = { 13, 12, 11, 10, 9, 8, 7 };
byte btnPins [] = { 5, 4, 3, 2 };
byte brightnessList [] = { 100, 200, 300, 400, 500, 600, 700, 800, 900, 1023 };
byte delayTimeList [] = { 50, 100, 150, 200, 250, 300 };

int flashBtnPin = 6;
int startTime;

int brightnessStage = 9;
int delayTimeStage = 3;

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
      delay ( 20 );

      switch ( btnPins [ i ] )
      {
        case 5:
          brightnessStage = 9;
          delayTimeStage = 3;

          Serial.println ( "Reset..." );
          Serial.println ( brightnessStage );
          Serial.println ( delayTimeStage );

          break;

        case 4:
          delayTimeStage += 1;

          if ( delayTimeStage > 5 )
          {
            delayTimeStage = 0;
            segDisplay ( delayTimeStage );
            Serial.println ( delayTimeStage );
          }

          else
          {
            segDisplay ( delayTimeStage );
            Serial.println ( delayTimeStage );
          }

          break;
          
        case 3:
          brightnessStage += 1;

          if ( brightnessStage > 9)
          {
            brightnessStage = 9;
            segDisplay ( brightnessStage );
            Serial.println ( brightnessStage );
          }

          else
          {
            segDisplay ( brightnessStage );
            Serial.println ( brightnessStage );
          }

          break;

        case 2:
          brightnessStage -= 1;

          if ( brightnessStage < 0 )
          {
            brightnessStage = 0;
            segDisplay ( brightnessStage );
            Serial.println ( brightnessStage );
          }

          else
          {
            segDisplay ( brightnessStage );
            Serial.println ( brightnessStage );
          }

          break;

        default:
          Serial.println ( btnPins [ i ] + 1 );

          break;
      }
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
      analogWrite ( ledPins [ i ], brightnessList [ brightnessStage ] );
    }

    startTime = millis ();
    delay ( delayTimeList [ delayTimeStage ] );

    for ( int i = 0; i < 6; i ++ )
    {
      analogWrite ( ledPins [ i ], 0 );
    }
  }
}