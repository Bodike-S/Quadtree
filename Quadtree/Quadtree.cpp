#include <iostream>
#include<time.h>
#include "Quadtree.h"

int main()
{
    srand(time(NULL));
    float h, w;
    size_t c;
    cout << "Enter window size: \nheight: ";
    cin >> h;
    cout << "\nwidth: ";
    cin >> w;
    cout << "\nEnter count shape: ";
    cin >> c;
    cout << "\nWait ..."<<endl;
    //Quadtree  tree(Rectangle(w/2, h/2, w/2, h/2), c, 0);
    Quadtree *tree;
    RenderWindow window(VideoMode(w, h), "Quad Tree");
    /*Point* po;
    vector<Point*> points;
    vector<Point*> found;*/
    Entity *entity;
    vector<Entity*> entities;
    vector<Entity*> found;

    /*CircleShape shape;
    shape.setRadius(3);
    shape.setOrigin(3, 3);*/

    RectangleShape shape;
    shape.setOutlineColor(Color::Blue);

    int wr = 20, hr = 20;

    //Rectangle area(200, 200, 100, 100);

    while (window.isOpen())
    {
        Event e;
        while (window.pollEvent(e))
        {
            if (e.type == Event::Closed)
                window.close();
            else if (e.type == Event::MouseButtonPressed && e.mouseButton.button == Mouse::Left)
            {
                /*po = new Point(Mouse::getPosition(window).x,
                    Mouse::getPosition(window).y);
                points.push_back(po);
                tree.insert(po);*/
                for (int i = 0; i < c; ++i) {
                    entity = new Entity(Mouse::getPosition(window).x,
                        Mouse::getPosition(window).y,wr, hr);
                    entity->angle = rand() % 360;
                    entities.push_back(entity);
                }
            }
           /* else if (e.type == Event::MouseMoved)
            {
                if (Mouse::isButtonPressed(Mouse::Right))
                {
                    area.x = Mouse::getPosition(window).x;
                    area.y = Mouse::getPosition(window).y;
                }
            }*/
            else if (e.type == Event::MouseMoved)
            {
                if (Mouse::isButtonPressed(Mouse::Right))
                {
                    wr = Mouse::getPosition(window).x;
                    hr = Mouse::getPosition(window).y;
                }
            }
        }

        tree = new Quadtree(Rectangle(w / 2, h / 2, w / 2, h / 2), c, 0);

        for (vector<Entity*>::iterator it = entities.begin(); it != entities.end(); ++it) {
            (*it)->Move();
            (*it)->collides = false;
            tree->insert(*it);
        }

        tree->checkCollision();

        /*for (size_t i = 0; i < points.size(); ++i) {
            points[i]->highlighted = false;
        }
        found = vector<Point*>();
        tree.query(area, found);
        for (size_t i = 0; i < found.size(); ++i)
            found[i]->highlighted = true;*/
        window.clear();

        shape.setOutlineThickness(-1);
        for (Entity *e : entities)
        {
            shape.setPosition(e->x, e->y);
            shape.setSize(Vector2f(e->w * 2, e->h * 2));
            shape.setOrigin(e->w, e->h);
            shape.setFillColor(e->collides ? Color::Red : Color::Green);
            window.draw(shape);
        }

        tree->draw(window);

        shape.setOutlineThickness(0);
        shape.setPosition(Mouse::getPosition(window).x,
            Mouse::getPosition(window).y);
        shape.setSize(Vector2f(wr * 2, hr * 2));
        shape.setOrigin(wr, hr);
        shape.setFillColor(Color(255, 255, 0, 50));
        window.draw(shape);

        /*for (Point* p : points)
        {
            shape.setPosition(p->x, p->y);
            shape.setFillColor(p->highlighted ? Color::Green : Color::White);
            window.draw(shape);
        }
        tree.draw(window);
        area.draw(window);*/

        window.display();
    }
    cout << "Bye" << endl;
    /*for (int i = 0; i < points.size(); ++i) {
        delete points[i];
    }*/
    for (int i = 0; i < entities.size(); ++i) {
        delete entities[i];
    }
    return 0;
}
