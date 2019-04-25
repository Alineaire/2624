#ifndef TIME_H
#define TIME_H


class Time
{
    public:
        Time();
        virtual ~Time();
        static Time* Instance()
        {
            if (Time::m_instance == nullptr)
            {
                Time::m_instance = new Time();
            }
            return Time::m_instance;
        }

        void init();
        void update();
        float ActualTime() { return time; }
        float DeltaTime() { return deltaTime; }

    protected:

    private:
        static Time* m_instance;
        float time;
        float deltaTime;
};

#endif // TIME_H
