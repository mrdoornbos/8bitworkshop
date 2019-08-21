
#include "bios.h"

#pragma opt_code_speed

#define LOCHAR 0x20
#define HICHAR 0x63

const byte LMASK[4] = {0xff, 0x3f, 0x0f, 0x03};

static void hline(byte x1, byte x2, byte y, byte pattern) {
  byte xb1 = x1/4;
  byte xb2 = x2/4;
  byte* dest = &vidmem[y][xb1];
  byte mask = LMASK[x1&3];
  if (xb1 == xb2) {
    mask &= ~LMASK[x2&3];
  }
  *dest = *dest & ~mask | (mask & pattern);
  if (xb1 != xb2) {
    dest++;
    while (++xb1 < xb2) {
      *dest++ = pattern;
    }
    *dest = *dest & LMASK[x2&3] | (~LMASK[x2&3] & pattern);
  }
}

// Fill rect (E,D,C,B) color A
void RECTAN(const ContextBlock *ctx) {
  for (byte y=_D; y<_D+_B; y++) {
    hline(_E, _E+_C, y, _A);
  }
}

const char BIGFONT[HICHAR-LOCHAR+1][7] = {/*{count:68,w:8,h:7,brev:1}*/
{0x00,0x00,0x00,0x00,0x00,0x00,0x00},{0x20,0x20,0x20,0x20,0x00,0x00,0x20},{0x50,0x50,0x00,0x00,0x00,0x00,0x00},{0x48,0xFC,0x48,0x48,0x48,0xFC,0x48},{0x20,0x78,0x80,0x70,0x08,0xF0,0x20},{0x00,0x48,0x10,0x20,0x40,0x90,0x00},{0x60,0x90,0x60,0xA0,0xA8,0x90,0x68},{0x60,0x60,0x20,0x00,0x00,0x00,0x00},{0x20,0x40,0x40,0x40,0x40,0x40,0x20},{0x40,0x20,0x20,0x20,0x20,0x20,0x40},{0x00,0xA8,0x70,0xF8,0x70,0xA8,0x00},{0x00,0x20,0x20,0xF8,0x20,0x20,0x00},{0x00,0x00,0x00,0x00,0x60,0x20,0x40},{0x00,0x00,0x00,0xF0,0x00,0x00,0x00},{0x00,0x00,0x00,0x00,0x00,0x60,0x60},{0x00,0x08,0x10,0x20,0x40,0x80,0x00},{0x70,0x88,0x88,0xA8,0x88,0x88,0x70},{0x20,0x60,0x20,0x20,0x20,0x20,0x70},{0x70,0x88,0x08,0x30,0x40,0x80,0xF8},{0x70,0x88,0x08,0x70,0x08,0x88,0x70},{0x10,0x30,0x50,0x90,0xF8,0x10,0x10},{0xF8,0x80,0x80,0x70,0x08,0x88,0x70},{0x70,0x88,0x80,0xF0,0x88,0x88,0x70},{0xF8,0x88,0x10,0x20,0x20,0x20,0x20},{0x70,0x88,0x88,0x70,0x88,0x88,0x70},{0x70,0x88,0x88,0x78,0x08,0x88,0x70},{0x00,0x00,0x60,0x00,0x60,0x00,0x00},{0x00,0x00,0x60,0x00,0x60,0x20,0x40},{0x10,0x20,0x40,0x80,0x40,0x20,0x10},{0x00,0x00,0xF8,0x00,0xF8,0x00,0x00},{0x40,0x20,0x10,0x08,0x10,0x20,0x40},{0x70,0x08,0x08,0x30,0x20,0x00,0x20},{0x70,0x88,0xB8,0xA8,0x90,0x80,0x70},{0x70,0x88,0x88,0xF8,0x88,0x88,0x88},{0xF0,0x88,0x88,0xF0,0x88,0x88,0xF0},{0x70,0x88,0x80,0x80,0x80,0x88,0x70},{0xF0,0x88,0x88,0x88,0x88,0x88,0xF0},{0xF8,0x80,0x80,0xF0,0x80,0x80,0xF8},{0xF8,0x80,0x80,0xF0,0x80,0x80,0x80},{0x70,0x88,0x80,0xB0,0x88,0x88,0x70},{0x88,0x88,0x88,0xF8,0x88,0x88,0x88},{0x70,0x20,0x20,0x20,0x20,0x20,0x70},{0x08,0x08,0x08,0x08,0x88,0x88,0x70},{0x88,0x90,0xA0,0xC0,0xA0,0x90,0x88},{0x80,0x80,0x80,0x80,0x80,0x80,0xF8},{0x88,0xD8,0xA8,0x88,0x88,0x88,0x88},{0x88,0xC8,0xA8,0xA8,0x98,0x88,0x88},{0xF8,0x88,0x88,0x88,0x88,0x88,0xF8},{0xF0,0x88,0x88,0xF0,0x80,0x80,0x80},{0x70,0x88,0x88,0xA8,0xA8,0x90,0x68},{0xF0,0x88,0x88,0xF0,0x90,0x90,0x88},{0x70,0x88,0x80,0x70,0x08,0x88,0x70},{0xF8,0x20,0x20,0x20,0x20,0x20,0x20},{0x88,0x88,0x88,0x88,0x88,0x88,0x70},{0x88,0x88,0x88,0x88,0x88,0x50,0x20},{0x88,0x88,0x88,0x88,0xA8,0xD8,0x88},{0x88,0x88,0x50,0x20,0x50,0x88,0x88},{0x88,0x88,0x50,0x20,0x20,0x20,0x20},{0xF8,0x08,0x10,0x20,0x40,0x80,0xF8},{0x70,0x40,0x40,0x40,0x40,0x40,0x70},{0x00,0x80,0x40,0x20,0x10,0x08,0x00},{0x70,0x10,0x10,0x10,0x10,0x10,0x70},{0x20,0x70,0xA8,0x20,0x20,0x20,0x00},{0x00,0x20,0x40,0xF8,0x40,0x20,0x00},{0x00,0x20,0x20,0x20,0xA8,0x70,0x20},{0x00,0x20,0x10,0xF8,0x10,0x20,0x00},{0x00,0x88,0x50,0x20,0x50,0x88,0x00},{0x00,0x20,0x00,0xF8,0x00,0x20,0x00}};

