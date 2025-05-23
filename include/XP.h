#include <SDL.h>
#include <Animation.h>
#include <Vector.h>

class XP
{
private:
    Vector pos;
    float acc, vel, maxVel;
    float xpAmount;
    bool absorbed;

    Animation xp;

public:
    XP(SDL_Renderer *renderer, Vector pos, float xpAmount);
    Vector getPos();
    float getXP();
    bool isAbsorbed();
    void moveXP(Vector finalPos);
    void drawXP(SDL_Renderer *renderer, Vector offset);
};
