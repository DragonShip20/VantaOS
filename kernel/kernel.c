void kernel_main() {
    char* vga = (char*)0xB8000;

    vga[0] = '.';   // znak
    vga[1] = 0x0F;  // kolor (jasnoszary na czarnym tle)

    while (1);
}