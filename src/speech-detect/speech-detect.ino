/*

Wearable device code

*/

// defines
#define SOUND_1_ON 1
#define SOUND_1_OFF 2
#define SOUND_2_ON 3 
#define SOUND_2_OFF 4
#define SOUND_3_ON 5
#define SOUND_3_OFF 6
#define SOUND_4_ON 7
#define SOUND_4_OFF 8
#define CONF_LEV_80 80
#define CONF_LEV_85 85
#define CONF_LEV_90 90
#define CONF_LEV_95 95
#define CONF_LEV_98 98
#define EIDSP_QUANTIZE_FILTERBANK   0
#define EI_CLASSIFIER_SLICES_PER_MODEL_WINDOW 3

// includes
#include <PDM.h>

#include <capstone26_inferencing.h>

#include <ArduinoBLE.h>

// Global variables
typedef struct {
    signed short *buffers[2];
    unsigned char buf_select;
    unsigned char buf_ready;
    unsigned int buf_count;
    unsigned int n_samples;
} inference_t;

static inference_t inference;
static bool record_ready = false;
static signed short *sampleBuffer;
static bool debug_nn = false;
static int print_results = -(EI_CLASSIFIER_SLICES_PER_MODEL_WINDOW);

static int vibration_Type[6] = {0,1,2,3,4,5};
static const int led_pin = LED_BUILTIN;
static const int VR = 3;

float confidence_lev = 0.85;

bool abraham_on = false;
bool alarm_on = false;
bool jordan_on = false;
bool smith_on = false;

// BLE LED Service
BLEService ledService("180A"); 

// BLE LED Switch Characteristic
BLEByteCharacteristic switchCharacteristic("2A57", BLERead | BLEWrite);

// Arduino setup function
void setup()
{
  // setup LEDs
  pinMode(led_pin, OUTPUT);
  pinMode(VR, OUTPUT);
  pinMode(LEDR, OUTPUT);
  pinMode(LEDG, OUTPUT);
  pinMode(LEDB, OUTPUT);

  // Bluetooth init first 
  if (!BLE.begin()) {
    while (1);
  }

  // set advertised local name and service UUID:
  BLE.setLocalName("Nano 33 BLE Sense");
  BLE.setAdvertisedService(ledService);

  // add the characteristic to the service
  ledService.addCharacteristic(switchCharacteristic);

  // add service
  BLE.addService(ledService);

  // set the initial value for the characteristic:
  switchCharacteristic.writeValue(0);

  // start advertising
  BLE.advertise();

  // turn on green LED
  digitalWrite(led_pin,HIGH); 
  digitalWrite(LEDR, HIGH);
  digitalWrite(LEDG, HIGH);  
  digitalWrite(LEDB, HIGH);
  
  // initialize clssifier
  run_classifier_init();

  // initialize microphone
  microphone_inference_start(EI_CLASSIFIER_SLICE_SIZE);
}

// type of vibration
void vibration(int type){
  switch(type)
  {
    case 0:
    {
      // one quick vibration and LED blink
      digitalWrite(VR,HIGH); 
      delay(100);
      digitalWrite(VR,LOW);
      delay(1000);
      break;
    }
    case 1: 
    {
      // two quick vibrations and LED blinks
      digitalWrite(VR,HIGH); 
      delay(25);
      digitalWrite(VR,LOW);
      delay(25);
      digitalWrite(VR,HIGH); 
      delay(25);
      digitalWrite(VR,LOW);
      delay(1000);
      break;
    }
    case 2:
    { 
      // one vibtarion and LED blink
      digitalWrite(VR,HIGH);
      digitalWrite(led_pin,HIGH); 
      delay(1000);
      digitalWrite(VR,LOW);
      digitalWrite(led_pin,LOW);
      delay(1000);
      break;
    }
    case 3: 
    {
      // three vibrations and LED blinks
      digitalWrite(VR,HIGH);
      digitalWrite(led_pin,HIGH); 
      delay(200);
      digitalWrite(VR,LOW);
      digitalWrite(led_pin,LOW);
      delay(200);
      digitalWrite(VR,HIGH);
      digitalWrite(led_pin,HIGH); 
      delay(200);
      digitalWrite(VR,LOW);
      digitalWrite(led_pin,LOW);
      delay(200);
      digitalWrite(VR,HIGH);
      digitalWrite(led_pin,HIGH); 
      delay(200);
      digitalWrite(VR,LOW);
      digitalWrite(led_pin,LOW);
      delay(1000);
      break;
    }
    case 4: 
    {
      // two vibrations and LED blinks
      digitalWrite(VR,HIGH);
      digitalWrite(led_pin,HIGH); 
      delay(200);
      digitalWrite(VR,LOW);
      digitalWrite(led_pin,LOW);
      delay(200);
      digitalWrite(VR,HIGH);
      digitalWrite(led_pin,HIGH); 
      delay(200);
      digitalWrite(VR,LOW);
      digitalWrite(led_pin,LOW);
      delay(1000);
      break;
    } 
    case 5: 
    {
      // four vibrations and LED blinks
      digitalWrite(VR,HIGH);
      digitalWrite(led_pin,HIGH); 
      delay(200);
      digitalWrite(VR,LOW);
      digitalWrite(led_pin,LOW);
      delay(200);
      digitalWrite(VR,HIGH);
      digitalWrite(led_pin,HIGH); 
      delay(200);
      digitalWrite(VR,LOW);
      digitalWrite(led_pin,LOW);
      delay(200);
      digitalWrite(VR,HIGH);
      digitalWrite(led_pin,HIGH); 
      delay(200);
      digitalWrite(VR,LOW);
      digitalWrite(led_pin,LOW);
      delay(200);
      digitalWrite(VR,HIGH);
      digitalWrite(led_pin,HIGH); 
      delay(200);
      digitalWrite(VR,LOW);
      digitalWrite(led_pin,LOW);
      delay(1000);
      break;
    }
  }
}

