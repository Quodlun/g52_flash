byte ledPins [] = { 3, 5, 6, 9, 10, 11 };
byte segPins [] = { 14, 15, 16, 17, 18, 19, 13 };
byte btnPins [] = { 2, 4, 7, 8, 12};
int brightnessList [] = { 0, 63, 127, 255 };
int delayTimeList [] = { 0, 50, 75, 100 };

long long int startTime;
int brightnessStage = 3;
int delayTimeStage = 1;

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

  for ( int i = 0; i < 6; i ++ )
  {
    pinMode ( ledPins [ i ], OUTPUT );
    analogWrite ( ledPins [ i ], 0 );
  }

  for ( int i = 0; i < 7; i ++ )
  {
    pinMode ( segPins [ i ], OUTPUT );
    digitalWrite ( segPins [ i ], LOW );
  }

  for ( int i = 0; i < 5; i ++ )
  {
    pinMode ( btnPins [ i ], INPUT);
    digitalWrite ( btnPins [ i ], LOW);
  }

  startTime = -7000;
}

void loop ()
{
  for ( int i = 0; i < 5; i ++ )
  {
    if ( digitalRead ( btnPins [ i ] ) == HIGH )
    {
      delay ( 20 );

      switch ( i + 1 )
      {
        case 1:
          reset ();

          segPrint ( delayTimeStage );
          delay ( 500 );
          segPrint ( brightnessStage );            

          break;
          
        case 2:
          delayTimeStage += 1;

          if ( delayTimeStage > 3 )
          
            delayTimeStage = 0;
          }

          segPrint ( delayTimeStage );
          Serial.print ( delayTimeStage );
          Serial.print ( "  " );
          Serial.println ( delayTimeList [ delayTimeStage ] );

          break;

        case 3:
          brightnessStage += 1;

          if ( brightnessStage > 3 )
          {
            brightnessStage = 3;
          }

          segPrint ( brightnessStage );

          Serial.print ( brightnessStage );
          Serial.print ( "  " );
          Serial.println ( brightnessList [ brightnessStage ] );

          break;

        case 4:
          brightnessStage -= 1;

          if ( brightnessStage < 0 )
          {
            brightnessStage = 0;
          }

          segPrint ( brightnessStage );

          Serial.print ( brightnessStage );
          Serial.print ( "  " );
          Serial.println ( brightnessList [ brightnessStage ] );

          break;
          
        case 5:
          flash ();

          break;
          
        default:
          break;
      }

      while ( digitalRead ( btnPins [ i ] ) == HIGH )
      {
        delay ( 1 );
      }

      delay ( 20 );
    }
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

void segPrint ( int segNum )
{
  for ( int i = 0; i < 7; i ++ )
  {
    digitalWrite ( segPins [ i ], segDigits [ segNum ] [ i ] );
  }
}

void reset ()
{
  brightnessStage = 3;
  delayTimeStage = 1;

  Serial.println ( "Reset... " );
  Serial.print ( brightnessList [ brightnessStage ] );
  Serial.print ( "  " );
  Serial.println ( delayTimeList [ delayTimeStage ] );
}