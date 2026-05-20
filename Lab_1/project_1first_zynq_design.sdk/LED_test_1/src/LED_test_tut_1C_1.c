#include "xparameters.h"
#include "xgpio.h"
#include "sleep.h"

// Định nghĩa kênh LED và ID của thiết bị dựa trên thông số phần cứng
#define LED_CHANNEL 1
#define GPIO_DEVICE_ID XPAR_AXI_GPIO_0_DEVICE_ID

XGpio Gpio;

int main() {
    // Khởi tạo khối giao tiếp ngoại vi với ID tương ứng
    XGpio_Initialize(&Gpio, GPIO_DEVICE_ID);

    // Thiết lập hướng của cổng giao tiếp
    // Các bit được đặt thành '0' sẽ đóng vai trò là đầu ra
    // 0x00 (tức là 00000000 trong hệ nhị phân) thiết lập cả 8 đèn LED thành đầu ra
    XGpio_SetDataDirection(&Gpio, LED_CHANNEL, 0x00);

    // Vòng lặp vô hạn để nhấp nháy đèn LED
    while (1) {
        // Trạng thái A: Bật xen kẽ các đèn (10101010 - 0xAA)
        XGpio_DiscreteWrite(&Gpio, LED_CHANNEL, 0xAA);
        usleep(500000); // Dừng 0.5 giây

        // Trạng thái B: Đảo ngược trạng thái sáng (01010101 - 0x55)
        XGpio_DiscreteWrite(&Gpio, LED_CHANNEL, 0x55);
        usleep(500000); // Dừng 0.5 giây
    }

    return 0;
}
