/* Edge Impulse ingestion SDK
 * Copyright (c) 2022 EdgeImpulse Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

// If your target is limited in memory remove this macro to save 10K RAM
#define EIDSP_QUANTIZE_FILTERBANK   0

/**
 * Define the number of slices per model window. E.g. a model window of 1000 ms
 * with slices per model window set to 4. Results in a slice size of 250 ms.
 * For more info: https://docs.edgeimpulse.com/docs/continuous-audio-sampling
 */
#define EI_CLASSIFIER_SLICES_PER_MODEL_WINDOW 3

/*
 ** NOTE: If you run into TFLite arena allocation issue.
 **
 ** This may be due to may dynamic memory fragmentation.
 ** Try defining "-DEI_CLASSIFIER_ALLOCATION_STATIC" in boards.local.txt (create
 ** if it doesn't exist) and copy this file to
 ** `<ARDUINO_CORE_INSTALL_PATH>/arduino/hardware/<mbed_core>/<core_version>/`.
 **
 ** See
 ** (https://support.arduino.cc/hc/en-us/articles/360012076960-Where-are-the-installed-cores-located-)
 ** to find where Arduino installs cores on your machine.
 **
 ** If the problem persists then there's not enough memory for this model and application.
 */

/* Includes ---------------------------------------------------------------- */
#include <PDM.h>

//#include <speech-recognition_inferencing.h>
//#include <Capstone26-project-1_inferencing.h> // { "Abraham", "Fire Alarm", "Jordan", "_noise", "_unknown" }
#include <Capstone26-project-2_inferencing.h> // { "Abraham", "DrSmith", "Fire Alarm", "Jordan", "_noise", "_unknown" }


#include <ArduinoBLE.h>

/** Audio buffers, pointers and selectors */
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
static bool debug_nn = false; // Set this to true to see e.g. features generated from the raw signal
static int print_results = -(EI_CLASSIFIER_SLICES_PER_MODEL_WINDOW);

static int vibration_Type[6] = {0,1,2,3,4,5};
static const int led_pin = LED_BUILTIN;
static const int VR = 3;

float confidence_lev = 0.85;

bool Abraham_on = false;
bool Alarm_on = false;
bool Jordan_on = false;
bool Smith_on = false;


BLEService ledService("180A"); // BLE LED Service

// BLE LED Switch Characteristic - custom 128-bit UUID, read and writable by central
BLEByteCharacteristic switchCharacteristic("2A57", BLERead | BLEWrite);

/**
 * @brief      Arduino setup function
 */
