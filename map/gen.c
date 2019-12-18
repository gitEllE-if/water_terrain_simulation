#include <fcntl.h>
#include <unistd.h>

int main(void)
{
	int fd = open("water.txt", O_RDWR|O_CREAT, S_IWRITE | S_IREAD);
	for (int i = 0; i < 100; i++)
	{
		for (int j = 0; j < 100; j++)
		{
			if (i > 44 && i < 64 && j > 44 && j < 64)
				write(fd, "2.0", 3);
			else
				write(fd, "0.0", 3);
			if (j != 99)
				write(fd, " ", 1);
		}
		write (fd, "\n", 1);
	}
}
