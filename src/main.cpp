/**
 * VÍ DỤ 3-02: QUẢN LÝ THẺ NHỚ BẰNG LỆNH KIỂU LINUX
 */
#include <Arduino.h>
#include <PTITCube.h>

PTIT_CDH cdh;
PTIT_Storage storage;

void setup() {
    cdh.begin(115200);
    storage.init();

    if (storage.isReady()) {
        cdh.println("CDH-FS: Shell CLI Ready (Go 'help' de xem danh sach lenh)");
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
            } else {
                cdh.println("Command not recognized. Type 'help' for commands.");
            }
        }
    }
}
