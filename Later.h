#pragma once

class Later
{
public:
    //int f = 1;

    template <class callable, class... arguments>
    Later(int after, bool async, callable&& f, arguments&&... args)
    {
        std::function<typename std::result_of<callable(arguments...)>::type()> task(std::bind(std::forward<callable>(f), std::forward<arguments>(args)...));

        if (async)
        {
            std::thread([after, task]() {
                while (1) {
                    std::this_thread::sleep_for(std::chrono::milliseconds(after));
                    task();
                }
                }).detach();
        }
        else
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(after));
            task();
        }
    }

};

