#define DC1_PIN1 5
#define DC1_PIN2 3
#define DC2_PIN1 9
#define DC2_PIN2 6
#define BTN_PIN 2
#define MAX_SPEED 255
#define NUMBER_OF_SENSORS 8
int sensor[NUMBER_OF_SENSORS] = {13, 12, 11, 10, 8, 7, 4, A0};
int sensorValue[NUMBER_OF_SENSORS];
int btnState = 0;
int isRunning,count;
unsigned long previousMillis = 0;

void setup()
{
    pinMode(DC1_PIN1, OUTPUT);
    pinMode(DC1_PIN2, OUTPUT);
    pinMode(DC2_PIN1, OUTPUT);
    pinMode(DC2_PIN2, OUTPUT);
    pinMode(BTN_PIN, INPUT);
    for (int i = 0; i < NUMBER_OF_SENSORS; i++)
        pinMode(sensor[i], INPUT);
    isRunning = 0;
    count = 0;
}

void stopMotors()
{
    analogWrite(DC1_PIN1, 0);
    analogWrite(DC1_PIN2, 0);
    analogWrite(DC2_PIN1, 0);
    analogWrite(DC2_PIN2, 0);
}

void moveLeft(int motorSpeed)
{
    analogWrite(DC1_PIN1, 0);
    analogWrite(DC1_PIN2, MAX_SPEED);
    analogWrite(DC2_PIN1, 0);
    analogWrite(DC2_PIN2, motorSpeed);


}
void moveLeft90()
{
    analogWrite(DC1_PIN1, 0);
    analogWrite(DC1_PIN2, MAX_SPEED);
    analogWrite(DC2_PIN1, MAX_SPEED);
    analogWrite(DC2_PIN2, 0);


}
void moveRight(int motorSpeed)
{

    analogWrite(DC1_PIN1, 0);
    analogWrite(DC1_PIN2, motorSpeed);
    analogWrite(DC2_PIN1, 0);
    analogWrite(DC2_PIN2, MAX_SPEED);
}
void moveRight90()
{

    analogWrite(DC1_PIN1, MAX_SPEED);
    analogWrite(DC1_PIN2, 0);
    analogWrite(DC2_PIN1, 0);
    analogWrite(DC2_PIN2, MAX_SPEED);
}



void moveForward()
{
    analogWrite(DC1_PIN1, 0);
    analogWrite(DC1_PIN2, MAX_SPEED);
    analogWrite(DC2_PIN1, 0);
    analogWrite(DC2_PIN2, MAX_SPEED);
}


void loop()
{
    if (millis() - previousMillis > 45)
    {   count++;
        previousMillis = millis();
       if(count > 1)
       {
        count=0;
        btnState = digitalRead(BTN_PIN);
        if(btnState == 1)
        {
            if(isRunning == 0)
                isRunning = 1;
            else
            {
                isRunning = 0;
                stopMotors();
            }
        }
       }
        if(isRunning == 1)        
        {
            for (int i = 0; i < NUMBER_OF_SENSORS; i++)
            {
                sensorValue[i] = digitalRead(sensor[i]);
                if(sensorValue[i] == 1)
                {
                    if(i == 0)
                        moveRight90();
                    if(i == 1)
                        moveRight(MAX_SPEED/5.5);
                    if(i == 2)
                        moveRight(MAX_SPEED/1.3);
                    if(i == 3 || i==4)
                        moveForward();
                    if(i == 5)
                        moveLeft(MAX_SPEED/1.3);
                    if(i == 6)
                        moveLeft(MAX_SPEED/5.5);
                    if(i == 7)
                        moveLeft90();
                }
            }
        }
    }

}
