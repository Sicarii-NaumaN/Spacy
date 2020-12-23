#ifndef SPACY_EVENT_H
#define SPACY_EVENT_H
const static int DEFAULT_BULLET_SPEED_CLIENT = 10;
#include <map>

struct VectorInterface {
    float x, y;
    VectorInterface(float xpos, float ypos): x(xpos), y(ypos) {}
};

struct ModelInterface {
    float width, height;
    ModelInterface(int w, int h): height(h), width(w) {}
};

struct EventInterface {
    enum EventType {
        SHOT,
        KEYPRESSED
    };
    EventType type; //move, blink
    EventInterface(EventType t): type(t) {}
};

struct KeyEvent: EventInterface {
  enum KeyState {
    PRESSED,
    RELEASED
  };

  int keyCode;
  int mouse_x, mouse_y;
  KeyState state;
  KeyEvent(int keyCode, int mx, int my, KeyState state):
    EventInterface(EventType::KEYPRESSED),
    keyCode(keyCode),
    mouse_x(mx),
    mouse_y(my),
    state(state){}
};

struct KeyPressedEvent: KeyEvent {
  KeyPressedEvent(int keyCode, int mx, int my):
    KeyEvent(keyCode, mx, my, KeyEvent::KeyState::PRESSED) {};
};

struct KeyReleasedEvent: KeyEvent {
  KeyReleasedEvent(int keyCode, int mx, int my):
    KeyEvent(keyCode, mx, my, KeyEvent::KeyState::RELEASED) {};
};

struct ShotInterface: EventInterface{
    int origin_x, origin_y;
    int mouse_x, mouse_y;
    ShotInterface(int ox, int oy, int mx, int my):
      EventInterface(EventType::SHOT),
      mouse_x(mx),
      mouse_y(my),
      origin_x(ox),
      origin_y(oy) {}
};

struct ObjectInterface {
    enum Type {
        PLAYER,
        BULLET,
        MAP
    };
    VectorInterface position;
    ModelInterface model;
    Type type;
    int ID;
    ObjectInterface(Type t, int id, VectorInterface pos, ModelInterface mod):type(t), ID(id), position(pos), model(mod) {}
};

struct PlayerInterface:ObjectInterface {
    PlayerInterface(int id, VectorInterface pos, ModelInterface mod): ObjectInterface(Type::PLAYER, id, pos, mod) {}
};

struct BulletStateInterface {
    enum State {
        ACTIVE,
        INACTIVE
    };
    BulletStateInterface(): state_(State::ACTIVE), live_tick(0) {};
    int live_tick;
    State state_;
};

struct BulletInterface:ObjectInterface {

    BulletInterface(int id, VectorInterface pos, int iniciator_id): ObjectInterface(Type::BULLET, id, pos, ModelInterface(15,15)),
                                                                   speed(DEFAULT_BULLET_SPEED_CLIENT), iniciator_ID(iniciator_id) {};
    BulletStateInterface state;
    int iniciator_ID;
    int speed;
};

#endif //SPACY_EVENT_H
