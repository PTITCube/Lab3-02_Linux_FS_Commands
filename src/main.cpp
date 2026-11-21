/**
 * VÍ DỤ 3-02: QUẢN LÝ THẺ NHỚ BẰNG LỆNH KIỂU LINUX
 */
#include <Arduino.h>
#include <PTITCube.h>

PTIT_CDH cdh;
PTIT_EPS eps;
PTIT_Storage storage;

void setup() {
    cdh.begin();

    // Kích hoạt hạ áp cấp nguồn ngoại vi trên PCB vệ tinh qua thư viện EPS
    eps.setBuckState(true);

    storage.init();

    if (storage.isReady()) {
        } else {
        cdh.println("CDH-FS: Error: SD Card not ready.");
    }
}

void loop() {
    if (cdh.available()) {
        String cmd = cdh.readStringUntil('\n');
        cmd.trim();
        
        if (cmd.length() > 0) {
            cdh.println("> " + cmd);
            String response = storage.handleCommand(cmd);
            if (response.length() > 0) {
                cdh.println(response);
            }
        }
    }
}