//Arduino main function
void loop()
{
    BLEDevice central = BLE.central();

    if (central) {

      //Blue LED showing connection
      digitalWrite(LEDR, HIGH);
      digitalWrite(LEDG, HIGH);
      digitalWrite(LEDB, LOW);   

      digitalWrite(led_pin,LOW);

      while (central.connected()) {

        if (switchCharacteristic.written()){
          switch (switchCharacteristic.value()){
            case SOUND_1_ON:
              abraham_on = true;
              break;
            case SOUND_1_OFF:
              abraham_on = false;
              break;
            case SOUND_2_ON:
              smith_on = true;
              break;
            case SOUND_2_OFF:
              smith_on = false;
              break;
            case SOUND_3_ON:
              jordan_on = true;
              break;
            case SOUND_3_OFF:
              jordan_on = false;
              break;
            case SOUND_4_ON:
              alarm_on = true;
              break;
            case SOUND_4_OFF:
              alarm_on = false;
              break;
            case CONF_LEV_80:
              confidence_lev = 0.8;
              break;
            case CONF_LEV_85:
              confidence_lev = 0.85;
              break;
            case CONF_LEV_90:
              confidence_lev = 0.9;
              break;
            case CONF_LEV_95:
              confidence_lev = 0.95;
              break;
            case CONF_LEV_98:
              confidence_lev = 0.98;
              break;
          }
          return;
        }
    
        bool m = microphone_inference_record();
        if (!m) {
          return;
        }

        // signal to be processed
        signal_t signal;
        signal.total_length = EI_CLASSIFIER_SLICE_SIZE;
        signal.get_data = &microphone_audio_signal_get_data;
        ei_impulse_result_t result = {0};
    
        run_classifier_continuous(&signal, &result, debug_nn);

        //Turn on LED and vibrate if sound detected
        if ((result.classification[0].value > confidence_lev) && abraham_on){ 
          vibration(vibration_Type[2]);
        }
        else if ((result.classification[2].value > confidence_lev) && alarm_on){
          vibration(vibration_Type[3]);
        }
        else if ((result.classification[3].value > confidence_lev) && jordan_on){
          vibration(vibration_Type[4]);
        }
        else if ((result.classification[1].value > confidence_lev) && smith_on){
          vibration(vibration_Type[5]);
        }  
      }
    }
    else {

      // no connection, turn LED back to green
      digitalWrite(LEDR, HIGH);
      digitalWrite(LEDG, HIGH);
      digitalWrite(LEDB, HIGH); 
      digitalWrite(led_pin,HIGH);
    }
}

// PDM buffer full callback
static void pdm_data_ready_inference_callback(void)
{
    int bytesAvailable = PDM.available();

    // read into the sample buffer
    int bytesRead = PDM.read((char *)&sampleBuffer[0], bytesAvailable);

    if (record_ready == true) {
        for (int i = 0; i<bytesRead>> 1; i++) {
            inference.buffers[inference.buf_select][inference.buf_count++] = sampleBuffer[i];

            if (inference.buf_count >= inference.n_samples) {
                inference.buf_select ^= 1;
                inference.buf_count = 0;
                inference.buf_ready = 1;
            }
        }
    }
}

// Init inferencing struct and setup/start PDM
static bool microphone_inference_start(uint32_t n_samples)
{
    inference.buffers[0] = (signed short *)malloc(n_samples * sizeof(signed short));

    if (inference.buffers[0] == NULL) {
        return false;
    }

    inference.buffers[1] = (signed short *)malloc(n_samples * sizeof(signed short));

    if (inference.buffers[1] == NULL) {
        free(inference.buffers[0]);
        return false;
    }

    sampleBuffer = (signed short *)malloc((n_samples >> 1) * sizeof(signed short));

    if (sampleBuffer == NULL) {
        free(inference.buffers[0]);
        free(inference.buffers[1]);
        return false;
    }

    inference.buf_select = 0;
    inference.buf_count = 0;
    inference.n_samples = n_samples;
    inference.buf_ready = 0;

    // configure the data receive callback
    PDM.onReceive(&pdm_data_ready_inference_callback);

    PDM.setBufferSize((n_samples >> 1) * sizeof(int16_t));

    // set the gain, defaults to 20
    PDM.setGain(127);

    record_ready = true;

    return true;
}

// Wait on new data
static bool microphone_inference_record(void)
{
    bool ret = true;

    if (inference.buf_ready == 1) {
        ret = false;
    }

    while (inference.buf_ready == 0) {
        delay(1);
    }

    inference.buf_ready = 0;

    return ret;
}

// Get audio signal data
static int microphone_audio_signal_get_data(size_t offset, size_t length, float *out_ptr)
{
    numpy::int16_to_float(&inference.buffers[inference.buf_select ^ 1][offset], out_ptr, length);

    return 0;
}