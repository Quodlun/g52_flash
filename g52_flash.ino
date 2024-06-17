byte ledPins [] = { A0, A1, A2, A3, A4, A5 };
int buttonPin = 5;

void setup ()
{
  for ( int i = 0; i < 8; i ++ )
  {
    pinMode ( ledPins [ i ], OUTPUT );
    digitalWrite ( ledPins [ i ], LOW );
  }
}

void loop ()
{
  if ( digitalRead ( buttonPin ) == HIGH )
  {
    for ( int i = 0; i < 6; i ++ )
    {
      analogWrite ( ledPins [ i ], 1023 );
    }

    delay ( 200 );

    for ( int i = 0; i < 6; i ++ )
    {
      analogWrite ( ledPins [ i ], 0 );
    }

    delay ( 7000 );
  }
}