const char SMLFONT[HICHAR-LOCHAR+1][5] = {/*{count:68,w:5,h:5,brev:1}*/
{ 0x00,0x00,0x00,0x00,0x00 },{ 0x40,0x40,0x00,0x40,0x00 },{ 0xA0,0xA0,0x00,0x00,0x00 },{ 0x60,0xF0,0xF0,0x60,0x00 },{ 0x40,0xE0,0xE0,0x40,0x00 },{ 0x90,0x20,0x40,0x90,0x00 },{ 0xC0,0xB0,0xE0,0xD0,0x00 },{ 0x20,0x40,0x00,0x00,0x00 },{ 0x20,0x40,0x40,0x20,0x00 },{ 0x40,0x20,0x20,0x40,0x00 },{ 0x40,0xE0,0x40,0xA0,0x00 },{ 0x00,0x40,0xE0,0x40,0x00 },{ 0x00,0x00,0x00,0x60,0x20 },{ 0x00,0x00,0xE0,0x00,0x00 },{ 0x00,0x00,0x00,0x40,0x00 },{ 0x20,0x20,0x40,0x40,0x00 },{ 0xE0,0xA0,0xA0,0xA0,0xE0 },{ 0xC0,0x40,0x40,0x40,0xE0 },{ 0xE0,0x20,0xE0,0x80,0xE0 },{ 0xE0,0x20,0x60,0x20,0xE0 },{ 0xA0,0xA0,0xE0,0x20,0x20 },{ 0xE0,0x80,0xE0,0x20,0xE0 },{ 0xE0,0x80,0xE0,0xA0,0xE0 },{ 0xE0,0x20,0x40,0x40,0x40 },{ 0xE0,0xA0,0xE0,0xA0,0xE0 },{ 0xE0,0xA0,0xE0,0x20,0xE0 },{ 0x00,0x40,0x00,0x40,0x00 },{ 0x00,0x40,0x00,0x60,0x20 },{ 0x00,0x20,0x40,0x20,0x00 },{ 0x00,0xE0,0x00,0xE0,0x00 },{ 0x00,0x40,0x20,0x40,0x00 },{ 0xE0,0x20,0x60,0x00,0x40 },{ 0xF0,0x90,0x10,0xD0,0xF0 },{ 0x60,0xA0,0xE0,0xA0,0x00 },{ 0xC0,0xE0,0xA0,0xE0,0x00 },{ 0x60,0x80,0x80,0xE0,0x00 },{ 0xC0,0xA0,0xA0,0xC0,0x00 },{ 0xE0,0xC0,0x80,0xE0,0x00 },{ 0xE0,0xC0,0x80,0x80,0x00 },{ 0x60,0x80,0xA0,0xE0,0x00 },{ 0xA0,0xA0,0xE0,0xA0,0x00 },{ 0xE0,0x40,0x40,0xE0,0x00 },{ 0x60,0x20,0xA0,0xE0,0x00 },{ 0xA0,0xC0,0xC0,0xA0,0x00 },{ 0x80,0x80,0x80,0xE0,0x00 },{ 0xE0,0xE0,0xE0,0xA0,0x00 },{ 0xE0,0xA0,0xA0,0xA0,0x00 },{ 0xE0,0xA0,0xA0,0xE0,0x00 },{ 0xE0,0xA0,0xE0,0x80,0x00 },{ 0xE0,0xA0,0xE0,0xF0,0x00 },{ 0xE0,0xA0,0xC0,0xA0,0x00 },{ 0xE0,0x80,0x60,0xE0,0x00 },{ 0xE0,0x40,0x40,0x40,0x00 },{ 0xA0,0xA0,0xA0,0xE0,0x00 },{ 0xA0,0xA0,0xC0,0x80,0x00 },{ 0xA0,0xE0,0xE0,0xE0,0x00 },{ 0xA0,0x40,0xA0,0xA0,0x00 },{ 0xA0,0xE0,0x40,0x40,0x00 },{ 0xE0,0x20,0x40,0xE0,0x00 },{ 0x60,0x40,0x40,0x60,0x00 },{ 0x40,0x40,0x20,0x20,0x00 },{ 0x60,0x20,0x20,0x60,0x00 },{ 0x40,0xA0,0x00,0x00,0x00 },{ 0x00,0x00,0x00,0x00,0xF0 },{ 0x80,0x40,0x00,0x00,0x00 },{ 0x00,0x60,0xA0,0xE0,0x00 },{ 0x80,0xE0,0xA0,0xE0,0x00 },{ 0x00,0x60,0x80,0xE0,0x00 }};

