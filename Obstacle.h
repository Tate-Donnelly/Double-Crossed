#pragma once
#include <Object.h>
class Obstacle :
    public df::Object
{
private:
    df::Vector m_corner;
    float m_horizontal;
    float m_vertical;
    sf::Color m_color;
    bool m_isTransparent;
public:
    Obstacle();
    Obstacle(df::Vector pos, df::Vector corner, float horizontal, float vertical, sf::Color color, bool transparent);

    void setCorner(df::Vector corner);
    df::Vector getCorner();

    void setHorizontal(float new_horizontal);
    float getHorizontal();

    void setVertical(float new_vertical);
    float getVertical();

    void setColor(sf::Color new_color);
    sf::Color getColor();

    void setTransparent(bool isTransparent = false);
    bool getTransparent();

    int draw() override;
};

