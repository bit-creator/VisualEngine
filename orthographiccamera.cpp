#include "orthographiccamera.h"

OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top, float near, float far) 
    // : Camera(glm::scale(glm::ortho(left, right, bottom, top, near, far), glm::vec3(0, 0, -1)),
    : Camera(glm::ortho(left, right, bottom, top, near, far) *
        glm::mat4(1, 0, 0, 0,
                  0, 1, 0, 0,
                  0, 0, -1,0,
                  0, 0, 0, 1),   
         near, far)
{  }
