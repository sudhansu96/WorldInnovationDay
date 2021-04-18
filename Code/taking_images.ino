#include <Adafruit_VC0706.h>
#include <SPI.h>
#include <SD.h>

// Define Slave Select pin
#define SD_CS  53

// Create an instance of Adafruit_VC0706 class
// We will use Serial1 for communication with the camera
Adafruit_VC0706 cam = Adafruit_VC0706(&Serial1);

void setup() {
  // Begin Serial port for communication with PC
  Serial.begin(115200);

  // Start the SD
  if(!SD.begin(SD_CS)) {
    // If the SD can't be started, loop forever
    Serial.println("SD failed or not present!");
    while(1);
  }

  // Start the camera
  if(!cam.begin()) {
    // If the camera can't be started, loop forever
    Serial.println("Camera failed or not present!");
    while(1);
  }

  // Set the image size to 640x480
  cam.setImageSize(VC0706_640x480);
}

void loop() {
  Serial.print("Taking picture in 3 seconds ... ");
  delay(3000);
  
  // Take a picture
  if(cam.takePicture()) {
    Serial.println("done!");
  } else {
    Serial.println("failed!");
  }

  // Create a name for the new file in the format IMAGExy.JPG
  char filename[13];
  strcpy(filename, "IMAGE00.JPG");
  for(int i = 0; i < 100; i++) {
    filename[5] = '0' + i/10;
    filename[6] = '0' + i%10;
    if(!SD.exists(filename)) {
      break;
    }
  }

  // Create a file with the name we created above and open it
  File imgFile = SD.open(filename, FILE_WRITE);

  // Get the size of the image
  uint16_t jpglen = cam.frameLength();
  Serial.print("Writing ");
  Serial.print(jpglen, DEC);
  Serial.print(" bytes into ");
  Serial.print(filename);
  Serial.print(" ... ");

  // Read all the image data
  while(jpglen > 0) {
    // Load the JPEG-encoded image data from the camera into a buffer
    uint8_t *buff;
    uint8_t bytesToRead = min(32, jpglen);
    buff = cam.readPicture(bytesToRead);

    // Write the image data to the file
    imgFile.write(buff, bytesToRead);
    jpglen -= bytesToRead;
  }

  // Safely close the file
  imgFile.close();
  
  Serial.println("done!");
  delay(3000);
}
