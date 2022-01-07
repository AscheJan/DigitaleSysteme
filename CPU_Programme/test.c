
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


//K&R implementation - erste Ueberlegung
void itoa(int n, char s[]){
	int i;
	int sign;
	if ((sign = n) < 0){
		n = -n;
	}
	do {
		s[i++] = n % 10 + '0';
	} while ((n /= 10) > 0);
	if (sign < 0){
		s[i++] = '-';
	s[i] = '\0';
	reverse(s);
}

 reverse(char s[]){
	int i;
	int j;
	char c;
	
	for (i = 0; j = strlen(s) - 1; i < j; i++, j--){
	c = s[i];
	s[i] = s[j];
	s[j] = c;
	}
}

}

int test_program(void) {
  puts("System restart\r\n");  

  /* Check some junk in memory */
  puts("String is ");
  putchar('0'+mylen(az));
  puts(" characters long\r\n");

  puts(az);
  putchar('0'+mylen(az));
  puts(bz);

  /* Run a serial port echo */
  *gpio_direction = 0xFFFF;
  while(1) {
    putchar(getchar());
    *gpio_value = *gpio_value + 1;
   
     
   puts(" Die Anzahl der Tasteneingaben:\r\n");
   puts(itoa(*gpio_value);
  }
  return 0;
}
