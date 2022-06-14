
//Declare pin functions on Arduino
#define STEP_PIN 2 //defines which pin the step pin is on
#define DIR_PIN 3 //defines which pin the direction pin is on
#define EN_PIN 4 //defines which pin the enable is on
#define ANALOG_IN A0 //defines which pin the anlog signal is read on 
#define NG_POSITION 200 //defines the positon for the correct lamba for natural gas
#define H2_POSITION 50 //defines the position for the correct lambda for H2

#define CLOSED 1

//Declare variables for functions
float GasPolynomial[] = {0.0517, 0.7576, -14.44}; //In ascending order of power
int currentValue = 0; //Holds the current position of the valve
int refValue = 0; //Holds the new position the valve should be at
int stepsNeeded = 0; //Holds the number of steps needed to get to the new position
int val = 0;
int tol = 50;

void setup() {
  pinMode(STEP_PIN, OUTPUT); //Set the step pin as an output
  pinMode(DIR_PIN, OUTPUT); //set the dir pin as output
  pinMode(EN_PIN, OUTPUT); //set the enable pin as an output

  digitalWrite(STEP_PIN, LOW); //Ensure the step pin is set low
  digitalWrite(DIR_PIN, LOW); //Ensure the dir pin has a defined polarity. (The value is irrelevant)
  digitalWrite(EN_PIN, LOW); //Make the enable pin low to enable the driver

  //According to SIT 877 Manual. There are 330 steps that it can take.
  Step(100, 0); //Move 350 steps to ensure system is at the zero position
  currentValue = 0; //Reset position to 0
  delay(100);
  Step(100, 1);
  Serial.begin(9600);
}


void loop() {
    /*refValue = map(analogRead(ANALOG_IN), 0, 1023, 0, 280); // Map the new position measured from the pot to a step value
    stepsNeeded = refValue - currentValue; //Calculate the number of steps needed to move
    Step(abs(stepsNeeded), stepsNeeded > 0 ? 1 : 0); //Move the valve to the new position. The ternary operator decides which direction based on the sign of the steps
    delay(100);*/
}

void Step(int steps, bool dir) //Function to step in a specific direction a certain number of times
{
  digitalWrite(EN_PIN, LOW); //Enable the stepper driver
  delay(10);
  if (dir == 1) {
    digitalWrite(DIR_PIN, HIGH); //Pull direction pin low to move "forward" and update the current position
    currentValue += steps;
  } else {
    digitalWrite(DIR_PIN, LOW); //Pull direction pin high to move "reverse" and update the current position
    currentValue -= steps;
  }
  for (int i = 0; i < steps; i++) //Loop through the number of steps
  {
    digitalWrite(STEP_PIN, HIGH); //Trigger one step forward
    delay(5);
    digitalWrite(STEP_PIN, LOW); //Pull step pin low so it can be triggered again
    delay(5);
  }
  delay(10);
  digitalWrite(EN_PIN, HIGH); //Disable the stepper driver
}
