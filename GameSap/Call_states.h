#ifndef CALL_STATES_H
#define CALL_STATES_H

class Call_states
{

private:
    //0 - 8 - кол-во мин, 9 - мина, 10 - взорванная мина
    unsigned short int stateDown;
    //0 - ничего, 1 - кнопка нажата, 2 - флаг был установлен, 3 - кнопка была нажата и флаг был установлен
    unsigned short int stateUp;

public:
    Call_states();
    unsigned short int getStateDown();
    unsigned short int getStateUp();

    void setStateDown(unsigned short int);
    void setStateUp(unsigned short int);

    bool isMine();
    bool isFlag();
    bool isClicked();
    void setMine();
};

#endif // CALL_STATES.H