void setup()
{

    pinMode(led_pin, OUTPUT);
    pinMode(VR, OUTPUT);
    pinMode(LEDR, OUTPUT); //mabe writing HIGH turns off the LED
    pinMode(LEDG, OUTPUT);
    pinMode(LEDB, OUTPUT);

    digitalWrite(led_pin,HIGH); 
    digitalWrite(LEDR, HIGH);               // will turn the LED off
    digitalWrite(LEDG, HIGH);               // will turn the LED off
    digitalWrite(LEDB, HIGH);                // will turn the LED off

  //BLUETOOTH INIT FIRST 
      if (!BLE.begin()) {
//    Serial.println("starting Bluetooth® Low Energy failed!");

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

//  Serial.println("BLE LED Peripheral");

  //END OF BLUETOOTH INIT

  // AUDIO PROCESSING INIT
  
    // put your setup code here, to run once:
//    Serial.begin(115200);
    // comment out the below line to cancel the wait for USB connection (needed for native USB)
//    while (!Serial);
//    Serial.println("Edge Impulse Inferencing Demo");

    // summary of inferencing settings (from model_metadata.h)
//    ei_printf("Inferencing settings:\n");
//    ei_printf("\tInterval: %.2f ms.\n", (float)EI_CLASSIFIER_INTERVAL_MS);
//    ei_printf("\tFrame size: %d\n", EI_CLASSIFIER_DSP_INPUT_FRAME_SIZE);
//    ei_printf("\tSample length: %d ms.\n", EI_CLASSIFIER_RAW_SAMPLE_COUNT / 16);
//    ei_printf("\tNo. of classes: %d\n", sizeof(ei_classifier_inferencing_categories) /
//                                            sizeof(ei_classifier_inferencing_categories[0]));
//    vibration_Type = [1,2,3,4,5];
    run_classifier_init();
    if (microphone_inference_start(EI_CLASSIFIER_SLICE_SIZE) == false) {
//        ei_printf("ERR: Could not allocate audio buffer (size %d), this could be due to the window length of your model\r\n", EI_CLASSIFIER_RAW_SAMPLE_COUNT);
        return;
    }
}

void vibration(int type){
  switch(type)
  {
    case 0:
    {
      digitalWrite(VR,HIGH); 
      delay(100);
      digitalWrite(VR,LOW);
      delay(1000);
      break;
    }
    case 1: 
    {
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
//    ei_printf("None");
  }
}

/**
 * @brief      Arduino main function. Runs the inferencing loop.
 */
void loop()
{


    BLEDevice central = BLE.central();

    if (central) {
      //Blue LED showing connection
      digitalWrite(LEDR, HIGH);         // will turn the LED off
      digitalWrite(LEDG, HIGH);       // will turn the LED off
      digitalWrite(LEDB, LOW);         // will turn the LED on

      digitalWrite(led_pin,LOW);

      while (central.connected()) {

        if (switchCharacteristic.written()){
          switch (switchCharacteristic.value()){
            case 01:
              Abraham_on = true;
              break;
            case 02:
              Abraham_on = false;
              break;
            case 7:
              Alarm_on = true;
              break;
            case 8:
              Alarm_on = false;
              break;
            case 05:
              Jordan_on = true;
              break;
            case 06:
              Jordan_on = false;
              break;
            case 03:
              Smith_on = true;
              break;
            case 04:
              Smith_on = false;
              break;
            case 80:
              confidence_lev = 0.8;
              break;
            case 85:
              confidence_lev = 0.85;
              break;
            case 90:
              confidence_lev = 0.9;
              break;
            case 95:
              confidence_lev = 0.95;
              break;
            case 98:
              confidence_lev = 0.98;
              break;
          }
          return;
        }
    
        bool m = microphone_inference_record();
        if (!m) {
    //        ei_printf("ERR: Failed to record audio...\n");
            return;
        }
    
        signal_t signal;
        signal.total_length = EI_CLASSIFIER_SLICE_SIZE;
        signal.get_data = &microphone_audio_signal_get_data;
        ei_impulse_result_t result = {0};
    
        EI_IMPULSE_ERROR r = run_classifier_continuous(&signal, &result, debug_nn);
        if (r != EI_IMPULSE_OK) {
    //        ei_printf("ERR: Failed to run classifier (%d)\n", r);
            return;
        }
    
        // "Abraham", "Fire Alarm", "Jordan", "_noise", "_unknown"

        // new!!! { "Abraham", "DrSmith", "Fire Alarm", "Jordan", "_noise", "_unknown" }

        
        //Turn on LED if "jordan" keyword is above threshold
        if ((result.classification[0].value > confidence_lev) && Abraham_on){ //abraham - 1
          vibration(vibration_Type[2]);
        }
        else if ((result.classification[2].value > confidence_lev) && Alarm_on){ //alarm - 3
          vibration(vibration_Type[3]);
        }
        else if ((result.classification[3].value > confidence_lev) && Jordan_on){ //jordan - 2 
          vibration(vibration_Type[4]);
        }
        else if ((result.classification[1].value > confidence_lev) && Smith_on){ //smith - 2 
          vibration(vibration_Type[5]);
        }  
    
        if (++print_results >= (EI_CLASSIFIER_SLICES_PER_MODEL_WINDOW)) {
            // print the predictions
    //        ei_printf("Predictions ");
    //        ei_printf("(DSP: %d ms., Classification: %d ms., Anomaly: %d ms.)",
    //            result.timing.dsp, result.timing.classification, result.timing.anomaly);
    //        ei_printf(": \n");
            for (size_t ix = 0; ix < EI_CLASSIFIER_LABEL_COUNT; ix++) {
                ei_printf("    %s: %.5f\n", result.classification[ix].label,
                          result.classification[ix].value);
            }
    #if EI_CLASSIFIER_HAS_ANOMALY == 1
    //        ei_printf("    anomaly score: %.3f\n", result.anomaly);
    #endif
    
            print_results = 0;
        }
      }
    }
    else {
      // no connection
      digitalWrite(LEDR, HIGH);               // will turn the LED off
      digitalWrite(LEDG, HIGH);               // will turn the LED off
      digitalWrite(LEDB, HIGH);                // will turn the LED off

      digitalWrite(led_pin,HIGH);
    }
}

/**
 * @brief      PDM buffer full callback
 *             Get data and call audio thread callback
 */
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

/**
 * @brief      Init inferencing struct and setup/start PDM
 *
 * @param[in]  n_samples  The n samples
 *
 * @return     { description_of_the_return_value }
 */
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

    // initialize PDM with:
    // - one channel (mono mode)
    // - a 16 kHz sample rate
    if (!PDM.begin(1, EI_CLASSIFIER_FREQUENCY)) {
//        ei_printf("Failed to start PDM!");
    }

    // set the gain, defaults to 20
    PDM.setGain(127);

    record_ready = true;

    return true;
}

/**
 * @brief      Wait on new data
 *
 * @return     True when finished
 */
static bool microphone_inference_record(void)
{
    bool ret = true;

    if (inference.buf_ready == 1) {
//        ei_printf(
//            "Error sample buffer overrun. Decrease the number of slices per model window "
//            "(EI_CLASSIFIER_SLICES_PER_MODEL_WINDOW)\n");
        ret = false;
    }

    while (inference.buf_ready == 0) {
        delay(1);
    }

    inference.buf_ready = 0;

    return ret;
}

/**
 * Get raw audio signal data
 */
static int microphone_audio_signal_get_data(size_t offset, size_t length, float *out_ptr)
{
    numpy::int16_to_float(&inference.buffers[inference.buf_select ^ 1][offset], out_ptr, length);

    return 0;
}

/**
 * @brief      Stop PDM and release buffers
 */
static void microphone_inference_end(void)
{
    PDM.end();
    free(inference.buffers[0]);
    free(inference.buffers[1]);
    free(sampleBuffer);
}

#if !defined(EI_CLASSIFIER_SENSOR) || EI_CLASSIFIER_SENSOR != EI_CLASSIFIER_SENSOR_MICROPHONE
#error "Invalid model for current sensor."
#endif
