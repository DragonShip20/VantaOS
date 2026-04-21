extern void init_idt(void);

void kernel_main() {
    char* vga = (char*)0xB8000;

    vga[0] = 'A';
    vga[1] = 0x0F;

    init_idt();

    vga[2] = 'B';
    vga[3] = 0x0F;

    while (1);
}