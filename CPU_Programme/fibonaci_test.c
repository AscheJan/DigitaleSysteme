
char text[] = "Hello world!\r\n";
char az[] = "Text ";  
char bz[] = " characters long\r\n";  

volatile char *serial_tx        = (char *)0xE0000000;
volatile char *serial_tx_full   = (char *)0xE0000004;
volatile char *serial_rx        = (char *)0xE0000008;
volatile char *serial_rx_empty  = (char *)0xE000000C;
volatile int  *gpio_value       = (int  *)0xE0000010;
volatile int  *gpio_direction   = (int  *)0xE0000014;

int getchar(void) {

  // Wait until status is zero 
  while(*serial_rx_empty) {
  }

  // Output character
  return *serial_rx;
}

int putchar(int c) {

  // Wait until status is zero 
  while(*serial_tx_full) {
  }

  // Output character
  *serial_tx = c;
  return c;
}

int puts(char *s) {
    int n = 0;
    while(*s) {
      putchar(*s);
      s++;
      n++;
    } 
    return n;
}

int mylen(char *s) {
    int n = 0;
    while(*s) {
      s++;
      n++;
    } 
    return n;
}

int test_program(void) {
puts("Start\r\n");
*gpio_direction = 0xFFFF;

int a = 1;
int b = 1;

for (;;) {
	int c = a + b;
	a = b;
	b = c;
	*gpio_value = a;
	for (int i = 0; i < 500000; i++);
	//getchar();
	}
  return 0;
}
