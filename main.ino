// Define the PIR sensor output pin
const int pirPin = 2;
// Define the ultrasonic sensor pins
const int trigPin = 3; // Trigger signal output pin
const int echoPin = 4; // Echo signal input pin
// Define the output pin for the lights
const int ledPin = 13;

const int ledPin1 = 12;

const int ledPin2 = 11;
// Define the detection distance of the ultrasonic sensor (in centimeters)
const int detectionDistance = 300; // Adjust as necessary
// Define the delay time after detection (in milliseconds)
const int delayDuration = 5000; // 5 seconds delay
// delay for color change, on/off
const int waitTime = 2500;

bool presenceDetected = false; // Variable to track detected presence
bool yellow = false;

void setup()
{
    pinMode(pirPin, INPUT);
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
    pinMode(ledPin, OUTPUT);
    digitalWrite(ledPin, LOW); // Starts lights off
    digitalWrite(ledPin1, LOW);
    pinMode(7, OUTPUT); // buzzer
    pinMode(13, OUTPUT);
    pinMode(12, OUTPUT);
    pinMode(11, OUTPUT);
    pinMode(7, OUTPUT);
    digitalWrite(ledPin2, HIGH);
}

void loop()
{
    // Check for presence detected by PIR sensor
    if (detectMotion())
    {
        presenceDetected = true;
        // delay to turn on lights
        digitalWrite(ledPin1, HIGH); // TURN ON YELLOW
        delay(waitTime);
        digitalWrite(ledPin2, LOW); // TURN OFF GREEN
        digitalWrite(ledPin1, LOW); // TURN OFF YELLOW
        digitalWrite(ledPin, HIGH); // TURN ON RED

        tone(7, 293, 66);
        delay(250);
        noTone(7);
        tone(7, 391, 99);
        delay(500); // Wait for the defined delay
    }
    else if (presenceDetected && detectObstacle())
    {
        digitalWrite(ledPin, HIGH); // TURN ON RED
        tone(7, 400, 00);
        delay(250);
        noTone(7);
    }
    else
    {
        presenceDetected = false;

        if (digitalRead(ledPin) == HIGH)
        {
            tone(7, 391, 99);
            delay(600);
            noTone(7);
            tone(7, 261, 63);

            delay(500);
            digitalWrite(ledPin, LOW); // TURN OFF RED
            digitalWrite(ledPin1, LOW);
        } // TURN OFF YELLOW

        digitalWrite(ledPin2, HIGH); // TURN ON GREEN
    }

    // Wait a short period before performing a new check
    delay(1000); // 1 second delay
}

// Function to detect presence using the PIR sensor
bool detectMotion()
{
    return digitalRead(pirPin) == HIGH;
}

// Function to detect obstacle presence using the ultrasonic sensor
bool detectObstacle()
{
    // Generate a 10µs pulse on the trigger pin
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    // Measure the time the echo signal takes to return
    long duration = pulseIn(echoPin, HIGH);

    // Calculate distance in centimeters
    int distance = duration * 0.034 / 2;

    // Check if distance is less than detection distance
    return (distance <= detectionDistance);
}
