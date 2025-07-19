#include "vga.h"

void kernel_main(void) {
    /* Switch to VGA mode 13h (320x200, 256 colors) */
    vga_set_mode_13h();
    
    /* Clear screen to black */
    vga_clear_screen(0);
    
    /* Draw color bars at the top */
    for (int color = 0; color < 16; color++) {
        int x_start = (color * 320) / 16;
        int x_end = ((color + 1) * 320) / 16;
        
        for (int y = 0; y < 40; y++) {
            for (int x = x_start; x < x_end; x++) {
                vga_put_pixel(x, y, color);
            }
        }
    }
    
    /* Draw a gradient pattern in the middle */
    for (int y = 50; y < 150; y++) {
        for (int x = 0; x < 320; x++) {
            uint8_t color = ((x + y) / 4) & 0xFF;
            vga_put_pixel(x, y, color);
        }
    }
    
    /* Draw some geometric shapes at the bottom */
    /* Red square */
    for (int y = 160; y < 190; y++) {
        for (int x = 20; x < 50; x++) {
            vga_put_pixel(x, y, 4);
        }
    }
    
    /* Green square */
    for (int y = 160; y < 190; y++) {
        for (int x = 70; x < 100; x++) {
            vga_put_pixel(x, y, 2);
        }
    }
    
    /* Blue square */
    for (int y = 160; y < 190; y++) {
        for (int x = 120; x < 150; x++) {
            vga_put_pixel(x, y, 1);
        }
    }
    
    /* White square */
    for (int y = 160; y < 190; y++) {
        for (int x = 170; x < 200; x++) {
            vga_put_pixel(x, y, 15);
        }
    }
    
    /* Draw diagonal lines */
    for (int i = 0; i < 200; i++) {
        if (i < 320) {
            vga_put_pixel(i, i, 14);  /* Yellow diagonal */
        }
    }
    
    /* Halt */
    while (1) {
        __asm__ volatile ("hlt");
    }
}