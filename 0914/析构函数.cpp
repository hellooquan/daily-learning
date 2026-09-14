#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <cstring>

class Cat
{
private:
    int fd;
    char *name;

public:
    Cat()
    {
        name = new char(20);
        strcpy(name, "Catname.txt");
        fd = open(name, O_RDWR);
        if (fd == -1)
        {
            perror("open failed");
            return;
        }
        std::cout << "构造Cat成功" << std::endl;
    }
    ~Cat()
    {
        close(fd);
        delete name;
        std::cout << "析构Cat成功" << std::endl;
    }
};
int main()
{
    Cat cat;

    return 0;
}