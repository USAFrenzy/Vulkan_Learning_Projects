#ifndef BASE_H
#define BASE_H


class BaseApplication
{
public:
    BaseApplication();
    ~BaseApplication();
    void Run();

private:
    void applicationLoop();
    void vulkanInit();
    void vulkanFree();

};



#endif // !BASE.H