static char font_chars[43][8] = {
    {
        0b00000000,
        0b00010000,
        0b00101000,
        0b01000100,
        0b01000100,
        0b01111100,
        0b01000100,
        0b01000100,
    }, // A
    {
        0b00000000,
        0b01111000,
        0b01000100,
        0b01000100,
        0b01111000,
        0b01000100,
        0b01000100,
        0b01111000,
    }, // B
    {
        0b00000000,
        0b00111000,
        0b01000100,
        0b01000000,
        0b01000000,
        0b01000000,
        0b01000100,
        0b00111000,
    }, // C
    {
        0b00000000,
        0b01111000,
        0b01000100,
        0b01000100,
        0b01000100,
        0b01000100,
        0b01000100,
        0b01111000,
    }, // D
    {
        0b00000000,
        0b01111100,
        0b01000000,
        0b01000000,
        0b01111000,
        0b01000000,
        0b01000000,
        0b01111100,
    }, // E
    {
        0b00000000,
        0b01111100,
        0b01000000,
        0b01000000,
        0b01111000,
        0b01000000,
        0b01000000,
        0b01000000,
    }, // F
    {
        0b00000000,
        0b00111100,
        0b01000000,
        0b01000000,
        0b01000000,
        0b01001100,
        0b01000100,
        0b00111100,
    }, // G
    {
        0b00000000,
        0b01000100,
        0b01000100,
        0b01000100,
        0b01111100,
        0b01000100,
        0b01000100,
        0b01000100,
    }, // H
    {
        0b00000000,
        0b00111000,
        0b00010000,
        0b00010000,
        0b00010000,
        0b00010000,
        0b00010000,
        0b00111000,
    }, // I
    {
        0b00000000,
        0b00000100,
        0b00000100,
        0b00000100,
        0b00000100,
        0b00000100,
        0b01000100,
        0b00111000,
    }, // J
    {
        0b00000000,
        0b01000100,
        0b01001000,
        0b01010000,
        0b01100000,
        0b01010000,
        0b01001000,
        0b01000100,
    }, // K
    {
        0b00000000,
        0b01000000,
        0b01000000,
        0b01000000,
        0b01000000,
        0b01000000,
        0b01000000,
        0b01111100,
    }, // L
    {
        0b00000000,
        0b01000100,
        0b01101100,
        0b01010100,
        0b01010100,
        0b01000100,
        0b01000100,
        0b01000100,
    }, // M
    {
        0b00000000,
        0b01000100,
        0b01000100,
        0b01100100,
        0b01010100,
        0b01001100,
        0b01000100,
        0b01000100,
    }, // N
    {
        0b00000000,
        0b00111000,
        0b01000100,
        0b01000100,
        0b01000100,
        0b01000100,
        0b01000100,
        0b00111000,
    }, // O
    {
        0b00000000,
        0b01111000,
        0b01000100,
        0b01000100,
        0b01111000,
        0b01000000,
        0b01000000,
        0b01000000,
    }, // P
    {
        0b00000000,
        0b00111000,
        0b01000100,
        0b01000100,
        0b01000100,
        0b01010100,
        0b01001000,
        0b00110100,
    }, // Q
    {
        0b00000000,
        0b01111000,
        0b01000100,
        0b01000100,
        0b01111000,
        0b01010000,
        0b01001000,
        0b01000100,
    }, // R
    {
        0b00000000,
        0b00111000,
        0b01000100,
        0b01000000,
        0b00111000,
        0b00000100,
        0b01000100,
        0b00111000,
    }, // S
    {
        0b00000000,
        0b01111100,
        0b00010000,
        0b00010000,
        0b00010000,
        0b00010000,
        0b00010000,
        0b00010000,
    }, // T
    {
        0b00000000,
        0b01000100,
        0b01000100,
        0b01000100,
        0b01000100,
        0b01000100,
        0b01000100,
        0b00111000,
    }, // U
    {
        0b00000000,
        0b01000100,
        0b01000100,
        0b01000100,
        0b01000100,
        0b01000100,
        0b00101000,
        0b00010000,
    }, // V
    {
        0b00000000,
        0b01000100,
        0b01000100,
        0b01000100,
        0b01010100,
        0b01010100,
        0b01101100,
        0b01000100,
    }, // W
    {
        0b00000000,
        0b01000100,
        0b01000100,
        0b00101000,
        0b00010000,
        0b00101000,
        0b01000100,
        0b01000100,
    }, // X
    {
        0b00000000,
        0b01000100,
        0b01000100,
        0b00101000,
        0b00010000,
        0b00010000,
        0b00010000,
        0b00010000,
    }, // Y
    {
        0b00000000,
        0b01111100,
        0b00000100,
        0b00001000,
        0b00010000,
        0b00100000,
        0b01000000,
        0b01111100,
    }, // Z
    {
        0b00000000,
        0b00111000,
        0b01000100,
        0b01001100,
        0b01010100,
        0b01100100,
        0b01000100,
        0b00111000,
    }, // 0
    {
        0b00000000,
        0b00010000,
        0b00110000,
        0b00010000,
        0b00010000,
        0b00010000,
        0b00010000,
        0b00111000,
    }, // 1
    {
        0b00000000,
        0b00111000,
        0b01000100,
        0b00000100,
        0b00011000,
        0b00100000,
        0b01000000,
        0b01111100,
    }, // 2
    {
        0b00000000,
        0b01111100,
        0b00000100,
        0b00001000,
        0b00011000,
        0b00000100,
        0b01000100,
        0b00111000,
    }, // 3
    {
        0b00000000,
        0b00001000,
        0b00011000,
        0b00101000,
        0b01001000,
        0b01111100,
        0b00001000,
        0b00001000,
    }, // 4
    {
        0b00000000,
        0b01111100,
        0b01000000,
        0b01111000,
        0b00000100,
        0b00000100,
        0b01000100,
        0b00111000,
    }, // 5
    {
        0b00000000,
        0b00011100,
        0b00100000,
        0b01000000,
        0b01111000,
        0b01000100,
        0b01000100,
        0b00111000,
    }, // 6
    {
        0b00000000,
        0b01111100,
        0b00000100,
        0b00001000,
        0b00010000,
        0b00100000,
        0b00100000,
        0b00100000,
    }, // 7
    {
        0b00000000,
        0b00111000,
        0b01000100,
        0b01000100,
        0b00111000,
        0b01000100,
        0b01000100,
        0b00111000,
    }, // 8
    {
        0b00000000,
        0b00111000,
        0b01000100,
        0b01000100,
        0b00111100,
        0b00000100,
        0b00001000,
        0b01110000,
    }, // 9
    {
        0b00000000,
        0b00001000,
        0b00010000,
        0b00100000,
        0b01000000,
        0b00100000,
        0b00010000,
        0b00001000,
    }, // <
    {
        0b00000000,
        0b00000000,
        0b00000000,
        0b01111100,
        0b00000000,
        0b01111100,
        0b00000000,
        0b00000000,
    }, // =
    {
        0b00000000,
        0b00100000,
        0b00010000,
        0b00001000,
        0b00000100,
        0b00001000,
        0b00010000,
        0b00100000,
    }, // >
    {
        0b00000000,
        0b00111000,
        0b01000100,
        0b00001000,
        0b00010000,
        0b00010000,
        0b00000000,
        0b00010000,
    }, // ?
    {
        0b00000000,
        0b00010000,
        0b01010100,
        0b00111000,
        0b00010000,
        0b00111000,
        0b01010100,
        0b00010000,
    }, // *
    {
        0b00000000,
        0b00000000,
        0b00000000,
        0b00000000,
        0b01111100,
        0b00000000,
        0b00000000,
        0b00000000,
    }, // -
    {
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
    }, // <space>
};
