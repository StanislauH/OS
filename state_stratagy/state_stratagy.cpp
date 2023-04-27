#include <iostream>

class Strategy {
public:
    virtual void execute() = 0;
};

class ConcreteStrategyA : public Strategy {
public:
    void execute() override {
        std::cout << "ConcreteStrategyA\n";
    }
};

class ConcreteStrategyB : public Strategy {
public:
    void execute() override {
        std::cout << "ConcreteStrategyB\n";
    }
};

class Context {
private:
    Strategy* strategy;
public:
    void setStrategy(Strategy* s) {
        strategy = s;
    }

    void executeStrategy() {
        strategy->execute();
    }
};

class State {
protected:
    Context* context;
public:
    virtual ~State() = default;
    void setContext(Context* c) {
        context = c;
    }
    virtual void handle() = 0;
};

class ConcreteStateA : public State {
public:
    void handle() override {
        context->setStrategy(new ConcreteStrategyA());
        context->executeStrategy();
    }
};

class ConcreteStateB : public State {
public:
    void handle() override {
        context->setStrategy(new ConcreteStrategyB());
        context->executeStrategy();
    }
};

int main() {
    Context context;
    ConcreteStateA stateA;
    stateA.setContext(&context);
    stateA.handle();

    ConcreteStateB stateB;
    stateB.setContext(&context);
    stateB.handle();
}