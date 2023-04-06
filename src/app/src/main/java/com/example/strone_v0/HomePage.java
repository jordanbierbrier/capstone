package com.example.strone_v0;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;

public class HomePage extends AppCompatActivity {
    Button pairingBtn, keywordBtn, logoutBtn;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_home_page);

        //Gives logic to the pairing button, when clicked it switches to the pairing page
        pairingBtn = findViewById(R.id.temp1);
        pairingBtn.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Intent intent = new Intent(HomePage.this, PairingPage.class);
                startActivity(intent);
                finish();
            }
        });

        //Gives logic to the keyword button, when clicked it switches to the keyword page
        keywordBtn = findViewById(R.id.temp2);
        keywordBtn.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Intent intent = new Intent(HomePage.this, KeywordPage.class);
                startActivity(intent);
                finish();
            }
        });

        //Gives logic to the logout button, when clicked it switches to the welcome page
        logoutBtn = findViewById(R.id.logoutBtn);
        logoutBtn.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Intent intent = new Intent(HomePage.this, MainActivity.class);
                startActivity(intent);
                finish();
            }
        });

    }
}