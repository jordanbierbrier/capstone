package com.example.strone_v0;

import static java.lang.Math.log;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.os.Bundle;
import android.util.Log;
import android.util.Pair;
import android.view.View;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.AutoCompleteTextView;
import android.widget.Button;
import android.widget.CompoundButton;
import android.widget.Spinner;
import android.widget.Switch;
import android.widget.Toast;

import java.nio.charset.StandardCharsets;

public class KeywordPage extends AppCompatActivity{
    Button backBtn;
    Switch abeSwitch, jorSwitch, SmithSwitch, alarmSwitch;
    private boolean isAbeOn = false;
    private boolean isJorOn = false;
    private boolean isAlarmOn = false;
    private boolean isSmithOn = false;
    private final static byte eighty_command = 0x50;
    private final static byte eightyfive_command = 0x55;
    private final static byte ninty_command = 0x5a;
    private final static byte nintyfive_command = 0x5F;
    private final static byte nintyeight_command = 0x62;

    String[] item = {"80", "85", "90", "95", "98"};

    AutoCompleteTextView autoCompleteTextView;

    ArrayAdapter<String> adapterItems;


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_keyword_page);
        SwitchAbe();
        SwitchAlarm();
        SwitchJor();
        SwitchSmith();
        confidenceList();
        backBtn = findViewById(R.id.backBtn);
        backBtn.setOnClickListener(new View.OnClickListener() {
            //changes the page from keyword page to the homepage
            @Override
            public void onClick(View view) {
                Intent intent = new Intent(KeywordPage.this, HomePage.class);
                startActivity(intent);
                finish();
            }
        });

    }
//Method for changing the confidence level of the model
    private void confidenceList(){

        this.autoCompleteTextView = findViewById(R.id.confidence);

        adapterItems = new ArrayAdapter<String>(this, R.layout.list_item, item);

        autoCompleteTextView.setAdapter(adapterItems);

        autoCompleteTextView.setOnItemClickListener(new AdapterView.OnItemClickListener() {
            //checks what confidence level is chosen and uses the remote control class to set the confidence
            @Override
            public void onItemClick(AdapterView<?> adapterView, View view, int positon, long l) {
                String item = adapterView.getItemAtPosition(positon).toString();

                switch (item) {
                    case "80":
                        PairingPage.remoteControl.setConfidence(eighty_command);
                        PairingPage.remoteControl.confidence(true);
                        break;
                    case "85":
                        PairingPage.remoteControl.setConfidence(eightyfive_command);
                        PairingPage.remoteControl.confidence(true);
                        break;
                    case "90":
                        PairingPage.remoteControl.setConfidence(ninty_command);
                        PairingPage.remoteControl.confidence(true);
                        break;
                    case "95":
                        PairingPage.remoteControl.setConfidence(nintyfive_command);
                        PairingPage.remoteControl.confidence(true);
                        break;
                    case "98":
                        PairingPage.remoteControl.setConfidence(nintyeight_command);
                        PairingPage.remoteControl.confidence(true);
                        break;
                }

                //
            }
        });
    }
//When the Abraham keyword is switched on it sends a toast and calls the method Abe_switch in remote control
    private void SwitchAbe() {
        this.abeSwitch = findViewById(R.id.abeSwitch);
        this.abeSwitch.setOnCheckedChangeListener(new CompoundButton.OnCheckedChangeListener() {
            @Override
            public void onCheckedChanged(CompoundButton compoundButton, boolean b) {
                isAbeOn = !isAbeOn;
                Toast.makeText(KeywordPage.this, "im switched", Toast.LENGTH_SHORT).show();
                PairingPage.remoteControl.Abe_Switch(isAbeOn);
            }

        });
    }
//When the Jordan keyword is switched on it sends a toast and calls the method Jor_switch in remote control
    private void SwitchJor() {
        this.jorSwitch = findViewById(R.id.jorSwitch);
        this.jorSwitch.setOnCheckedChangeListener(new CompoundButton.OnCheckedChangeListener() {
            @Override
            public void onCheckedChanged(CompoundButton compoundButton, boolean b) {
                isJorOn = !isJorOn;
                Toast.makeText(KeywordPage.this, "im switched", Toast.LENGTH_SHORT).show();
                PairingPage.remoteControl.Jor_Switch(isJorOn);
            }

        });
    }

//When the Alarm keyword is switched on it sends a toast and calls the method Alarm_Switch in remote control
    private void SwitchAlarm() {
        this.alarmSwitch = findViewById(R.id.alarmSwitch);
        this.alarmSwitch.setOnCheckedChangeListener(new CompoundButton.OnCheckedChangeListener() {
            @Override
            public void onCheckedChanged(CompoundButton compoundButton, boolean b) {
                isAlarmOn = !isAlarmOn;
                Toast.makeText(KeywordPage.this, "im switched", Toast.LENGTH_SHORT).show();
                PairingPage.remoteControl.Alarm_Switch(isAlarmOn);
            }

        });
    }
//When the Dr. Smith keyword is switched on it sends a toast and calls the method Smith_Switch in remote control
    private void SwitchSmith() {
        this.SmithSwitch = findViewById(R.id.SmithSwitch);
        this.SmithSwitch.setOnCheckedChangeListener(new CompoundButton.OnCheckedChangeListener() {
            @Override
            public void onCheckedChanged(CompoundButton compoundButton, boolean b) {
                isSmithOn = !isSmithOn;
                Toast.makeText(KeywordPage.this, "im switched", Toast.LENGTH_SHORT).show();
                PairingPage.remoteControl.Smith_Switch(isSmithOn);
            }

        });
    }

}