// draw a letter
static byte draw_char(const FontDescriptor* font, byte ch, byte x, byte y, byte op) {
  const byte* src = font->chartab + (ch-font->base_ch)*font->pattern_y;
  byte* dest = &vmagic[y][x>>2];// destination address
  byte magic = M_SHIFT(x) | M_XPAND | (op & 0x30);
  // big sizes?
  if (op & 0xc0) {
    char buf[8];		// expansion buffer
    char* mbuf = (buf - 0x4000);// make it magic
    byte sc = 1 << (op >> 6); // 2x2 = 2, 4x4 = 4, 8x8 = 8
    for (byte i=0; i<font->pattern_y; i++) {
      // expand into magic buffer onto stack
      hw_magic = M_XPAND;
      hw_xpand = 0b1100;	// on = 11, off = 00
      // 2x2 size
      mbuf[1] = mbuf[0] = *src++;
      // 4x4 size
      if (op & 0x80) {
        byte b = buf[0];
        mbuf[3] = mbuf[2] = buf[1];
        mbuf[1] = mbuf[0] = b;
      }
      // 8x8 size
      if ((op & 0xc0) == 0xc0) {
        byte b = buf[0];
        mbuf[7] = mbuf[6] = buf[3];
        mbuf[5] = mbuf[4] = buf[2];
        mbuf[3] = mbuf[2] = buf[1];
        mbuf[1] = mbuf[0] = b;
      }
      // draw to screen (magic, again)
      hw_xpand = op & 0xf;
      for (byte j=0; j<sc; j++) {
        hw_magic = magic; // reset flip flop
        EXIT_CLIPDEST(dest);
        for (byte k=0; k<sc; k++) {
          byte b = buf[k];
          *dest++ = b;
          *dest++ = b;
        }
        dest += VBWIDTH-sc*2;
      }
    }
  } else {
    hw_xpand = op & 0xf;
    for (byte i=0; i<font->pattern_y; i++) {
      char b = *src++;
      EXIT_CLIPDEST(dest);
      hw_magic = magic; // reset flip flop
      *dest++ = b;	// expand lower nibble -> 1st byte
      *dest++ = b;	// expand upper nibble -> 2nd byte
      *dest++ = 0;	// leftover -> 3rd byte
      dest += VBWIDTH-3;	// we incremented 3 bytes for this line
    }
  }
  return font->frame_x << (op >> 6);
}

#define FONT_IX ((const FontDescriptor*)ctx->regs.w.ix)

