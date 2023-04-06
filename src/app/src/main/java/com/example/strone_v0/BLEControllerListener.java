package com.example.strone_v0;

public interface BLEControllerListener {
    void BLEControllerConnected();
    void BLEControllerDisconnected();
    void BLEDeviceFound(String name, String address);
}
