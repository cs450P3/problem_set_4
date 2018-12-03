
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


int main()
{

	int bits_specifying_virtual_page = 7;
	int bits_in_physical_address = 8;

	// is this a physical page?
	int number_of_bytes_in_a_page = 32;

	int address = 0x89115670;
	char buffer[50];
	sprintf(buffer, "%x", address);

	printf("%s\n", buffer);

	// the virtual segment size = bits_specifying_virtual_page
	// the remaining bits are the offset

	int physical_page_number_offset = bits_in_physical_address - bits_specifying_virtual_page;

	int size_of_segment = sizeof(char) * bits_specifying_virtual_page;

	char* virtual_segment = malloc(size_of_segment);

	memcpy(virtual_segment, buffer, size_of_segment);
	virtual_segment[size_of_segment] = '\0';
	printf("%s\n", virtual_segment);


	int size_of_physical_offset = sizeof(char) * physical_page_number_offset;

	char* physical_offset = malloc(size_of_physical_offset);
	memcpy(physical_offset, buffer + size_of_segment, size_of_physical_offset);

	physical_offset[physical_page_number_offset] = '\0';
	printf("%s\n", physical_offset);

	int index = atoi(virtual_segment);
	printf("index = %i\n", index);



















	return 0;
}
