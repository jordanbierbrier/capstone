package com.example.strone_v0;

import android.widget.Toast;

public class RemoteControl {
//Constants that are send to the ardunio
        private final static byte Abe_Command_on = 0x1;
        private final static byte Abe_Command_off = 0x2;

        private final static byte Alarm_Command_on = 0x3;
        private final static byte Alarm_Command_off = 0x4;

        private final static byte Jor_Command_on = 0x5;
        private final static byte Jor_Command_off = 0x6;

        private final static byte Smith_Command_on = 0x7;
        private final static byte Smith_Command_off = 0x8;

        byte C_command = 0x9;


    private final static byte VALUE_OFF = 0x0;
        private final static byte VALUE_ON = (byte)0xFF;

        private com.example.strone_v0.BLEController bleController;

        public RemoteControl(com.example.strone_v0.BLEController bleController) {
            this.bleController = bleController;
        }
//creates the byte array of data that is then sent to the arduino
        private byte [] createControlWord(byte type, byte ... args) {
            byte [] command = new byte[1];
            if( args[0] == VALUE_ON){
                command[0] = type;
            }else if (args[0] == VALUE_OFF && type == Abe_Command_on )
                command[0] = Abe_Command_off;
             else if (args[0] == VALUE_OFF && type == Jor_Command_on )
                command[0] = Jor_Command_off;
             else if (args[0] == VALUE_OFF && type == Alarm_Command_on )
                command[0] = Alarm_Command_off;
            else if (args[0] == VALUE_OFF && type == Smith_Command_on )
                command[0] = Smith_Command_off;

            return command;
        }
    //sends the correct commands to the Arduino through the sendData method when Abraham is switched
        public void Abe_Switch(boolean on) {
            this.bleController.sendData(createControlWord(Abe_Command_on, on?VALUE_ON:VALUE_OFF));
        }
    //sends the correct commands to the Arduino through the sendData method when Jordan is switched
        public void Jor_Switch(boolean on) {
            this.bleController.sendData(createControlWord(Jor_Command_on, on?VALUE_ON:VALUE_OFF));
        }
    //sends the correct commands to the Arduino through the sendData method when Alarm is switched
        public void Alarm_Switch(boolean on) {
            this.bleController.sendData(createControlWord(Alarm_Command_on, on?VALUE_ON:VALUE_OFF));
        }
    //sends the correct commands to the Arduino through the sendData method when Dr. Smith is switched
        public void Smith_Switch(boolean on) {
            this.bleController.sendData(createControlWord(Alarm_Command_on, on?VALUE_ON:VALUE_OFF));
        }
    //sends the correct commands to the Arduino through the sendData method when confidence is chosen
        public void confidence(boolean on) {
            this.bleController.sendData(createControlWord(C_command, on?VALUE_ON:VALUE_OFF));
        }
    //Sets the current confidence variable
        public void setConfidence(byte c) {
            C_command = c ;
        }
}

