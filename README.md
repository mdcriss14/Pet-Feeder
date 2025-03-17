# Pet Feeder
 A smart pet feeder equipped with five integrated sensors and actuators.
	This automated pet feeder ensures your pet gets the right amount of food based on weight detection, light levels, and distance measurement. 

	The system:
- Weighs food using an HX711-based load cell
- Detects ambient light to control LED indicators
- Measures pet's distance using an ultrasonic sensor
- Controls a servo motor to release food based on weight and proximity

	
 	Features:
- Automatic Food Dispensing: The servo motor releases food based on weight and pet presence.
- Smart Weight Measurement: The system uses a load cell to ensure proper portion sizes.
- Distance Detection: The feeder detects if the pet is nearby before dispensing food.
- Light-Based LED Control: The LED turns on when light levels are low.

	Components Used:
- HX711 Load Cell – Measures food weight
- HC-SR04 Ultrasonic Sensor – Detects pet proximity
- Photoresistor (LDR) – Detects ambient light
- Servo Motor – Controls the food dispensing mechanism
- LED Indicator – Provides visual feedback

	How It Works:
- Calibration: The system first calibrates the weight sensor for accurate measurements.
- Pet Detection: The ultrasonic sensor checks if a pet is nearby.
- Food Dispensing: If the weight is below 20g and the pet is detected, the servo opens the feeder.
- Light Sensitivity: The LED turns on in low-light conditions for visibility.