static void draw_string(ContextBlock *ctx, const char* str, byte x, byte y, byte op) {
  do {
    byte ch = *str++;
    if (!ch) {
      _E = x;
      break;
    }
    if (ch < 0x20) {
      x += draw_char(&FNTSYS, ' ', x, y, op); // TODO
    } else if (ch < 0x64) {
      x += draw_char(&FNTSYS, ch, x, y, op);
    } else if (ch >= 0x80) {
      x += draw_char(FONT_IX, ch, x, y, op);
    } else {
      /*
      if (ch & 0x10) {
        ctx->regs.b.ixl = *str++;
        ctx->regs.b.ixh = *str++;
      }
      if (ch & 0x1)
        _E = *str++;
      if (ch & 0x2)
        _D = *str++;
      if (ch & 0x4)
        _C = *str++;
      */
      // TODO: only can change font
    }
  } while (1);
}

// String display routine (pass pointer to string)
void STRDIS2(ContextBlock *ctx, char *str) {
  byte opts = _C;
  byte x = _E;
  byte y = _D;
  void* fontdesc = (void*) ctx->regs.w.ix;
  draw_string(ctx, str, x, y, opts); // TODO: opts
}

// String display routine
void STRDIS(ContextBlock *ctx) {
  char* str = (char*) _HL;
  STRDIS2(ctx, str);
}

// Character display routine
void CHRDIS(ContextBlock *ctx) {
  char chstr[2];
  chstr[0] = _A;
  chstr[1] = 0;
  STRDIS2(ctx, chstr);
}

// BCD routine
const char BCDTAB[18] = "0123456789*+,-./ ";

// DISNUM - (E.D) x/y (C) options (B) ext (HL) BCD-addr
void DISNUM(ContextBlock *ctx) {
  // TODO: options, B
  byte x = _E;
  byte y = _D;
  byte opt = _C;
  byte ext = _B;
  byte ndigits = ext & 63;
  const FontDescriptor* font = (ext&64) ? &FNTSML : &FNTSYS;
  byte add = (ext&64) ? 128 : 0;
  byte noleadingzero = ext & 128;
  byte* pbcd = (byte*) _HL;
  pbcd += (ndigits-1)/2;
  while (ndigits--) {
    byte val = *pbcd;
    if (ndigits & 1) {
      val >>= 4;
    } else {
      val &= 15;
      pbcd--;
    }
    if (val == 0 && noleadingzero) {
      val = 16;
    } else {
      noleadingzero = 0;
    }
    x += draw_char(font, BCDTAB[val]+add, x, y, opt);
  }
}

// write pattern (E,D,C,B) magic A @ HL
void WRIT(ContextBlock *ctx) {
  byte w = _C;
  byte h = _B;
  byte x = _E;
  byte y = _D;
  byte magic = _A | (x & 3);	// add X shift
  byte* src = (byte*) _HL;
  byte* dest = &vmagic[y][0]; // destination address
  byte xb = (magic & M_FLOP) ? (39-(x>>2)) : (x>>2);
  byte i,j,b;
  // iterate through all lines
  for (j=0; j<h; j++) {
    EXIT_CLIPDEST(dest);
    hw_magic = magic;
    if (magic & M_XPAND) {
      // when XPAND set, write twice as many bytes
      for (i=0; i<w*2; i+=2) {
        b = *src++;
        // when FLOP set, sprite position is also mirrored
        if (magic & M_FLOP) {
          dest[xb-i] = b;
          dest[xb-i-1] = b;
        } else {
          dest[xb+i] = b;
          dest[xb+i+1] = b;
        }
      }
    } else {
      for (i=0; i<w; i++) {
        // when FLOP set, sprite position is also mirrored
        if (magic & M_FLOP) {
          dest[xb-i] = *src++;
        } else {
          dest[xb+i] = *src++;
        }
      }
    }
    if (magic & M_FLOP)
      dest[xb-i] = 0;
    else
      dest[xb+i] = 0;
    dest += VBWIDTH;
  }
}

// write sized pattern (E,D) magic A @ HL
void WRITP(ContextBlock *ctx) {
  byte* src = (byte*) _HL;
  // get size
  _C = *src++;
  _B = *src++;
  // update src
  _HL = (word) src;
  WRIT(ctx);
}

// write relative pattern (E,D) magic A @ HL
void WRITR(ContextBlock *ctx) {
  byte* src = (byte*) _HL;
  // sub offset
  _E -= *src++;
  _D -= *src++;
  // update src
  _HL = (word) src;
  WRITP(ctx);
}

