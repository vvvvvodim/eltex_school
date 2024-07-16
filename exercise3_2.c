#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdint.h>

// Преобразование строки IP-адреса в числовое значение
uint32_t parse_ip(const char* ip_str) {
	uint32_t ip = 0;
	uint8_t octet;
	char* ip_copy = strdup(ip_str);
	char* token = strtok(ip_copy, ".");
	for (int i = 0; i < 4; i++) {
		if (token == NULL) return 0;
		else {
			octet = (uint8_t)atoi(token);
			ip = (ip << 8) | octet;
			token = strtok(NULL, ".");
		}
	}
	free(ip_copy);
	return ip;
}

// Генерация случайного IP-адреса
uint32_t generate_ip() {
	return ((rand() % 256) << 24) | ((rand() % 256) << 16) | ((rand() % 256) << 8) | (rand() % 256);
}

// Проверка принадлежности IP-адреса к подсети
int is_in_subnet(uint32_t ip, uint32_t subnet, uint32_t mask) {
	return (ip & mask) == (subnet & mask);
}

// Вывести на экран IP-адрес
void print_ip(uint32_t ip) {
	printf("%d.%d.%d.%d", (ip >> 24) & 0xFF, (ip >> 16) & 0xFF, (ip >> 8) & 0xFF, ip & 0xFF);
}

int main(int argc, char* argv[]) {
	if (argc != 4) {
		fprintf(stderr, "Usage: %s <gateway_ip> <subnet_mask> <number_of_packets>\n", argv[0]);
		return EXIT_FAILURE;
	}
	uint32_t gateway = parse_ip(argv[1]);
	uint32_t mask = parse_ip(argv[2]);
	int N = atoi(argv[3]);

	// Инициализируем генерацию рандомных чисел
	srand(time(NULL));

	int own_IP_count = 0;
	for (int i = 0; i < N; i++) {
		uint32_t random_ip = generate_ip();
		//uint32_t random_ip = (rand() % UINT32_MAX);
		if (is_in_subnet(random_ip, gateway, mask)) own_IP_count++;
		printf("Packet %d IP: ", i + 1);
		print_ip(random_ip);
		printf(" - %s\n", is_in_subnet(random_ip, gateway, mask) ? "Same Subnet" : "Different Subnet");
	}
	printf("\nPackets destined to own subnet: %d (%.2f%%)\n", own_IP_count, own_IP_count * 100 / N);
	printf("Packets destined to other network : %d (%.2f%%)\n", N - own_IP_count, (N - own_IP_count) * 100 / N);

	return EXIT_SUCCESS;
}