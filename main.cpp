/**
 * scene graph:
 *      impliment deep copy
 *      impliment destroy
 *      impliment pool defragmentation
 */

#include <iostream>

#include <cstdlib>

#include "engine.h"
#include "samples.h"

int main() {
    auto& eng = Engine::engine();
//    DemoSample();
    sphereSample();

    eng.engine().run();

    return 0;
}
