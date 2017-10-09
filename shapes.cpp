float VELOCITY = 50.; //Distance moved in 1 second
float DEG_PER_SEC = 180.; //Degrees moved turning for 1 second

const int8_t pins[4] = {A0, A1, A2, A3}; //Left then right
unsigned long lastTime = 0;

bool GET_CONSTANTS = false; //Set to false for normal operation

void setup(){
	Serial.begin(9600);
	allOff();
	if(GET_CONSTANTS){
		findConstants();
	}
}


void loop(){
	if(Serial.available()>0){
		float sideNum = Serial.parseFloat();
		float length = Serial.parseFloat();
		drawShape(sideNum, length);
	}
}

void drawShape(float sides, float length){
	int millisToDelayLength = distanceToDelay(length);
	int degreesOfShape = 180*(sides-2);
	int degreesPerSide = degreesOfShape / sides;
	int millisToDelayDegrees = degreesToDelay(degreesPerSide);
	Serial.println("There is a total of "+String(degreesOfShape)+" degrees. Each side has "+String(degreesPerSide)+" degrees.");
	lastTime = millis();
	for(int i=0;i<sides;i++){
		Serial.println("Starting side "+String(i));
		forward(millisToDelayLength);
		turnLeft(millisToDelayDegrees);
	}
	float timeTaken = (millis() - lastTime) / 1000;
	Serial.println("Finished in: "+String(timeTaken)+" seconds.");
	
}

int distanceToDelay(int distance){
	float time = distance / VELOCITY;
	Serial.println("Each side will have a delay of: "+String(time)+" seconds.");
	return int(time*1000);
}

int degreesToDelay(int degrees){
	float time = degrees / DEG_PER_SEC;
	Serial.println("Each turn will have a delay of "+String(time)+" seconds.");
	return int(time*1000);
}

void turnLeft(int time){
	allOff();
	analogWrite(pins[1], 150);
	analogWrite(pins[2], 150);
	delay(time);
	allOff();
}

void forward(int time){
	allOff();
	analogWrite(pins[0], 150);
	analogWrite(pins[2], 150);
	delay(time);
	allOff();
}

void allOff(){
	for(int i=0;i<4;i++){
		analogWrite(pins[i], 0);
	}
}

void findConstants(){
	Serial.println(F("I will drive forward for 1 second."));
	forward(1000);
  delay(6000);
	Serial.println(F("I will now turn right for 1 second."));
	turnLeft(1000);
	while(1);
}
	
	
