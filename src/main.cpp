/**
 * VÍ DỤ 2: QUẢN LÝ THẺ NHỚ BẰNG LỆNH KIỂU LINUX
 * 
 * Mô tả:
 * Ví dụ này mô phỏng cách nhận lệnh từ một cổng cdh (ví dụ Ground Station)
 * và chuyển nó cho Storage module xử lý như một file system của Linux.
 *
 * Các lệnh hỗ trợ: pwd, cd, ls, mkdir, rm, touch
 */

#include <Arduino.h>

#include <PTITCube.h>

PTIT_CDH cdh;

PTIT_Storage storage;

void setup() {
    cdh.begin(115200);
    while (!cdh) { delay(10); }

    cdh.println("\n[EXAMPLE] Khởi động hệ thống lưu trữ...");
    storage.init();
    
    if (storage.isReady()) {
        cdh.println("[EXAMPLE] SD Card đã sẵn sàng!");
        cdh.println("Bạn có thể gõ các lệnh sau vào ô cdh Monitor (kèm Enter/NL):");
        cdh.println("  pwd      - Xem thư mục hiện tại");
        cdh.println("  ls       - Liệt kê file và thư mục");
        cdh.println("  mkdir x  - Tạo thư mục tên x");
        cdh.println("  cd x     - Chuyển vào thư mục x");
        cdh.println("  touch x  - Tạo file x");
        cdh.println("  rm x     - Xóa file hoặc thư mục x");
    } else {
        cdh.println("[EXAMPLE] LỖI: Không tìm thấy thẻ SD.");
    }
}

void loop() {
    // Đọc lệnh từ cdh Monitor
    if (cdh.available()) {
        String cmd = cdh.readStringUntil('\n');
        cmd.trim();
        
        if (cmd.length() > 0) {
            cdh.print("User> ");
            cdh.println(cmd);
            
            // Xử lý lệnh
            String response = storage.handleCommand(cmd);
            
            if (response == "") {
                cdh.println("Lệnh không hợp lệ.");
            } else {
                cdh.println(response);
            }
                    }
    }
}
