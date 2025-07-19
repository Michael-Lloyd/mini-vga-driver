#ifndef VGA_H
#define VGA_H

#include <stdint.h>

/* VGA memory addresses */
#define VGA_TEXT_BUFFER 0xB8000      /* Text mode video memory */
#define VGA_GRAPHICS_BUFFER 0xA0000  /* Graphics mode video memory */

/* VGA mode 13h resolution (320x200, 256 colors) */
#define VGA_WIDTH 320
#define VGA_HEIGHT 200

/* VGA register I/O ports */
#define VGA_AC_INDEX 0x3C0        /* Attribute Controller Index */
#define VGA_AC_WRITE 0x3C0        /* Attribute Controller Write */
#define VGA_AC_READ 0x3C1         /* Attribute Controller Read */
#define VGA_MISC_WRITE 0x3C2      /* Miscellaneous Output Register */
#define VGA_SEQ_INDEX 0x3C4       /* Sequencer Index */
#define VGA_SEQ_DATA 0x3C5        /* Sequencer Data */
#define VGA_GC_INDEX 0x3CE        /* Graphics Controller Index */
#define VGA_GC_DATA 0x3CF         /* Graphics Controller Data */
#define VGA_CRTC_INDEX 0x3D4      /* CRT Controller Index */
#define VGA_CRTC_DATA 0x3D5       /* CRT Controller Data */
#define VGA_INSTAT_READ 0x3DA     /* Input Status Read */

void vga_set_mode_13h(void);
void vga_put_pixel(uint16_t x, uint16_t y, uint8_t color);
void vga_clear_screen(uint8_t color);

#endif