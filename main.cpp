#include <iostream>

#include <cstdlib>

#include "engine.h"
#include "samples.h"

int main() {
    auto& eng = Engine::engine();

    DemoSample();
//    WrapSample();

    eng.engine().run();

    return 0;
}
