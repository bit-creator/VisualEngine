#include "window.h"

Window::Window() noexcept
    : _version(3.3f)
    , _width(1366u)
    , _height(720u)
    , _title("default window")
{ setup(); }

Window::Window(const GLfloat& version) noexcept
    : _version(version)
    , _width(1366u)
    , _height(720u)
    , _title("default window")
{ setup(); }

Window::Window(const GLint& width, const GLint& height) noexcept
    : _version(3.3f)
    , _width(width)
    , _height(height)
    , _title("default window")
{ setup(); }

Window::Window(const std::string& title) noexcept
    : _version(3.3f)
    , _width(1366u)
    , _height(720u)
    , _title(title)
{ setup(); }

Window::Window(const GLfloat& version, const std::string& title) noexcept
    : _version(version)
    , _width(1366u)
    , _height(720u)
    , _title(title)
{ setup(); }

Window::Window(const GLfloat& version, const GLint& width, const GLint& height) noexcept
    : _version(version)
    , _width(width)
    , _height(height)
    , _title("default window")
{ setup(); }

Window::Window(const GLint& width, const GLint& height, const std::string& title) noexcept
    : _version(3.3f)
    , _width(width)
    , _height(height)
    , _title(title)
{ setup(); }

Window::Window(const GLfloat& version, const GLint& width, const GLint& height, const std::string& title) noexcept
    : _version(version)
    , _width(width)
    , _height(height)
    , _title(title)
{ setup(); }

Window::~Window() noexcept
{ /*delete _window;*/ }

void Window::setup() noexcept
{
    if (!glfwInit())
    {
        std::cout << "|    EROR     | initialize GLFW\n" << "|             | " << glGetError() << '\n';
        std::raise(SIGTERM);
    }
    std::cout << "| SUCCSESSFUL | initialize GLFW\n";

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, (GLint)(_version));

    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, ((GLint)(_version*10))%10);

    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    _window = std::make_shared<GLFWwindow*>(glfwCreateWindow(_width, _height, _title.c_str(), nullptr, nullptr));

    if(_window == nullptr)
    {
        std::cout << "|    EROR     | Window create\n";
        glfwTerminate();
        std::raise(SIGTERM);
    }

    std::cout << "| SUCCSESSFUL | Window create\n";

    glfwMakeContextCurrent(*_window);

    glewExperimental = GL_TRUE;

    if (auto err =glewInit(); err != GLEW_OK)
    {
        std::cout << "|    EROR     | initialize GLEW\n" << "|             | " << glewGetErrorString(err) << '\n' << "|             | " << glGetError() << '\n';
        glfwTerminate();
        std::raise(SIGTERM);
    }
    std::cout << "| SUCCSESSFUL | Initialize GLEW\n";

    glfwGetFramebufferSize(*_window, &_width, &_height);

    glViewport(0, 0, _width, _height);

    glfwSetKeyCallback(*_window, callBack);
}

Window::pointer Window::get() noexcept
{ return _window; }

Window::const_pointer Window::get() const noexcept
{ return _window; }

Window::operator Window::raw_pointer( ) const
{ return *_window; }

Window::operator Window::raw_pointer( )
{ return *_window; }

void Window::callBack(raw_pointer window, int key, int scancode, int action, int mode)
{
    if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GL_TRUE);
        std::cout << "|    INFO     | escape pressed\n";    
    }
}
