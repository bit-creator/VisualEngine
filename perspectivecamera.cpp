#include "perspectivecamera.h"

PerspectiveCamera::PerspectiveCamera(float fovy, float aspect, float near, float far) 
    // : Camera(glm::scale(glm::perspective(fovy, aspect, near, far), glm::vec3(0, 0, -1)),
    : Camera( glm::perspective(fovy, aspect, near, far) *
        glm::mat4(1, 0, 0, 0,
                  0, 1, 0, 0,
                  0, 0, -1,0,
                  0, 0, 0, 1),  
         near, far)
{  }
