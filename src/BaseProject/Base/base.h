

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