void kmain(void) {
  char *video_mem = (char *)0xb8000;
  video_mem[0] = 'A';
  video_mem[1] = 0x04;
}
