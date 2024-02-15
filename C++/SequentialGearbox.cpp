#include <string>
#include <iostream>


class State;
class StateContext;
class FirstGear;
class SecondGear;
class ThirdGear;
class FourthGear;
class FithGear;
class SixthGear;
class GearN;
class GearR;


class State
{
    std::string name;
public:
    State(const std::string& name)
        : name(name) {}
    std::string GetName()
    {
        return name;
    }
    virtual void MaxRPM(StateContext*) = 0;
    virtual void MinRPM(StateContext*) = 0;
   
};

class StateContext
{
private:
    State* state;
public:
    StateContext(State* state)
        : state(state) {}

    void MaxRPM()
    {
        std::cout << "Gearing up " << state->GetName() << "..." << std::endl;
        state->MaxRPM(this);
    }

    void MinRPM()
    {
        std::cout << "Gearing down " << state->GetName() << "..." << std::endl;
        state->MinRPM(this);
    }

    void SetState(State* s)
    {
        std::cout << "Changing state from " << state->GetName()
            << " to " << s->GetName() << "..." << std::endl;
        delete state;
        state = s;
    }
    State* GetState()
    {
        return state;
    }

    ~StateContext()
    {
        delete state;
    }
};


class FirstGear : public State
{
public:
    FirstGear() : State("Gear 1") {}
    virtual void MaxRPM(StateContext* state);
    virtual void MinRPM(StateContext* state);
  
};

class SecondGear : public State
{
public:
    SecondGear() : State("Gear 2") {}
    virtual void MaxRPM(StateContext* state);
    virtual void MinRPM(StateContext* state);
  
};

class ThirdGear : public State
{
public:
    ThirdGear() : State("Gear 3") {}
    virtual void MaxRPM(StateContext* state);
    virtual void MinRPM(StateContext* state);
    
};

class FourthGear : public State
{
public:
    FourthGear() : State("Gear 4") {}
    virtual void MaxRPM(StateContext* state);
    virtual void MinRPM(StateContext* state);
    
};

class FithGear : public State
{
public:
    FithGear() : State("Gear 5") {}
    virtual void MaxRPM(StateContext* state);
    virtual void MinRPM(StateContext* state);
  
};

class SixthGear : public State
{
public:
    SixthGear() : State("Gear 6") {}
    virtual void MaxRPM(StateContext* state);
    virtual void MinRPM(StateContext* state);
  
};

class GearN : public State
{
public:
    GearN() : State("Neutral") {}
    virtual void MaxRPM(StateContext* state);
    virtual void MinRPM(StateContext* state);
  
};

class GearR : public State
{
public:
    GearR() : State("Reverse") {}
    virtual void MaxRPM(StateContext* state);
    virtual void MinRPM(StateContext* state);
  
};

void GearN::MaxRPM(StateContext* state)
{
    state->SetState(new FirstGear());
}

void GearN::MinRPM(StateContext* state)
{
    state->SetState(new GearR());
}

void FirstGear::MaxRPM(StateContext* state)
{
    state->SetState(new SecondGear());
}

void FirstGear::MinRPM(StateContext* state)
{
    state->SetState(new GearN());
}

void SecondGear::MaxRPM(StateContext* state)
{
    state->SetState(new ThirdGear());
}

void SecondGear::MinRPM(StateContext* state)
{
    state->SetState(new FirstGear());
}

void ThirdGear::MaxRPM(StateContext* state)
{
    state->SetState(new FourthGear());
}

void ThirdGear::MinRPM(StateContext* state)
{
    state->SetState(new SecondGear());
}

void FourthGear::MaxRPM(StateContext* state)
{
    state->SetState(new FithGear());
}

void FourthGear::MinRPM(StateContext* state)
{
    state->SetState(new ThirdGear());
}

void FithGear::MaxRPM(StateContext* state)
{
    state->SetState(new SixthGear());
}

void FithGear::MinRPM(StateContext* state)
{
    state->SetState(new FourthGear());
}

void SixthGear::MaxRPM(StateContext* state)
{
    std::cout << "Nothing happens" << std::endl;
}

void SixthGear::MinRPM(StateContext* state)
{
    state->SetState(new FithGear());
}

void GearR::MinRPM(StateContext* state)
{
    std::cout << "Nothing happens" << std::endl;
}

void GearR::MaxRPM(StateContext* state)
{
    state->SetState(new GearN());
}

int main()
{
    StateContext* sc = new StateContext(new GearN());

    sc->MaxRPM();
    sc->MaxRPM();
    sc->MaxRPM();
    sc->MaxRPM();
    sc->MaxRPM();
    sc->MaxRPM();
    sc->MaxRPM();
    sc->MinRPM();
    sc->MinRPM();
    sc->MinRPM();
    sc->MinRPM();
    sc->MinRPM();
    sc->MinRPM();
    sc->MinRPM();
    sc->MinRPM();
    sc->MaxRPM();
    delete sc;
    return 0;
}