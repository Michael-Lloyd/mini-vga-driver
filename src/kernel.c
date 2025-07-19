#include "vga.h"
#include "frame_data.h"

void kernel_main(void) {
    // Switch to VGA mode 13h (320x200, 256 colors)
    vga_set_mode_13h();
    
    // Clear screen to black
    vga_clear_screen(0);
    
    // Draw a blue rectangle first to verify VGA is working
    for (int y = 10; y < 50; y++) {
        for (int x = 10; x < 100; x++) {
            vga_put_pixel(x, y, 1);  // Blue
        }
    }
    
    // Draw the Bad Apple frame
    for (int y = 0; y < 200; y++) {
        for (int x = 0; x < 320; x++) {
            int index = y * 320 + x;
            uint8_t color = frame_data[index];
            vga_put_pixel(x, y, color);
        }
    }
    
    // Halt
    while (1) {
        __asm__ volatile ("hlt");
    }
}