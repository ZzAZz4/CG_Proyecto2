

#ifndef OGL_TIME_H
#define OGL_TIME_H

struct Time {
    inline static float deltaTime;
    inline static float lastFrame;

    static void Init();
    static void Update();
    static float GetFPS();
};

#endif // OGL_TIME_H
